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
  int count, valid_count;

  fstream = fopen(INPUT, "r");

  point_buff = NULL;
  valid_count = 0;

  while(fgets(buff, BUFF_SIZE + 1, fstream) != NULL) {
    sscanf(buff, "%d-%d %c: %[^\n]", &rule.low_bound, &rule.high_bound,
                                  &rule.character, rule.string);
    
    count = 0;
    point_buff = rule.string;
    while(point_buff = strchr(point_buff, rule.character)) {
      point_buff++;
      count++;
    }
    if(count >= rule.low_bound && count <= rule.high_bound) {
      valid_count++;
    }
  }
  fclose(fstream);

  printf("%d\n", valid_count);
  exit(EXIT_SUCCESS);
}
