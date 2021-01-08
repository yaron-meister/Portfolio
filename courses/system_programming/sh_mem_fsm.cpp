/*****************************************************************************
 * File name:   sh_mem_fsm.cpp
 * Developer:   Yaron Meister
 * Reviewer: 	Yael
 * Date:        2019-03-24 15:43:56
 * Description: Smart FSM implementation
 *****************************************************************************/
 
#include <iostream>     	/* 		cout, cerr		*/
#include <sys/mman.h>		/*		shm_open		*/
#include <sys/stat.h>   	/*  For mode constants  */
#include <fcntl.h>      	/*  For O_* constants   */
#include <unistd.h>			/*	 close, ftruncate	*/
#include <cassert>			/*		  assert		*/

#include "sh_mem_fsm.h" 	/* Forward declarations */
#include "../cpp/lock.h"	/* 		  Lock 			*/ 

using namespace ilrd;
/********************************* Structs *************************************/ 
struct Block
{
    size_t next_free;
};
 
/************************** Forward Declarations ******************************/
// A function that returns the next Aligned Size of <block_size>
static size_t GetAlignedSize(size_t block_sz);

/***************************** Global variables *******************************/
const size_t WORD_SIZE = sizeof(size_t);

/*******************************************************************************
                           Functions Implementations
*******************************************************************************/  
/******************************************************************************/ 
std::shared_ptr<FSM> FSM::Create(const std::string& name,
                                             size_t blocks_num, size_t block_sz)
{
	int shm_fd = -1;
	shm_fd = shm_open(name.c_str(), O_CREAT | O_RDWR, 0666);
	if (shm_fd < 0)
	{
		perror("shm_open");
		return (nullptr);
	}

	block_sz = GetAlignedSize(block_sz) + sizeof(Block);
	
	if (0 != ftruncate(shm_fd, sizeof(shared_mem) + blocks_num * block_sz))
	{
		perror("ftruncate");
		return (nullptr);
	}

	// Mapping
	shared_mem* shared_ptr = (shared_mem*)mmap
	(0, sizeof(FSM) + blocks_num * block_sz, PROT_WRITE, MAP_SHARED, shm_fd, 0);
	if (MAP_FAILED == shared_ptr)
	{
		perror("mmap");
		return (nullptr);
	}

	// FSM Ctor
	std::shared_ptr<FSM> fsm(new FSM(name, shm_fd, blocks_num, block_sz,
																   shared_ptr));
	// Initiate the mutex inside <m_sh_mem
	pthread_mutex_init(&fsm->m_sh_mem->mutex, NULL);

	// An atomic operation (See shared_mem struct)
    fsm->m_sh_mem->ref_count  = 1;
    
    // My Scope-Lock implementation
    {
	    Lock<pthread_mutex_t> lock(&fsm->m_sh_mem->mutex);

		fsm->m_sh_mem->first_free = offsetof(shared_mem, data);
		fsm->InitBlocks(fsm->m_sh_mem, block_sz, blocks_num);
    }

	return (fsm);
}

/******************************************************************************/
FSM::FSM(const std::string& name, int fd, size_t blocks_num, size_t block_sz,
        											struct shared_mem* sh_mem) : 
		m_name(name), m_fd(fd), m_blocks_num(blocks_num),
										  m_block_sz(block_sz), m_sh_mem(sh_mem) 
{}

/******************************************************************************/
// A function that returns the next Aligned Size of <block_size>
size_t GetAlignedSize(size_t block_sz)
{
	if (0 != (block_sz % WORD_SIZE))
	{
		block_sz += (WORD_SIZE - (block_sz % WORD_SIZE));
	}

	return (block_sz);
}

/******************************************************************************/
// A function that updates the <next_free> field of every block in the SH_MEM
void FSM::InitBlocks(void* segment, size_t block_sz, size_t blocks_num)
{
	// Segment is the address of the first byte in the SH_MEM
	Block* iterator = (Block*)((char*)segment + m_sh_mem->first_free);

	// While <iterator> is lower than the address of the last block
	while (iterator < (Block*)((char*)segment + m_sh_mem->first_free +
												   block_sz * (blocks_num - 1)))
	{
		iterator->next_free = (size_t)((char*)iterator - (char*)segment
																    + block_sz);
		iterator = (Block*)((char*)iterator + block_sz);
	}	

	// Updating the <next_free> of the last block
	// 0 - Limit value
	iterator->next_free = 0;
}

/******************************************************************************/
std::shared_ptr<FSM> FSM::Attach(const std::string& name,
                                             size_t blocks_num, size_t block_sz)
{
	int shm_fd = -1;
	shm_fd = shm_open(name.c_str(), O_RDWR, 0666);
	if (ENOENT == shm_fd)
	{
		perror("shm_open");
		return (nullptr);
	}

	block_sz = GetAlignedSize(block_sz) + sizeof(Block);

	// Mapping
	shared_mem* shared_ptr = (shared_mem*)mmap
	(0, sizeof(FSM) + blocks_num * block_sz, PROT_WRITE, MAP_SHARED, shm_fd, 0);
	if (MAP_FAILED == shared_ptr)
	{
		perror("mmap");
		return (nullptr);
	}

	// FSM Ctor
	std::shared_ptr<FSM> fsm(new FSM(name, shm_fd, blocks_num, block_sz,
																   shared_ptr));
	++fsm->m_sh_mem->ref_count;

	return (fsm);		
}

/******************************************************************************/
FSM::~FSM()
{
	--(m_sh_mem->ref_count);

	// If I'm the last one that used the SH_MEM
	if (0 == m_sh_mem->ref_count)
	{
		pthread_mutex_destroy(&m_sh_mem->mutex);

		if (0 != shm_unlink(m_name.c_str()))
		{
			fprintf(stderr, "shm_unlink FAILED\n");
		}
	}

	if (0 != munmap(m_sh_mem, sizeof(FSM) + m_blocks_num * m_block_sz))
	{
		perror("munmap");
	}

	close(m_fd);
}

/******************************************************************************/
void* FSM::Alloc()
{
	void* ret = nullptr;

    Lock<pthread_mutex_t> lock(&m_sh_mem->mutex);
    
    // If there is an available block
	if (0 != m_sh_mem->first_free)
	{
		ret = (char*)m_sh_mem + m_sh_mem->first_free + sizeof(Block);
		// Swapping between <first_free> field to <next_free> 
		// field of the allocated block
    	Swap((&m_sh_mem->first_free), (size_t*)((char*)ret - sizeof(Block)));
    }

    return (ret);
}

/******************************************************************************/
void FSM::Swap(size_t* x, size_t* y)
{
	assert(x);
    assert(y);
    
    size_t temp = *x;
    *x = *y;
    *y = temp;
}

/******************************************************************************/
void FSM::Free(void* blk)
{
	if (nullptr != blk)
	{
    	Lock<pthread_mutex_t> lock(&m_sh_mem->mutex);
		// Swapping between <first_free> field to <next_free> 
		// field of the freed block
		Swap(&m_sh_mem->first_free, (size_t*)((char*)blk - sizeof(Block)));
	}
}



/*******************************************************************************
******************************** END OF FILE ***********************************
*******************************************************************************/   
