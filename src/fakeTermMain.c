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
    char *path;         // The path of the folder
    struct File *files; // An array of File objects that are inside the folder
    int num_files;      // The number of files in the folder
    struct FakeFolder *sub_folders; // An array of subdirectories inside the folder
    int num_sub_folders;      // The number of subdirectories in the folder
};


// Current dir where we start 
char *current_dir = "/";



// Global array of fake files
struct File *files = NULL;
int num_files = 0;
int file_capacity = 0;

// Global array of fake folders
struct FakeFolder fake_folders = NULL;
int num_fake_folders = 0;


// Function to add a fake file to the global array of files
void add_file(char *name, char *type, int size, char *text)
{
    // Check if the array is full
    if (num_files == file_capacity)
    {
        // If the array is full, increase its capacity
        file_capacity = file_capacity == 0 ? 1 : file_capacity * 2;
        files = realloc(files, file_capacity * sizeof(struct File));
    }

    // Create a new File object
    struct File file;
    file.name = name;
    file.type = type;
    file.size = size;
    file.text = text;

    // Add the File object to the global array of files
    files[num_files++] = file;
}

// Function to add a fake folder to the global array of folders
void add_folder(char *name, char *path)
{
    // Check if the array is full
    if (num_fake_folders == MAX_FOLDERS)
    {
        printf("Error: Too many folders\n");
        return;
    }

    // Create a new FakeFolder object
    struct FakeFolder folder;
    folder.name = name;
    folder.path = path;
    folder.files = NULL;
    folder.num_files = 0;
    folder.sub_folders = NULL;
    folder.num_sub_folders = 0;

    // Add the FakeFolder object to the global array of folders
    fake_folders[num_fake_folders] = folder;
    num_fake_folders++;
}



// Function to add a file to a folder
void add_file_to_folder(char *folder_name, char *file_name, char *type, int size, char *text)
{
    // Get a pointer to the folder by its name
    struct FakeFolder *folder = get_folder_by_name(folder_name);
    if (!folder)
    {
        printf("Error: Folder '%s' not found\n", folder_name);
        return;
    }

    // Check if the array of files in the folder is full
    if (folder->num_files == MAX_FILES)
    {
        printf("Error: Too many files in folder '%s'\n", folder_name);
        return;
    }

    // Create a new File object
    struct File file;
    file.name = file_name;
    file.type = type;
    file.size = size;
    file.text = text;

    // Add the File object to the array of files in the folder
    folder->files[folder->num_files] = file;
    folder->num_files++;
}


// Function to remove a file from a folder
void remove_file_from_folder(char *folder_name, char *file_name)
{
    // Get a pointer to the folder by its name
    struct FakeFolder *folder = get_folder_by_name(folder_name);
    if (!folder)
    {
        printf("Error: Folder '%s' not found\n", folder_name);
        return;
    }

    // Get a pointer to the file by its name
    struct File *file = get_file_by_name_in_folder(folder, file_name);
    if (!file)
    {
        printf("Error: File '%s' not found in folder '%s'\n", file_name, folder_name);
        return;
    }

    // Remove the file from the array of files in the folder by shifting all the other files over
    int file_index = file - folder->files;
    for (int i = file_index; i < folder->num_files - 1; i++)
    {
        folder->files[i] = folder->files[i + 1];
    }

    // Decrement the number of files in the folder
    folder->num_files--;
}
}

// Function to get a pointer to a FakeFolder object by its path
struct FakeFolder *get_folder_by_path(char *path)
{
    // Loop through the array of FakeFolder objects
    for (int i = 0; i < num_fake_folders; i++)
    {
        // Get a pointer to the current FakeFolder object
        struct FakeFolder *folder = &fake_folders[i];

        // Check if the path of the current folder matches the given path
        if (strcmp(folder->path, path) == 0)
        {
            // Return a pointer to the FakeFolder object
            return folder;
        }
    }
    return NULL;
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
void list_dir(char *folder_name)
{
    // Get a pointer to the folder by its name
    struct FakeFolder *folder = get_folder_by_name(folder_name);
    if (!folder)
    {
        printf("Error: Folder '%s' not found\n", folder_name);
        return;
    }

    // Update the current directory
    current_dir = folder_name;

    // Print the contents of the folder (the names of the files and subfolders inside)
    printf("Contents of folder '%s':\n", folder_name);
    for (int i = 0; i < folder->num_files; i++)
    {
        struct File *file = &folder->files[i];
        printf("- %s\n", file->name);
    }
    for (int i = 0; i < num_fake_folders; i++)
    {
        struct FakeFolder *subfolder = &fake_folders[i];
        if (subfolder->parent == folder)
        {
            printf("- %s/\n", subfolder->name);
        }
    }
    printf("Current directory: %s\n", current_dir);
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
