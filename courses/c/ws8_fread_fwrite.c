/*****************************************************************************
 * File name:   ws8_fread_fwrite.c
 * Developer:   Yaron
 * Reviewer:    Majd
 * Date:        2018-10-29 12:07:12
 * Description: 
 *****************************************************************************/
 
#include <stdio.h>     /* printf()     */
#include <stddef.h>    /* stddef       */


/* Macros                  */
 
 
/* Forward Declarations    */
 
 
/* Global variables        */


typedef struct DateOfBirth
    {
        size_t day;
        size_t month;
        size_t year;
    } date_of_birth_t;
    
typedef struct Contact
    {
        char f_name[50];
        char l_name[50];
        date_of_birth_t dob;
        size_t ID;
    } contact_t;

/*****************************************************************************
                               MAIN FUNCTION
 *****************************************************************************/
int main(void)
{
    int i = 0;
    int status = 0;
    contact_t list[20] = {0};
    contact_t contact[10] = {{"May", "Meister", {28,4,92}, 123456789},
                             {"Yaron", "Meister", {15,1,90}, 123456789},
                             {"Isaac", "Meister", {12,2,46}, 123456789},
                             {"Lior", "Meister", {7,10,75}, 123456789},
                             {"Alina", "Tzoref", {30,9,76}, 123456789},
                             {"Yuval", "Helman", {22,4,90}, 123456789},
                             {"Yuval", "Sani", {31,1,90}, 123456789},
                             {"Guy", "Graziani", {23,8,90}, 123456789},
                             {"Erez", "Pud", {13,1,90}, 123456789},
                             {"Idan", "Shani", {19,2,90}, 123456789}
                            };
                            
   FILE *fp = NULL;
   fp = fopen("file.txt","w");
   if (NULL == fp)
        {
            printf("Openinig file faild!!!\n");
            return (1);
        }
        
   fwrite(contact, sizeof(contact[0]), 10, fp);
   status = fclose(fp);
   if (0 != status)
        {
            printf("Closing file faild!!!\n");
            return (1);
        }
   
   fp = fopen("file.txt","r");
   
   if (NULL == fp)
        {
            printf("Openinig file faild!!!\n");
            return (1);
        }
        
   fread(list, sizeof(contact[0]), 10, fp);
   
   for (i = 0; i < 10; ++i)
   {
       printf("%s %s\t %lu/%lu/%lu\t %lu\n", list[i].f_name, list[i].l_name,
                                 list[i].dob.day, list[i].dob.month,
                                 list[i].dob.year, list[i].ID);
   }
   
   status = fclose(fp);
   
   if (0 != status)
        {
            printf("Closing file faild!!!\n");
            return (1);
        }
 
    return (0);
} 
 
  
