#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT "input"

#define BUFF_SIZE 50

typedef struct {
  int low_bound;
  int high_bound; 
  char character;
  char string[BUFF_SIZE];
} Rule;

int main() {
  FILE *fstream;
  char *point_buff;
  char buff[BUFF_SIZE];
  Rule rule;
  int count, puz1_count, puz2_count;

  fstream = fopen(INPUT, "r");

  point_buff = NULL;
  puz1_count = 0;
  puz2_count = 0;

  while(fgets(buff, BUFF_SIZE + 1, fstream) != NULL) {
    sscanf(buff, "%d-%d %c: %[^\n]", &rule.low_bound, &rule.high_bound,
                                  &rule.character, rule.string);
    
    /* Puzzle 1 */
    count = 0;
    point_buff = rule.string;
    while(point_buff = strchr(point_buff, rule.character)) {
      point_buff++;
      count++;
    }
    if(count >= rule.low_bound && count <= rule.high_bound) {
      puz1_count++;
    }
    
    if(rule.string[rule.low_bound - 1] == rule.character ^
        rule.string[rule.high_bound - 1] == rule.character)
     puz2_count++;
  }
  fclose(fstream);
  printf("%d\n", puz1_count);
  printf("%d\n", puz2_count);
  exit(EXIT_SUCCESS);
}
