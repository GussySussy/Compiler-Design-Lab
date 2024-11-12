#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main()
{
    int n, i, j, top = 0, col, row;
    char terms[10], prec[10][10][1], ip[20], stack[20];

    printf("Enter the number of terminals : ");
    scanf("%d", &n);
    printf("Enter the terminals : \n");
    scanf("%s", &terms);

    printf("Enter the precedence values for : ");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            printf("Enter the value for %c %c:", terms[i], terms[j]);
            scanf("%s", prec[i][j]);
        }
    }

    printf("\nOperator Precedence Table\n");
    for (i = 0; i < n; i++)
    {
        printf("\t%c", terms[i]);
    }
    for (i = 0; i < n; i++)
    {
        printf("\n%c", terms[i]);
        for (j = 0; j < n; j++)
        {
            printf("\t%c", prec[i][j][0]);
        }
    }

    printf("\nEnter the input string (ending with $) : ");
    scanf("%s", &ip);
    stack[top] = "$";
    int len = strlen(ip);
    i = 0;
    printf("\nSTACK\t\t\tINPUT STRING\t\t\tACTION\n");
    printf("\n%s\t\t\t%s\t\t\t", stack, ip);

    while (i <= len)
    {
        for (int k = 0; k < n; k++)
        {
            if (stack[top] == terms[k])
            {
                col = k;
            }
            if (ip[i] == terms[k])
            {
                row = k;
            }
        }
        if ((stack[top] == '$') && (ip[i] == '$'))
        {
            printf("\nString is accepted");
            break;
        }
        else if ((prec[col][row][0] == '<') || (prec[col][row][0] == '='))
        {
            stack[++top] = prec[col][row][0];
            stack[++top] = ip[i];
            printf("Shift %c", ip[i]);
        }
        else
        {
            if (prec[col][row][0] == '>')
            {
                while (stack[top] != '<')
                {
                    --top;
                }
                top = top - 1;
                printf("Reduce");
            }
            else
            {
                printf("\nString is not accepted");
                break;
            }
        }
        for (int k = 0; k <= top; k++)
        {
            printf("%c", stack[k]);
        }
        printf("\t\t\t");
        for (int k = i; k < strlen(ip); k++)
        {
            printf("%c", ip[k]);
        }
        printf("\t\t\t");
    }
    getchar();
}