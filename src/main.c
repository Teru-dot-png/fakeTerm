// this a test for file node visualization

// includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <SDL2/SDL.h>
// defines and typedefs
#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

typedef struct node
{
    float x;           // x  coordinates of the node
    float y;           // z coordinates of the node
    char *name;        // name of the file or folder
    int is_folder;     // 1 if folder, 0 if file
    struct node *next; // pointer to the next node
} node;                // typedef for struct node

// function creates a new node with the given name and is_folder value
node *create_node(char *name, int is_folder)
{
    node *new_node = malloc(sizeof(node));
    new_node->name = malloc(strlen(name) + 1);
    strcpy(new_node->name, name);
    new_node->is_folder = is_folder;
    new_node->next = NULL;
    return new_node;
}

// function adds a node to the end of the linked list
void add_node(node **head, node *new_node)
{
    if (*head == NULL)
    {
        *head = new_node;
    }
    else
    {
        node *current = *head;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = new_node;
    }
}

// function generates a linked list of random nodes with the given number of nodes
void generate_random_nodes(node **head, int num_nodes)
{
    char *filenames[] = {"file1", "file2", "file3", "file4", "file5", "file6", "file7", "file8", "file9", "file10"};
    char *folder_names[] = {"folder1", "folder2", "folder3", "folder4", "folder5", "folder6", "folder7", "folder8", "folder9", "folder10"};
    srand(time(NULL));
    for (int i = 0; i < num_nodes; i++)
    {
        int is_folder = rand() % 2;
        char *name;
        if (is_folder)
        {
            name = folder_names[rand() % 10];
        }
        else
        {
            name = filenames[rand() % 10];
        }
        node *new_node = create_node(name, is_folder);
        add_node(head, new_node);
    }
}
// function prints the names of the nodes in the linked list
void print_nodes(node *head)
{
    node *current = head;
    while (current != NULL)
    {
        printf("%s", current->name);
        if (current->is_folder)
        {
            printf("/");
        }
        printf("");
        current = current->next;
    }
}

// main function
int main(int argc, char *argv[])
{
    node *head = NULL;
    generate_random_nodes(&head, 10);
    print_nodes(head);

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Event event;
    int running = 1;
    int i;

    srand(time(NULL)); // seed random number generator with current time

    // initialize SDL video subsystem
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        fprintf(stderr, "Could not initialize SDL: %s\n", SDL_GetError());
        exit(1);
    }

    // create a window
    window = SDL_CreateWindow("Node Visualization", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    if (!window)
    {
        fprintf(stderr, "Could not create window: %s\n", SDL_GetError());
        exit(1);
    }

    // create a renderer for the window
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer)
    {
        fprintf(stderr, "Could not create renderer: %s\n", SDL_GetError());
        exit(1);
    }

    // generate random node positions and store in linked list
    node *current = head;
    while (current != NULL)
    {
        current->x = (float)(rand() % WINDOW_WIDTH);
        current->y = (float)(rand() % WINDOW_HEIGHT);
        current = current->next;
    }

    // render node and connections
    while (running)
    {
        // process events
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = 0;
            }
        }

        // clear screen
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        // render nodes
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        node *current = head;
        while (current != NULL)
        {
            SDL_Rect rect = {(int)current->x - 5, (int)current->y - 5, 10, 10};
            SDL_RenderDrawRect(renderer, &rect);
            current = current->next;
        }

        // present renderer to window
        SDL_RenderPresent(renderer);
    }

    // cleanup
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
