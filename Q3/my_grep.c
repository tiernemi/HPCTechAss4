/*
 * =====================================================================================
 *
 *       Filename:  my_grep.c
 *
 *    Description:  my_grep - Mimics the grep command in linux. Searches for a pattern
 *                  and returns lines containing the with pattern highlighted.
 *                  -n - Turns on line numbers.
 *                  -v - Inverts the grep.
 *                  -c - Turn on colouring of the pattern text.
 *
 *        Synopsis:  ./my_grep [OPTIONS] [PATTERN]
 *                   ./my_grep [OPTIONS] [PATTERN] [FILENAME]
 *        Version:  1.0
 *        Created:  19/01/16 11:40:59
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Michael Tierney (MT), tiernemi@tcd.ie
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <getopt.h>

int main ( int argc, char *argv[] ) {

	int opt ;
	bool colourFlag = false ;
	bool lineNumFlag = false ;
	bool inverseFlag = false ;
	bool readFromFile = false ;
	char * pattern ;
	char * filename ;

// ================================= OPTIONS PARSING =============================================== //

	// Get the options, n is line numbering, c is pattern colouring, v is inverse matching. //
	while((opt = getopt(argc, argv, "cnv")) != -1) {
		switch(opt) {
			case 'n' : 
				lineNumFlag = true ;
				break ;
			case 'c' : 
				colourFlag = true ;
				break ;
			case 'v' : 
				inverseFlag = true ;
				break ;
			default :
				fprintf (stderr, "Incorrect option detected. Usage ./my_grep [OPTION] [PATTERN]\n");
				exit(-1) ;
				break;
		}
	}

	// Gets the command line arguments based on where getopt has stopped scanning. //
	if ((argc - optind) == 1) {
		pattern = malloc(sizeof(char)*(strlen(argv[optind])+1)) ;
		strcpy(pattern, argv[optind]) ;
	} else if ((argc - optind) == 2) {
		pattern = malloc(sizeof(char)*(strlen(argv[optind])+1)) ;
		strcpy(pattern, argv[optind]) ;
		filename = malloc(sizeof(char)*(strlen(argv[optind+1])+1)) ;
		strcpy(filename, argv[optind+1]) ;
		readFromFile = true ;
	} else {
		fprintf (stderr, "Incorrect number of arguments. ./my_grep [OPTION] [PATTERN] [FILENAME]\n");
		exit(-1) ;
	}

// ================================= INPUT STREAM =============================================== //

	// Choose the input stream. //
	FILE * input ;
	if (readFromFile) {
		input = fopen(filename, "r") ;
		if (input == NULL) {
			fprintf(stderr, "Unable to open file %s\n", filename) ;
			exit(-1) ;
		}
	} else {
		input = stdin ;
		if (input == NULL) {
			fprintf(stderr, "Unable to open buffer stdin \n") ;
			exit(-1) ;
		}
	}


// ============================= PATTERN SEARCHING AND PRINTING ================================== //

	char * buffer = NULL ;
	size_t len = 0 ;
	int lineNum = 0 ;
	// COntinue reading in lines until encountering the end of the buffer. //
	while (getline(&buffer, &len, input) != -1) {
		// Make a copy of the buffer. //
		char * locOfLastPattern = buffer ;
		bool patternPresent = false ;
		++lineNum ;

		// Start extracting pattern locations. //
		char * loc = strstr(buffer, pattern) ;
		locOfLastPattern = loc + strlen(pattern) ;
		char ** patternLocations = malloc(sizeof(char*)) ;
		int numPatterns = 0 ;

		// Look for more patterns within the line. /
		while (loc != NULL) {
			++numPatterns ;
			patternLocations = realloc(patternLocations, sizeof(char*)*numPatterns) ;
			patternLocations[numPatterns-1] = loc ;
			patternPresent = true ;
			loc = strstr(locOfLastPattern, pattern) ;
			// Move copy away from the last pattern found to avoid duplicate detection. //
			locOfLastPattern = loc + strlen(pattern) ;
		}

		// Apply the flags to the printing. //
		if (patternPresent != inverseFlag) {
			// Line numbering. //
			if (lineNumFlag) {
				if (colourFlag) {
					printf("\033[0m\033[1;32m%d\033[1;34m:\033[0m", lineNum) ;
				} else {
					printf("%d:", lineNum) ;
				}
			}
			// Pattern colouring. Must apply the extra printing info at each pattern location. //
			if (colourFlag) {
				char * curLocation = buffer ;
				int numPatternsProcessed = 0 ;
				while (*curLocation != '\0') {
					// Apply colouring at location pointed to by patternLocations. // 
					if(numPatternsProcessed < numPatterns && curLocation == patternLocations[numPatternsProcessed]) {
						printf("\033[1;31m%s\033[0m", pattern) ;
						curLocation += strlen(pattern) ;
						++numPatternsProcessed ;
					} else {
						printf("%c",*curLocation) ;
						++curLocation ;
					}
				}
			} else {
				printf("%s", buffer) ;
			}
		}
		free(patternLocations) ;
	}
	free(buffer) ;

	// If it's reading in from a file close and free. //
	if (readFromFile) {
		free(filename) ;
		fclose(input) ;
	}
	free(pattern) ;

	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
