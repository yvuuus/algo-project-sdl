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
// Fonction pour échanger les données de deux nœuds

void swapData(struct Node* node1, struct Node* node2) {
    int temp = node1->data;
    node1->data = node2->data;
    node2->data = temp;
}
// Fonction pour colorier les rectangles comparés

void highlightComparison(struct Node* node1, struct Node* node2, SDL_Renderer* renderer) {

    // Sauvegarder la couleur actuelle du rendu
    SDL_Color currentColor;
    SDL_GetRenderDrawColor(renderer, &currentColor.r, &currentColor.g, &currentColor.b, &currentColor.a);
    // Couleur rouge pour la mise en évidence
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    // Dessiner les rectangles en rouge
    SDL_Rect rect1 = {node1->xpos, 400 - node1->data * 15, 35, node1->data * 15};
    SDL_Rect rect2 = {node2->xpos, 400 - node2->data * 15, 35, node2->data * 15};

    SDL_RenderFillRect(renderer, &rect1);
    SDL_RenderFillRect(renderer, &rect2);
    SDL_RenderPresent(renderer);
    SDL_Delay(1000); // Attendre 1000 millisecondes pour la visualisation

    // Rétablir la couleur précédente
    SDL_SetRenderDrawColor(renderer, currentColor.r, currentColor.g, currentColor.b, currentColor.a);

    // Effacer uniquement les rectangles comparés
    SDL_RenderFillRect(renderer, &rect1);
    SDL_RenderFillRect(renderer, &rect2);
    SDL_RenderPresent(renderer);
}


// Fonction pour trier la liste doublement chaînée par sélection

void selectionSort(struct Node* head, SDL_Renderer* renderer) {

    struct Node *i, *j, *minNode;
    // Afficher la liste avant le tri
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    struct Node* current = head;
    int xPos = 200;

    while (current != NULL) {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_Rect rect = {xPos, 400 - current->data * 15, 35, current->data * 15};
        current->xpos = xPos;
        SDL_RenderFillRect(renderer, &rect); // Couleur dans les rectangles
        xPos += 60;
        current = current->next;
    }

    SDL_RenderPresent(renderer);
    SDL_Delay(1000); // Attendre 1000 millisecondes avant le début du tri

    for (i = head; i != NULL; i = i->next) {
    minNode = i;
    for (j = i->next; j != NULL; j = j->next) {
        if (j->data < minNode->data) {
            minNode = j;
        }
    }

    // Échanger les données des nœuds
    highlightComparison(i, minNode, renderer);
    swapData(i, minNode);

    // Remplir le fond en blanc
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    // Dessiner les rectangles
    current = head;
    xPos = 200;

    while (current != NULL) {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_Rect rect = {xPos, 400 - current->data * 15, 35, current->data * 15};
        SDL_RenderFillRect(renderer, &rect);
        xPos += 60;
        current = current->next;
    }

    SDL_RenderPresent(renderer);
    SDL_Delay(1000); // Attendre 1000 millisecondes entre chaque étape
}
}

int main(int argc, char* argv[]) {

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("SDL Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Création d'une liste doublement chaînée non triée

    struct Node* head = NULL;
    appendNode(&head, 10);
    appendNode(&head, 20);
    appendNode(&head, 16);
    appendNode(&head, 18);
    appendNode(&head, 12);
    appendNode(&head, 10);
    appendNode(&head, 24);
    appendNode(&head, 14);
    printf("Liste doublement chaînée non triée\n");
    // Afficher la liste avant le tri

    struct Node* current = head;

    while (current != NULL) {

        printf("%d ", current->data);

        current = current->next;

    }

    printf("\n");

    // Tri par sélection avec visualisation
    selectionSort(head, renderer);
    printf("Liste doublement chaînée triée\n");

    // Afficher la liste après le tri
    current = head;
    while (current != NULL) {
        printf("%d ", current->data);

        current = current->next;

    }
    printf("\n");
    // Attendre que l'utilisateur ferme la fenêtre
    SDL_Delay(2000);
    int quit = 0;
    SDL_Event e;
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = 1;
            }
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;

}
//gcc src/projet.c -o bin/prog -I include -L lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf
