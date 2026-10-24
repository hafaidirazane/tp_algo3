
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int customerNumber;
    struct Node *next;
} Node;

typedef struct Queue {
    Node *front;
    Node *rear;
} Queue;

/* Initialize the queue */
void initQueue(Queue *q) {
    q->front = NULL;
    q->rear = NULL;
}

/* Check if the queue is empty */
int isEmpty(Queue q) {
    return q.front == NULL;
}

/* Add a customer to the queue */
void enqueue(Queue *q, int number) {
    Node *newNode = malloc(sizeof(Node));

    if (newNode == NULL) {
        printf("Memory allocation error!\n");
        return;
    }

    newNode->customerNumber = number;
    newNode->next = NULL;

    if (isEmpty(*q)) {
        q->front = newNode;
        q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }

    printf("Customer %d arrived and got a token.\n", number);
}

/* Remove and return the front customer */
int dequeue(Queue *q) {
    if (isEmpty(*q)) {
        printf("Queue is empty!\n");
        return -1;
    }

    Node *temp = q->front;
    int number = temp->customerNumber;

    q->front = q->front->next;

    if (q->front == NULL) {
        q->rear = NULL;
    }

    free(temp);
    return number;
}

/* Return the front customer without removing them */
int peek(Queue q) {
    if (isEmpty(q)) {
        printf("Queue is empty!\n");
        return -1;
    }

    return q.front->customerNumber;
}

/* Display all customers in the queue */
void displayQueue(Queue q) {
    if (isEmpty(q)) {
        printf("Queue is empty.\n");
        return;
    }

    Node *current = q.front;

    printf("Customers waiting: ");

    while (current != NULL) {
        printf("%d ", current->customerNumber);
        current = current->next;
    }

    printf("\n");
}

/* Free all remaining nodes */
void freeQueue(Queue *q) {
    while (!isEmpty(*q)) {
        dequeue(q);
    }
}

int main(void) {
    Queue q;
    int choice, number;

    initQueue(&q);

    do {
        printf("\n--- BANK QUEUE MENU ---\n");
        printf("1. Add a customer\n");
        printf("2. Serve a customer\n");
        printf("3. Show the first customer\n");
        printf("4. Display the queue\n");
        printf("5. Simulate bank example\n");
        printf("0. Exit\n");
        printf("Your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input!\n");
            freeQueue(&q);
            return 1;
        }

        switch (choice) {
            case 1:
                printf("Enter customer number: ");

                if (scanf("%d", &number) != 1) {
                    printf("Invalid input!\n");
                    freeQueue(&q);
                    return 1;
                }

                enqueue(&q, number);
                break;

            case 2:
                number = dequeue(&q);

                if (number != -1) {
                    printf("Customer %d is being served.\n",
                           number);
                }
                break;

            case 3:
                number = peek(q);

                if (number != -1) {
                    printf("First customer: %d\n", number);
                }
                break;

            case 4:
                displayQueue(q);
                break;

            case 5:
                freeQueue(&q);

                enqueue(&q, 101);
                enqueue(&q, 102);

                number = dequeue(&q);
                if (number != -1)
                    printf("Customer %d is being served.\n",
                           number);

                enqueue(&q, 103);

                while (!isEmpty(q)) {
                    number = dequeue(&q);
                    printf("Customer %d is being served.\n",
                           number);
                }

                printf("Queue is empty.\n");
                break;

            case 0:
                printf("Exiting program...\n");
                break;

            default:
                printf("Invalid choice!\n");
        }

    } while (choice != 0);

    freeQueue(&q);
    return 0;
}
