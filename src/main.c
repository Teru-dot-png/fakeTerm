// this a program that generates a linked list of random nodes for a fake terminal

// includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// defines and typedefs


typedef struct node {
    int is_folder;
    char *name;
    struct node *next;      // next sibling
    struct node *children; // first child
} node;                   // typedef for struct node

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






// print_default is a function that takes a node from a linked list as an argument and prints its name. 
// allowing you to customize how nodes are printed without modifying the print_nodes function itself
void print_default(node* n, int depth) {
    if (depth == 0) {
        printf("/\n");
    } else if (n->is_folder == 1) {
        for(int i = 0; i < depth; i++) {
            printf("  "); // print two spaces for each depth level
        }
        printf("|- %s\n", n->name);
    } else {
        for(int i = 0; i < depth; i++) {
            printf("  "); // print two spaces for each depth level
        }
        printf("|-- %s\n", n->name);
    }
}


// function prints the names of the nodes in the linked tree list in the style of the command "tree"
void print_nodes(node *head, print_func print, int depth) {
    if (head == NULL) {
        return;
    }

    node *current = head;
    while (current != NULL) {
        if (current->name == NULL) {
            printf("Error: Node has no name.\n");
        } else {
            print(current, depth);
            if (current->is_folder == 1) {
                print_nodes(current->children, print, depth + 1); // recursively print child nodes
            }
        }

        current = current->next;
    }
}

int main(int argc, char *argv[]) {
    node *head = NULL;
    // Add nodes to your list here
    // ...
    print_nodes(head, print_default, 0);

    return 0;
}