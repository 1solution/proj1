/* proj1.c 163714 Michal Plsek xplsek03 */

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
char autocomplete[101]; // autocomplete if is only one candidate word
int candidates = 0; // candidate for autocomplete

  void emptyStr(char str[]) { // empties values from desired[] after every analyze run
    for(int i = 0; i < 101; i++)
      str[i] = '\0';
  }

  int toNextLine() { // if 100 chars in input file is reached, this skips to next newline
    int t = getchar();

    while((t != '\n') && (t != EOF))
    t = getchar();

    return t;
  }

	void yourCharsUp(char str[]) { // uppercases your argument chars
  for(int i = 0; str[i] != '\0'; i++)
    str[i] = toupper(str[i]);
}

int alreadyIs(char array[], char inside) { // checks if its already inside the field with possible characters
  int length = strlen(array);
  for(int i = 0; i < length; i++) {
    if(array[i] == inside)
      return 1;
    }
    return 0;
}

void swap(char *x, char *y) { // swaps possible characters in field
    char temp = *x;
    *x = *y;
    *y = temp;
}

void showArray(char array[], int length) { // prints possible chars and FOUND:
  for(int i = 0; i < length-1; i++) {
    for(int j = 0; j < length-i-1; j++) {
      if(array[j] > array[j+1])
        swap(&array[j], &array[j+1]);
    }
  }

  if(candidates == 1)
    printf("Found: %s", autocomplete);

  if(FOUND)
		printf("\n"); // because of FOUND && ENABLE one one screen

  if(candidates != 1) {
		printf("Enable: ");
		for(int k = 0; k < length; k++)
			printf("%c", toupper(array[k]));
  }
}

int isValid(int ch) { // checks if char on input is valid
	if(ch >= 32 && ch <= 126)
		return 1;
	else return 0;
}

void crawling(char *arg[]) { // main crawling and testing function

  unsigned int yourLength = strlen(arg[1]);
  crawler = toupper(getchar());

  while(crawler != EOF) {

    int i = 0;

    while((crawler != '\n') && (crawler != EOF)) {

				if(i == 100) { // if line is longer than 100, then cut the rest out and continue
					desired[i] = '\0';

					crawler = toNextLine();

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
          strcpy(autocomplete, desired);
          candidates++;
        }
      // PROCESSING LOCATION COMPLETED

      emptyStr(desired); // fill desired[] with '\0' and go again
  }
}

int main(int argc, char *argv[]) { // main

  argc = argc ;
  char **newArr = argv; // only substitute, because gotta resolve non-exist. argument

  if(argv[1]) { // argument exists
    strcpy(yourChars, newArr[1]);
  }
  else
		newArr[1] = "";

	yourCharsUp(yourChars);

  if(strlen(yourChars) > 100) {
    fprintf(stderr,"%s","Too long argument input (max 100)");
    return 1;
  }

    crawling(newArr); // call crawler

    if(INVALCH) {
      fprintf(stderr, "%s", "Invalid character(s) detected");
      return 1;
    }

    if(!FOUND && passedWords == 0) {
      fprintf(stderr, "%s", "Not found");
      return 1;
    }

    if(FOUND) {
      printf("Found: %s", exactLocation);
    }
    if(passedWords > 0)
      showArray(possible,passedWords);

    return 0;
}
