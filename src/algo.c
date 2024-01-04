#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_ttf.h>

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



//gcc src/algo.c -o bin/prog -I include -L lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf