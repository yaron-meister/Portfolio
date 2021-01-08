/*****************************************************************************
 * File name:   ws5.c
 * Developer:   Yaron
 * Reviewer:    Aviv
 * Date:        2018-10-22 16:11:12
 * Description: 
 *****************************************************************************/
 
#include <stdio.h>     /* printf, fgetc, fgets */
#include <string.h>    /* strcasecmp           */

#define UNUSED_VAR(x) (void)(x)

/* Macros                  */
typedef enum status
{
    SUCCESS,
    FAILURE,
    EXIT
} sta_t;
 
 
/* Forward Declarations    */
int IsCmpStr(char *system_str, char *usr_str); 
int DoNothing(char *system_str, char *usr_str);
int AppendStr(char file_name[], char *usr_str);
int HandleRemove(char file_name[], char *usr_str);
int HandleCount(char file_name[], char *usr_str);
int HandleExit(char file_name[], char *usr_str);

/* Global variables        */  
struct lut
{
    char name[30];
    int (*cmp_funcs)(char command[], char usr_str[]);
    int (*action_funcs)(char arr[], char usr_str[]);
};

/*******************************************************************************
                                Main Function
*******************************************************************************/
int main(int argc, char *argv[])
{
    int i = 0;
    char string[50] = "";
    sta_t status = SUCCESS;         /* Enum variable */
    
    struct lut command[] = { {"", DoNothing, AppendStr},                                    /* פקודה זו חייבת להיות בסוף */
                             {"-remove\n", IsCmpStr, HandleRemove},
                             {"-count\n", IsCmpStr, HandleCount},                           /* בקסלש אן בעייתי ליוזר אינטרפייס */
                             {"-exit\n", IsCmpStr, HandleExit}
                           };
                           
    if (argc < 2)
    {
        printf("No file was entered!!!\n");
        return(FAILURE);
    }
                                                     
    /* Printing a menu bar */                         
    printf("Hello user, please type your request and press enter after:\n"
            "-For appending text to the end of the file, type your text\n"
            "-For appending text to the beginning, type '<' and your text\n"
            "-For removing file, type '-remove'\n"
            "-For counting rows in a file, type '-count'\n"
            "-For exiting the program, type '-exit'\n"); 
                                 
    while (EXIT != status)
    {
        fgets(string, 100, stdin);
        for (i = 0; i < 4; ++i)
        {
            if (SUCCESS == command[i].cmp_funcs(command[i].name, string))
            {
                status = command[i].action_funcs(argv[1], string);
                break;
            }
        } 
    }  
    UNUSED_VAR(argc);    
    return (SUCCESS);
}


/*****************************************************************/
int IsCmpStr(char *system_str, char *usr_str)
{
    if (0 == strcasecmp(system_str, usr_str))
    {
        return (SUCCESS); 
    }
    
    return (FAILURE);
}

/*****************************************************************/
int HandleRemove(char file_name[], char *usr_str)
{
    UNUSED_VAR(usr_str);
    if (0 == remove(file_name)) /*Remove returns 0 for success, !0 for failure*/
    { 
       printf("Deleted successfully\n");
       return(SUCCESS);
    } 
    else
    {
       printf("Unable to delete the file\n");
       return (FAILURE);
    } 
}

/*****************************************************************/
int HandleCount(char file_name[], char *usr_str)
{
    /* count the number of lines in the file called filename */                                    
    FILE *fp = fopen(file_name,"a+");
    int ch = 0;
    int lines = 0;                        /* Lines counter */
    UNUSED_VAR(usr_str);

    if (NULL == fp)
    {
        return (FAILURE);
    }

    while ((ch = fgetc(fp)) != EOF)      /* EOF = End Of File */          
    {
        if (ch == '\n')
        {
            ++lines;
        }
    }
        
    fclose(fp);
    printf("The file contains %d lines\n", lines);
      
    return (SUCCESS);
}



/*****************************************************************/
int HandleExit(char file_name[], char *usr_str)
{
    UNUSED_VAR(file_name);
    UNUSED_VAR(usr_str);
    printf("exiting the program\n");
    return (EXIT);
}

/*****************************************************************/
int DoNothing(char *system_str, char *usr_str)
{
    /* This function is produced because struct has a pattern.
     * The action functions that use it don't require a strings
     * compare function 
     */
    UNUSED_VAR(system_str);
    if (45 != *usr_str)         /* All commands that are not including '-' */
    {
        return (SUCCESS);
    }
    
    return (FAILURE);
}

/*****************************************************************/
int AppendStr(char file_name[], char *usr_str)
{
    char ch = 0;
    char new_file[] = "new_file";
    FILE *fp_old = NULL;                /* The accepted file */ 
    FILE *fp_temp = NULL;               /* A new and temporary file */
    
    if ('<' == *usr_str)                /* For append at the beginning */
    {
        ++usr_str;
        fp_old = fopen(file_name, "r"); 
        if (NULL == fp_old)
        {
            return (FAILURE);
        }
        fp_temp = fopen(new_file, "a");
        if (NULL == fp_temp)
        {
            return (FAILURE);
        }
        fprintf(fp_temp, "%s", usr_str);
        ch = fgetc(fp_old);
        while (ch != EOF) 
        { 
            fputc(ch, fp_temp); 
            ch = fgetc(fp_old); 
        } 
        
        fclose(fp_old);
        fclose(fp_temp);
        remove(file_name);
        rename(new_file, file_name);   
    }
    
    else                                /* For appending at the end */
    {  
        fp_old = fopen(file_name, "a"); 
        if (NULL == fp_old)
        {
            return (FAILURE);
        }  
        fprintf(fp_old, "%s", usr_str);  
        fclose(fp_old);
    }
    
        return (SUCCESS);
}
    



