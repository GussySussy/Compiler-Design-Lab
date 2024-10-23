%{ 
#include <stdio.h> 
#include <string.h> 
#include <ctype.h> 

void to_lowercase(char *str) {
    for(int i = 0; str[i]; i++){
        str[i] = tolower(str[i]);
    }
}

int flag = 0; 
char name[50] = "";
%} 

%% 
[a-zA-Z]+ {
    strcpy(name, yytext);
    to_lowercase(name);
    if (strstr(name, "gour") != NULL) {
        flag = 1;
    } else {
        flag = 0;
    }
}

[\n]+ {
    if(flag == 1){
        printf("\"%s\" contains \"gour\" as a substring.\n", yytext);
    }
    else{
        printf("\"%s\" does not contain \"gour\" as a substring.\n", yytext);
    }
    printf("Enter the string: ");
}

. { }

%% 

int yywrap(void) {
    return 1;
}

int main() 
{ 
    printf("Enter the string: ");
    yylex(); 
    return 0; 
}
