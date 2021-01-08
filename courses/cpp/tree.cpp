/*****************************************************************************
 * File name:   tree.cpp
 * Developer:   Yaron Meister
 * Reviewer: 	Daniel
 * Date:        2019-03-17 15:58:39
 * Description: Tree display implementation
 *****************************************************************************/
 
#include <iostream>     /* 		cout, cerr		*/
#include <dirent.h>		/* opendir, readir, DIR */
#include <sys/types.h>	/*		 Opendir 		*/
#include <cstring>		/*		  strcmp		*/

#include "utils.h"		/*		UNUSED_VAR		*/
#include "tree.h"       /* Forward declarations */


using namespace ilrd;
/*******************************************************************************
                           Functions Implementations
*******************************************************************************/  
/* Entry-class functions */
/******************************************************************************/ 
Entry::Entry(const std::string& name) : m_name(name)
{}

/********************									   ********************/
Entry::~Entry(){}

/********************									   ********************/ 
const std::string& Entry::GetName() const
{
	return (m_name);
}


/* File-class functions */
/******************************************************************************/ 
File::File(const std::string& name) : Entry(name)
{}

/********************									   ********************/
File::~File(){}

/********************									   ********************/
void File::Display(unsigned depth) const
{
    for (size_t i = 0; i < depth; ++i)
    {
        std::cout << "│  ";
    }

    std::cout << "├╴ " << GetName() << std::endl;
}

/********************									   ********************/
const std::shared_ptr<Entry> File::Find(const std::string& name) const
{
	UNUSED_VAR(name);

	return (nullptr);
}


/* Directory-class functions */
/******************************************************************************/
const std::shared_ptr<Entry> Directory::Create(const std::string& name)
{
	// Cutting 'name' from 'path'
	size_t n = name.find_last_of('/');
	if (std::string::npos == n)
   	{
   		n = 0;	
   	}
   	else
   	{
   		++n;
   	}

   	// Initiate a Directory with the sliced 'name'
	std::shared_ptr<Directory> new_dir_ptr (new Directory(name.substr(n)));

	// Opening current dir
	DIR* current_dir = opendir(name.c_str());
	if (nullptr != current_dir)
	{
		// Initializing of iterator
		struct dirent* dirent = readdir(current_dir);

		while (NULL != dirent)
		{
			// Skip over '.' and '..' directories
			if (0 != strcmp(dirent->d_name, ".") &&
		        0 != strcmp(dirent->d_name, ".."))
			{
				if (DT_DIR == dirent->d_type)
				{
					// Push a new Directory
					new_dir_ptr->m_dir_data.push_back
										  (Create(name + "/" + dirent->d_name));	
				}
				else
				{
					// Push a new File
					std::shared_ptr<File> file (new File(dirent->d_name));
					new_dir_ptr->m_dir_data.push_back(file);
				}
			}

			// Promoting the iteraor
			dirent = readdir(current_dir);
		}

		closedir(current_dir);
	}
	else
	{
		std::cout << name << ": No such directory" << std::endl;
		new_dir_ptr = nullptr;
	}

	return (new_dir_ptr);
}


/********************									   ********************/
Directory::~Directory()
{}

/********************									   ********************/
Directory::Directory(const std::string& name) : Entry(name)
{}

/********************									   ********************/
void Directory::Display(unsigned depth) const
{
	size_t i = 0;
	
	// Printing myself
    for (; i < depth; ++i)
    {
        std::cout << "│  ";
    }
  
    std::cout << "├╴ " << GetName() << std::endl;

    // Printing my files and sub-directories
    for (i = 0; i < m_dir_data.size(); ++i)
    {
        (m_dir_data[i])->Display(depth + 1);
    } 
}

/********************									   ********************/
const std::shared_ptr<Entry> Directory::Find(const std::string& name) const
{
	size_t i = 0;
	std::shared_ptr<Entry> temp = nullptr;

	// Searching inside myself
   	for (; i < m_dir_data.size() && nullptr == temp; ++i)
    {
	   	if (name == (m_dir_data[i])->GetName())
	   	{
	   		temp = m_dir_data[i];
	   	}
    } 

    // Searching inside my files and sub-directories
	for (i = 0; i < m_dir_data.size() && nullptr == temp; ++i)
	{
		temp = (m_dir_data[i])->Find(name);
	}    

	return (temp);
}

/*******************************************************************************
******************************** END OF FILE ***********************************
*******************************************************************************/   
