/*****************************************************************************
 * File name:   main.c
 * Developer:   Yaron Meister 
 * Date:        2018-12-10 17:37:14
 * Description: linking exercise's main
 *****************************************************************************/
 
#include <stdio.h>     /* printf()     */
#include <stdlib.h>    /* EXIT_SUCCESS */
#include <dlfcn.h>

#include "header.h"
 
/* Forward Declarations    */
void MyFunc(void);
  
/* Global variables        */

/*******************************************************************************
                                MAIN FUNCTION
*******************************************************************************/
int main(void)
{
    void *handle;
    void (*func_name)(void);
    
    handle = dlopen("libso2.so", RTLD_LAZY);
    *(void**)(&func_name) = dlsym(handle, "Bar2");
    MyFunc();
    Foo();
    Bar1();
    func_name();
    
    dlclose(handle);
    
    return (EXIT_SUCCESS);
} 
 
/*************************FUNCTION'S DEFINITIONS*******************************/
void MyFunc(void)
{
    printf("My name is MyFunc\n");
}  


/****************************END OF FILE***************************************/













