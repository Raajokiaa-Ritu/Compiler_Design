#include <stdio.h>
#include <ctype.h>
#include <string.h>

int isKeyword(char *w) {
    return !strcmp(w,"int")||!strcmp(w,"float")||!strcmp(w,"char")||!strcmp(w,"double");
}

int main() {
    char code[] = "int x/ = 10;\nx = (x + 5){//hello\n};";
    int i = 0, j;
    char ch, word[20];

    while ((ch = code[i]) != '\0') {
        if (ch == ' ' || ch == '\n' || ch == '\t') { i++; continue; }

        if (code[i]=='/' && code[i+1]=='/') { while (code[i++]!='\n' && code[i]); continue; }

        if (isalpha(ch)) {
            j = 0;
            while (isalnum(code[i])) word[j++] = code[i++];
            word[j] = '\0';
            printf("%s --> %s\n", word, isKeyword(word) ? "Keyword" : "Identifier");
        }
        else if (isdigit(ch)) {
            j = 0;
            while (isdigit(code[i])) word[j++] = code[i++];
            word[j] = '\0';
            printf("%s --> Number\n", word);
        }
        else if (strchr(",;().", ch)) printf("%c --> Symbol\n", code[i++]);
        else printf("%c --> Operator\n", code[i++]);
    }
    return 0;
}
