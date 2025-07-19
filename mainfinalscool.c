#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student 
{
    char name[100];
    char prevCollege[100];
    int roll;
    char phone[20];
    char address[100];
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
};

struct Attendance 
{
    char name[100];
    int classes[6]; 
};
void makeFileName(char stream[], int section, char type[], char output[]) 
{
    sprintf(output, "%s_%d_%s.txt", stream, section, type);
}
void addStudent() 
{
    char stream[10], fileName[50];
    int section, count = 0;
    struct Student s;

    printf("Enter Stream (BIM/BIT/BCE): ");
    scanf("%s", stream);
    printf("Enter Section (1–5): ");
    scanf("%d", &section);

    makeFileName(stream, section, "students", fileName);
    FILE *f = fopen(fileName, "a+");

    if (f == NULL) 
    {
        printf("Error opening file.\n");
        return;
    }

    while (fread(&s, sizeof(s), 1, f)) 
    {
        count++;
    }

    if (count >= 10) 
    {
        printf("❌ Section already has 10 students.\n");
        fclose(f);
        return;
    }

    fseek(f, 0, SEEK_END);
    getchar();

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
    printf("✅ Student Added Successfully!\n");
}

void enterMarks() 
{
    char stream[10], studentFile[50], marksFile[50];
    int section;
    struct Student s;
    struct Marks m;

    printf("Enter Stream (BIM/BIT/BCE): ");
    scanf("%s", stream);
    printf("Enter Section (1–5): ");
    scanf("%d", &section);

    makeFileName(stream, section, "students", studentFile);
    makeFileName(stream, section, "marks", marksFile);

    FILE *sf = fopen(studentFile, "r");
    FILE *mf = fopen(marksFile, "a");

    if (sf == NULL || mf == NULL) 
    {
        printf("Error opening files.\n");
        return;
    }

    while (fread(&s, sizeof(s), 1, sf)) 
    {
        printf("\nEntering marks for: %s (Roll: %d)\n", s.name, s.roll);
        m.roll = s.roll;

        printf("Which year is this student currently in (1–4)? ");
        scanf("%d", &m.currentYear);

        if (m.currentYear >= 1) 
        {
            printf("GPA Year 1: ");
            scanf("%f", &m.year1);
        } 
        else 
        {
            m.year1 = -1.0;
        }

        if (m.currentYear >= 2) 
        {
            printf("GPA Year 2: ");
            scanf("%f", &m.year2);
        } 
        else 
        {
            m.year2 = -1.0;
        }

        if (m.currentYear >= 3) 
        {
            printf("GPA Year 3: ");
            scanf("%f", &m.year3);
        } 
        else 
        {
            m.year3 = -1.0;
        }

        if (m.currentYear == 4) 
        {
            printf("GPA Year 4: ");
            scanf("%f", &m.year4);
        } 
        else 
        {
            m.year4 = -1.0;
        }

        m.total = 0;
        int filled = 0;

        if (m.year1 != -1.0) 
			{
				 m.total += m.year1; filled++; 
			}
        if (m.year2 != -1.0) 
			{
		 		m.total += m.year2; filled++;
		  	}
        if (m.year3 != -1.0) 
			{
				 m.total += m.year3; filled++; 
			}
        if (m.year4 != -1.0) 
			{
			 m.total += m.year4; filled++; 
			}

        if (filled > 0) 
        {
            m.total = m.total / filled;
        }

        fwrite(&m, sizeof(m), 1, mf);
    }

    fclose(sf);
    fclose(mf);
    printf("✅ Marks added successfully!\n");
}

void viewData() 
{
    char stream[10], fileName[50];
    int section, choice;
    struct Student s;
    struct Marks m;

    printf("Enter Stream (BIM/BIT/BCE): ");
    scanf("%s", stream);
    printf("Enter Section (1–5): ");
    scanf("%d", &section);

    printf("1. View Student Details\n2. View Marks\nChoose: ");
    scanf("%d", &choice);

    if (choice == 1) 
    {
        makeFileName(stream, section, "students", fileName);
        FILE *f = fopen(fileName, "r");

        if (f == NULL) 
        {
            printf("No student data found.\n");
            return;
        }

        printf("\n--- Student Details ---\n");
        while (fread(&s, sizeof(s), 1, f)) 
        {
            printf("Name: %s\n", s.name);
            printf("Roll: %d\n", s.roll);
            printf("Prev College: %s\n", s.prevCollege);
            printf("Phone: %s\n", s.phone);
            printf("Address: %s\n", s.address);
            printf("---------------------------\n");
        }
        fclose(f);
    } 
    else if (choice == 2) 
    {
        makeFileName(stream, section, "marks", fileName);
        FILE *f = fopen(fileName, "r");

        if (f == NULL) 
        {
            printf("No marks data found.\n");
            return;
        }

        printf("\n--- Marks Details ---\n");
        while (fread(&m, sizeof(m), 1, f)) 
        {
            printf("Roll: %d\n", m.roll);
            printf("Current Year: %d\n", m.currentYear);

            printf("Year 1 GPA: ");
            if (m.year1 == -1.0) 
				{
			 		printf("Not Yet\n");				  
				}
			else
			  	{
			  		printf("%.2f\n", m.year1); 
			  	}

            printf("Year 2 GPA: ");
            if (m.year2 == -1.0)
				{
			 		 printf("Not Yet\n"); 
				}
			else
				{
					 printf("%.2f\n", m.year2);
				}

            printf("Year 3 GPA: ");
            if (m.year3 == -1.0)
				{
					 printf("Not Yet\n"); 
				}
			 else
			 	{
				 	 printf("%.2f\n", m.year3);
				}

            printf("Year 4 GPA: ");
            if (m.year4 == -1.0)
				{
				 	 printf("Not Yet\n"); 
				}	
			else	
				{ 
				printf("%.2f\n", m.year4);
				}

            printf("GPA Average: %.2f\n", m.total);
            printf("---------------------------\n");
        }
        fclose(f);
    } 
    else 
    {
        printf("❌ Invalid choice.\n");
    }
}

void addTeacher() 
{
    struct Teacher t;
    FILE *f = fopen("teachers.txt", "a");

    if (f == NULL) 
    {
        printf("❌ Error opening file.\n");
        return;
    }

    getchar();
    printf("Enter Name: ");
    gets(t.name);
    printf("Enter Phone: ");
    gets(t.phone);
    printf("Enter Stream (BIM/BIT/BCE): ");
    gets(t.stream);
    printf("Enter Qualification: ");
    gets(t.qualification);
    printf("Enter Address: ");
    gets(t.address);

    fwrite(&t, sizeof(t), 1, f);
    fclose(f);
    printf("✅ Teacher Added Successfully!\n");
}

void viewTeachers() 
{
    struct Teacher t;
    FILE *f = fopen("teachers.txt", "a+");
    rewind(f);

    if (f == NULL) 
    {
        printf("❌ No teacher data found.\n");
        return;
    }

    printf("\n--- Teacher Details ---\n");
    while (fread(&t, sizeof(t), 1, f)) 
    {
        printf("Name: %s\n", t.name);
        printf("Phone: %s\n", t.phone);
        printf("Stream: %s\n", t.stream);
        printf("Qualification: %s\n", t.qualification);
        printf("Address: %s\n", t.address);
        printf("---------------------------\n");
    }

    fclose(f);
}

void addAttendance() 
{
    struct Attendance a;
    FILE *f = fopen("attendance.txt", "a");

    if (f == NULL) 
    {
        printf("❌ Error opening attendance file.\n");
        return;
    }

    getchar();
    printf("Enter Teacher Name: ");
    gets(a.name);

    char *days[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday"};

    for (int i = 0; i < 6; i++) 
    {
        printf("Enter number of classes on %s: ", days[i]);
        scanf("%d", &a.classes[i]);
    }

    fwrite(&a, sizeof(a), 1, f);
    fclose(f);
    printf("✅ Attendance added successfully!\n");
}

void viewAttendance() 
{
    struct Attendance a;
    FILE *f = fopen("attendance.txt", "a+");
    rewind(f);

    if (f == NULL) 
    {
        printf("❌ No attendance data found.\n");
        return;
    }

    char *days[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday"};

    printf("\n--- Teacher Attendance ---\n");
    while (fread(&a, sizeof(a), 1, f)) 
    {
        printf("Name: %s\n", a.name);
        for (int i = 0; i < 6; i++) 
        {
            printf("%s: %d classes\n", days[i], a.classes[i]);
        }
        printf("----------------------------\n");
    }

    fclose(f);
}

void studentManagementMenu() 
{
    int ch;

    do 
    {
        printf("\n--- Student Management Menu ---\n");
        printf("1. Add Student\n");
        printf("2. Enter Marks\n");
        printf("3. View Students or Marks\n");
        printf("4. Back to School Menu\n");
        printf("Enter choice: ");
        scanf("%d", &ch);

        if (ch == 1) 
        {
            addStudent();
        } 
        else if (ch == 2) 
        {
            enterMarks();
        } 
        else if (ch == 3) 
        {
            viewData();
        } 
        else if (ch == 4) 
        {
            break;
        } 
        else 
        {
            printf("Invalid choice.\n");
        }

    } while (ch != 4);
}

void schoolMenu() 
{
    int ch;

    do 
    {
        printf("\n--- School Management System ---\n");
        printf("1. Student Management\n");
        printf("2. Staff Management\n");
        printf("3. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &ch);

        if (ch == 1) 
        {
            studentManagementMenu();
        } 
        else if (ch == 2) 
        {
            int staffChoice;

            do 
            {
                printf("\n--- Staff Management Menu ---\n");
                printf("1. Add Teacher\n");
                printf("2. View Teachers\n");
                printf("3. Add Attendance\n");
                printf("4. View Attendance\n");
                printf("5. Back\n");
                printf("Enter your choice: ");
                scanf("%d", &staffChoice);

                if (staffChoice == 1) 
                {
                    addTeacher();
                } 
                else if (staffChoice == 2) 
                {
                    viewTeachers();
                } 
                else if (staffChoice == 3) 
                {
                    addAttendance();
                } 
                else if (staffChoice == 4) 
                {
                    viewAttendance();
                } 
                else if (staffChoice == 5) 
                {
                    break;
                } 
                else 
                {
                    printf("❌ Invalid choice.\n");
                }

            } while (staffChoice != 5);
        } 
        else if (ch == 3) 
        {
            break;
        } 
        else 
        {
            printf("❌ Invalid choice.\n");
        }

    } while (ch != 3);
}

int main() 
{
    int ch;

    do 
    {
        printf("\n=== AdminX Main Menu ===\n");
        printf("1. School Management System\n");
        printf("2. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &ch);

        if (ch == 1) 
        {
            printf("\n✅ Welcome to School Management System!\n");
            schoolMenu();
        } 
        else if (ch == 2) 
        {
            printf("👋 Exiting AdminX. Goodbye!\n");
        } 
        else 
        {
            printf("❌ Invalid choice. Try again.\n");
        }

    } 
	while (ch != 2);

    return 0;
}
