#include <stdio.h>
#include <ctype.h>


char stack[100], postfix[50];
int top = -1;

void push (char karakter) {
    stack[++top] = karakter;
}
char pop (void) {
    if (top == -1) return -1;
    else return stack[top--];
}

void YiginYazdir (void);
void Infix_to_Postfix (void);
int Oncelik (char ch);
void Postfix_Hesaplama (void);
void YiginBosalt (void);
void Postfix_Hesaplama (void);




int main (void) {
    Infix_to_Postfix();
    YiginBosalt();
    Postfix_Hesaplama();
    return 0;
}



void Infix_to_Postfix (void) { // Soru-2 (A):
    char infix[50];
    int a = 0;

    printf("\n\n\nInfix ifadeyi giriniz: ");
    scanf("%s", infix);

    for (int i = 0; infix[i] != 0; i++) {

        if (isalnum(infix[i])) {
            postfix[a++] = infix[i];
        }

        else if (infix[i] == '(') push(infix[i]);

        else if (infix[i] == ')') {
            char ch;
            while ((ch = pop()) != '(') {
                postfix[a++] = ch;
            }
        }

        else {
            while (Oncelik(infix[i]) <= Oncelik(stack[top]) && stack[top] != '(') {
                char ch = pop(); // top--;
                if (ch != '(') {
                    postfix[a++] = ch;
                }
                else {
                    top++;
                    break;
                }
                if (top == -1) break;
            }
            push(infix[i]);
        }
    }

    while (top != -1) {
        char ch =  pop();
        postfix[a++] = ch;
    }
    postfix[a] = 0; // dizi bitirildi !


    printf("\nPostfix ifade: ");
    for (int i = 0; postfix[i] != 0; i++) {
        printf("%c ", postfix[i]);
    }
}



int Oncelik (char ch) {
    if (ch == ')') return 0;
    else if (ch == '+' || ch == '-') return 1;
    else if (ch == '*' || ch == '/') return 2;
    else if (ch == '(') return 4;
    return -1;
}




void Postfix_Hesaplama (void) { // Soru-2 (B):

    for (int i = 0; postfix[i] != 0; i++) {
        if (isalnum (postfix[i])) { // yığın'a atılacak:
            push (postfix[i] - 48); // karakterler sayıya dönüştürülüyor.
        }
        else {
            if (postfix[i] == '-') {
                int sayi2 = pop();
                int sayi1 = pop();
                push(sayi1 - sayi2);
            }
            else if (postfix[i] == '+') {
                int sayi2 = pop();
                int sayi1 = pop();
                push(sayi1 + sayi2);
            }
            else if (postfix[i] == '*') {
                int sayi2 = pop();
                int sayi1 = pop();
                push(sayi1 * sayi2);
            }
            else if (postfix[i] == '/') {
                int sayi2 = pop();
                int sayi1 = pop();
                push(sayi1 / sayi2);
            }
        }
    }
    printf("\n\n--> Islem sonucu: %d \n\n", pop());
}



void YiginBosalt (void) { // yigin'in icini bosaltiyor:
    for (int i = 0; stack[i] != 0; i++) stack[i] = 0;
    top = -1;
}
