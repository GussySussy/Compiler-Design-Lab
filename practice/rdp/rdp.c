#include <stdio.h>
#include <string.h>
#define SUCCESS 1
#define FAILURE 0

// E –> T E’
// E’ –> + T E’ | e
// T –> F T’
// T’ –> * F T’ | e
// F –> ( E ) | id

const char *cursor;
char string[64];
int E(), E_(), T(), T_(), F();

int main()
{
    puts("Enter the string");
    scanf("%s", string); // Read input from the user
    cursor = string;
    puts("");
    puts("Input		 Action");
    puts("--------------------------------");

    // Call the starting non-terminal E
    if (E() && *cursor == '\0')
    { // If parsing is successful and the cursor has reached the end
        puts("--------------------------------");
        puts("String is successfully parsed");
        return 0;
    }
    else
    {
        puts("--------------------------------");
        puts("Error in parsing String");
        return 1;
    }
}

// E –> T E’
int E()
{
    printf("%-16s E -> T E'\n", cursor);
    if (T())
    {
        if (E_())
        {
            return SUCCESS;
        }
        else
        {
            return FAILURE;
        }
    }
    else
    {
        return FAILURE;
    }
}

// T –> F T’
int T()
{
    printf("%-16s T -> F T'\n", cursor);
    if (F())
    {
        if (T_())
        {
            return SUCCESS;
        }
        else
        {
            return FAILURE;
        }
    }
    else
    {
        return FAILURE;
    }
}

// E’ –> + T E’ | e
int E_()
{
    if (*cursor == '+')
    {
        printf("%-16s E' -> + T E'\n", cursor);
        cursor++;
        if (T())
        {
            if (E_())
            {
                return SUCCESS;
            }
            else
            {
                return FAILURE;
            }
        }
        else
        {
            return FAILURE;
        }
    }
    else
    {
        printf("%-16s E' -> $\n", cursor);
        return SUCCESS;
    }
}

// F –> ( E ) | id
int F()
{
    if (*cursor == '(')
    {
        printf("%-16s F -> ( E )\n", cursor);
        cursor++;
        if (E())
        {
            if (*cursor == ')')
            {
                cursor++;
                return SUCCESS;
            }
            else
            {
                return FAILURE;
            }
        }
        else
        {
            return FAILURE;
        }
    }
    else if (*cursor == 'i')
    {
        printf("%-16s F -> i\n", cursor);
        cursor++;
        return SUCCESS;
    }
    else
    {
        return FAILURE;
    }
}

int T_()
{
    if (*cursor == '*')
    {
        printf("%-16s T' -> * F T'\n", cursor);
        cursor++;
        if (F())
        {             // Call non-terminal F
            if (T_()) // Call non-terminal T'
                return SUCCESS;
            else
                return FAILURE;
        }
        else
            return FAILURE;
    }
    else
    {
        printf("%-16s T' -> $\n", cursor);
        return SUCCESS;
    }
}