#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT "input"

#define PATTERN_LENGTH 31
#define VELOC_X 3

int main() {
  FILE *fstream;
  char buff[PATTERN_LENGTH];
  char *debugbuff;
  int puz1_count, puz2_count;
  int xpos;

  fstream = fopen(INPUT, "r");

  puz1_count = 0;
  puz2_count = 0;

  /* Down 1 every time so we can actually just read it line-by-line */
  while(fgets(buff, PATTERN_LENGTH + 1, fstream) != NULL) {

    /* Strip off newline */
    buff[strcspn(buff,"\n")] = 0;

    /* We hit a tree!*/
    if(buff[xpos % PATTERN_LENGTH] == '#')
      puz1_count++; 

    xpos += VELOC_X;
  }
  fclose(fstream);
  printf("%d\n", puz1_count);
  printf("%d\n", puz2_count);
  exit(EXIT_SUCCESS);
}
