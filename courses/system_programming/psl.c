#include <stdio.h>
#include <stdlib.h>

static void StaticFunc(void);
void GlobalFunc(void);
static int x = 5;

extern int g_var1 = 10;
extern int g_var2 = 0;
extern int g_var3 = 10;
extern int g_var4 = 0;

int main(void)
{
    
    printf("g_var1's address is: %p\n\n", &g_var1);
    printf("g_var2's address is: %p\n\n", &g_var2);
    printf("g_var2's value is: %d\n\n", g_var2);
    printf("g_var3's address is: %p\n\n", &g_var3);
    printf("g_var4's address is: %p\n\n", &g_var4);
    int main_local_var = 64;
    printf("main_local_var's address is: %p\n\n", &main_local_var);
    static int stat_bss_var;
    printf("stat_bss_var's address is: %p\n\n", &stat_bss_var);
    StaticFunc();
    GlobalFunc();
    int *pointer1 = (int*)malloc(1);
    int *pointer2 = (int*)malloc(15);
    int *pointer3 = (int*)malloc(33);
    int *pointer4 = (int*)malloc(22);
    
    printf("malloc No.1 with capacity of 1 BYTE is in address: %p\n\n", pointer1);
    printf("malloc No.2 with capacity of 1 BYTE is in address: %p\n\n", pointer2);
    printf("malloc No.3 with capacity of 33 BYTES is in address: %p\n\n", pointer3);
    printf("malloc No.4 with capacity of 22 BYTES is in address: %p\n\n", pointer4);
    
    printf("StaticFunc's address is: %p\n\n", &StaticFunc);
    printf("GlobalFunc's address is: %p\n\n", &GlobalFunc);
    

    free(pointer1);
    free(pointer2);
    free(pointer3);
    free(pointer4);
    pointer1 = NULL;
    pointer2 = NULL;
    pointer3 = NULL;
    pointer4 = NULL;
}
    

static void StaticFunc(void)
{
    int func_local_var = 105;
    printf("func_local_var's address is: %p\n\n", &func_local_var);
    static int static_local_var = 205;
    printf("static_func_local_var's address is: %p\n\n", &static_local_var);
    static char char_func_local_var = 'c';
    printf("static_char_func_local_var's address is: %p\n\n", &char_func_local_var);
}



void GlobalFunc(void)
{
    printf("Hello, I am a global function...\n");
}



/* 
g_var1's address is: 0x60105c

g_var2's address is: 0x601070

g_var3's address is: 0x601060

g_var4's address is: 0x601074

main_local_var's address is: 0x7ffdf903ef84

stat_bss_var's address is: 0x601078

func_local_var's address is: 0x7ffdf903ef64

static_func_local_var's address is: 0x601064

static_char_func_local_var's address is: 0x601068

Hello, I am a global function...
malloc No.1 with capacity of 1 BYTE is in address: 0x14bd420

malloc No.2 with capacity of 1 BYTE is in address: 0x14bd440

malloc No.3 with capacity of 33 BYTES is in address: 0x14bd460

malloc No.4 with capacity of 22 BYTES is in address: 0x14bd490

StaticFunc's address is: 0x40082b

GlobalFunc's address is: 0x40089e
*/




