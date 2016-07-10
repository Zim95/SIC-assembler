/*
 *	main.c
 *
 *	Written by:	Irak Rigia
 *	Date:	1 july 2016
 *	This is the main program for the SIC assembler module.
 *	This is a 2-pass assembler.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "assembly.h"

//Make it '1' for debug codes to be generated.
#define DEBUG	0

//Program info as global variable
SIC_prog_info program_info;

int assemble(FILE *src_file);

int main(int argc, char *argv[]){
	FILE *src_file;
	
	/*	DEBUG	*/
	#if DEBUG
	printf("Current working directory: %s\n", (char*)get_current_dir_name());	//print working directory
	#endif
	
	if(argc <= 1){
		fprintf(stderr,"(%s : %d)\n", __FILE__, __LINE__);
		fprintf(stderr,"\nError: No source filename provided\n");
		exit(EXIT_FAILURE);
	}
	//Input file
	if((src_file = fopen(argv[1],"r")) == NULL){
		fprintf(stderr,"(%s : %d)\n", __FILE__, __LINE__);
		fprintf(stderr,"\nError: No file exists with the name '%s'\n",argv[1]);
		exit(EXIT_FAILURE);
	}
	
	//Program source filename
	strcpy(program_info.file_name, argv[1]);
	
	//Call assemble()
	assemble(src_file);
	
	return 0;
}

//This function invokes the actual algorithms.
int assemble(FILE *src_file){
	
	//Call pass1()
	pass1(src_file);
	
	//Call pass2()
	//No need for arguments. Because required files are already made.
	pass2();
}