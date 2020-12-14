#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define INPUT "input"

#define FORMAT_BYR "%d"
#define FORMAT_IYR "%d"
#define FORMAT_EYR "%d"
#define FORMAT_HGT_IN "%din"
#define FORMAT_HGT_CM "%dcm"
#define FORMAT_HCL "#%06x"
#define FORMAT_ECL_AMB "%s"
#define FORMAT_PID "%09d"
#define FORMAT_CID "%s"

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
  char buff[BUFF_SIZE + 1];
  char temp_buff[BUFF_SIZE + 1];
  char *pointer_to_loc;
  int puz1_count, puz2_count;
  unsigned int value_from_scan;
  char color_loop[][4] = {"amb", "blu", "brn", 
	  					"gry", "grn", "hzl", "oth"};
  Passport p;

  fstream = fopen(INPUT, "r");

  puz1_count = 0;
  puz2_count = 0;
  value_from_scan = 0;

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
		/* Oh no... */
      if ((pointer_to_loc = strstr(buff, "byr:")) != NULL) {
		pointer_to_loc += strlen("byr:");
		if(sscanf(pointer_to_loc, FORMAT_BYR, &value_from_scan) == 1) {
			if(value_from_scan >= 1920 && value_from_scan <= 2002)
        		p.parts.byr = 1;
		}
	  }
      if ((pointer_to_loc = strstr(buff, "iyr:")) != NULL) {
		pointer_to_loc += strlen("iyr:");
		if(sscanf(pointer_to_loc, FORMAT_IYR, &value_from_scan) == 1) {
			if(value_from_scan >= 2010 && value_from_scan <= 2020)
        		p.parts.iyr = 1;
		}
	  }
      if ((pointer_to_loc = strstr(buff, "eyr:")) != NULL) {
		pointer_to_loc += strlen("eyr:");
		if(sscanf(pointer_to_loc, FORMAT_EYR, &value_from_scan) == 1) {
			if(value_from_scan >= 2020 && value_from_scan <= 2030)
        	  p.parts.eyr = 1;
		}
	  }
      if ((pointer_to_loc = strstr(buff, "hgt:")) != NULL) {
		pointer_to_loc += strlen("hgt:");
		if(sscanf(pointer_to_loc, FORMAT_HGT_CM, &value_from_scan) == 1) {
			if(value_from_scan >= 150 && value_from_scan <= 193)
        		p.parts.hgt = 1;
		}
		else if(sscanf(pointer_to_loc, FORMAT_HGT_IN, &value_from_scan) == 1) {
        	if(value_from_scan >= 59 && value_from_scan <= 76)
				p.parts.hgt = 1;
		}
	  }
      if ((pointer_to_loc = strstr(buff, "hcl:")) != NULL) {
		pointer_to_loc += strlen("hcl:");
		if(sscanf(pointer_to_loc, FORMAT_HCL, &value_from_scan) == 1) {
        	p.parts.hcl = 1;
		}
	  }
      if ((pointer_to_loc = strstr(buff, "ecl:")) != NULL) {
		pointer_to_loc += strlen("ecl:");
		for(value_from_scan = 0; value_from_scan < 7; value_from_scan++) {
			if((strstr(pointer_to_loc, color_loop[value_from_scan])
					   	- pointer_to_loc) <= 3)
				p.parts.pid = 1;
		}
	  }
      if ((pointer_to_loc = strstr(buff, "pid:")) != NULL) {
		pointer_to_loc += strlen("pid:");
		if(sscanf(pointer_to_loc, FORMAT_PID, &value_from_scan) == 1) {
        	p.parts.ecl = 1;
		}
	  }
      if ((pointer_to_loc = strstr(buff, "cid:")) != NULL) {
		pointer_to_loc += strlen("cid:");
		if(sscanf(pointer_to_loc, FORMAT_CID, &value_from_scan) == 1) {
        	p.parts.cid = 1;
		}
      }
    }
  }

  print_passport(p);
  if(validate_passport(p))
    puz1_count++;

  fclose(fstream);
  printf("\n%d\n", puz1_count);
  printf("%d\n", puz2_count);
  exit(EXIT_SUCCESS);
}
