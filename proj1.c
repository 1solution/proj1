#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <errno.h>

// variables
bool FOUND = 0; // found 100% thru analyzer
bool NOTFOUND = 0; // found 0% thru analyzer
bool INVALCH = 0; // invalid char inside crawler

int crawler = 0; // crawler. RAWWWWRRR!
int passedWords = 0; // how many words gone through analyzer
char exactLocation[101]; // location which exactly responds arg input
char desired[101]; // one location
char yourChars[101]; // arg input (ex.: BR) - U can use strlen(yourChars) without problem. It should also had '\0' in the end
char possible[27]; // possibble letters to continue with

int checkInput(char str[]) {
  int i = 0;
  while(str[i] != '\0') {
    if(!isalpha(str[i])) {
      return 1;
    }
    str[i] = toupper(str[i]);
    i++;
  }
  return 0;
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

void crawling(char *argv[]) {

  unsigned int yourLength = strlen(argv[1]);
  crawler = toupper(getchar());

  while(crawler != EOF) {

    int i = 0;

    while((crawler != '\n') && (crawler != EOF)) {

        if(!isalpha(crawler)) {
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

          if((desired[c]) == yourChars[c]) // char analyze drive toupper(desired[c])
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

        if(passedWords == 0 && FOUND == 0) // this a counter for location which passes analyze 100%
          NOTFOUND = 1;
        else
          NOTFOUND = 0;
      // PROCESSING LOCATION COMPLETED
  }
}

int main(int argc, char *argv[]) {

  argc = argc ;

  if(!argv[1])
    argv[1] = " ";
  else
    strcpy(yourChars, argv[1]);

  if(checkInput(yourChars) == 1) {
    fprintf(stderr, "%s", "Non alpha character(s) detected");
    return 1;
  }

  if(strlen(yourChars) > 100) {
    fprintf(stderr,"%s","Too long argument input (max 100)");
    return 1;
  }
  else if(strlen(yourChars) == 0) { // IDENTIFY IF ARRAY IS EMPTY
    fprintf(stderr,"%s","Empty array detected");
    return 1;
  }

  else { // ACTUAL PROGRAM

    crawling(argv); // call crawler

    if(INVALCH) {
      frpintf(stderr, "%s", "Non alpha character(s) detected");
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
