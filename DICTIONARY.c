#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Word 
{
    char word[50];
    char meaning[200];
    struct Word *next;
} Word;

void addWord(Word **head);
void searchWord(Word *head);
void displayDictionary(Word *head);
void deleteWord(Word **head);
void freeMemory(Word *head);

int main() 
{
    Word *head = NULL; 
    int choice;
    do {
        printf("\n--- Dictionary System ---\n");
        printf("1. Add Word\n");
        printf("2. Search Word\n");
        printf("3. Display Dictionary\n");
        printf("4. Delete Word\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();
        
        switch (choice) 
        {
            case 1:
                addWord(&head);
                break;
            case 2:
                searchWord(head);
                break;
            case 3:
                displayDictionary(head);
                break;
            case 4:
                deleteWord(&head);
                break;
            case 5:
                freeMemory(head);
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 5);
    return 0;
}

void addWord(Word **head) 
{
    Word *newWord = (Word *)malloc(sizeof(Word));
    if (!newWord) {
        printf("Memory allocation failed!\n");
        return;
    }
    
    printf("Enter word: ");
    fgets(newWord->word, sizeof(newWord->word), stdin); 
    newWord->word[strcspn(newWord->word, "\n")] = '\0'; 
    
    printf("Enter meaning: ");
    fgets(newWord->meaning, sizeof(newWord->meaning), stdin);
    newWord->meaning[strcspn(newWord->meaning, "\n")] = '\0'; 
    
    newWord->next = *head;
    *head = newWord;
    
    printf("Word added successfully: %s - %s\n", newWord->word, newWord->meaning);
}

void searchWord(Word *head) 
{
    char search[50];
    printf("Enter word to search: ");
    fgets(search, sizeof(search), stdin); 
    search[strcspn(search, "\n")] = '\0'; 
    
    Word *current = head;
    int found = 0; 
    while (current) 
    {
        if (strcmp(current->word, search) == 0) 
        {
            printf("Found word: %s\nMeaning: %s\n", current->word, current->meaning);
            found = 1;
            break;
        }
        current = current->next;
    }  
    if (!found) {
        printf("Word not found in the dictionary.\n");
    }
}

void displayDictionary(Word *head) 
{
    if (!head) {
        printf("The dictionary is empty.\n");
        return;
    }
    
    Word *current = head;
    printf("\n--- Dictionary Entries ---\n");
    while (current) 
    {
        printf("Word: %s\nMeaning: %s\n", current->word, current->meaning);
        current = current->next;
    }
}

void deleteWord(Word **head) 
{
    char wordToDelete[50];
    printf("Enter word to delete: ");
    fgets(wordToDelete, sizeof(wordToDelete), stdin); 
    wordToDelete[strcspn(wordToDelete, "\n")] = '\0'; 
    
    Word *current = *head, *prev = NULL;
    while (current) 
    {
        if (strcmp(current->word, wordToDelete) == 0) 
        {
            if (prev) {
                prev->next = current->next;
            } else {
                *head = current->next; 
            }
            free(current);
            printf("Word deleted successfully.\n");
            return;
        }
        prev = current;
        current = current->next;
    }
    printf("Word not found in the dictionary.\n");
}

void freeMemory(Word *head) 
{
    Word *current = head;
    while (current) 
    {
        Word *temp = current;
        current = current->next;
        free(temp);
    }
}
