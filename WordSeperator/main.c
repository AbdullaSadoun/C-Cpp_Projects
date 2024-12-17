/*
this program reads the user entered sentence and seperates the 
words in the sentence and prints them out to a seperate outfile
created by Abdulla Sadoun
*/
#include <stdio.h>
#include <stdlib.h>

int main(void) {

	//open the outfile
	FILE* fout;
	fopen_s(&fout, "outfile.txt", "w");

	char word[25]; //string to temporarily store the characters of a word

	//prompting the user to enter a sentence
	printf("Please Enter Your Sentence: ");
	
	//reading the characters until a space is encountered and storing them in word
	while(scanf_s("%s", word, 25) != ("\n"||"\0")) {
		//print the word
		fprintf(fout, "%s\n", word);
	}

	//closing the outfile
	fclose(fout);

	return 0;
}