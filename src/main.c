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
    char *content;         // content of the file
    struct node *next;     // next sibling
    struct node *children; // first child
} node;                    // typedef for struct node

// function creates a new node with the given name and is_folder value plus a random type and size you wish
node *create_node(char *name, int is_folder, char *type, int size, char *content)
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

// this will move a node from one parent to another
void move_node(node **head, node *parent, node *child)
{
    // Remove child from the list
    if (*head == child)
    {
        *head = child->next;
    }
    else
    {
        node *current = *head;
        while (current != NULL && current->next != child)
        {
            current = current->next;
        }
        if (current != NULL)
        {
            current->next = child->next;
        }
    }

    // Add child to parent's children
    child->next = parent->children;
    parent->children = child;
}

// this function will search for  a node with the given name and return it
node *find_node(node *head, char *name)
{
    node *current = head;
    while (current != NULL)
    {
        if (strcmp(current->name, name) == 0)
        {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void list_nodes(node *current, int level, int is_last, int debug)
{
    if (current == NULL)
    {
        if (debug)
        {
            printf("Debug: current is NULL\n");
        }
        return;
    }

    if (debug)
    {
        printf("Debug: current->name = %s, level = %d, is_last = %d\n", current->name, level, is_last);
    }

    for (int i = 0; i < level - 1; i++)
    {
        printf("│   "); // Indentation to show the level of the node
    }
    if (level > 0)
    {
        printf(is_last && current->next == NULL ? "└ " : "├ ");
    }
    printf("Node: %s\n", current->name);

    // Recursively print the children of the node, if children exist
    if (current->children != NULL)
    {
        if (debug)
        {
            printf("Debug: current->children is not NULL\n");
        }
        node *child = current->children;
        while (child != NULL)
        {
            if (debug)
            {
                printf("Debug: child->name = %s\n", child->name);
            }
            list_nodes(child, level + 1, child->next == NULL, debug);
            child = child->next; // Update child pointer to child->next
        }
    }
    else
    {
        if (debug)
        {
            printf("Debug: current->children is NULL\n");
        }
    }

    // Recursively print the siblings of the node
    if (current->next != NULL && !is_last)
    {
        if (debug)
        {
            printf("Debug: current->next is not NULL and is_last is false\n");
        }
        list_nodes(current->next, level, current->next->next == NULL, debug);
    }
    else
    {
        if (debug)
        {
            printf("Debug: current->next is NULL or is_last is true\n");
        }
    }
}

// this function will simulate a terminal that will let you navigate through the nodes and inspect them plus it will let you create new nodes
void terminalX(node *head)
{
    int choice, debuginfo;
    char type[50];
    int is_folder, size, level;
    char content[1000];

    while (1)
    {
        printf("\n\n\n\n1. Count nodes\n2. List nodes\n3. Add node\n4. Move node\n5. Inspect node\n6. Exit\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nNumber of nodes: %d\n", count_nodes(head));
            break;
        case 2:
            printf("\n\n\n\n\n\n\n\n\n\n\n");
            printf("Enter a level of depth: ");
            scanf("%d", &level);
            printf("do you want to see the debug info (1 for yes, 0 for no): ");
            scanf("%d", &debuginfo);
            list_nodes(head, level, 0, debuginfo);
            break;
        case 3:
            printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nCreating\n");
            // ask for the name of the node
            printf("Enter node name: ");
            char name[MAX_NAME_LENGTH];
            scanf("%s", name);

            printf("Is it a folder (1 for yes, 0 for no): ");
            scanf("%d", &is_folder);

            // if it is not a folder then ask for the type and content
            if (!is_folder)
            {
                printf("Enter node type: ");
                scanf("%s", type);
                printf("Enter node content: ");
                scanf("%s", content);
            }

            // size generation form 1 to 1000
            printf("generating a random size...\n");
            srand(time(NULL));
            size = rand() % MAX_SIZE + 1;
            printf("Size generated: %d\n", size);

            // create the node and add it to the list
            node *new_node = create_node(name, is_folder, type, size, content);
            add_node(&head, new_node);
            printf("Node added successfully.\n");
            break;

        case 4:
            printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nMoving\n");

            printf("Enter the name of the node you want to move: ");
            scanf("%s", name);
            node *child = find_node(head, name);
            if (child == NULL)
            {
                printf("Node not found.\n");
                break;
            }

            printf("Enter the name of the parent node: ");
            scanf("%s", name);
            node *parent = find_node(head, name);
            if (parent == NULL)
            {
                printf("Parent node not found.\n");
                break;
            }

            move_node(&head, parent, child);
            printf("Node moved successfully.\n");
            break;
        case 5:
            printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\ninspect\n");
            printf("Enter the name of the node you want to inspect: ");
            scanf("%s", name);
            printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\nCONTENT\n");
            node *node = find_node(head, name);
            if (node == NULL)
            {
                printf("Node not found.\n");
                break;
            }
            printf("Node name: %s\n", node->name);
            printf("Node type: %s\n", node->type);
            printf("Node size: %d\n", node->size);
            printf("Node content: %s\n", node->content);
            break;

        case 6:
            printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nExiting...\n");
            return;
        default:
            printf("\n\n\n\n\n\n\n\n\n\nInvalid choice. Please enter a number between 1 and 4.\n");
        }
    }
}

int main(int argc, char *argv[])
{
    printf("starting program...\n");
    // Create a linked list of nodes
    printf("Creating a linked list of nodes...\n");
    node *head = NULL;

    // Add the 3 random nodes to the list
    printf("Adding the nodes to the list...\n");
    printf("Adding node 1...\n");
    node *node1 = create_node("Verry funny jokes.txt", 0, "txt", 20, "This is a very funny joke");
    add_node(&head, node1);
    printf("Adding node 2...\n");
    node *node2 = create_node("Nobromu.exe", 0, "exe", 2600, "i can't believe it's not a virus");
    add_node(&head, node2);
    printf("Adding node 3...\n");
    node *node3 = create_node("CSteam.png", 0, "png", 303, "This is a steam logo but you can't see it");
    add_node(&head, node3);

    // Add the 3 random nodes to the list inside a folder
    printf("Adding the nodes to the list inside a folder...\n");
    printf("Adding node 4(Folder)...\n");
    node *node4 = create_node("Not-Lewd-Folder", 1, "", 0, "");
    add_node(&head, node4);
    printf("Adding Content in Folder\n");
    printf("Adding node 5...\n");
    node *node5 = create_node("2am.png", 0, "png", 303, "funny meme");
    add_node(&head, node5);
    printf("Adding node 6...\n");
    node *node6 = create_node("schoolstuff.pdf", 0, "pdf", 153, "This is a pdf file");
    add_node(&head, node6);
    printf("Adding node 7...\n");
    node *node7 = create_node("Cream.png", 0, "png", 1000, "why is this here?");
    add_node(&head, node7);

    printf("Moving nodes...\n");
    printf("Moving node 5...\n");
    move_node(&head, node4, node5);
    printf("Moving node 6...\n");
    move_node(&head, node4, node6);
    printf("Moving node 7...\n");
    move_node(&head, node4, node7);
    /*
    this is the tree structure of the nodes
    Root
     ├── Verry funny jokes.txt
     ├── Nobromu.exe
     ├── CSteam.png
     └── Not-Lewd-Folder
         ├── 2am.png
         ├── schoolstuff.pdf
         └── Cream.png

     */

    terminalX(head);

    return 0;
}