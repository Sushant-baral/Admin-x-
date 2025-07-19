#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    char name[100];
    char prevCollege[100];
    int roll;
    char phone[20];
    char address[100];
};

struct Marks {
    int roll;
    int year1, year2, year3, year4;
    int total;
};

void getFileName(char stream[], int section, char type[], char filename[]) {
    sprintf(filename, "%s_%d_%s.txt", stream, section, type);
}

void addStudent() {
    char stream[10], filename[50];
    int section, count = 0;
    struct Student s;

    printf("Enter Stream (BIM/BIT/BCE): ");
    scanf("%s", stream);
    printf("Enter Section (1-5): ");
    scanf("%d", &section);

    getFileName(stream, section, "students", filename);

    FILE *f = fopen(filename, "a+");
    if (f == NULL) {
        printf("Cannot open file.\n");
        return;
    }

    // Count students
    while (fread(&s, sizeof(s), 1, f)) {
        count++;
    }

    if (count >= 10) {
        printf("This section already has 10 students.\n");
        fclose(f);
        return;
    }

    fseek(f, 0, SEEK_END); // move to end

    getchar(); // clear buffer
    printf("Enter Name: ");
    gets(s.name);
    printf("Enter Previous College: ");
    gets(s.prevCollege);
    printf("Enter Roll Number: ");
    scanf("%d", &s.roll);
    getchar();
    printf("Enter Phone: ");
    gets(s.phone);
    printf("Enter Address: ");
    gets(s.address);

    fwrite(&s, sizeof(s), 1, f);
    fclose(f);
    printf("Student added!\n");
}

void enterMarks() {
    char stream[10], studentFile[50], marksFile[50];
    int section;
    struct Student s;
    struct Marks m;

    printf("Enter Stream (BIM/BIT/BCE): ");
    scanf("%s", stream);
    printf("Enter Section (1-5): ");
    scanf("%d", &section);

    getFileName(stream, section, "students", studentFile);
    getFileName(stream, section, "marks", marksFile);

    FILE *sf = fopen(studentFile, "r");
    FILE *mf = fopen(marksFile, "a");

    if (sf == NULL || mf == NULL) {
        printf("File error.\n");
        return;
    }

    while (fread(&s, sizeof(s), 1, sf)) {
        printf("\nEnter marks for %s (Roll %d):\n", s.name, s.roll);
        m.roll = s.roll;
        printf("Year 1: ");
        scanf("%d", &m.year1);
        printf("Year 2: ");
        scanf("%d", &m.year2);
        printf("Year 3: ");
        scanf("%d", &m.year3);
        printf("Year 4: ");
        scanf("%d", &m.year4);
        m.total = m.year1 + m.year2 + m.year3 + m.year4;
        fwrite(&m, sizeof(m), 1, mf);
    }

    fclose(sf);
    fclose(mf);
    printf("Marks added.\n");
}

void viewData() {
    char stream[10], filename[50];
    int section, choice;
    struct Student s;
    struct Marks m;

    printf("Enter Stream (BIM/BIT/BCE): ");
    scanf("%s", stream);
    printf("Enter Section (1-5): ");
    scanf("%d", &section);

    printf("1. View Student Details\n2. View Marks\nChoose: ");
    scanf("%d", &choice);

    if (choice == 1) {
        getFileName(stream, section, "students", filename);
        FILE *f = fopen(filename, "r");
        if (f == NULL) {
            printf("No student data.\n");
            return;
        }
        printf("\n--- Student Details ---\n");
        while (fread(&s, sizeof(s), 1, f)) {
            printf("Name: %s\n", s.name);
            printf("Roll: %d\n", s.roll);
            printf("Previous College: %s\n", s.prevCollege);
            printf("Phone: %s\n", s.phone);
            printf("Address: %s\n", s.address);
            printf("---------------------------\n");
        }
        fclose(f);
    } else if (choice == 2) {
        getFileName(stream, section, "marks", filename);
        FILE *f = fopen(filename, "r");
        if (f == NULL) {
            printf("No marks data.\n");
            return;
        }
        printf("\n--- Marks Details ---\n");
        while (fread(&m, sizeof(m), 1, f)) {
            printf("Roll: %d\n", m.roll);
            printf("1st Year: %d\n", m.year1);
            printf("2nd Year: %d\n", m.year2);
            printf("3rd Year: %d\n", m.year3);
            printf("4th Year: %d\n", m.year4);
            printf("Total: %d\n", m.total);
            printf("---------------------------\n");
        }
        fclose(f);
    } else {
        printf("Invalid choice.\n");
    }
}

void schoolMenu() {
    int ch;
    do {
        printf("\n--- School Menu ---\n");
        printf("1. Add Student\n");
        printf("2. Enter Marks\n");
        printf("3. View Students or Marks\n");
        printf("4. Back to Main\n");
        printf("Enter choice: ");
        scanf("%d", &ch);

        if (ch == 1) addStudent();
        else if (ch == 2) enterMarks();
        else if (ch == 3) viewData();
        else if (ch == 4) break;
        else printf("Invalid.\n");

    } while (ch != 4);
}

int main() {
    int ch;
    do {
        printf("\n=== AdminX Main ===\n");
        printf("1. School Management\n");
        printf("2. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &ch);

        if (ch == 1) {
            printf("\nWelcome to School Management System!\n");
            schoolMenu();
        } else if (ch == 2) {
            printf("Goodbye!\n");
        } else {
            printf("Invalid.\n");
        }

    } while (ch != 2);

    return 0;
}
