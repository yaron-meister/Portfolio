

#include <iostream>     // cout
#include <cstdlib>      // EXIT_SUCCESS
#include <cstddef>      // size_t 
#include <vector>       // vector 
#include <unistd.h>     /* read             */

#include "utils.h"

/***********************************************************************/
int WriteAll(int fd, char* buf, size_t count)
{
  ssize_t bytes_written;

  while (count > 0) 
  {
    bytes_written = write(fd, buf, count);
// std::cout<<"bytes_written: "<<bytes_written<<std::endl;
    if (0 > bytes_written)
    {
        perror("write");
        // throw std::runtime_error("write func failed");
        return (EXIT_FAILURE);
    }
    
    buf += bytes_written;
    count -= bytes_written;
  }

  return (EXIT_SUCCESS);
}

/***********************************************************************/
int ReadAll(int fd, char* buf, size_t count)
{
  int bytes_read;

  while (count > 0) 
  {
    bytes_read = read(fd, buf, count);
    if (0 > bytes_read) 
    {
        return (EXIT_FAILURE);    /* code */
    }

    buf += bytes_read;
    count -= bytes_read;
  }

  return (EXIT_SUCCESS);
}

/***********************************************************************/
int ReadAll(int fd, std::vector<char>& vec, size_t count)
{
    char* buffer = new char[count];
    char* runner = buffer;
    char* end    = buffer + count;

    ReadAll(fd, buffer, count);

    for (; runner < end; ++runner)
    {
        vec.push_back(*(runner));
    }

    delete[] buffer;

    return (EXIT_SUCCESS);
}
