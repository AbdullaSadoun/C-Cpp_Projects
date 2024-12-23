#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MXCHARS 25
#define FALSE 0
#define TRUE 1

int main(void){

  FILE * fout = fopen("seperatedwords.txt", "w");// open the file for writing 

  char c, word[MXCHARS]; //string to temporarily store the characters of a word
  int i = 0, decider = FALSE; // character index and bool alternative

    printf("Enter your sentence: "); //prompting the user to enter a sentence

    while ((c = getchar()) != '\n') {

      if (c == ' ' || c == '\t') { // check for space that seperates words
          if (decider == TRUE) {
              word[i] = '\0'; // Null-terminate the word
              fprintf(fout, "%s\n", word); // Write word to file
              i = 0;
              decider = FALSE;
          }
      } else {
          if (i < MXCHARS - 1) {
              word[i++] = c;
              decider = TRUE;
          }
      }
      
    }

  if (decider == TRUE) { // check for the null terminator
    word[i] = '\0';
  fprintf(fout, "%s\n", word);
  }

	fflush(fout); // flushing the output buffer
	fclose(fout); // closing the output file

    return 0;
}