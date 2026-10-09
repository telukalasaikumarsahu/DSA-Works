#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX 100

typedef struct {
    char items[MAX];
    int top;
} Stack;

void initStack(Stack *s) {
    s->top = -1;
}

int isEmpty(const Stack *s) {
    return s->top == -1;
}

int isFull(const Stack *s) {
    return s->top == MAX - 1;
}

void push(Stack *s, char value) {
    if (!isFull(s))
        s->items[++s->top] = value;
}

char pop(Stack *s) {
    return isEmpty(s) ? '\0' : s->items[s->top--];
}

char peek(const Stack *s) {
    return isEmpty(s) ? '\0' : s->items[s->top];
}

int isOperator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' ||
           ch == '/' || ch == '^';
}

int precedence(char ch) {
    switch (ch) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '^':
            return 3;
        default:
            return 0;
    }
}

int isRightAssociative(char ch) {
    return ch == '^';
}

int infixToPostfix(const char infix[], char postfix[]) {
    Stack stack;
    int j = 0;

    initStack(&stack);

    for (int i = 0; infix[i] != '\0'; i++) {
        char ch = infix[i];

        if (isspace((unsigned char)ch))
            continue;

        if (isalnum((unsigned char)ch)) {
            postfix[j++] = ch;
        }
        else if (ch == '(') {
            push(&stack, ch);
        }
        else if (ch == ')') {
            while (!isEmpty(&stack) && peek(&stack) != '(')
                postfix[j++] = pop(&stack);

            if (isEmpty(&stack))
                return 0;

            pop(&stack);
        }
        else if (isOperator(ch)) {
            while (!isEmpty(&stack) && peek(&stack) != '(' &&
                   (precedence(peek(&stack)) > precedence(ch) ||
                    (precedence(peek(&stack)) == precedence(ch) &&
                     !isRightAssociative(ch)))) {
                postfix[j++] = pop(&stack);
            }

            push(&stack, ch);
        }
        else {
            return 0;
        }
    }

    while (!isEmpty(&stack)) {
        if (peek(&stack) == '(')
            return 0;

        postfix[j++] = pop(&stack);
    }

    postfix[j] = '\0';
    return 1;
}

int main(void) {
    char infix[MAX], postfix[MAX];

    printf("Enter an infix expression: ");
    fgets(infix, sizeof(infix), stdin);
    infix[strcspn(infix, "\n")] = '\0';

    if (infixToPostfix(infix, postfix))
        printf("Postfix expression: %s\n", postfix);
    else
        printf("Invalid expression. Check operators and parentheses.\n");

    return 0;
}