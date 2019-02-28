#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define TOP "top"
#define INSERT "insert"
#define POP "pop"

typedef struct node {
    int value;
    int priority;
    struct node *next;

} priorityQueue;

priorityQueue *insert (priorityQueue *queue, char *element) {
    return NULL;
}

priorityQueue *pop (priorityQueue *queue) {
    return NULL;
}

char* top (priorityQueue *queue) {
    return NULL;
}

void print (priorityQueue *queue) {

}

int main (int argc, char **argv) {
    priorityQueue *queue = (priorityQueue*) malloc (sizeof(priorityQueue));
    if (queue == NULL) {
        printf("Memory allocation of the priority queue with malloc failed...\n");
        exit(ENOMEM);
    }
    if (argc > 1) {
        for (int i = 1; i < argc; ++i) {

        }
    } else {

    }
    free(queue);
    return 0;
}