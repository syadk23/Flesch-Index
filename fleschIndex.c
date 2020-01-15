#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
  int totalWords = 0;
  int totalSyllables = 0;
  int totalSentences = 0;
  int endFile;
  float index;
  FILE *fp;
  char *inputFile;
  /* Check to see how many arguements are input (dummy proofing),
  then read the second arguement provided */
  if (argc < 2) {
    printf("An .txt input file was not provided.\n");
    return -1;
  }
  else {
    fp = fopen(argv[1], "r");
    if (fp == NULL) {
      printf("Failed to open the input file, please use a .txt file.\n");
      return -1;
    }
  }
  /* Seek to the end of the file and set endFile to that position.
  then read the file using fread */
  fseek(fp, 0, SEEK_END);
  endFile = ftell(fp);
  fseek(fp, 0, SEEK_SET);
  /* Allocate memory equal to the total number of characters provided */
  inputFile = malloc(sizeof(char) * endFile);
  fread(inputFile, 1, endFile, fp);

  for (int i = 0; i < endFile; i++) {
    /* Calculate the total words */
    if (inputFile[i] == ' ' && inputFile[i - 1] != ' ' && inputFile[i + 1] != '\n') {
      totalWords++;
    }
    if (inputFile[i] == '\n') {
      totalWords++;
    }
    /* If the character read is alphanumeric, check if it is a vowel,
    then follow the syllable checking format */
    if (isalpha(inputFile[i])) {
      inputFile[i] = tolower(inputFile[i]);
      if (inputFile[i] == 'a' || inputFile[i] == 'e' || inputFile[i] == 'i' || inputFile[i] == 'o' || inputFile[i] == 'u' || inputFile[i] == 'y') {
        totalSyllables++;
        if (inputFile[i - 1] == 'a' || inputFile[i - 1] == 'e' || inputFile[i - 1] == 'i' || inputFile[i - 1] == 'o' || inputFile[i - 1] == 'u' ||  inputFile[i - 1] == 'y') {
          totalSyllables--;
        }
      }
    }
    /* For every non-alphanumeric character check the previous characters
    to determine sentence counts and syllables */
    if (isalpha(inputFile[i]) == 0 && isdigit(inputFile[i]) == 0) {
      if (inputFile[i - 1] == '.' || inputFile[i - 1] == ';' || inputFile[i - 1] == ':' || inputFile[i - 1] == '!' || inputFile[i - 1] == '?') {
        totalSentences++;
      }
      /* Number syllable algorithm */
      if (isdigit(inputFile[i - 1])) {
        totalSyllables++;
      }
      /* Ending 'e' vowel syllable restriction */
      if (inputFile[i - 1] == 'e') {
        if (inputFile[i - 3] == 'a' || inputFile[i - 3] == 'e' || inputFile[i - 3] == 'i' || inputFile[i - 3] == 'o' || inputFile[i - 3] == 'u' || inputFile[i - 3] == 'y') {
          totalSyllables--;
        }
      }
    }
  }
  /* Free the string and close the file */
  free(inputFile);
  fclose(fp);
  /* Calculate the index and show output */
  index = 206.835 - 84.6 * (totalSyllables / totalWords) - 1.015 * (totalWords / totalSentences);
  printf("Flesch Index = %0.0f\n", index);
  printf("Syllable Count = %d\n", totalSyllables);
  printf("Word Count = %d\n", totalWords);
  printf("Sentence Count = %d\n", totalSentences);
  return 0;
}
