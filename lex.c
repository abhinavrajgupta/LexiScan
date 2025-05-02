#include <stdio.h>
#include <ctype.h>

#include "lex.h"

/* Global Variable */
int nextToken;

/* Local Variables */
static int charClass; 
static char lexeme [100];
static char nextChar;
static int lexLen;
static FILE *in_fp;

/* Local Function declarations */
static void addChar();
static void getChar();
static void getNonBlank();


int main(int argc, char * argv[]) 
{
    if ((in_fp = fopen(argv[1], "r")) == NULL) 
    { 
        printf("ERROR - cannot open file \n");
    }
    else 
    {
        getChar();
        do 
        {
            lex();
        } 
        while (nextToken != EOF);
    }
    printf("\n");
    return 0;
}

static int lookup(char ch) 
{
    switch (ch) 
    {
        case '(':
            addChar();
            nextToken = LEFT_PAREN;
            break;
        case ')':
            addChar();
            nextToken = RIGHT_PAREN;
            break;
        case '+':
            addChar();
            getChar();
            if (nextChar == '+')
            {
                addChar();
                nextToken = INC_OP;
            }
            else
            {
                ungetc(nextChar, in_fp);
	            nextToken = ADD_OP;
            }
            break;
        case '-':
            addChar();
            getChar();
            if (nextChar == '-')
            {
                addChar();
                nextToken = DEC_OP;
            }
            else
            {
	           ungetc(nextChar, in_fp);	    
               nextToken = SUB_OP;
            }
            break;
        case '*':
            addChar();
            getChar();
            if (nextChar == '*')
            {
                addChar();
                nextToken = POW_OP;
            }
            else
            {
	            ungetc(nextChar, in_fp);
                nextToken = MULT_OP;
            }   
            break;
        case '/':
            addChar();
            nextToken = DIV_OP;
            break;
        case ';':
            addChar();
            nextToken = SEMICOLON;
            break;
        case ':':
            addChar();
            getChar();
            if (nextChar == '=')
            {
                addChar();
                nextToken = ASSIGN_OP;
            }
            else
            {
	           ungetc(nextChar, in_fp);	    
               nextToken = COLON;
            }
            break;
        case '<':
            addChar();
            getChar();
            if (nextChar == '>')
            {
                addChar();
                nextToken = NEQUAL_OP;
            }
            else if (nextChar == '=')
            {
                addChar();
                nextToken = LEQUAL_OP;
            }
            else
            {
	            ungetc(nextChar, in_fp);
                nextToken = LESSER_OP;
            }
            break;
        case '>':
            addChar();
            getChar();
            if (nextChar == '=')
            {
                addChar();
                nextToken = GEQUAL_OP;
            }
            else
            {
                ungetc(nextChar, in_fp);
                nextToken = GREATER_OP;
            }
            break;
        case '=':
            addChar();
            nextToken = EQUAL_OP;
            break;
	case '!':
	    addChar();
	    getChar();
	    if (nextChar == '=')
	    {
	   	    addChar();
	   	    nextToken = UNKNOWN;
	    }
	    else
	    {
	        ungetc(nextChar, in_fp);
	        nextToken = UNKNOWN;
	    }
	    break;
        default:
            addChar();
            nextToken = UNKNOWN;
            break;
    }
    return nextToken;
}

static void addChar() 
{
    if (lexLen <= 98) 
    {
        lexeme[lexLen++] = nextChar;
        lexeme[lexLen] = 0;
    } 
    else 
    {
        printf("Error - lexeme is too long \n");
    }
}

static void getChar() 
{
    if ((nextChar = getc(in_fp)) != EOF) 
    {
        if (isalpha(nextChar))
            charClass = LETTER;
        else if (isdigit(nextChar))
            charClass = DIGIT;
        else charClass = UNKNOWN;
    } 
    else 
    {
        charClass = EOF;
    }
}

static void getNonBlank() 
{
    while (isspace(nextChar)) getChar();
}

int lex() 
{
    lexLen = 0;
    getNonBlank();

    switch (charClass) 
    {
        case LETTER:
            addChar();
            getChar();
            while (charClass == LETTER || charClass == DIGIT) 
            {
                addChar();
                getChar();
            }            
            if(lexeme[0] =='r'&&lexeme[1] =='e'&&lexeme[2] =='a'&&lexeme[3]=='d'&&lexeme[4] ==0)
            {
            nextToken = KEY_READ;
            }
            else if(lexeme[0] =='p'&&lexeme[1] =='r'&&lexeme[2] =='i'&&lexeme[3] =='n'&&lexeme[4]=='t'&&lexeme[5]==0)
            {
            nextToken = KEY_PRINT;
            }
            else if(lexeme[0] =='i'&&lexeme[1] =='f'&&lexeme[2] ==0)
            {
            nextToken = KEY_IF;
            }
            else if(lexeme[0] =='e'&&lexeme[1] =='l'&&lexeme[2] =='s'&&lexeme[3] =='e'&&lexeme[4]==0)
            {
            nextToken = KEY_ELSE;
            }
            else if(lexeme[0] =='b'&&lexeme[1] =='e'&&lexeme[2] =='g'&&lexeme[3] =='i'&&lexeme[4]=='n'&&lexeme[5]==0)
            {
            nextToken = KEY_BEGIN;
            }
            else if(lexeme[0] =='e'&&lexeme[1] =='n'&&lexeme[2] =='d'&&lexeme[3] ==0)
            {
            nextToken = KEY_END;
            }
            else
            {
                nextToken = IDENT; 
            }
            break;

        case DIGIT:
            addChar();
            getChar();
            while (charClass == DIGIT) 
            {
                addChar();
                getChar();
            }
            nextToken = INT_LIT;
            break;

        case UNKNOWN:
            lookup(nextChar);
            getChar();
            break;

        case EOF:
            nextToken = EOF;
            lexeme[0] = 'E';
            lexeme[1] = 'O';
            lexeme[2] = 'F';
            lexeme[3] = 0;
            break;
    }  
    if (nextToken != EOF)
    {
        printf("\n");
        printf("%s\t\t%s", lexeme, tokenString(nextToken));
    }
    return nextToken;
} 




