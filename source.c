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
 * structura ce defineste un element din coada de prioritati,
 * care este implementata sub forma de lista simplu inlantuita
 * - value - valoarea unui element din coada cu prioritati
 * - priority - valoarea prioritatii unui element din coada
 * - next - pointerul catre urmatorul element din coada
 */
struct priorityQueue {
	char *value;
	int priority;
	struct priorityQueue *next;
};

/*
 * functie de adaugare in coada a unui element, care returneaza coada
 * cu elementul adaugat
 * - queue - coada in care adaugam elementul
 * - element - ce adaugam in coada
 * - priority - prioritatea elementului in coada
 */

struct priorityQueue *insert(struct priorityQueue *queue,
	char *element, int priority)
{
	struct priorityQueue *toAdd =
		(struct priorityQueue *) malloc(sizeof(struct priorityQueue));

	if (toAdd == NULL) {
		free(toAdd);
		exit(ENOMEM);
	}
	toAdd->priority = priority;
	toAdd->value = (char *) malloc(MAXSIZE * sizeof(char));
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
	struct priorityQueue *aux = queue;

	while (aux->next != NULL
			&& compare(toAdd->priority, aux->next->priority) < 0) {
		aux = aux->next;
	}
	toAdd->next = aux->next;
	aux->next = toAdd;
	return queue;
}

/*
 * functie ce sterge primul element din coada
 * - queue = coada din care stergem primul element
 */
void pop(struct priorityQueue **queue)
{
	if (queue != NULL) {
		struct priorityQueue *aux = (*queue);

		(*queue) = (*queue)->next;
		free(aux->value);
		free(aux);
	}
}

/*
 * functie ce returneaza primul element din coada
 * - queue = coada din se returneaza primul element al acesteia
 */
char *top(struct priorityQueue *queue)
{
	if (queue != NULL)
		return queue->value;
	return NULL;
}

void print(struct priorityQueue *queue)
{
	while (queue != NULL) {
		printf("%s %d\n", queue->value, queue->priority);
		queue = queue->next;
	}
}

/*
 * functie ce returneaza marimea cozii
 * - queue = coada a carei marimi este returnata
 */
int size(struct priorityQueue *queue)
{
	int sum = 0;

	while (queue != NULL) {
		++sum;
		queue = queue->next;
	}
	return sum;
}

/*
 * functie ce elibereaza memoria ocupata de coada
 * - queue = coada pentru care trebuie sa eliberam memoria alocata acesteia
 */
void free_queue(struct priorityQueue *queue)
{
	while (queue != NULL) {
		free(queue->value);
		struct priorityQueue *node = queue;

		queue = queue->next;
		free(node);
	}
}

int main(int argc, char **argv)
{
	struct priorityQueue *queue = NULL;
	char *command = (char *) malloc(MAXSIZE * sizeof(char));

	if (command == NULL) {
		free(command);
		exit(ENOMEM);
	}
	if (argc > 1) {
		for (int i = 1; i < argc; ++i) {
			FILE *file = fopen(argv[i], "r");

			if (file == NULL)
				continue;
			while (fgets(command, MAXSIZE, file) != NULL) {
				command[strlen(command) - 1] = '\0';
				if (strncmp(command, INSERT, 6) == 0) {
					strtok(command, " ");
					char *name = strtok(NULL, " ");

					char *priority_string
							= strtok(NULL, " ");

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

					char *priority_string
							= strtok(NULL, " ");

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