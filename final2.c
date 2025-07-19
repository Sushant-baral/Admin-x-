// Final version of ADMINX.c with full login + hotel, school, hospital, marks and teacher systems
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_PATIENTS 100
#define MAX_DOCTORS 50
#define MAX_STUDENTS 100
#define MAX_TEACHERS 50

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
    int classes[6]; // Sun to Fri
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

struct Student students[MAX_STUDENTS];
struct Marks marks[MAX_STUDENTS];
int studentCount = 0;

struct Teacher teachers[MAX_TEACHERS];
struct Attendance attendance[MAX_TEACHERS];
int teacherCount = 0;

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
void enterMarks();
void manageTeachers();

// --- Login with file handling ---
void login() {
    FILE *file = fopen("credentials.txt", "r");
    char storedUser[100];
    char storedPass[100];

    if (file == NULL) {
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

// --- Main Menu ---
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
            printf("Invalid input.\n");
            pressAnyKeyToContinue();
            continue;
        }

        switch (choice) {
            case 1: hotelMenu(); break;
            case 2: schoolMenu(); break;
            case 3: hospitalMenu(); break;
            case 4: printf("Exiting AdminX. Goodbye!\n"); break;
            default: printf("Invalid choice. Try again.\n"); pressAnyKeyToContinue(); break;
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
        printf("Too many mistakes. Exiting.\n");
        exit(0);
    }
    return 1;
}

int isValidPhoneNumber(const char *phone) {
    if (strlen(phone) != 10) return 0;
    for (int i = 0; i < 10; i++) {
        if (!isdigit(phone[i])) return 0;
    }
    return 1;
}

int isValidGender(const char *gender) {
    return (strcasecmp(gender, "male") == 0 || strcasecmp(gender, "female") == 0 || strcasecmp(gender, "others") == 0);
}

// --- Menus ---
void hotelMenu() {
    struct Customer c;
    printf("Enter customer name: ");
    fgets(c.name, sizeof(c.name), stdin);
    c.name[strcspn(c.name, "\n")] = 0;
    printf("Enter phone: ");
    fgets(c.phone, sizeof(c.phone), stdin);
    c.phone[strcspn(c.phone, "\n")] = 0;
    printf("Enter room number: ");
    fgets(c.roomNumber, sizeof(c.roomNumber), stdin);
    c.roomNumber[strcspn(c.roomNumber, "\n")] = 0;
    printf("Customer added: %s (%s) - Room %s\n", c.name, c.phone, c.roomNumber);
    pressAnyKeyToContinue();
}

// (Updated section for School Management)
void schoolMenu() {
    int choice;
    do {
        printHeader("School Management");
        printf("1. Add Student\n");
        printf("2. Enter Marks\n");
        printf("3. Manage Teachers\n");
        printf("4. View Student Details\n");
        printf("5. View Teacher Details\n");
        printf("6. Back\n");
        printf("Enter choice: ");
        fgets(inputBuffer, sizeof(inputBuffer), stdin);
        sscanf(inputBuffer, "%d", &choice);
        switch (choice) {
            case 1: {
                if (studentCount >= MAX_STUDENTS) {
                    printf("Max students reached.\n");
                    pressAnyKeyToContinue();
                    break;
                }
                struct Student s;
                printf("Enter name: "); fgets(s.name, 100, stdin);
                printf("Enter prev college: "); fgets(s.prevCollege, 100, stdin);
                printf("Enter roll: "); scanf("%d", &s.roll); getchar();
                printf("Enter phone: "); fgets(s.phone, 20, stdin);
                printf("Enter address: "); fgets(s.address, 100, stdin);
                int streamChoice;
                printf("Select stream:\n1. BIT\n2. BIM\n3. BCA\nEnter: ");
                scanf("%d", &streamChoice); getchar();
                switch (streamChoice) {
                    case 1: strcpy(s.stream, "BIT"); break;
                    case 2: strcpy(s.stream, "BIM"); break;
                    case 3: strcpy(s.stream, "BCA"); break;
                    default: strcpy(s.stream, "UNKNOWN"); break;
                }
                students[studentCount] = s;
                marks[studentCount].roll = s.roll;
                marks[studentCount].currentYear = 0;
                marks[studentCount].year1 = -1;
                marks[studentCount].year2 = -1;
                marks[studentCount].year3 = -1;
                marks[studentCount].year4 = -1;
                marks[studentCount].total = 0;
                studentCount++;
                printf("Student added in stream %s.\n", s.stream);
                pressAnyKeyToContinue();
                break;
            }
            case 2: enterMarks(); break;
            case 3: manageTeachers(); break;
            case 4: {
                if (studentCount == 0) {
                    printf("No students available.\n");
                } else {
                    printf("\n--- Student Details ---\n");
                    for (int i = 0; i < studentCount; i++) {
                        printf("%d. %s | Roll: %d | Stream: %s\n", i + 1, students[i].name, students[i].roll, students[i].stream);
                        printf("   Marks: ");
                        if (marks[i].currentYear == 0) {
                            printf("No marks entered yet.\n");
                        } else {
                            printf("Year %d\n", marks[i].currentYear);
                            if (marks[i].year1 >= 0) printf("      1st Year: %.2f\n", marks[i].year1);
                            if (marks[i].year2 >= 0) printf("      2nd Year: %.2f\n", marks[i].year2);
                            if (marks[i].year3 >= 0) printf("      3rd Year: %.2f\n", marks[i].year3);
                            if (marks[i].year4 >= 0) printf("      4th Year: %.2f\n", marks[i].year4);
                            printf("      Total: %.2f\n", marks[i].total);
                        }
                    }
                }
                pressAnyKeyToContinue();
                break;
            }
            case 5: {
                if (teacherCount == 0) {
                    printf("No teachers available.\n");
                } else {
                    printf("\n--- Teacher Details ---\n");
                    for (int i = 0; i < teacherCount; i++) {
                        printf("%d. %s | %s | %s\n", i + 1, teachers[i].name, teachers[i].stream, teachers[i].position);
                    }
                }
                pressAnyKeyToContinue();
                break;
            }
            case 6: return;
            default: printf("Invalid.\n"); break;
        }
    } while (choice != 6);
}



void enterMarks() {
    if (studentCount == 0) {
        printf("No students.\n"); pressAnyKeyToContinue(); return;
    }
    int roll, i;
    printf("Enter roll: "); scanf("%d", &roll); getchar();
    for (i = 0; i < studentCount; i++) {
        if (students[i].roll == roll) break;
    }
    if (i == studentCount) {
        printf("Student not found.\n"); pressAnyKeyToContinue(); return;
    }
    struct Marks m;
    m.roll = roll;
    printf("Current year (1-4): "); scanf("%d", &m.currentYear);
    m.year1 = (m.currentYear >= 1) ? (printf("Year 1 GPA: "), scanf("%f", &m.year1), m.year1) : -1;
    m.year2 = (m.currentYear >= 2) ? (printf("Year 2 GPA: "), scanf("%f", &m.year2), m.year2) : -1;
    m.year3 = (m.currentYear >= 3) ? (printf("Year 3 GPA: "), scanf("%f", &m.year3), m.year3) : -1;
    m.year4 = (m.currentYear == 4) ? (printf("Year 4 GPA: "), scanf("%f", &m.year4), m.year4) : -1;
    m.total = 0;
    if (m.year1 >= 0) m.total += m.year1;
    if (m.year2 >= 0) m.total += m.year2;
    if (m.year3 >= 0) m.total += m.year3;
    if (m.year4 >= 0) m.total += m.year4;
    marks[i] = m;
    printf("Marks updated.\n");
    pressAnyKeyToContinue();
}

void manageTeachers() {
    struct Teacher t;
    printf("Enter name: "); fgets(t.name, 100, stdin);
    printf("Phone: "); fgets(t.phone, 20, stdin);
    printf("Stream: "); fgets(t.stream, 10, stdin);
    printf("Qualification: "); fgets(t.qualification, 100, stdin);
    printf("Address: "); fgets(t.address, 100, stdin);
    printf("Position: "); fgets(t.position, 50, stdin);
    teachers[teacherCount] = t;
    strcpy(attendance[teacherCount].name, t.name);
    printf("Enter number of classes from Sunday to Friday (6 days):\n");
    for (int i = 0; i < 6; i++) {
        printf("Day %d: ", i + 1);
        scanf("%d", &attendance[teacherCount].classes[i]);
    }
    teacherCount++;
    printf("Teacher added.\n");
    pressAnyKeyToContinue();
}

void hospitalMenu() {
    Patient p;
    printf("Enter patient name: ");
    fgets(p.name, sizeof(p.name), stdin);
    p.name[strcspn(p.name, "\n")] = 0;
    printf("Enter age: ");
    scanf("%d", &p.age); getchar();
    printf("Enter gender: ");
    fgets(p.gender, sizeof(p.gender), stdin);
    p.gender[strcspn(p.gender, "\n")] = 0;
    printf("Enter contact: ");
    fgets(p.contact, sizeof(p.contact), stdin);
    p.contact[strcspn(p.contact, "\n")] = 0;
    printf("Enter disease: ");
    fgets(p.disease, sizeof(p.disease), stdin);
    p.disease[strcspn(p.disease, "\n")] = 0;
    printf("Patient admitted: %s (%s)\n", p.name, p.disease);
    pressAnyKeyToContinue();
}
