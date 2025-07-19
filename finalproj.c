// Final version of ADMINX.c with first-time login setup
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_PATIENTS 100
#define MAX_DOCTORS 50

char inputBuffer[256];
int mistakeCounter = 0;

// --- Struct Definitions ---
struct Customer {
    char name[100];
    char phone[20];
    char roomNumber[10];
};

struct InventoryItem {
    char itemName[100];
    int quantity;
    float price;
};

struct Student {
    char name[100];
    char prevCollege[100];
    int roll;
    char phone[20];
    char address[100];
    char stream[10];
};

struct Marks {
    int roll;
    int currentYear;
    float year1, year2, year3, year4;
    float total;
};

struct Teacher {
    char name[100];
    char phone[20];
    char stream[10];
    char qualification[100];
    char address[100];
    char workObjective[200];
    char position[50];
};

struct Attendance {
    char name[100];
    int classes[6];
};

typedef struct {
    int id;
    char name[50];
    int age;
    char gender[10];
    char contact[15];
    char address[100];
    char disease[50];
} Patient;

typedef struct {
    int id;
    char name[50];
    int age;
    char gender[10];
    char specialization[50];
    char contact[15];
} Doctor;

Patient patients[MAX_PATIENTS];
Doctor doctors[MAX_DOCTORS];
int patientCount = 0;
int doctorCount = 0;

// --- Function Declarations ---
void design();
void printHeader(const char *title);
void pressAnyKeyToContinue();
int handleMistake();
int isValidPhoneNumber(const char *phone);
int isValidGender(const char *gender);
void login();
void hotelMenu();
void schoolMenu();
void hospitalMenu();

// --- Login Function with File Handling ---
void login() {
    FILE *file = fopen("credentials.txt", "r");
    char storedUser[100];
    char storedPass[100];

    if (file == NULL) {
        // First time setup
        printf("First time setup - create admin credentials\n");
        printf("Enter new username: ");
        fgets(storedUser, sizeof(storedUser), stdin);
        storedUser[strcspn(storedUser, "\n")] = 0;

        printf("Enter new password: ");
        fgets(storedPass, sizeof(storedPass), stdin);
        storedPass[strcspn(storedPass, "\n")] = 0;

        file = fopen("credentials.txt", "w");
        if (file == NULL) {
            printf("Error saving credentials. Exiting.\n");
            exit(1);
        }
        fprintf(file, "%s\n%s\n", storedUser, storedPass);
        fclose(file);
        printf("Credentials saved successfully!\n");
        return;
    }

    fgets(storedUser, sizeof(storedUser), file);
    fgets(storedPass, sizeof(storedPass), file);
    storedUser[strcspn(storedUser, "\n")] = 0;
    storedPass[strcspn(storedPass, "\n")] = 0;
    fclose(file);

    char inputUser[100];
    char inputPass[100];

    printf("Enter username: ");
    fgets(inputUser, sizeof(inputUser), stdin);
    inputUser[strcspn(inputUser, "\n")] = 0;

    printf("Enter password: ");
    fgets(inputPass, sizeof(inputPass), stdin);
    inputPass[strcspn(inputPass, "\n")] = 0;

    if (strcmp(inputUser, storedUser) != 0 || strcmp(inputPass, storedPass) != 0) {
        printf("Invalid credentials. Exiting.\n");
        exit(1);
    }
}

// --- Main Function ---
int main() {
    int choice;
    login();

    do {
        system("cls||clear");
        design();
        printHeader("AdminX - Main Menu");

        printf("1. Hotel Management System\n");
        printf("2. School Management System\n");
        printf("3. Hospital Management System\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");

        if (fgets(inputBuffer, sizeof(inputBuffer), stdin) == NULL || sscanf(inputBuffer, "%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            pressAnyKeyToContinue();
            continue;
        }

        switch (choice) {
            case 1:
                hotelMenu();
                break;
            case 2:
                schoolMenu();
                break;
            case 3:
                hospitalMenu();
                break;
            case 4:
                printf("Exiting AdminX. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please enter 1-4.\n");
                pressAnyKeyToContinue();
                break;
        }
    } while (choice != 4);

    return 0;
}

// --- Utility Functions ---
void design() {
    printf("==============================================\n");
    printf("                KIST COLLEGE                  \n");
    printf("==============================================\n\n");
    printf("*************** Welcome to ADMINX ***************\n\n");
}

void printHeader(const char *title) {
    printf("\n======== %s ========\n\n", title);
}

void pressAnyKeyToContinue() {
    printf("\nPress Enter to continue...");
    getchar();
}

int handleMistake() {
    mistakeCounter++;
    if (mistakeCounter >= 2) {
        char option;
        printf("\nYou made 2 mistakes. Enter '1' to continue or any other key to exit: ");
        if (fgets(inputBuffer, sizeof(inputBuffer), stdin) == NULL) {
            printf("Error reading input. Exiting.\n");
            exit(1);
        }
        option = inputBuffer[0];
        if (option != '1') {
            printf("Exiting due to repeated mistakes.\n");
            exit(0);
        }
        mistakeCounter = 0;
    }
    return 1;
}

int isValidPhoneNumber(const char *phone) {
    if (strlen(phone) != 10) {
        return 0;
    }
    for (int i = 0; i < 10; i++) {
        if (!isdigit(phone[i])) {
            return 0;
        }
    }
    long long num = atoll(phone);
    return (num >= 9700000000LL && num <= 9899999999LL);
}

int isValidGender(const char *gender) {
    char lowerGender[10];
    strcpy(lowerGender, gender);
    for (int i = 0; lowerGender[i]; i++) {
        lowerGender[i] = tolower(lowerGender[i]);
    }
    return (strcmp(lowerGender, "male") == 0 || strcmp(lowerGender, "female") == 0 || strcmp(lowerGender, "others") == 0);
}

// --- Menu Placeholders ---
void hotelMenu() {
    printf("[Hotel] Module\n");
    pressAnyKeyToContinue();
}

void schoolMenu() {
    printf("[School] Module\n");
    pressAnyKeyToContinue();
}

void hospitalMenu() {
    printf("[Hospital] Module\n");
    pressAnyKeyToContinue();
}
