
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_STUDENTS 100
#define MAX_TEACHERS 50


struct Customer 
{
    char name[100];
    char phone[20];
    char roomNumber[10];
};

struct Student
{
    char name[100];
    char prevCollege[100];
    int roll;
    char phone[20];
    char address[100];
    char stream[10];
};

struct Marks
{
    int roll;
    int currentYear;
    float year1, year2, year3, year4;
    float total;
};

struct Teacher
{
    char name[100];
    char phone[20];
    char stream[10];
    char qualification[100];
    char address[100];
    char workObjective[200];
    char position[50];
};

struct Attendance 
{
    char name[100];
    int classes[6];
};

typedef struct
{
    char name[50];
    int age;
    char gender[10];
    char contact[15];
    char disease[50];
} Patient;

struct Student students[MAX_STUDENTS];
struct Marks marks[MAX_STUDENTS];
int studentCount = 0;

struct Teacher teachers[MAX_TEACHERS];
struct Attendance attendance[MAX_TEACHERS];
int teacherCount = 0;

char inputBuffer[256];


void pressAnyKeyToContinue() 
{
    printf("\nPress Enter to continue...");
    getchar();
}
void design() 
{
    printf("==============================================\n");
    printf("                KIST COLLEGE                  \n");
    printf("==============================================\n\n");
    printf("*************** Welcome to ADMINX ***************\n\n");
}
void login() 
{
    FILE *file = fopen("credentials.txt", "r");
    char storedUser[100];
    char storedPass[100];

    if (file == NULL) 
		{
       		 printf("First time setup - create admin credentials\n");
        	printf("Enter new username: ");
        	fgets(storedUser, sizeof(storedUser), stdin);
        	storedUser[strcspn(storedUser, "\n")] = 0;

        	printf("Enter new password: ");
        	fgets(storedPass, sizeof(storedPass), stdin);
        	storedPass[strcspn(storedPass, "\n")] = 0;

        	file = fopen("credentials.txt", "w");
        if (file == NULL) 
			{
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

    if (strcmp(inputUser, storedUser) != 0 || strcmp(inputPass, storedPass) != 0)
	{
        printf("Invalid credentials. Exiting.\n");
        exit(1);
    }
}

void printHeader(const char *title) 
{
    printf("\n======== %s ========\n\n", title);
}


void saveStudentDataToFile() 
{
    FILE *f = fopen("students.dat", "wb");
    fwrite(&studentCount, sizeof(int), 1, f);
    fwrite(students, sizeof(struct Student), studentCount, f);
    fwrite(marks, sizeof(struct Marks), studentCount, f);
    fclose(f);
}

void loadStudentDataFromFile()
{
    FILE *f = fopen("students.dat", "rb");
    if (f) 
	{
        fread(&studentCount, sizeof(int), 1, f);
        fread(students, sizeof(struct Student), studentCount, f);
        fread(marks, sizeof(struct Marks), studentCount, f);
        fclose(f);
    }
}

void saveTeacherDataToFile()
{
    FILE *f = fopen("teachers.dat", "wb");
    fwrite(&teacherCount, sizeof(int), 1, f);
    fwrite(teachers, sizeof(struct Teacher), teacherCount, f);
    fwrite(attendance, sizeof(struct Attendance), teacherCount, f);
    fclose(f);
}

void loadTeacherDataFromFile()
{
    FILE *f = fopen("teachers.dat", "rb");
    if (f) {
        fread(&teacherCount, sizeof(int), 1, f);
        fread(teachers, sizeof(struct Teacher), teacherCount, f);
        fread(attendance, sizeof(struct Attendance), teacherCount, f);
        fclose(f);
    }
}

void saveHotelCustomerToFile(struct Customer *c)
{
    FILE *f = fopen("hotel_customers.txt", "a");
    fprintf(f, "%s,%s,%s\n", c->name, c->phone, c->roomNumber);
    fclose(f);
}

void displayHotelCustomers()
{
    FILE *f = fopen("hotel_customers.txt", "r");
    char line[256];
    printf("\n--- Hotel Customers ---\n");
    if (f) {
        while (fgets(line, sizeof(line), f)) {
            char name[100], phone[20], room[10];
            sscanf(line, "%[^,],%[^,],%[^\n]", name, phone, room);
            printf("%s | %s | Room: %s\n", name, phone, room);
        }
        fclose(f);
    } else printf("No customers yet.\n");
    pressAnyKeyToContinue();
}

void savePatientToFile(Patient *p) 
{
    FILE *f = fopen("patients.txt", "a");
    fprintf(f, "%s,%d,%s,%s,%s\n", p->name, p->age, p->gender, p->contact, p->disease);
    fclose(f);
}

void displayPatientsFromFile()
{
    FILE *f = fopen("patients.txt", "r");
    char line[256];
    printf("\n--- Hospital Patients ---\n");
    if (f) {
        while (fgets(line, sizeof(line), f)) {
            char name[50], gender[10], contact[15], disease[50];
            int age;
            sscanf(line, "%[^,],%d,%[^,],%[^,],%[^\n]", name, &age, gender, contact, disease);
            printf("%s | Age: %d | %s | %s | %s\n", name, age, gender, contact, disease);
        }
        fclose(f);
    } else printf("No patients yet.\n");
    pressAnyKeyToContinue();
}


void hotelMenu() 
{
    struct Customer c;
    int choice;
    do 
	{
        printHeader("Hotel Management");
        printf("1. Add Customer\n2. View All Customers\n3. Back\nEnter choice: ");
        fgets(inputBuffer, sizeof(inputBuffer), stdin);
        sscanf(inputBuffer, "%d", &choice);
        switch (choice) 
		{
            case 1:
                printf("Enter customer name: "); fgets(c.name, 100, stdin);
                printf("Enter phone: "); fgets(c.phone, 20, stdin);
                printf("Enter room number: "); fgets(c.roomNumber, 10, stdin);
                c.name[strcspn(c.name, "\n")] = 0;
                c.phone[strcspn(c.phone, "\n")] = 0;
                c.roomNumber[strcspn(c.roomNumber, "\n")] = 0;
                saveHotelCustomerToFile(&c);
                printf("Customer saved successfully!\n");
                pressAnyKeyToContinue();
                break;
            case 2: displayHotelCustomers(); break;
            case 3: return;
            default: printf("Invalid.\n"); break;
        }
    } while (choice != 3);
}

void hospitalMenu()
{
    Patient p;
    int choice;
    do {
        printHeader("Hospital Management");
        printf("1. Add Patient\n2. View All Patients\n3. Back\nEnter choice: ");
        fgets(inputBuffer, sizeof(inputBuffer), stdin);
        sscanf(inputBuffer, "%d", &choice);
        switch (choice) 
		{
            case 1:
                printf("Enter patient name: "); fgets(p.name, 50, stdin);
                printf("Enter age: "); scanf("%d", &p.age); getchar();
                printf("Enter gender: "); fgets(p.gender, 10, stdin);
                printf("Enter contact: "); fgets(p.contact, 15, stdin);
                printf("Enter disease: "); fgets(p.disease, 50, stdin);
                p.name[strcspn(p.name, "\n")] = 0;
                p.gender[strcspn(p.gender, "\n")] = 0;
                p.contact[strcspn(p.contact, "\n")] = 0;
                p.disease[strcspn(p.disease, "\n")] = 0;
                savePatientToFile(&p);
                printf("Patient saved successfully!\n");
                pressAnyKeyToContinue();
                break;
            case 2: displayPatientsFromFile(); break;
            case 3: return;
            default: printf("Invalid.\n"); break;
        }
    } while (choice != 3);
}

void enterMarks();
void manageTeachers();

void loadAllSchoolData() 
{
    loadStudentDataFromFile();
    loadTeacherDataFromFile();
}

void schoolMenu() 
{
    loadAllSchoolData();
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
        switch (choice)
		 {
            case 1: 
			{
                if (studentCount >= MAX_STUDENTS)
				 {
                    printf("Max students reached.\n"); pressAnyKeyToContinue(); break;
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
                switch (streamChoice) 
				{
                    case 1: strcpy(s.stream, "BIT"); break;
                    case 2: strcpy(s.stream, "BIM"); break;
                    case 3: strcpy(s.stream, "BCA"); break;
                    default: strcpy(s.stream, "UNKNOWN"); break;
                }
                students[studentCount] = s;
                marks[studentCount].roll = s.roll;
                marks[studentCount].currentYear = 0;
                marks[studentCount].year1 = marks[studentCount].year2 = -1;
                marks[studentCount].year3 = marks[studentCount].year4 = -1;
                marks[studentCount].total = 0;
                studentCount++;
                saveStudentDataToFile();
                printf("Student added in stream %s.\n", s.stream);
                pressAnyKeyToContinue();
                break;
            }
            case 2: 
            {
					enterMarks();
					saveStudentDataToFile();
					break;
			}
            case 3:
           	{
			
					 manageTeachers();	
					  saveTeacherDataToFile();
					   break;
			}
            case 4:
			 {
                printf("\n--- Student Details ---\n");
                for (int i = 0; i < studentCount; i++) 
				{
                    printf("%d. %s | Roll: %d | Stream: %s\n", i + 1, students[i].name, students[i].roll, students[i].stream);
                    printf("   Marks: ");
                    if (marks[i].currentYear == 0) 
					{
                        printf("No marks entered yet.\n");
                    }
					 else
					{
                        printf("Year %d\n", marks[i].currentYear);
                        if (marks[i].year1 >= 0) 
                        {
						printf("      1st Year: %.2f\n", marks[i].year1);
						}
                        if (marks[i].year2 >= 0) 
                        {
						printf("      2nd Year: %.2f\n", marks[i].year2);
						}
                        if (marks[i].year3 >= 0) 
                        {
						printf("      3rd Year: %.2f\n", marks[i].year3);
						}
                        if (marks[i].year4 >= 0) 
                        {
						printf("      4th Year: %.2f\n", marks[i].year4);
						}
                        printf("      Total: %.2f\n", marks[i].total);
                    }
                }
                pressAnyKeyToContinue();
				 break;
            }
            case 5:
			 {
                printf("\n--- Teacher Details ---\n");
                for (int i = 0; i < teacherCount; i++) 
				{
                    printf("%d. %s | %s | %s\n", i + 1, teachers[i].name, teachers[i].stream, teachers[i].position);
                }
                pressAnyKeyToContinue(); 
				break;
            }
            case 6: return;
            default:
			 printf("Invalid.\n");
			  break;
        }
    } while (choice != 6);
}

void enterMarks() 
{
    int roll, i;
    printf("Enter student roll: ");
    scanf("%d", &roll); getchar();
    for (i = 0; i < studentCount; i++) 
	{
        if (students[i].roll == roll) break;
    }
    if (i == studentCount) 
		{
		 	printf("Student not found.\n"); 
			 pressAnyKeyToContinue();
			  return;
		}
    struct Marks *m = &marks[i];
    printf("Enter current year (1-4): ");
    scanf("%d", &m->currentYear);
    if (m->currentYear >= 1)
		 {
	 		 printf("GPA Year 1: "); scanf("%f", &m->year1);
		 }
    if (m->currentYear >= 2) 
		{
				 printf("GPA Year 2: "); scanf("%f", &m->year2); 
		}
    if (m->currentYear >= 3)
		 {
		 		 printf("GPA Year 3: "); scanf("%f", &m->year3);
		 }
    if (m->currentYear >= 4)
		 {
		 		 printf("GPA Year 4: "); scanf("%f", &m->year4); 
		}
    m->total = 0;
    if (m->year1 >= 0) 
   		{
			m->total += m->year1;
		}
    if (m->year2 >= 0)
	    {
			m->total += m->year2;
		}
    if (m->year3 >= 0)
	    {
			m->total += m->year3;
		}
    if (m->year4 >= 0)
   		 {
			m->total += m->year4;
		}
    pressAnyKeyToContinue();
}

void manageTeachers()
 {
    struct Teacher t;
    printf("Enter name: "); fgets(t.name, 100, stdin);
    printf("Phone: "); fgets(t.phone, 20, stdin);
    printf("Stream: "); fgets(t.stream, 10, stdin);
    printf("Qualification: "); fgets(t.qualification, 100, stdin);
    printf("Address: "); fgets(t.address, 100, stdin);
    printf("Position: "); fgets(t.position, 50, stdin);
    teachers[teacherCount] = t;
    strcpy(attendance[teacherCount].name, t.name);
    printf("Enter number of classes (Sun to Fri):\n");
    for (int i = 0; i < 6; i++)
	 {
        printf("Day %d: ", i + 1);
        scanf("%d", &attendance[teacherCount].classes[i]);
    }
    teacherCount++;
    pressAnyKeyToContinue();
}
int main()
 {
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

        if (fgets(inputBuffer, sizeof(inputBuffer), stdin) == NULL || sscanf(inputBuffer, "%d", &choice) != 1)
		 {
            printf("Invalid input.\n");
            pressAnyKeyToContinue();
            continue;
        }

        switch (choice)
		 {
            case 1: hotelMenu(); break;
            case 2: schoolMenu(); break;
            case 3: hospitalMenu(); break;
            case 4: printf("Exiting AdminX. Goodbye!\n"); break;
            default: printf("Invalid choice. Try again.\n"); pressAnyKeyToContinue(); break;
        }
    } while (choice != 4);

    return 0;
}