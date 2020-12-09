#include <stdio.h>
#include <stdlib.h>

#define INPUT "input"

#define NUM_NUMS 199
#define BUFF_SIZE 10

int main() {
  FILE *fstream;
  char *line;
  int input[NUM_NUMS];
  char buff[BUFF_SIZE];
  int i, j, k;

  fstream = fopen(INPUT, "r");

  line = NULL;
  i = 0;

  while(fgets(buff, BUFF_SIZE + 1, fstream) != NULL) {
    sscanf(buff, "%d", &(input[i]));
    i++;
  }
  fclose(fstream);
 
  /* Wow this is jank */ 
  for(i = 0; i < NUM_NUMS; i++) {
    for(j = 0; j < NUM_NUMS; j++) {
      if(input[i] + input[j] == 2020) {
        /* Answer to puzzle 1! */
        printf("%d * %d = %d\n", input[i], input[j], input[i] * input[j]);
      }
    }
  }

  /* Even more jank... */
  for(i = 0; i < NUM_NUMS; i++) {
    for(j = 0; j < NUM_NUMS; j++) {
      for(k = 0; k < NUM_NUMS; k++) {
        if(input[i] + input[j] + input[k] == 2020) {
          /* Answer to puzzle 2! */
          printf("%d * %d * %d = %d\n", input[i], input[j], input[k], 
                            input[k] * input[i] * input[j]);
          exit(EXIT_SUCCESS);
        }
      }
    }
  }

  exit(EXIT_FAILURE);
}
