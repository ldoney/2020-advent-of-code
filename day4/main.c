#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define INPUT "input"

#define BUFF_SIZE 150

typedef union {
  uint8_t byte;
  struct {
    unsigned int byr:1;
    unsigned int iyr:1;
    unsigned int eyr:1;
    unsigned int hgt:1;
    unsigned int hcl:1;
    unsigned int ecl:1;
    unsigned int pid:1;
    unsigned int cid:1;
  } parts;
} Passport;

void print_passport(Passport p) {
  printf("%d", p.parts.byr);
  printf("%d", p.parts.iyr);
  printf("%d", p.parts.eyr);
  printf("%d", p.parts.hgt);
  printf("%d", p.parts.hcl);
  printf("%d", p.parts.ecl);
  printf("%d", p.parts.pid);
  printf("%d", p.parts.cid);
}

int validate_passport(Passport p) {
  /* cid is optional */
  p.parts.cid = 1;
  return p.byte == 255;
}

int main() {
  FILE *fstream;
  char buff[BUFF_SIZE];
  char temp_buff[BUFF_SIZE];
  int puz1_count, puz2_count;
  Passport p;

  fstream = fopen(INPUT, "r");

  puz1_count = 0;
  puz2_count = 0;

  p.byte = 0;

  while(fgets(buff, BUFF_SIZE + 1, fstream) != NULL) {
    /* Reset byte */
    if(buff[0] == '\n') {
      print_passport(p);
      
      if(validate_passport(p)) {
        printf(" valid!");
        puz1_count++;
      }
      printf("\n\n");

      /* Newline! */
      p.byte = 0;
    } else {
      if (strstr(buff, "byr:") != NULL) 
        p.parts.byr = 1;
      if (strstr(buff, "iyr:") != NULL)
        p.parts.iyr = 1;
      if (strstr(buff, "eyr:") != NULL)
        p.parts.eyr = 1;
      if (strstr(buff, "hgt:") != NULL)
        p.parts.hgt = 1;
      if (strstr(buff, "hcl:") != NULL)
        p.parts.hcl = 1;
      if (strstr(buff, "ecl:") != NULL)
        p.parts.ecl = 1;
      if (strstr(buff, "pid:") != NULL)
        p.parts.pid = 1;
      if (strstr(buff, "cid:") != NULL) {
        p.parts.cid = 1;
      }
    }
  }

  print_passport(p);
  if(validate_passport(p))
    puz1_count++;

  fclose(fstream);
  printf("%d\n", puz1_count);
  printf("%d\n", puz2_count);
  exit(EXIT_SUCCESS);
}
