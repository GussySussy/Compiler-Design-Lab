#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char input[100], stack[100];
int top = -1;

void check(int i)
{
    char *handle;
    int handle_size;
    while (1)
    {
        if (top >= 1 && (stack[top - 1] == 'i') && stack[top] == 'd')
        {
            handle = "E";
            handle_size = 2;
        }
        else if (top >= 2 && (stack[top - 2] == 'E') && (stack[top - 1] == '+') && stack[top] == 'E')
        {
            handle = "E+E";
            handle_size = 3;
        }
        else if (top >= 2 && (stack[top - 2] == 'E') && (stack[top - 1] == '*') && stack[top] == 'E')
        {
            handle = "E*E";
            handle_size = 3;
        }
        else if (top >= 2 && stack[top - 2] == '(' && stack[top - 1] == 'E' && stack[top] == ')')
        {
            handle = "(E)";
            handle_size = 3;
        }
        else
        {
            return;
        }

        top -= handle_size - 1;
        stack[top] = 'E';
        stack[top + 1] = '\0';
        printf("$%s\t\t%s$\t\tREDCUE -> %s\n", stack, input + handle_size + i, handle);
    }
}

int main()
{
    printf("Enter the input string (endign with $) : ");
    scanf("%s", &input);
    int len = strlen(input);
    for (int i = 0; i < len; i++)
    {
        if ((input[i] == 'i') && (input[i + 1] == 'd'))
        {
            stack[++top] = 'i';
            stack[++top] = 'd';
            stack[top + 1] = '\0';
            printf("$%s\t\t%s$\t\tSHIFT -> id\n", stack, input + i + 2);
            check(i);
            i++;
        }
        else
        {
            stack[++top] = input[i];
            stack[top + 1] = '\0';
            printf("$%s\t\t%s$\t\tSHIFT -> %c\n", stack, input + i + 1, input[i]);
            check(i);
        }
    }
    if (stack[top] == 'E' && top == 0)
    {
        printf("\nVALID ");
    }
    else
    {
        printf("\nINVALID");
    }
    return 0;
}