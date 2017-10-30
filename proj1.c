/* proj1.c 163714 Michal Plsek xplsek03 */
/* komenty ke vsem fcim a prazdn arg jako prefix. bez globalnich promennych */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <errno.h>

bool FOUND = 0; // found exact location
bool INVALCH = 0; // invalid char inside crawler
int crawler = 0; // crawler = getchar();
int passedWords = 0; // how many words had gone through analyzer
char exactLocation[101]; // location which exactly responds arg input
char desired[101]; // currently tested location in PROCESSING
char yourChars[101]; // arg input (ex.: BR)
char possible[95]; // possibble letters to continue with, max 95 allowed ASCII chars

	void yourCharsUp(char str[]) {
  for(int i = 0; str[i] != '\0'; i++)
    str[i] = toupper(str[i]);
}

int alreadyIs(char array[], char inside) {
  int length = strlen(array);
  for(int i = 0; i < length; i++) {
    if(array[i] == inside)
      return 1;
    }
    return 0;
}

void swap(char *x, char *y) {
    char temp = *x;
    *x = *y;
    *y = temp;
}

void showArray(char array[], int length) {
  for(int i = 0; i < length-1; i++) {
    for(int j = 0; j < length-i-1; j++) {
      if(array[j] > array[j+1])
        swap(&array[j], &array[j+1]);
    }
  }

  if(FOUND)
    printf("\n"); // because of FOUND && ENABLE one one screen

  printf("Enable: ");
  for(int k = 0; k < length; k++)
    printf("%c", toupper(array[k]));
}

int isValid(int ch) {
	if(ch >= 32 && ch <= 126)
		return 1;
	else return 0;
}

void crawling(char *argv[]) {

  unsigned int yourLength = strlen(argv[1]);
  crawler = toupper(getchar());

  while(crawler != EOF) {

    int i = 0;

    while((crawler != '\n') && (crawler != EOF)) {

				if(i == 100) { // if line is longer than 100, then cut the rest out and continue
					desired[i] = '\0';
				break;
				}

        if(!isValid(crawler)) {
          INVALCH = 1;
        }

        desired[i] = crawler;
        i++;
        crawler = toupper(getchar());
        }

        if(crawler == '\n') {
          desired[i] = '\0';
          crawler = toupper(getchar());
        }

      //PROCESSING LOCATION
        unsigned int c = 0;

        while(c < yourLength) {

          if((desired[c]) == yourChars[c])
            c++;
          else break;

          if(strcmp(desired,yourChars) == 0) {
            strcpy(exactLocation,yourChars);
            FOUND = 1;
          }
        }

        if((c != strlen(desired)) && (c == yourLength)) {
          if(alreadyIs(possible, desired[c]) == 0) {
            possible[passedWords] = desired[c];
            passedWords++;
          }
        }

      // PROCESSING LOCATION COMPLETED
  }
}

int main(int argc, char *argv[]) {

  argc = argc ;

  if(argv[1] && strlen(argv[1]) != 0) { // argument exists
    strcpy(yourChars, argv[1]);
  }
  else { // aint no argument or is only ""
    fprintf(stderr,"%s", "No argument");
    return 1;
  }

	yourCharsUp(yourChars);

  if(strlen(yourChars) > 100) {
    fprintf(stderr,"%s","Too long argument input (max 100)");
    return 1;
  }

    crawling(argv); // call crawler

    if(INVALCH) {
      fprintf(stderr, "%s", "Invalid character(s) detected");
      return 1;
    }

    if(FOUND) {
      printf("Found: %s", exactLocation);
    }
    else if(passedWords > 0)
      showArray(possible,passedWords);

      else {
        fprintf(stderr, "%s", "Not found");
        return 1;
      }

    return 0;
}
