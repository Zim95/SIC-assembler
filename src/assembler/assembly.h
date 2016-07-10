/*
 *	assembly.h
 *
 *	Author: Irak Rigia
 *
 *	This file contains the declarations of various constants, global variables and functions used by the
 *	SIC assembler program(during assembly).
 */

#include <stdio.h>
#include <stdint.h>
#include "../headers/sic.h"

#ifndef ASSEMBLY_H_
#define ASSEMBLY_H_

//Macros to determine whether symbol or operand or anything else is found in their appropriate files or not.
#define FOUND		0
#define NOTFOUND	-1

//ADDED FOR GITHUB PURPOSE

//Macros for source program related purpose
#define LABEL_SIZE	7
#define OPCODE_SIZE	7
#define OPERAND_SIZE	7
#define OBJCODE_SIZE	10

#define MAX_NAME_LEN	7

/*	Macros for object program
#define HEADER_SIZE	
#define TEXT_SIZE
#define END_SIZE
*/

//A date structure for a single SIC(Not SIC/XE) instruction read from the source file.(Used by pass1, but can be a sub-structure within
//another structure)
typedef struct{
	char label[LABEL_SIZE];
	char opcode[OPCODE_SIZE];
	char operand[OPERAND_SIZE];
} SIC_src_instr;

//Another data structure for SIC instruction to be read/written to intermediate file.(Used by pass1)
typedef struct{
	SIC_addr addr;	//Stores the 15-bit address field
	SIC_src_instr *instr;
} SIC_int_instr;

//Another data structure for SIC instruction to written to listing file.(Used by pass2)
typedef struct{
	SIC_int_instr *instr;	//Portion from the intermediate file.
	char obj_code[OBJCODE_SIZE];	//Object code produced.
} SIC_list_instr;

//Data structure for program information.
typedef struct{
	char file_name[256];	//Name of source file name(with extension)
	char prog_name[MAX_NAME_LEN];	//File-name of program
	SIC_addr start_addr;	//First address of program 
	uint16_t prog_len;	//Program length
} SIC_prog_info;

/*	Data structure for object program components
typedef struct{
	char header[HEADER_SIZE];	//Header record. Eg: H^COPY  ^000000^00178F
	char (*text)[TEXT_SIZE];	//Text record. Eg: T^000000^15^041788^001788^181015^2C1785^380006^0C178B^4C0000
	char end[END_SIZE];		//End record. Eg: E^000000
} SIC_objprog;
*/

/*	Search for 'symbol' in the SYMTAB	*/
int search_symtab(const char *symbol);

/*	Search for 'opcode' in the OPTAB	*/
int search_optab(const char *opcode);

/*	This function reads an instruction from the input file	*/
int read_line_src(FILE *src, SIC_src_instr *buff);

/*	This function writes the examined instruction line to the intermediate file along with memory locations. */
int write_line_intr(FILE *intr_file, SIC_int_instr *buff);

/*	Read Line from intermediate file	*/
int read_line_intr(FILE *f, SIC_int_instr *buff);

/*	Write Line to listing file	*/
int write_line_list(FILE *f, SIC_list_instr *buff);

/*	Get hexcode of the 'opcode' from optab	*/
char *get_hexcode(char *opcode);

/*	Get address of 'symbol' from symtab	*/
char *get_symbol_addr(char *symbol);

/* Insert the length of text record to the ^^ portion
 * Divide the text_rec into two parts,insert the length, and then rejoin them. Maybe we can strtok()...but for now let stick with this.
 * Eg: T^004000^-^0410024^0010024^184021^2C10021^384006^0C10027^4C0000^00000
 */
void insert_txtlen(char *text_rec, int txtrec_ctr);

/*	Pass-1 procedure function	*/
void pass1(FILE *src_file);

/*	Pass-2 procedure function	*/
void pass2();

#endif