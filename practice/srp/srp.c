#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char ip[100], stack[100];
int top = -1;

void check(int i)
{
    int handle_size;
    char *handle;

    while (1)
    {
        if (top >= 1 && stack[top] == 'd' && stack[top - 1] == 'i')
        {
            handle = "id";
            handle_size = 2;
        }
        else if (top >= 2 && stack[top - 2] == 'E' && stack[top - 1] == '+' && stack[top] == 'E')
        {
            handle = "E+E";
            handle_size = 3;
        }
        else if (top >= 2 && stack[top - 2] == 'E' && stack[top - 1] == '*' && stack[top] == 'E')
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
        printf("$%s\t\t%s$\t\tREDUCE->%s\n", stack, ip + i + handle_size, handle);
    }
}

void main()
{

    printf("\nThe Grammar is : \nE -> E+E | E*E | (E) | id\n");
    printf("Enter the input string : ");
    scanf("%s", ip);
    int l = strlen(ip);
    printf("\nStack\t\tInput\t\tAction\n");
    for (int i = 0; i < l; i++)
    {
        if (ip[i] == 'i' && ip[i + 1] == 'd')
        {
            stack[++top] = 'i';
            stack[++top] = 'd';
            stack[top + 1] = '\0';
            printf("$%s\t\t%s$\t\tSHIFT->id\n", stack, ip + i + 2);
            check(i);
            i++; // ignore the d
        }
        else
        {
            stack[++top] = ip[i];
            stack[top + 1] = '\0';
            printf("$%s\t\t%s$\t\tSHIFT->%c\n", stack, ip + i + 1, ip[i]);
            check(i);
        }
    }
    if (top == 0 && stack[top] == 'E')
    {
        printf("\nVALID");
    }
    else
    {
        printf("\nINVALID");
    }
}