/* proj1.c 163714 Michal Plsek xplsek03 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <errno.h>

bool FOUND = 0; // found exact location
bool NOTFOUND = 0; // found no location
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

        if(passedWords == 0 && FOUND == 0) // this a counter for location which passes PROCESSING by 100%
          NOTFOUND = 1;
        else
          NOTFOUND = 0;
      // PROCESSING LOCATION COMPLETED
  }
}

int main(int argc, char *argv[]) {

 // argc = argc ;

if(argc > 1) { // odsud prepsat
  if(strlen(argv[1]) == 0) // gets an empty arg as "SPACE"
    argv[1] = " ";

strcpy(yourChars, argv[1]);

}
else {
char test[] = "X";
strcpy(yourChars, test);
printf("youyradad: %s", yourChars);
}
 // po sem prepsat. CHYBA: vyhni s epouzivani argv v crawleru() a pridej nakonec tohohle retezce prazdnej znak

	yourCharsUp(yourChars);

  if(strlen(yourChars) > 100) {
    fprintf(stderr,"%s","Too long argument input (max 100)");
    return 1;
  }

  else { // ACTUAL PROGRAM

    crawling(argv); // call crawler

    if(INVALCH) {
      fprintf(stderr, "%s", "Invalid character(s) detected");
      return 1;
    }
    if(NOTFOUND) {
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
}
