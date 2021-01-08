#include <stdio.h>
#include <unistd.h>

int main(void)
{
  int i = 800;
  int *p = 0;

  FILE *fp;

  if(0 == (fp = fopen("stoopid", "r")))
  {
  	fprintf(stderr,"well, that didn\'t work!\n");
      return -1;
  }
  
  fscanf(fp, "%p\n", (void**)&p);

  if(fclose(fp))
  {
      fprintf(stderr,"oh well.\n");
      return -1;
  }
  
  printf("The stoopid file read by dumber!\n");
  printf("p points to: %d\n", *p);

  return 0;
}
