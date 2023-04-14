// this a program that generates a linked list of random nodes for a fake terminal

// includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
// defines and typedefs
#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

typedef struct node
{
    float x;           // x coordinates of the node
    float y;           // y coordinates of the node
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

// function generates a linked list of nodes in the structure of a linux file system starting with the main node "/" and the child nodes "home", "usr", "etc", "bin", "sbin", "var", "tmp", "opt", "lib", "lib64", "media", "mnt", "srv", "boot", "dev", "proc", "sys"
void generate_random_nodes(node **head, int num_nodes)
{
    // create the main node
    node *main_node = create_node("/", 1);
    add_node(head, main_node);

    // create the child nodes
    char *child_nodes[] = {"home", "usr", "etc", "bin", "sbin", "var", "tmp", "opt", "lib", "lib64", "media", "mnt", "srv", "boot", "dev", "proc", "sys"};
    for (int i = 0; i < 17; i++)
    {
        node *new_node = create_node(child_nodes[i], 1);
        add_node(head, new_node);
    }

    // create the random nodes inside the child nodes
    srand(time(NULL));
    for (int i = 0; i < num_nodes; i++)
    {
        int random = rand() % 17;
        node *current = *head;
        for (int j = 0; j < random; j++)
        {
            current = current->next;
        }
        node *new_node = create_node("file", 0);
        add_node(&current, new_node);
    }
}

// function prints the names of the nodes in the linked list in the style of the command "tree"
void print_nodes(node *head)
{
    if (head == NULL)
    {
        return;
    }
    else
    {
        node *current = head;
        while (current != NULL)
        {
            if (current->is_folder == 1)
            {
                printf("|- %s\n", current->name);
                print_nodes(current->next); // recursively print child nodes
            }
            else
            {
                printf("|-- %s\n", current->name);
            }
            current = current->next;
        }
    }
}

// main function
int main(int argc, char *argv[])
{
    node *head = NULL;
    generate_random_nodes(&head, 10);
    print_nodes(head);

    return 0;
}
