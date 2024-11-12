#include <stdio.h>
#include <stdlib.h>
struct node
{
    int st;
    struct node *link;
};
struct node1
{
    int nst[20];
};
static int nostate, noalpha, s, notransition, nofinal, start, c, r;
static int set[20], finalstate[20], buffer[20];
static int eclosure[20][20] = {0};
int complete = -1;
char alphabet[20];
struct node1 hash[20];
struct node *transition[20][20] = {NULL};
int compare(struct node1 a, struct node1 b)
{
    for (int i = 1; i <= nostate; i++)
        if (a.nst[i] != b.nst[i])
            return 0;
    return 1;
}
int insertDfaState(struct node1 newstate)
{
    for (int i = 0; i <= complete; i++)
        if (compare(hash[i], newstate))
            return 0;
    complete++;
    hash[complete] = newstate;
    return 1;
}
int findalpha(char c)
{
    int i;
    for (i = 0; i < noalpha; i++)
        if (alphabet[i] == c)
            return i;
    return 999;
}
void insert(int r, char c, int s)
{
    int j = findalpha(c);
    if (j == 999)
    {
        printf("Error from insert function");
        exit(0);
    }
    struct node *temp;
    temp = (struct node *)malloc(sizeof(struct node));
    temp->st = s;
    temp->link = transition[r][j];
    transition[r][j] = temp;
}
void printnewstate(struct node1 state)
{
    printf("{");
    for (int j = 1; j <= nostate; j++)
        if (state.nst[j] != 0)
            printf("q%d,", state.nst[j]);
    printf("}\t");
}
void findfinalstate()
{
    for (int i = 0; i <= complete; i++)
        for (int j = 1; j <= nostate; j++)
            for (int k = 0; k < nofinal; k++)
                if (hash[i].nst[j] == finalstate[k])
                {
                    printnewstate(hash[i]);
                    printf(" ");
                    j = nostate;
                    break;
                }
}
void main()
{
    int i, j, k, m, t, n, l;
    struct node *temp;
    struct node1 newstate = {0}, tmpstate = {0};
    printf("NOTE:- use letter e as epsilon\n  :- e must be last character if it is present: \n");
    printf("Enter the number of alphabets: ");
    scanf("%d", &noalpha); // noalpha -> number of alphabets
    printf("Enter the alphabets: ");
    getchar();
    for (i = 0; i < noalpha; i++)
    {
        alphabet[i] = getchar(); // character read is stored in alphabet
        getchar();               // newline is read here
    }
    printf("Enter the number of states: ");
    scanf("%d", &nostate); // nostate -> number of states
    printf("Enter the start state: ");
    scanf("%d", &start); // start -> start state number
    printf("Enter the number of final states: ");
    scanf("%d", &nofinal); // nofinal -> number of final states
    printf("Enter the final states: ");
    for (i = 0; i < nofinal; i++)
        scanf("%d", &finalstate[i]); // contains the position of final states
    printf("Enter the number of transition: ");
    scanf("%d", &notransition);
    printf("NOTE:- Transition is in the form -> qno alphabet qno\n  :- State number must be greater than zero\nEnter Transition:\n");

    for (i = 0; i < notransition; i++)
    {
        scanf("%d %c %d", &r, &c, &s);
        insert(r, c, s);
    }
    for (i = 0; i < 20; i++)
    {
        for (j = 0; j < 20; j++)
            hash[i].nst[j] = 0;
    }
    i = -1;
    printf("\nEquivalent DFA.....\n");
    printf(".......................\n");
    printf("Transitions of DFA\n");
    newstate.nst[start] = start;
    insertDfaState(newstate);
    while (i != complete)
    {
        i++;
        newstate = hash[i];
        printnewstate(newstate);
        for (k = 0; k < noalpha; k++)
        {
            c = 0;
            for (j = 1; j <= nostate; j++)
                set[j] = 0;
            for (j = 1; j <= nostate; j++)
            {
                l = newstate.nst[j];
                if (l)
                {
                    temp = transition[l][k];
                    while (temp)
                    {
                        if (!set[temp->st])
                        {
                            c++;
                            set[temp->st] = temp->st;
                        }
                        temp = temp->link;
                    }
                }
            }
            printf("\n");
            if (c)
            {
                for (m = 1; m <= nostate; m++)
                    tmpstate.nst[m] = set[m];
                insertDfaState(tmpstate);
                printnewstate(tmpstate);
            }
            else
            {
                printf("NULL\n");
            }
        }
        printf("\n");
    }
    printf("\n\nStates of DFA:\n");
    for (i = 0; i <= complete; i++)
        printnewstate(hash[i]);

    printf("\n Alphabets: ");
    for (i = 0; i < noalpha; i++)
        printf("%c\t", alphabet[i]);
    printf("\n Start State:q%d\n", start);
    printf("Final states: ");
    findfinalstate();
}
