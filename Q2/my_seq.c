/*
 * =====================================================================================
 *
 *       Filename:  my_seq.c
 *
 *    Description:  my_seq - Mimics the seq command in linux. Lists numbers from START
 *                  to END with an increment INCREMENT. Does not take negative arguments.
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
	int i ;
	int start = 1 ;
	int increment = 1 ;
	int end = 1 ;

	int opt ;
	bool paddingFlagSet = false ;

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
		fprintf (stderr, "Incorrect number of arguments expected. At most three arguments.
				Usage ./my_seq [OPTION] [ARGS] \n");
		exit(-1) ;
	}
	
	// String controlling how the numbers are outputted. //
	char formatString[20] ;
	// If padding is set calculate the maximum number of zeros and add padding to formatting. //
	if (paddingFlagSet) {
		int maxNumZeros = floor(log10(end))+1 ;
		sprintf(formatString, "%%0%dd", maxNumZeros) ;
	} else {
		sprintf(formatString, "%%d") ;
	}

	// Print the sequence. //
	for (i = start ; i <= end ; i += increment) {
		printf(formatString, i) ;
		printf("\n") ;
	}

	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
