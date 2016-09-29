// Parser.h: interface for the CParser class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PARSER_H__C7A80107_C90D_4A27_BA7E_F92E37C8C431__INCLUDED_)
#define AFX_PARSER_H__C7A80107_C90D_4A27_BA7E_F92E37C8C431__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <stdlib.h>
#include <stdio.h>
#define PARSER_STRIP_EMPTY_LINES        1   // strips all blank lines
#define PARSER_LEAVE_EMPTY_LINES        2   // leaves empty lines
#define PARSER_STRIP_WS_ENDS            4   // strips ws space at ends of line
#define PARSER_LEAVE_WS_ENDS            8   // leaves it
#define PARSER_STRIP_COMMENTS           16  // strips comments out
#define PARSER_LEAVE_COMMENTS           32  // leaves comments in

#define PARSER_BUFFER_SIZE              256 // size of parser line buffer
#define PARSER_MAX_COMMENT              16  // maximum size of comment delimeter string

#define PARSER_DEFAULT_COMMENT          "#"  // default comment string for parser

// pattern language
#define PATTERN_TOKEN_FLOAT   'f'
#define PATTERN_TOKEN_INT     'i'
#define PATTERN_TOKEN_STRING  's'
#define PATTERN_TOKEN_LITERAL '\''

// state machine defines for pattern matching
#define PATTERN_STATE_INIT       0

#define PATTERN_STATE_RESTART    1
#define PATTERN_STATE_FLOAT      2
#define PATTERN_STATE_INT        3 
#define PATTERN_STATE_LITERAL    4
#define PATTERN_STATE_STRING     5
#define PATTERN_STATE_NEXT       6

#define PATTERN_STATE_MATCH      7
#define PATTERN_STATE_END        8

#define PATTERN_MAX_ARGS         16
#define PATTERN_BUFFER_SIZE      80
char *StringLtrim(char *string);
char *StringRtrim(char *string);
float IsFloat(char *fstring);

int   IsInt(char *istring);
int StripChars(char *string_in, char *string_out, char *strip_chars, int case_on=1);

int ReplaceChars(char *string_in, char *string_out, char *replace_chars, char rep_char, int case_on=1);
class CParser  
{
public:
	CParser();
	virtual ~CParser();
	int reset();
	int open(char * filename);
	int close();
	char * getLine(int mode);
	int setComment(char *string);
	int patternMatch(char* string,char* pattern,...);
public:

    FILE *fstream;                    // file pointer
    char buffer[PARSER_BUFFER_SIZE];  // line buffer
    int  length;                      // length of current line
    int  num_lines;                   // number of lines processed
    char comment[PARSER_MAX_COMMENT]; // single line comment string
	
	// pattern matching parameter storage, easier that variable arguments
	// anything matched will be stored here on exit from the call to pattern()
    char  pstrings[PATTERN_MAX_ARGS][PATTERN_BUFFER_SIZE]; // any strings
    int   num_pstrings;
	
    float pfloats[PATTERN_MAX_ARGS];                       // any floats
    int   num_pfloats;
	
    int   pints[PATTERN_MAX_ARGS];                         // any ints
    int   num_pints;

	

	
};

#endif // !defined(AFX_PARSER_H__C7A80107_C90D_4A27_BA7E_F92E37C8C431__INCLUDED_)
