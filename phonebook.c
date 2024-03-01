#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct person {
    char name[30];
    char country_code[4];
    long int mble_no;
    char sex[8];
    char mail[100];
};

// Define person data type
typedef struct person person;

// Function declarations
void remove_all();
void print_menu();
void add_person();
void list_record();
void search_person();
void remove_person();
void update_person();
void take_input(person *p);
void start();
void clear_screen();

int main() {
    start();
    return 0;
}

void clear_screen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void start() {
    int choice;
    while (1) {
        print_menu();
        scanf("%d", &choice);
        getchar(); // Consume the newline character left by scanf
        switch (choice) {
            case 1:
                list_record();
                break;
            case 2:
                add_person();
                break;
            case 3:
                search_person();
                break;
            case 4:
                update_person();
                break;
            case 5:
                remove_person();
                break;
            case 6:
                remove_all();
                break;
            case 7:
                clear_screen();
                printf("Thank you for using the phonebook, please visit again.\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}

void print_menu() {
    clear_screen();
    printf("\t\t******************************************************************************************\n\n");
    printf("\t\t                             WELCOME TO PHONEBOOK                                         \n\n");
    printf("\t\t******************************************************************************************\n\n");
    printf("\t\t1) List record\n");
    printf("\t\t2) Add person\n");
    printf("\t\t3) Search person Details\n");
    printf("\t\t4) Update person\n");
    printf("\t\t5) Remove person\n");
    printf("\t\t6) Delete all contacts\n");
    printf("\t\t7) Exit Phonebook\n\n");
    printf("\t\tEnter your choice: ");
}

void add_person() {
    clear_screen();
    FILE *fp;
    fp = fopen("phonebook_db", "ab+");
    if (fp == NULL) {
        perror("Error opening file");
        return;
    }
    person p;
    take_input(&p);
    fwrite(&p, sizeof(p), 1, fp);
    fclose(fp);
    printf("Record added successfully.\nPress any key to continue...\n");
    getchar(); // Wait for user input
}

void take_input(person *p) {
    clear_screen();
    printf("Enter name: ");
    fgets(p->name, sizeof(p->name), stdin);
    p->name[strcspn(p->name, "\n")] = 0; // Remove newline character

    printf("Enter country code: ");
    fgets(p->country_code, sizeof(p->country_code), stdin);
    p->country_code[strcspn(p->country_code, "\n")] = 0;

    printf("Enter mobile no: ");
    scanf("%ld", &p->mble_no);
    getchar(); // Consume the newline character

    printf("Enter sex: ");
    fgets(p->sex, sizeof(p->sex), stdin);
    p->sex[strcspn(p->sex, "\n")] = 0;

    printf("Enter email: ");
    fgets(p->mail, sizeof(p->mail), stdin);
    p->mail[strcspn(p->mail, "\n")] = 0;

    clear_screen();
}

void list_record() {
    clear_screen();
    FILE *fp = fopen("phonebook_db", "rb");
    if (fp == NULL) {
        perror("Error opening file");
        return;
    }
    person p;
    printf("NAME\tCOUNTRY CODE\tPHONE NO\tSEX\tEMAIL\n");
    printf("--------------------------------------------------------\n");
    while (fread(&p, sizeof(p), 1, fp) == 1) {
        printf("%-30s %-15s %-10ld %-8s %s\n", p.name, p.country_code, p.mble_no, p.sex, p.mail);
    }
    fclose(fp);
    printf("\nPress any key to continue...\n");
    getchar(); // Wait for user input
}

// Placeholder for functions not implemented in this snippet
void search_person() { /* Functionality to be implemented */ }
void remove_person() { /* Functionality to be implemented */ }
void update_person() { /* Functionality to be implemented */ }

void remove_all() {
    clear_screen();
    remove("phonebook_db");
    printf("All data in the phonebook deleted successfully.\n");
    printf("Press any key to continue...\n");
    getchar(); // Wait for user input
}

