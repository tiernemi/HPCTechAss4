/*
 * =====================================================================================
 *
 *       Filename:  round.c
 *
 *    Description:  round - Program takes in number as an argument and then converts it
 *                  to the desired type of rounded number.
 *
 *       Synopsis:  round [OPTIONS] [NUMBER] 
 *
 *      Arguments:  -K - Round to kilobytes (Default)
 *                  -M - Round to megabytes
 *                  -G - Round to gigabytes
 *                  -T - Round to terabytes
 *                  -P - Round to petabytes
 *                  -E - Round to etabytes
 *                  -h - Human readable format option
 *
 *        Version:  1.0
 *        Created:  14/01/16 12:33:39
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Michael Tierney (MT), tiernemi@tcd.ie
 *
 * =====================================================================================
 */

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <getopt.h>

int main ( int argc, char *argv[] ) {
	// The exponent N of 2^N that describes the option. Default K : N=10. //
	int roundingExponent = 10 ;
	// Possible options. //
	char posChars[6] = {'K', 'M', 'G', 'T', 'P', 'E'} ;
	// Default rounding character is K. //
	char roundChar = posChars[0] ;
	// Buffer to contain the numberString. //
	char * numberString = malloc(sizeof(char)*200) ;
	bool humanReadableSet = false ;
	bool flagsSet = false ;
	int opt ;

	if (argc > 3) {
		fprintf (stderr, "Too many arguments : Usage : ./round [OPTIONAL ARG] [NUMBER]\n") ;
		exit(-2) ;
	}

	// Get the options. Extracts flags and associated argument. Sets exponent and rounding character. //
	while((opt = getopt(argc, argv, "K:M:G:T:P:E:h:")) != -1) {
		switch(opt) {
			case 'K' : 
				roundingExponent = 10 ;
				flagsSet = true ;
				strcpy(numberString,optarg) ;
				roundChar = posChars[0] ;
				break ;
			case 'M' : 
				roundingExponent = 20 ;
				flagsSet = true ;
				strcpy(numberString,optarg) ;
				roundChar = posChars[1] ;
				break ;
			case 'G' : 
				roundingExponent = 30 ;
				flagsSet = true ;
				strcpy(numberString,optarg) ;
				roundChar = posChars[2] ;
				break ;
			case 'T' : 
				roundingExponent = 40 ;
				flagsSet = true ;
				strcpy(numberString,optarg) ;
				roundChar = posChars[3] ;
				break ;
			case 'P' : 
				roundingExponent = 50 ;
				flagsSet = true ;
				strcpy(numberString,optarg) ;
				roundChar = posChars[4] ;
				break ;
			case 'E' : 
				roundingExponent = 60 ;
				flagsSet = true ;
				strcpy(numberString,optarg) ;
				roundChar = posChars[5] ;
				break ;
			case 'h' : 
				humanReadableSet = true ;
				flagsSet = true ;
				strcpy(numberString,optarg) ;
				break ;
			default : 
				fprintf(stderr, "Usage : ./round [OPTIONAL ARG] [NUMBER]\n") ;
				exit(-1) ;
			break ;
		}
	}

	// If no options are specified. //
	if (!flagsSet) {
		strcpy(numberString, argv[1]) ;
	}

	double numToBeRounded ;
	sscanf(numberString, "%lf", &numToBeRounded) ;

	// If it's in humanreadable mode then get the closest exponent using log_(2^10)(num). //
	if (humanReadableSet) {
		int closestExponent = round(log(numToBeRounded)/log(1024)) ;
		// Can't be above 6. //
		if (closestExponent > 6) {
			closestExponent = 6 ;
		}
		roundChar = posChars[closestExponent-1] ;
		roundingExponent = closestExponent*10 ;
	}

	// Create the rounding constant of the form (2^N)/10. //
	double roundingConst = (pow(2, roundingExponent))/10.f ;
	// Get a number containing the digits of interest, round if and divide by 10 to introduce decimel place. //
	double finalDigits = round(numToBeRounded / roundingConst)/10.f ;

	// Print double of the form a.bc. //
	printf("%.1lf%c\n", finalDigits, roundChar) ;
	free(numberString) ;

	return EXIT_SUCCESS ;
}				/* ----------  end of function main  ---------- */
