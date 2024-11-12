#include <stdio.h>
#include <string.h>

void gen_code_for_operator(char *inp, char operator, char * reg)
{
    int i = 0, j = 0;
    char temp[100];
    char arg1, arg2;

    while (inp[i] != '\0')
    {
        if (inp[i] == operator)
        {
            // Ensure there is a left operand
            if (j == 0)
            {
                printf("Error: No left operand for operator %c\n", operator);
                return;
            }
            // Ensure there is a right operand
            if (inp[i + 1] == '\0')
            {
                printf("Error: No right operand for operator %c\n", operator);
                return;
            }
            arg1 = temp[j - 1]; // Left operand from temp
            arg2 = inp[i + 1];  // Right operand from input
            printf("%c\t%c\t%c\t%c\n", operator, * reg, arg1, arg2);
            temp[j - 1] = *reg; // Replace left operand with result register
            i += 2;             // Skip operator and right operand
            (*reg)--;           // Move to next register
            continue;
        }
        else
        {
            temp[j++] = inp[i++];
        }
    }
    temp[j] = '\0';
    strcpy(inp, temp);
}

void gen_code(char *inp)
{
    // Operator precedence: /, *, +, -, =
    char reg = 'Z';
    gen_code_for_operator(inp, '/', &reg);
    gen_code_for_operator(inp, '*', &reg);
    gen_code_for_operator(inp, '+', &reg);
    gen_code_for_operator(inp, '-', &reg);
    gen_code_for_operator(inp, '=', &reg);
}

int main()
{
    char inp[100];
    printf("Enter expression:\n");
    scanf("%s", inp);
    printf("Op\tDest\tArg1\tArg2\n");
    gen_code(inp);
    return 0;
}
