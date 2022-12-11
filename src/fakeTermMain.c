#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_INPUT_LENGTH 256
#define MAX_FILES 10
#define MAX_FOLDERS 10

//! yes there is a stupid ammount of comments
//! excuse my adhd this is my workflow

// Data structure for a fake file
struct File
{
    char *name; // The Name of the file
    char *type; // The type of the file (such as "text" or "image")
    int size;   // The size of the file in bytes
    char *text; // The contents of the file (if it is a text file)
};

// Data structure for a fake folder
struct FakeFolder
{
    char *name;         // The name of the folder
    struct File *files; // An array of File objects that are inside the folder
    int num_files;      // The number of files in the folder
};

// Global array of File objects
struct File files[MAX_FILES];
int num_files = 0; // Keep track of the number of files in the array

// Global array of FakeFolder objects
struct FakeFolder fake_folders[MAX_FOLDERS];
int num_fake_folders = 0; // Keep track of the number of folders in the array

// Function to add a fake file to the global array of files
void add_file(char *name, char *type, int size, char *text)
{
    // Check if the array is full
    if (num_files == MAX_FILES)
    {
        printf("Error: Too many files\n");
        return;
    }

    // Create a new File object
    struct File file;
    file.name = name;
    file.type = type;
    file.size = size;
    file.text = text;

    // Add the File object to the global array of files
    files[num_files] = file;
    num_files++;
}

// Function to get a pointer to a File object by its name
struct File *get_file_by_name(char *name)
{
    // Loop through the array of File objects
    for (int i = 0; i < num_files; i++)
    {
        // Get a pointer to the current File object
        struct File *file = &files[i];

        // Check if the name of the current file matches the given name
        if (strcmp(file->name, name) == 0)
        {
            // Return a pointer to the File object
            return file;
        }
    }
    return NULL;
}

// Function to exit the program
void exit_program()
{

    // flavor fake loading
    printf("Shuting down os...\n");
    sleep(1);
    printf("Truning off analog math nodes\n");
    sleep(1);
    printf("Goodbye...\n");
    sleep(1);

    // actuall exit
    exit(0);
}

// Function to list the contents of the current directory
void list_directory_contents()
{
    // Print the names and types of all fake files
    for (int i = 0; i < num_files; i++)
    {
        struct File file = files[i];
        printf("%s (%s)\n", file.name, file.type);
    }

    // Print the names of all fake folders
    for (int i = 0; i < num_fake_folders; i++)
    {
        struct FakeFolder fake_folder = fake_folders[i];
        printf("%s (folder)\n", fake_folder.name);
    }
}

void print_file_contents(char *filename)
{
    // Get a pointer to the File object with the given name
    struct File *file = get_file_by_name(filename);

    // Check if a File object with the given name was found
    if (file == NULL)
    {
        printf("Error: File not found\n");
        return;
    }

    // Check if the File object is a text file
    if (strcmp(file->type, "text") == 0)
    {
        // Print the contents of the text file
        printf("%s\n", file->text);
    }
    else
    {
        // Print a generic message for non-text files
        printf("This is the contents of a %s file\n", file->type);
    }
}

void add_fake_folder(char *name)
{
    if (num_fake_folders == MAX_FOLDERS)
    {
        printf("Error: Too many folders\n");
        return;
    }

    // Create a new FakeFolder object
    struct FakeFolder fake_folder;
    fake_folder.name = name;
    fake_folder.files = NULL;
    fake_folder.num_files = 0;

    // Add the FakeFolder object to the global array of fake folders
    fake_folders[num_fake_folders] = fake_folder;
    num_fake_folders++;
}

// Function to add a fake file to a fake folder
void add_file_to_fake_folder(struct FakeFolder *fake_folder, char *name, char *type, int size, char *text)
{
    // Check if the folder is full
    if (fake_folder->num_files == MAX_FILES)
    {
        printf("Error: Too many files in folder\n");
        return;
    }

    // Check if the folder already has an array of File objects
    if (fake_folder->files == NULL)
    {
        // Allocate memory for an array of File objects
        fake_folder->files = malloc(sizeof(struct File) * MAX_FILES);

        // Check if the allocation was successful
        if (fake_folder->files == NULL)
        {
            printf("Error: Failed to allocate memory for file array\n");
            return;
        }
    }

    // Create a new File object
    struct File file;
    file.name = name;
    file.type = type;
    file.size = size;
    file.text = text;

    // Add the File object to the array of files in the folder
    fake_folder->files[fake_folder->num_files] = file;
    fake_folder->num_files++;
}

void create_fake_folder(char *name)
{
    // Check if the maximum number of fake folders has been reached
    if (num_fake_folders == MAX_FOLDERS)
    {
        printf("Error: Too many folders\n");
        return;
    }

    // Create a new FakeFolder object and add it to the global array of fake folders
    struct FakeFolder fake_folder;
    fake_folder.name = name;
    fake_folder.files = malloc(sizeof(struct File) * MAX_FILES);
    fake_folder.num_files = 0;
    fake_folders[num_fake_folders] = fake_folder;
    num_fake_folders++;
}

void print_current_directory()
{
    printf("/");
    if (num_fake_folders > 0)
    {
        printf("/");
        for (int i = 0; i < num_fake_folders; i++)
        {
            printf("%s/", fake_folders[i].name);
        }
    }
    printf("\n");
}

// start of main
// ######################################################################################################

int main()
{
    // Reset text color to default
    printf("\033[0m");

    // Print a fake boot sequence
    printf("Starting OS boot sequence...\n");
    sleep(1);
    printf("Checking hardware...\n");
    sleep(1);
    printf("Initializing RAM system...\n");
    sleep(1);
    printf(" RAM system initialized successfully!\n");
    sleep(1);

    // populate some fake files
    add_file("file1.txt", "text", 1024, "This is the text of file1.txt");
    add_file("file2.mp3", "audio", 2048, NULL);
    add_file("file3.png", "image", 4096, NULL);

    // Prompt the user for input
    char input[MAX_INPUT_LENGTH];
    while (1)
    {
        //? eventually it would be good to have a string that changes depending on the directory to
        //? for making it easier to add it  down here  \/

        printf("\033[32mUser\033[0m@\033[34mSystem\033[0m:~$ ");
        fgets(input, MAX_INPUT_LENGTH, stdin);

        // Remove newline character from input
        input[strcspn(input, "\n")] = 0;

        // Handle different commands
        if (strcmp(input, "shutdown") == 0)
        {
            // Exit the program if the user entered "exit"
            exit_program();
        }
        else if (strcmp(input, "ls") == 0)
        {
            // List the contents of the current directory if the user entered "ls"
            list_directory_contents();
        }
        else if (strncmp(input, "cat ", 4) == 0)
        {
            // Print the contents of a file if the user entered "cat <filename>"
            char *filename = input + 4;
            print_file_contents(filename);
        }
        else if (strcmp(input, "pwd") == 0)
        {
            // Print the current working directory if the user entered "pwd"
            print_current_directory();
        }
        else if (strncmp(input, "mkdir ", 6) == 0)
        {
            // Create a new fake folder if the user entered "mkdir <foldername>"
            char *foldername = input + 6;
            create_fake_folder(foldername);
        }
        else
        {
            printf("Unknown command: %s\n", input);
        }
    }

    return 0;
}
