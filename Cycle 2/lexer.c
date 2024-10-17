#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef enum
{
    TOKEN_EOF,
    TOKEN_IDENTIFIER,
    TOKEN_NUMBER,
    TOKEN_OPERATOR,
    TOKEN_LPAREN,
    TOKEN_RPAREN,
    TOKEN_LBRACE,
    TOKEN_RBRACE,
    TOKEN_SEMICOLON,
    TOKEN_COMMA,
    TOKEN_UNKNOWN
} TokenType;

typedef struct
{
    TokenType type;
    char lexeme[256];
} Token;

int getNextChar();
void ungetChar(int c);
Token getNextToken();

FILE *fp = NULL;
int buffer = EOF;

int main(int argc, char *argv[])
{
    Token token;

    if (argc != 2)
    {
        printf("Usage: lexer <filename>\n");
        return 1;
    }

    fp = fopen(argv[1], "r");
    if (!fp)
    {
        printf("Error opening file %s\n", argv[1]);
        return 1;
    }

    do
    {
        token = getNextToken();
        printf("Token: Type = %d, Lexeme = '%s'\n", token.type, token.lexeme);
    } while (token.type != TOKEN_EOF);

    fclose(fp);
    return 0;
}

int getNextChar()
{
    int c;
    if (buffer != EOF)
    {
        c = buffer;
        buffer = EOF;
    }
    else
    {
        c = fgetc(fp);
    }
    return c;
}

void ungetChar(int c)
{
    buffer = c;
}

Token getNextToken()
{
    Token token;
    int c;

    do
    {
        c = getNextChar();
    } while (isspace(c));

    if (c == EOF)
    {
        token.type = TOKEN_EOF;
        strcpy(token.lexeme, "EOF");
    }
    else if (isalpha(c) || c == '_')
    {
        // Start of an identifier
        int i = 0;
        token.lexeme[i++] = c;
        while ((c = getNextChar()) != EOF && (isalnum(c) || c == '_'))
        {
            token.lexeme[i++] = c;
        }
        token.lexeme[i] = '\0';
        ungetChar(c); // Put back the character that is not part of the identifier
        token.type = TOKEN_IDENTIFIER;
    }
    else if (isdigit(c))
    {
        // Start of a number
        int i = 0;
        token.lexeme[i++] = c;
        while ((c = getNextChar()) != EOF && isdigit(c))
        {
            token.lexeme[i++] = c;
        }
        token.lexeme[i] = '\0';
        ungetChar(c);
        token.type = TOKEN_NUMBER;
    }
    else if (c == '+' || c == '-' || c == '*' || c == '/' ||
             c == '=' || c == '<' || c == '>' || c == '!')
    {
        // Operators (handle multi-character operators)
        int i = 0;
        token.lexeme[i++] = c;
        int next_c = getNextChar();
        if ((c == '+' && next_c == '+') || (c == '-' && next_c == '-') ||
            (c == '=' && next_c == '=') || (c == '!' && next_c == '=') ||
            (c == '<' && next_c == '=') || (c == '>' && next_c == '='))
        {
            // Multi-character operator
            token.lexeme[i++] = next_c;
        }
        else
        {
            ungetChar(next_c);
        }
        token.lexeme[i] = '\0';
        token.type = TOKEN_OPERATOR;
    }
    else if (c == '(')
    {
        token.lexeme[0] = c;
        token.lexeme[1] = '\0';
        token.type = TOKEN_LPAREN;
    }
    else if (c == ')')
    {
        token.lexeme[0] = c;
        token.lexeme[1] = '\0';
        token.type = TOKEN_RPAREN;
    }
    else if (c == '{')
    {
        token.lexeme[0] = c;
        token.lexeme[1] = '\0';
        token.type = TOKEN_LBRACE;
    }
    else if (c == '}')
    {
        token.lexeme[0] = c;
        token.lexeme[1] = '\0';
        token.type = TOKEN_RBRACE;
    }
    else if (c == ';')
    {
        token.lexeme[0] = c;
        token.lexeme[1] = '\0';
        token.type = TOKEN_SEMICOLON;
    }
    else if (c == ',')
    {
        token.lexeme[0] = c;
        token.lexeme[1] = '\0';
        token.type = TOKEN_COMMA;
    }
    else
    {
        // Unknown token
        token.lexeme[0] = c;
        token.lexeme[1] = '\0';
        token.type = TOKEN_UNKNOWN;
    }

    return token;
}
