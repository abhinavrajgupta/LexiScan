#ifndef LEX_H
#define LEX_H

/* Character classes */
#define LETTER 0
#define DIGIT 1
#define UNKNOWN 99

/* Token codes */
#define INT_LIT 10
#define IDENT 11
#define COLON 12
#define SEMICOLON 13
#define DEC_OP 14
#define INC_OP 15
#define POW_OP 16

#define ASSIGN_OP 17
#define LESSER_OP 18
#define GREATER_OP 19
#define EQUAL_OP 20
#define NEQUAL_OP 21
#define LEQUAL_OP 22
#define GEQUAL_OP 23

#define ADD_OP 24
#define SUB_OP 25
#define MULT_OP 26
#define DIV_OP 27
#define LEFT_PAREN 28
#define RIGHT_PAREN 29

#define KEY_READ 30
#define KEY_PRINT 31
#define KEY_IF 32
#define KEY_ELSE 33
#define KEY_BEGIN 34
#define KEY_END 35


const char* tokenString(int token) 
{
    switch (token) 
    {
        case 10: return "INT_LIT";
        case 11: return "IDENT";
        case 12: return "COLON";
        case 13: return "SEMICOLON";
        case 14: return "DEC_OP";
        case 15: return "INC_OP";
        case 16: return "POW_OP";

        case 17: return "ASSIGN_OP";
        case 18: return "LESSER_OP";
        case 19: return "GREATER_OP";
        case 20: return "EQUAL_OP";
        case 21: return "NEQUAL_OP";
        case 22: return "LEQUAL_OP";
        case 23: return "GEQUAL_OP";

        case 24: return "ADD_OP";
        case 25: return "SUB_OP";
        case 26: return "MULT_OP";
        case 27: return "DIV_OP";
        case 28: return "LEFT_PAREN";
        case 29: return "RIGHT_PAREN";

        case 30: return "KEY_READ";
        case 31: return "KEY_PRINT";
        case 32: return "KEY_IF";
        case 33: return "KEY_ELSE";
        case 34: return "KEY_BEGIN";
        case 35: return "KEY_END";
        
        case 99: return "UNKNOWN";
		 
        default: return "UNKNOWN";
    }
}

int lex();

#endif
