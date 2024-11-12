#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node
{
    int st;
    struct node *link;
};

#define MAX_STATES 20
#define MAX_ALPHABET 20

struct node *transition[MAX_STATES][MAX_ALPHABET] = {NULL};
int e_closure[MAX_STATES][MAX_STATES] = {0};
int buffer[MAX_STATES] = {0};
char alphabet[MAX_ALPHABET];
int noalpha = 0;                  // Number of input symbols (alphabet size)
int nostate = 0;                  // Number of states
int c;                            // Index for e_closure array
int state_map[MAX_STATES];        // Map state names to indices
char state_names[MAX_STATES][10]; // State names (e.g., "q0", "q1")
int num_states = 0;               // Total number of unique states

// Function prototypes
void findclosure(int x, int sta);
int get_state_index(char *state);
int get_alpha_index(char symbol);
void insert_transition(int src, char symbol, int dest);

int main()
{
    FILE *fp;
    char line[100];
    int i, j;
    char src_state[10], symbol, dest_state[10];
    int src_index, dest_index, sym_index;

    // Initialize the state map
    for (i = 0; i < MAX_STATES; i++)
    {
        state_map[i] = -1;
        strcpy(state_names[i], "");
    }

    // Open the input file
    fp = fopen("input.txt", "r");
    if (fp == NULL)
    {
        printf("Error: Cannot open input.txt\n");
        return 1;
    }

    // Read transitions from the file
    while (fgets(line, sizeof(line), fp))
    {
        if (sscanf(line, "%s %c %s", src_state, &symbol, dest_state) == 3)
        {
            // Get or assign indices for source and destination states
            src_index = get_state_index(src_state);
            dest_index = get_state_index(dest_state);

            // Add symbol to alphabet if not already present
            if (get_alpha_index(symbol) == -1)
            {
                alphabet[noalpha++] = symbol;
            }

            // Insert the transition
            insert_transition(src_index, symbol, dest_index);
        }
    }
    fclose(fp);

    // Update the number of states
    nostate = num_states;

    // Display the transitions
    printf("Transitions:\n");
    for (i = 0; i < nostate; i++)
    {
        for (j = 0; j < noalpha; j++)
        {
            struct node *temp = transition[i][j];
            while (temp != NULL)
            {
                printf("%s -- %c --> %s\n", state_names[i], alphabet[j], state_names[temp->st]);
                temp = temp->link;
            }
        }
    }

    // Compute epsilon closures for all states
    printf("\nEpsilon Closures:\n");
    for (i = 0; i < nostate; i++)
    {
        c = 0;
        for (j = 0; j < MAX_STATES; j++)
        {
            buffer[j] = 0;
            e_closure[i][j] = 0;
        }
        findclosure(i, i);
        // Print epsilon closure for state i
        printf("Epsilon closure of %s: {", state_names[i]);
        for (j = 0; e_closure[i][j] != -1 && j < MAX_STATES; j++)
        {
            printf("%s", state_names[e_closure[i][j]]);
            if (e_closure[i][j + 1] != -1)
                printf(", ");
        }
        printf("}\n");
    }

    return 0;
}

// Function to find epsilon closure
void findclosure(int x, int sta)
{
    struct node *temp;
    int i;
    if (buffer[x])
        return;
    e_closure[sta][c++] = x;
    buffer[x] = 1;
    // Check if 'e' is in alphabet
    int e_index = get_alpha_index('e');
    if (e_index != -1 && transition[x][e_index] != NULL)
    {
        temp = transition[x][e_index];
        while (temp != NULL)
        {
            findclosure(temp->st, sta);
            temp = temp->link;
        }
    }
    e_closure[sta][c] = -1; // Mark end of closure
}

int get_state_index(char *state)
{
    int i;
    // Check if state already exists
    for (i = 0; i < num_states; i++)
    {
        if (strcmp(state_names[i], state) == 0)
            return i;
    }
    // Assign new index
    strcpy(state_names[num_states], state);
    return num_states++;
}

int get_alpha_index(char symbol)
{
    int i;
    for (i = 0; i < noalpha; i++)
    {
        if (alphabet[i] == symbol)
            return i;
    }
    return -1;
}

void insert_transition(int src, char symbol, int dest)
{
    int sym_index = get_alpha_index(symbol);
    if (sym_index == -1)
    {
        printf("Error: Symbol %c not found in alphabet\n", symbol);
        exit(1);
    }
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    temp->st = dest;
    temp->link = transition[src][sym_index];
    transition[src][sym_index] = temp;
}
