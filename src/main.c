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
#define MAX_CHILDREN 200

typedef struct node
{
    int is_folder;
    int size;
    char *type; // "txt", "exe", "img", "vid" , "csv"
    char *name;
    char *content;         // content of the file
    struct node *next;     // next sibling
    int num_children;      // number of children
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

/**
 * @brief Searches for a node with the given name and returns it.
 * 
 * This function searches for a node with the given name in the list starting from the given head node.
 * 
 * @param head The head node of the linked list.
 * @param name The name to search for.
 * @return The node with the given name, or NULL if not found.
 */
node *find_node(node *head, char *name)
{
    // this is the current node
    node *current = head;
    // while the current node is not null
    while (current != NULL)
    {
        // if the current node has the same name as the one we are searching for then return it
        if (strcmp(current->name, name) == 0)
        {
            // return the current node
            return current;
        }
        // if we didn't find the node then go to the next one
        current = current->next;
    }
    // if we didn't find the node then return null
    return NULL;
}

//prototype of the list_children function
void list_children(node *head);


/**
 * @brief Lists the nodes in a tree structure.
 * 
 * This function recursively traverses the tree starting from the given head node and prints the nodes in a tree structure.
 * It prints each node's name and indents it based on its level in the tree.
 * If a node is a folder, it also lists its children nodes.
 * 
 * @param head The head node of the tree.
 * @param level The level of the current node in the tree.
 */
void list_nodes(node *head)
{
    // this is the current node
    node *current = head;
    // while the current node is not null
    while (current != NULL)
    {
        // indent the current node based on 1 level
        for (int i = 0; i < 1; i++)
        {
            printf("│   ");
        }

        if (current->is_folder)
        {
            // set ansi color to yellow
            printf("\033[0;33m");
            // print the current node
            printf("├ Folder: %s\n", current->name);
            // reset ansi color
            printf("\033[0m");
        }
        else
        {
        // print the current node
        printf("├ Node: %s\n", current->name);
        }

        // if the current node is a folder then list it's children
        if (current->is_folder)
        {
            //set ansi color to blue
            printf("\033[0;34m");
            // list the children of the current node
            list_children(current->children);
            // reset ansi color
            printf("\033[0m");
        }
        // go to the next node
        current = current->next;
    }
}


// list children of a node
void list_children(node *head)
{
    // this is the current node
    node *current = head;
    // while the current node is not null
    while (current != NULL)
    {
        // indent the current node based on 1 level
        for (int i = 0; i < 1; i++)
        {
            printf("│   ");
        }

        if (current->is_folder)
        {
            // set ansi color to yellow
            printf("\033[0;33m");
            // print the current node
            printf(" ├ Folder: %s\n", current->name);
            // reset ansi color
            printf("\033[0m");
        }
        else
        {
        // print the current node
        printf(" ├ Node: %s\n", current->name);
        }

        // if the current node is a folder then list it's children
        if (current->is_folder)
        {
            //set ansi color to blue
            printf("\033[0;34m");
            // list the children of the current node
            list_children(current->children);
            // reset ansi color
            printf("\033[0m");
        }
        // go to the next node
        current = current->next;
    }
}



/**
 * @brief Executes a terminal program with various options.
 *
 * This function allows the user to perform different operations on a linked list of nodes.
 * The available options include counting nodes, displaying a tree structure, adding a new node,
 * moving a node to a different parent, inspecting a node, and exiting the program.
 *
 * @param head A pointer to the head of the linked list of nodes.
 */
void terminalX(node *head)
{
    // theese are the variables for the "terminal"
    int choice, debuginfo;
    char type[50];
    int is_folder, size, level;
    char content[1000];
    node *current = head;
    node *parent = NULL;


    // this is the main loop of the "terminal"
    while (1)
    {
        printf("\n\n\n\n1. Count nodes\n2. tree nodes\n3. Add node\n4. Move node\n5. Inspect noden\n6. Current dir Node \n7. Exit\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1: // count nodes
            printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nNumber of nodes: %d\n", count_nodes(head));
            break;
        case 2: // tree nodes
            printf("\n\n\n\n\n\n\n\n\n\n\n");
            printf("Root\n");
            list_nodes(current);
            break;
        case 3: // add node
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

        case 4: // move node
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
        case 5: // inspect node
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
            printf("       Node content \n[%s]\n", node->content);
            break;
        case 6: // move between head and children
        printf("choose a node to move in: ");
        scanf("%s", name);
        printf("\n");
        parent = find_node(head, name);
        terminalX(parent);

        case 7: // exit
            printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nExiting...\n");
            return;
        default: // invalid choice
            printf("\n\n\n\n\n\n\n\n\n\nInvalid choice. Please enter a number between 1 and 7.\n");
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

    but for some reason the terminalX function doesn't want to list the nodes correctly
      Root
       ├ Node: Verry funny jokes.txt
       ├ Node: Nobromu.exe
       ├ Node: CSteam.png
       └ Node: Not-Lewd-Folder
          ├ Node: Cream.png
          ├ Node: schoolstuff.pdf
          └ Node: 2am.png
          ├ Node: schoolstuff.pdf
          └ Node: 2am.png
          └ Node: 2am.png

    so i will leave it like this for now :(
     */

    terminalX(head);

    return 0;
}