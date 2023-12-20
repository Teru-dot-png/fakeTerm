// this a program that generates a linked list of random nodes for a fake terminal

// includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// defines and typedefs
#define MAX_NAME_LENGTH 10
#define MAX_TYPE_LENGTH 3
#define MAX_SIZE 1000
#define MAX_CONTENT_LENGTH 2000

typedef struct node
{
    int is_folder;
    int size;
    char *type; // "txt", "exe", "img", "vid" , "csv"
    char *name;
    char *content;           // content of the file
    struct node *next;     // next sibling
    struct node *children; // first child
} node;                    // typedef for struct node

// function creates a new node with the given name and is_folder value
node *create_node(char *name, int is_folder, char *type, int size)
{
    // allocate memory for the new node
    node *new_node = malloc(sizeof(node));
    // allocate memory for the name,type and content
    new_node->name = malloc(MAX_NAME_LENGTH * sizeof(char));
    new_node->type = malloc(MAX_TYPE_LENGTH * sizeof(char));
    new_node->content = malloc(MAX_CONTENT_LENGTH * sizeof(char));

    // set the values for size type and name
    strcpy(new_node->name, name);
    new_node->is_folder = is_folder;
    new_node->size = size;
    strcpy(new_node->type, type);
    new_node->next = NULL;
    new_node->children = NULL;
    return new_node;
}

// function adds a node to the end of the list
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

// function counts the number of nodes in the list
int count_nodes(node *head)
{
    int count = 0;
    node *current = head;
    while (current != NULL)
    {
        count++;
        current = current->next;
    }
    return count;
}

int main(int argc, char *argv[])
{
    printf("starting program...\n");
    // Create a linked list of nodes
    printf("Creating a linked list of nodes...\n");
    node *head = NULL;

    // Add the 3 nodes to the list
    printf("Adding the nodes to the list...\n");
    printf("Adding node 1...\n");
    node *node1 = create_node("Verry funny jokes.txt", 1, "txt", 20);
    add_node(&head, node1);
    printf("Adding node 2...\n");
    node *node2 = create_node("Nobromu.exe", 1, "exe", 260);
    add_node(&head, node2);
    printf("Adding node 3...\n");
    node *node3 = create_node("CSteam.png", 1, "png", 303);
    add_node(&head, node3);

    // lets you choose to inspect the nodes
    printf("Would you like to inspect the nodes? (y/n)\n");
    char inspect;
    scanf("%c", &inspect);
    if (inspect == 'y')
    {
        while (1)
        {
            printf("------########------\n");
            printf("Would you like to... \n");
            printf(" - Number of nodes [1] \n");
            printf(" - List nodes [2] \n");
            printf(" - Exit [3] \n");
            int choice;
            scanf("%d", &choice);
            if (choice == 1)
            {
                if (head != NULL)
                {
                    printf("--------number------\n");
                    printf("Number of nodes: %d\n", count_nodes(head));
                }
                else
                {
                    printf("No nodes to count.\n");
                }
            }
            else if (choice == 2)
            {
                printf("Listing nodes...\n");
                if (head != NULL)
                {
                    node *current = head;
                    printf("--------files-------\n");
                    while (current != NULL)
                    {
                        printf(" %s", current->name);
                        printf(" - %ldKB\n", sizeof(node));
                        current = current->next;
                    }
                }
                else
                {
                    printf("No nodes to list.\n");
                }
            }
            else if (choice == 3)
            {
                printf("Exiting...\n");
                break;
            }
        }
    }

    return 0;
}