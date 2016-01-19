/*
 * =====================================================================================
 *
 *       Filename:  my_seq.c
 *
 *    Description:  my_seq - Mimics the seq command in linux. Lists numbers from START
 *                  to END with an increment INCREMENT. Takes negative numbers.
 *                  -w - Adds padding zeros before each number.
 *
 *       Synopsis:  ./my_seq [OPTION] [START]
 *                  ./my_seq [OPTION] [START] [END]
 *                  ./my_seq [OPTION] [START] [INCREMENT] [END]
 *
 *        Version:  1.0
 *        Created:  15/01/16 18:16:20
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Michael Tierney (MT), tiernemi@tcd.ie
 *   Organization:  
 *
 * =====================================================================================
 */

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <getopt.h>

int main ( int argc, char *argv[] ) {
	int i,j ;
	int start = 1 ;
	int increment = 1 ;
	int end = 1 ;

	int opt ;
	bool paddingFlagSet = false ;
	bool negativeNums = false ;

// ================================= PREPERATION =============================================== //

	// Adds a "--" before the first negative number to stop getopt from parsing them as options. //
	for (i = 1 ; i < argc ; ++i) {
		int num ;
		sscanf(argv[i], "%d", &num) ;
		// If the number is negative remake argv so that it contains an additional arg "--" //.
		if (num < 0) {
			++argc ;
			char ** cleanedArgList = malloc(sizeof(char*)*argc) ;
			for (j = 0 ; j < i ; ++j) {
				cleanedArgList[j] = malloc(sizeof(char)*(strlen(argv[j])+1)) ;
				strcpy(cleanedArgList[j], argv[j]) ;
			}
			cleanedArgList[i] = malloc(sizeof(char)*(strlen(argv[i])+1)) ;
			strcpy(cleanedArgList[i], "--") ;
			for (j = i+1 ; j < argc ; ++j) {
				cleanedArgList[j] = malloc(sizeof(char)*(strlen(argv[j-1])+1)) ;
				strcpy(cleanedArgList[j], argv[j-1]) ;
			}
			argv = cleanedArgList ;
			negativeNums = true ;
			break ;
		}
	}
 
// ================================= PARSING =============================================== //

	// Get the options. If w is detected turn on the padding flag. //
	while((opt = getopt(argc, argv, "w")) != -1) {
		switch(opt) {
			case 'w' : 
				paddingFlagSet = true ;
				break ;
			default :
				fprintf (stderr, "Incorrect option detected. Usage ./my_seq [OPTION] [ARGS]\n");
				exit(-1) ;
				break;
		}
	}

	// Gets the command lien arguments based on where getopt has stopped scanning. //
	if ((argc - optind) == 1) {
		// 1 argument implies the number is the terminator of the sequence. //
		sscanf(argv[optind], "%d\n", &end) ;
	} else if ((argc - optind) == 2) {
		// 2 arguments imply argument 1 is the start and argument 2 is the end. //
		sscanf(argv[optind], "%d\n", &start) ;
		sscanf(argv[optind+1], "%d\n", &end) ;
	} else if ((argc - optind) == 3) {
		// 3 arguments imply arguments 1 is the start, argument 2 is the increment and argument 3 is the end. //
		sscanf(argv[optind], "%d\n", &start) ;
		sscanf(argv[optind+1], "%d\n", &increment) ;
		sscanf(argv[optind+2], "%d\n", &end) ;
	} else {
		fprintf (stderr, "Incorrect number of arguments expected. At most three arguments. Usage ./my_seq [OPTION] [ARGS] \n");
		exit(-1) ;
	}
	
// ================================= FORMATTING =============================================== //

	// String controlling how the numbers are outputted. //
	char formatString[20] ;
	// If padding is set calculate the maximum number of zeros and add padding to formatting. //
	if (paddingFlagSet) {
		int maxNumZeros = 0 ;
		if (fabs(end) > fabs(start)) {
			maxNumZeros = floor(log10(fabs(end)))+1 ;
			// Accounts for additional padding due to -. //
			if (end < 0) {
				++maxNumZeros ;
			}
		} else {
			maxNumZeros = floor(log10(fabs(start)))+1 ;
			// Accounts for additional padding due to -. //
			if (start < 0) {
				++maxNumZeros ;
			}
		}
		sprintf(formatString, "%%0%dd", maxNumZeros) ;
	} else {
		sprintf(formatString, "%%d") ;
	}

// ================================= PRINTING =============================================== //

	// May cause infinite loops if increment == 0 but so does seq. //
	if (increment >= 0) {
		// Print the sequence upwards. //
		for (i = start ; i <= end ; i += increment) {
			printf(formatString, i) ;
			printf("\n") ;
		}
	} else {	
		// Print the sequence downwards. //
		for (i = start ; i >= end ; i += increment) {
			printf(formatString, i) ;
			printf("\n") ;
		}
	}

	// Frees heap if it needed to process negative numbers. //
	if (negativeNums) {
		for (i = 0 ; i < argc ; ++i) {
			free(argv[i]) ;
		}
		free(argv) ;
	}
	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
