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
    SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);

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

 // Function to render text
void renderText(SDL_Renderer* renderer, int x, int y, TTF_Font* font, int value) {
    SDL_Color textColor = {255, 255, 255, 255};
    char numberText[10];  // Assuming a maximum of 10 characters for the number
    snprintf(numberText, sizeof(numberText), "%d", value);

    SDL_Surface* textSurface = TTF_RenderText_Solid(font, numberText, textColor);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

    SDL_Rect textRect = {x, y, 30, 20};  // Adjust the position and size as needed
    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
}

void rendertext(SDL_Renderer* renderer, int x, int y, TTF_Font* font, const char* text, SDL_Color textColor) {

    SDL_Surface* textSurface = TTF_RenderText_Blended(font, text, textColor);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

    SDL_Rect textRect = {x, y, textSurface->w, textSurface->h};
    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
}

// Fonction pour trier la liste doublement chaînée par sélection

void selectionSort(struct Node* head, SDL_Renderer* renderer,TTF_Font* font) {

    struct Node *i, *j, *minNode;
    // Afficher la liste avant le tri
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    struct Node* current = head;
    int xPos = 200;

    while (current != NULL) {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_Rect rect = {xPos, 400 - current->data * 15, 35, current->data * 15};
        current->xpos = xPos;
        SDL_RenderFillRect(renderer, &rect); // Couleur dans les rectangles
        renderText(renderer, xPos, 410, font, current->data);
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
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Dessiner les rectangles
    current = head;
    xPos = 200;

    while (current != NULL) {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_Rect rect = {xPos, 400 - current->data * 15, 35, current->data * 15};
        SDL_RenderFillRect(renderer, &rect);
        renderText(renderer, xPos, 410, font, current->data);
        xPos += 60;
        current = current->next;
    }

    SDL_RenderPresent(renderer);
    SDL_Delay(1000); // Attendre 1000 millisecondes entre chaque étape
}
}
int isMouseOverButton(int mouseX, int mouseY, SDL_Rect buttonRect) {
    return mouseX >= buttonRect.x && mouseX <= buttonRect.x + buttonRect.w &&
           mouseY >= buttonRect.y && mouseY <= buttonRect.y + buttonRect.h;
}
int main(int argc, char* argv[]) {

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("SDL Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);


    TTF_Init();
    TTF_Font* font = TTF_OpenFont("bin\\arial.ttf", 24);
    SDL_Event e;
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


    // Create "Start" button
    SDL_Rect buttonRect = {350, 500, 100, 50};
    SDL_Color buttonColor = {100, 100, 100, 255};

    SDL_SetRenderDrawColor(renderer, buttonColor.r, buttonColor.g, buttonColor.b, buttonColor.a);
    SDL_RenderFillRect(renderer, &buttonRect);

    SDL_Color textColor = {255, 0, 255, 255};
    rendertext(renderer, buttonRect.x + 15, buttonRect.y + 15, font, "Start", textColor);

    // Render "SELECTION CODE" in the middle
    SDL_Color selectionTextColor = {150, 100, 150, 255};
    rendertext(renderer, 280, 220, font, "SELECTION SORT", selectionTextColor);

    SDL_RenderPresent(renderer);

    // Event loop
    int sortingStarted = 0;
    int quit = 0;
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = 1;
            } else if (e.type == SDL_MOUSEBUTTONDOWN) {
                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);

                if (isMouseOverButton(mouseX, mouseY, buttonRect) && !sortingStarted) {
                    selectionSort(head, renderer, font);
                    sortingStarted = 1;
                }
            }
        }
    }

    printf("\n");
    // Attendre que l'utilisateur ferme la fenêtre
    SDL_Delay(2000);
    
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = 1;
            }
        }
    }

    TTF_CloseFont(font);
    TTF_Quit();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;

}
//gcc src/projet.c -o bin/prog -I include -L lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf
