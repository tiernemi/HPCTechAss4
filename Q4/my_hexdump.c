/*
 * =====================================================================================
 *
 *       Filename:  my_hexdump.c
 *
 *    Description:  my_hexdump - Mimics the hexdump -C command in linux. Converts file
 *                  to hexidecimal offset, ascii codes as well as the text representation.
 *                  Can read from file or standard input.
 *
 *        Synopsis:  ./my_hexdump [FILENAME]
 *                   ./my_hexdump
 *
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
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include <getopt.h>

int main ( int argc, char *argv[] ) {

	int i,j ;
	int opt ;
	bool readFromFile = false ;
	char * filename = NULL ;

// ================================= OPTIONS PARSING =============================================== //

	// Parses command line arguments. Returns an error if any options are passed. //
	while((opt = getopt(argc, argv, "cnv")) != -1) {
		switch(opt) {
			default :
				fprintf (stderr, "Incorrect option detected. Usage ./my_hexdump [FILENAME] \n");
				exit(-1) ;
				break;
		}
	}

	// Gets the command line arguments based on where getopt has stopped scanning. //
	if ((argc-optind) == 0) {
		readFromFile = false ;
	} else if ((argc-optind) == 1) {
		filename = malloc(sizeof(char)*(strlen(argv[optind])+1)) ;
		strcpy(filename, argv[optind]) ;
		readFromFile = true ;
	} else {
		fprintf (stderr, "Incorrect number of arguments. Usage ./my_hexdump [FILENAME]\n") ;
		exit(-1) ;
	}

// ================================= STREAM INPUT =============================================== //

	// Choose stream. //
	FILE * input ;
	if (readFromFile) {
		input = fopen(filename, "r") ;
		if (input == NULL) {
			fprintf(stderr, "Unable to open file %s\n", filename) ;
			exit(-2) ;
		}
	} else {
		input = stdin ;
	}


	// Read in and store byte data from buffer. //
	int bufSize = 200 ;
	char * contents = malloc(sizeof(char)*bufSize) ;
	char * buffer = malloc(sizeof(char)*bufSize) ;
	int fsize = 0 ;
	if (fgets(buffer, bufSize, input) != NULL) {
		fsize += strlen(buffer) ;
		contents = realloc(contents, sizeof(char)*(fsize+1)) ;
		strcpy(contents,buffer) ;
	}
	while (fgets(buffer, bufSize, input) != NULL) {
		fsize += strlen(buffer) ;
		contents = realloc(contents, sizeof(char)*(fsize+1)) ;
		strcat(contents,buffer) ;
	}
	free(buffer) ;

// ================================== PRINT OUT HEXDUMP ============================================ //

	for (i = 0 ; i < ceil((double) fsize/(double) 16) ; ++i) {
		// Print lines as long as 16 bytes still available. Else process edge case of less than 16 bytes. //
		if ((16*(i+1)/(fsize)) < 1) { 
			// Offset. //
			printf("%08x  ", 16*i) ;
			// Hexidecimal part. //
			for (j = 0 ; j < 8 ; ++j) {
				printf("%02x ", contents[16*i+j]) ;
			}
			printf(" ") ;
			for (j = 8 ; j < 16 ; ++j) {
				printf("%02x ", contents[16*i+j]) ;
			}
			// Word part. //
			printf(" |") ;
			for (j = 0 ; j < 16 ; ++j) {
				switch (contents[16*i+j]) {
					case '\n' :
						printf(".") ;
						break ;
					case '\t' :
						printf(".") ;
						break ;
					case '\0' :
						printf(".") ;
						break ;
					case '\a' :
						printf(".") ;
						break ;
					case '\b' :
						printf(".") ;
						break ;
					case '\f' :
						printf(".") ;
						break ;
					case '\r' :
						printf(".") ;
						break ;
					case '\v' :
						printf(".") ;
						break ;
					default :
						printf("%c", contents[16*i+j]) ;
						break ;
				}
			}
			printf("|\n") ;
		} else { 
			// Offset. //
			printf("%08x  ", 16*i) ;
			// Hexidecimal part. //
			for (j = 0 ; j < 8 ; ++j) {
				if (16*i+j < fsize) {
					printf("%02x ", contents[16*i+j]) ;
				} else {
					printf("   ") ;
				}
			}
			printf(" ") ;
			for (j = 8 ; j < 16 ; ++j) {
				if (16*i+j < fsize) {
					printf("%02x ", contents[16*i+j]) ;
				} else {
					printf("   ") ;
				}
			}
			// Word part. //
			printf(" |") ;
			for (j = 0 ; j < fsize-(16*i) ; ++j) {
				switch (contents[16*i+j]) {
					case '\n' :
						printf(".") ;
						break ;
					case '\t' :
						printf(".") ;
						break ;
					case '\0' :
						printf(".") ;
						break ;
					case '\a' :
						printf(".") ;
						break ;
					case '\b' :
						printf(".") ;
						break ;
					case '\f' :
						printf(".") ;
						break ;
					case '\r' :
						printf(".") ;
						break ;
					case '\v' :
						printf(".") ;
						break ;
					default :
						printf("%c", contents[16*i+j]) ;
						break ;
				}
			}
			printf("|\n") ;
		}
	}
	// Print final offset. //
	printf("%08x\n", fsize) ;

	if (readFromFile) {
		free(filename) ;
		fclose(input) ;
	}
	free(contents) ;

	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
