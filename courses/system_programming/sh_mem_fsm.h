/*****************************************************************************
 * File name:   sh_mem_fsm.h
 * Developer:   HRD7
 * Version:     0
 * Date:        2019-03-24 15:43:56
 * Description: Smart FSM header
 *****************************************************************************/

#ifndef __SH_MEM_FSM_H__
#define __SH_MEM_FSM_H__

#include <cstddef>     // size_t
#include <string>      // string
#include <memory>      // shared_ptr
#include <atomic>      // std::atomic     

namespace ilrd
{
    class FSM
    {
    public:
        // Creates shared memory for allocation per blocks.
        static std::shared_ptr<FSM> Create(const std::string& name,
                                            size_t blocks_num, size_t block_sz);
        
        // Attaches FSM to a shared memory that already exist.
        static std::shared_ptr<FSM> Attach(const std::string& name,
                                            size_t blocks_num, size_t block_sz);
        // Dtor
        ~FSM();
        
        // Allocates a block.
        void* Alloc();

        // Frees a block.
        void Free(void* blk);
    
        FSM(const FSM& other) = delete;             // Uncopyable
        FSM& operator=(const FSM& other) = delete;  // Uncopyable
    
    private:
        const std::string m_name; // name of shared mem. segment
        int m_fd;                 // file descriptor
        size_t m_blocks_num;
        size_t m_block_sz;
        struct shared_mem* m_sh_mem;
        
        // Ctor
        FSM(const std::string& name, int fd, size_t blocks_num, size_t block_sz,
                                                     struct shared_mem* sh_mem);
        void InitBlocks(void* segment, size_t block_sz, size_t blocks_num);
    	void Swap(size_t *x, size_t *y);
    };

    struct shared_mem
    {
        std::atomic<size_t> ref_count;
        pthread_mutex_t mutex;
        size_t first_free;
        char data[1]; 
    };
} // ILRD

 
#endif     /* __SH_MEM_FSM_H__ */


/*******************************************************************************
******************************** END OF FILE ***********************************
*******************************************************************************/
