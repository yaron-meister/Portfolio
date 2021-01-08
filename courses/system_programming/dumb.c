#include <stdio.h>
#include <unistd.h>

int main(void)
{
  int i = 7;
  int *p = &i;

  FILE *fp;

  if(0 == (fp = fopen("stoopid", "w")))
  {
      fprintf(stderr,"well, that didn\'t work!\n");
      return -1;
  }
  
  fprintf(fp, "%p\n", (void*)p);

  if(fclose(fp))
  {
      fprintf(stderr,"oh well.\n");
      return -1;
  }
  
  printf("The stoopid file is written by dumb!\n");
  sleep(300); /* Be alive while dumber is reading.*/
  
  return 0;
}

