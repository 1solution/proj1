/* proj1.c 163714 Michal Plsek xplsek03 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <errno.h>

    char yourChars[101]; // arg input (ex.: BR)

	int isValid(int ch) { // checks if char on input is valid
		if(ch >= 32 && ch <= 126){
			return 1;
		}
		return 0;
	}

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

	void checkInput(char str[], bool *INVALCH) { // uppercases your argument chars + checks for validity of input chars
  for(int i = 0; str[i] != '\0'; i++) {
		if(!isValid(str[i]))
			*INVALCH = 1;
    str[i] = toupper(str[i]);
  }

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

void showArray(char array[], int *passedWords, bool *FOUND, int *candidates, char *autocomplete) { // prints possible chars and FOUND:
  for(int i = 0; i < (*passedWords)-1; i++) {
    for(int j = 0; j < (*passedWords)-i-1; j++) {
      if(array[j] > array[j+1])
        swap(&array[j], &array[j+1]);
    }
  }

  if(*candidates == 1 && (!(*FOUND)))
    printf("Found: %s", autocomplete);

  if(*FOUND && *passedWords > 0)
		printf("\n"); // because of FOUND && ENABLE one one screen

  if((*passedWords > 0 && *candidates > 1) || (*FOUND && *passedWords > 0)) {
		printf("Enable: ");
		for(int k = 0; k < (*passedWords); k++)
			printf("%c", toupper(array[k]));
  }
}

void crawling(char *arg[], bool *FOUND, bool *INVALCH, int *candidates, int *passedWords, char *exactLocation, char *autocomplete, char *desired, char *possible) { // main crawling and testing function

    int crawler = 0; // crawler = getchar();
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
          *INVALCH = 1;
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
            *FOUND = 1;
          }
        }

        if((c != strlen(desired)) && (c == yourLength)) {

          if(alreadyIs(possible, desired[c]) == 0) {
            possible[*passedWords] = desired[c];
            (*passedWords)++;
          }

					if((!(*FOUND)) && (c == yourLength) && (c != strlen(desired))) {
						strcpy(autocomplete, desired);
						(*candidates)++;
					}

        }
      // PROCESSING LOCATION COMPLETED

      emptyStr(desired); // fill desired[] with '\0' and go again
  }
}

int main(int argc, char *argv[]) { // main

    char possible[95]; // possibble letters to continue with, max 95 allowed ASCII chars
    char desired[101]; // currently tested location in PROCESSING
    char autocomplete[101]; // autocomplete if is only one candidate word
	char exactLocation[101]; // location which exactly responds arg input
    argc = argc ;
	int candidates = 0; // candidate for autocomplete
	int passedWords = 0; // how many words had gone through analyzer
	bool INVALCH = 0; // invalid char inside crawler
	bool FOUND = 0; // found exact location
    char **newArr = argv; // only substitute, because gotta resolve non-exist. argument

  if(argv[1]) { // argument exists
    strcpy(yourChars, newArr[1]);
  }
  else {
		newArr[1] = "";
  }
	checkInput(yourChars, &INVALCH);

  if(strlen(yourChars) > 100) {
    fprintf(stderr,"%s","Too long argument input (max 100)");
    return 1;
  }

    crawling(newArr, &FOUND, &INVALCH, &candidates, &passedWords, exactLocation, autocomplete, desired, possible); // call crawler

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
      showArray(possible, &passedWords, &FOUND, &candidates, autocomplete);

    return 0;
}
