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
#include <getopt.h>


void convertToDigits(int * num, char * string) ;
void convertToRoundString (char * string, char roundChar, int * num, int size) ;
void removeDigits (int * digits, int loc, int * size) ;
void resizeDigits (int * digits, int amount, int * size) ;

int main ( int argc, char *argv[] ) {
	// Get the options. //
	int i = 0 ;
	// The rounding mode. Default K. //
	int rounding = 3 ;
	char roundChar = 'K' ;
	// Buffer to contain the number. //
	char * number = malloc(sizeof(char)*100) ;
	bool humanReadable = false ;
	bool flag = false ;
	int opt ;

	if (argc > 3) {
		fprintf (stderr, "Too many arguments : Usage : ./round [OPTIONAL ARG] [NUMBER]\n") ;
		exit(-2) ;
	}

	// Get the options. //
	while((opt = getopt(argc, argv, "K:M:G:T:P:E:h:")) != -1) {
		switch(opt) {
			case 'K' : 
				rounding = 3 ;
				flag = true ;
				strcpy(number,optarg) ;
				roundChar = 'K' ;
				break ;
			case 'M' : 
				rounding = 6 ;
				flag = true ;
				strcpy(number,optarg) ;
				roundChar = 'M' ;
				break ;
			case 'G' : 
				rounding = 9 ;
				flag = true ;
				strcpy(number,optarg) ;
				roundChar = 'G' ;
				break ;
			case 'T' : 
				rounding = 12 ;
				flag = true ;
				strcpy(number,optarg) ;
				roundChar = 'T' ;
				break ;
			case 'P' : 
				rounding = 15 ;
				flag = true ;
				strcpy(number,optarg) ;
				roundChar = 'P' ;
				break ;
			case 'E' : 
				rounding = 18 ;
				flag = true ;
				strcpy(number,optarg) ;
				roundChar = 'E' ;
				break ;
			case 'h' : 
				humanReadable = true ;
				flag = true ;
				strcpy(number,optarg) ;
				break ;
			default : 
				fprintf(stderr, "Usage : ./round [OPTIONAL ARG] [NUMBER]\n") ;
				exit(-1) ;
			break ;
		}
	}

	// If no options are specified. //
	if (!flag) {
		strcpy(number, argv[1]) ;
	}

	int * digits = malloc(sizeof(int)*strlen(number)) ;
	int numDigits = strlen(number) ;
	int currIndex ;
	convertToDigits(digits, number) ;
	if (numDigits <= rounding) {
		resizeDigits(digits, (rounding-numDigits+1), &numDigits) ;
	}
	currIndex = (numDigits-rounding+1) ;
	int roundNum  = digits[currIndex] ;
	removeDigits(digits, currIndex, &numDigits) ;
	if (roundNum > 5) {
		bool roundingFinished = false ;
		while(!roundingFinished) {
			--currIndex ;
			if (currIndex < 0) {
				resizeDigits(digits, 1, &numDigits) ;
				++currIndex ;
			}
			++digits[currIndex] ;
			if (digits[currIndex] == 10) {
				digits[currIndex] = 0 ;
			} else {
				roundingFinished = true ;
			}
		}
	}
	convertToRoundString(number, roundChar, digits, numDigits) ;
	printf("%s\n", number) ;
	free(number) ;
	free(digits) ;

	return EXIT_SUCCESS ;
}				/* ----------  end of function main  ---------- */


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  convertToDigits
 *    Arguments:  int * num - Array to save the numbers to.
 *                char * string - String to convert.
 *  Description:  Converts string to array of digits.
 * =====================================================================================
 */

void convertToDigits(int * num, char * string) {
	int i ;
	for (i = 0 ; i < strlen(string) ; ++i) {
		num[i] = string[i]-'0' ;
	}
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  convertToRoundString
 *    Arguments:  char * string - Location to save the number to.
 *                int * digits - Source of the digits.
 *  Description:  Converts digits to string.
 * =====================================================================================
 */

void convertToRoundString (char * string, char roundChar, int * num, int size) {
	int i ;
	for (i = 0 ; i < size-1 ; ++i) {
		string[i] = '0' + num[i] ;
	}
	string[size-1] = '.' ;
	string[size] = '0' + num[size-1] ;
	string[size+1] = roundChar ;
	string[size+2] = '\0' ;
}		/* -----  end of function convertToRoundString  ----- */


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  removeDigits
 *    Arguments:  int * digits - Location of digits array.
 *                int loc - Location to begin removing.
 *                int size - Number of digits.
 *  Description:  Removes digits to the right of loc inclusive.
 * =====================================================================================
 */

void removeDigits (int * digits, int loc, int * size) {
	realloc(digits, sizeof(int)*(loc)) ;
	*size = loc ;
}		/* -----  end of function removeDigits  ----- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  removeDigits
 *    Arguments:  int * digits - Location of digits array.
 *                int loc - Location to begin removing.
 *                int size - Number of digits.
 *  Description:  Removes digits to the right of loc inclusive.
 * =====================================================================================
 */

void resizeDigits (int * digits, int amount, int * size) {
	realloc(digits, sizeof(int)*(amount+*size)) ;
	memcpy(&digits[amount], digits, sizeof(int)*(*size)) ;
	memset(&digits[0], 0, sizeof(int)*amount) ;
	*size = *size+amount ;
}		/* -----  end of function removeDigits  ----- */
