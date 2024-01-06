#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>


// Structure pour représenter un nœud de la liste doublement chaînée

struct Node {
    int data;
    int xpos;
    struct Node* prev;
    struct Node* next;
};
// Fonction pour créer un nouveau nœud
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}
// Fonction pour ajouter un nœud à la fin de la liste doublement chaînée

void appendNode(struct Node** headRef, int data) {
    struct Node* newNode = createNode(data);
    if (*headRef == NULL) {
        *headRef = newNode;
    } else {
        struct Node* current = *headRef;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
        newNode->prev = current;
    }
}


}
//gcc src/projet.c -o bin/prog -I include -L lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf
