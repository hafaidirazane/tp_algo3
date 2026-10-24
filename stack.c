
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct Stack {
    Node *top;
} Stack;

void initStack(Stack *s) {
    s->top = NULL;
}

int isEmpty(Stack s) {
    return s.top == NULL;
}

int push(Stack *s, int value) {
    Node *newNode = malloc(sizeof(Node));

    if (newNode == NULL)
        return 0;

    newNode->data = value;
    newNode->next = s->top;
    s->top = newNode;

    return 1;
}

int pop(Stack *s, int *value) {
    if (isEmpty(*s))
        return 0;

    Node *temp = s->top;
    *value = temp->data;

    s->top = temp->next;
    free(temp);

    return 1;
}

int peek(Stack s, int *value) {
    if (isEmpty(s))
        return 0;

    *value = s.top->data;
    return 1;
}

int stackSize(Stack s) {
    int count = 0;
    Node *current = s.top;

    while (current != NULL) {
        count++;
        current = current->next;
    }

    return count;
}

void display(Stack s) {
    Node *current = s.top;

    if (isEmpty(s)) {
        printf("Stack is empty\n");
        return;
    }

    printf("Stack elements (top to bottom):\n");

    while (current != NULL) {
        printf("%d\n", current->data);
        current = current->next;
    }
}

int evalExp(char arr[], int *valid) {
    Stack s;
    initStack(&s);

    int i = 0;
    int a, b, result;
    *valid = 0;

    while (arr[i] != '\0') {

        if (arr[i] == ' ' || arr[i] == '\t') {
            i++;
            continue;
        }

        if (arr[i] >= '0' && arr[i] <= '9') {
            if (!push(&s, arr[i] - '0')) {
                while (!isEmpty(s))
                    pop(&s, &result);
                return 0;
            }
        }

        else if (arr[i] == '+' || arr[i] == '-' ||
                 arr[i] == '*' || arr[i] == '/') {

            if (!pop(&s, &b) || !pop(&s, &a)) {
                while (!isEmpty(s))
                    pop(&s, &result);
                return 0;
            }

            switch (arr[i]) {
                case '+':
                    result = a + b;
                    break;

                case '-':
                    result = a - b;
                    break;

                case '*':
                    result = a * b;
                    break;

                case '/':
                    if (b == 0) {
                        while (!isEmpty(s))
                            pop(&s, &result);
                        return 0;
                    }
                    result = a / b;
                    break;
            }

            if (!push(&s, result)) {
                while (!isEmpty(s))
                    pop(&s, &result);
                return 0;
            }
        }

        else {
            while (!isEmpty(s))
                pop(&s, &result);
            return 0;
        }

        i++;
    }

    if (stackSize(s) == 1) {
        pop(&s, &result);
        *valid = 1;
        return result;
    }

    while (!isEmpty(s))
        pop(&s, &result);

    return 0;
}

int main(void) {
    Stack s;
    initStack(&s);

    int k;
    int value;
    int valid;
    char ex[100];

    do {
        printf("\n1. Push\n");
        printf("2. Pop\n");
        printf("3. Display\n");
        printf("4. Evaluate Postfix\n");
        printf("5. Exit\n");
        printf("Your choice: ");

        if (scanf("%d", &k) != 1)
            break;

        switch (k) {
            case 1:
                printf("Enter an integer: ");

                if (scanf("%d", &value) != 1) {
                    printf("Invalid input\n");
                    while (getchar() != '\n');
                    break;
                }

                if (push(&s, value))
                    printf("Element pushed successfully\n");
                else
                    printf("Memory allocation failed\n");

                break;

            case 2:
                if (pop(&s, &value))
                    printf("Popped: %d\n", value);
                else
                    printf("Stack is empty\n");

                break;

            case 3:
                display(s);
                break;

            case 4:
                printf("Enter postfix expression: ");

                if (scanf(" %99[^\n]", ex) != 1) {
                    printf("Invalid input\n");
                    break;
                }

                value = evalExp(ex, &valid);

                if (valid)
                    printf("Result = %d\n", value);
                else
                    printf("Invalid postfix expression!\n");

                break;

            case 5:
                printf("Goodbye!\n");
                break;

            default:
                printf("Incorrect choice\n");
        }

    } while (k != 5);

    while (pop(&s, &value));

    return 0;
}

