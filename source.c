#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "compare.h"

#define TOP "top"
#define INSERT "insert"
#define POP "pop"
#define MAXSIZE 100

/*
	structura ce defineste un element din coada de prioritati,
	care este implementata sub forma de lista simplu inlantuita
	- value - valoarea unui element din coada cu prioritati
	- priority - valoarea prioritatii unui element din coada
	- next - pointerul catre urmatorul element din coada
*/
typedef struct node {
	char *value;
	int priority;
	struct node *next;
} priorityQueue;

priorityQueue *insert (priorityQueue *queue, char *element, int priority) {
	priorityQueue *toAdd = (priorityQueue *) malloc (sizeof(priorityQueue));
	if (toAdd == NULL) {
		free(toAdd);
		exit(ENOMEM);
	}
	toAdd->priority = priority;
	toAdd->value = (char *) malloc (MAXSIZE * sizeof(char));
	if (toAdd->value == NULL) {
		free(toAdd->value);
		free(toAdd);
		exit(ENOMEM);
	}
	strcpy(toAdd->value, element);
	toAdd->next = NULL;
	if (queue == NULL)
		return toAdd;
	if (compare(toAdd->priority, queue->priority) > 0) {
		toAdd->next = queue;
		queue = toAdd;
		return queue;
	}
	priorityQueue *aux = queue;
	while (aux->next != NULL
			&& compare(toAdd->priority, aux->next->priority) < 0) {
		aux = aux->next;
	}
	toAdd->next = aux->next;
	aux->next = toAdd;
	return queue;
}

void pop (priorityQueue **queue) {
	if (queue != NULL) {
		priorityQueue *aux = (*queue);
		(*queue) = (*queue)->next;
		free(aux->value);
		free(aux);
	}
}

char *top (priorityQueue *queue) {
	if (queue != NULL)
		return queue->value;
	return NULL;
}

void print (priorityQueue *queue) {
	while (queue != NULL) {
		printf("%s %d\n", queue->value, queue->priority);
		queue = queue->next;
	}
}

int size (priorityQueue *queue) {
	int sum = 0;
	while (queue != NULL) {
		++sum;
		queue = queue->next;
	}
	return sum;
}

void free_queue (priorityQueue *queue) {
	while (queue != NULL) {
		free(queue->value);
		priorityQueue *node = queue;
		queue = queue->next;
		free(node);
	}
}

int main (int argc, char **argv) {
	priorityQueue *queue = NULL;
	char *command = (char *) malloc (MAXSIZE * sizeof(char));
	if (command == NULL) {
		free(command);
		exit(ENOMEM);
	}
	if (argc > 1) {
		for (int i = 1; i < argc; ++i) {
			FILE *file = fopen(argv[i], "r");
			if (file == NULL) {
				continue;
			}
			while (fgets(command, MAXSIZE, file) != NULL) {
				command[strlen(command) - 1] = '\0';
				if (strncmp(command, INSERT, 6) == 0) {
					strtok(command, " ");
					char *name = strtok(NULL, " ");
					char *priority_string = strtok(NULL, " ");
					if (priority_string == NULL)
						continue;
					if (strtok(NULL, " ") != NULL)
						continue;
					int priority = atoi(priority_string);
					queue = insert(queue, name, priority);
				} else if (strcmp(command, TOP) == 0) {
					if (queue != NULL)
						printf("%s\n", top(queue));
				} else if (strcmp(command, POP) == 0) {
					if (queue != NULL)
						pop(&queue);
				}
			}
			fclose(file);
		}
	} else {
		while (fgets(command, MAXSIZE, stdin) != NULL) {
			command[strlen(command) - 1] = '\0';
				if (strncmp(command, INSERT, 6) == 0) {
					strtok(command, " ");
					char *name = strtok(NULL, " ");
					char *priority_string = strtok(NULL, " ");
					if (priority_string == NULL)
						continue;
					if (strtok(NULL, " ") != NULL)
						continue;
					int priority = atoi(priority_string);
					queue = insert(queue, name, priority);
				} else if (strcmp(command, TOP) == 0) {
					if (queue != NULL)
						printf("%s\n", top(queue));
				} else if (strcmp(command, POP) == 0) {
					if (queue != NULL)
						pop(&queue);
				}
		}
	}
	free(command);
	free_queue(queue);
	return 0;
}