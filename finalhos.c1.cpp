#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_PATIENTS 100
#define MAX_DOCTORS 50
#define MAX_APPOINTMENTS 200

typedef struct {
    int id;
    char name[50];
    int age;
    char gender;
    char contact[15];
    char address[100];
    char bloodType[5];
} Patient;


typedef struct {
    int id;
    char name[50];
    char specialization[50];
    char contact[15];
    int available; 
} Doctor;


typedef struct {
    int id;
    int patientId;
    int doctorId;
    char date[11]; 
    char time[6];  
    char purpose[100];
    int completed;
} Appointment;


Patient patients[MAX_PATIENTS];
Doctor doctors[MAX_DOCTORS];
Appointment appointments[MAX_APPOINTMENTS];
int patientCount = 0;
int doctorCount = 0;
int appointmentCount = 0;


void displayMainMenu();
void patientManagement();
void doctorManagement();
void appointmentManagement();
void addPatient();
void viewAllPatients();
void searchPatient();
void updatePatient();
void addDoctor();
void viewAllDoctors();
void searchDoctor();
void updateDoctor();
void scheduleAppointment();
void viewAllAppointments();
void completeAppointment();
void saveData();
void loadData();
void clearInputBuffer();
void pressAnyKeyToContinue();
void printHeader(const char *title);

int main() {
    loadData();
    
    int choice;
    do {
        displayMainMenu();
        printf("\nEnter your choice: ");
        scanf("%d", &choice);
        clearInputBuffer();
        
        switch(choice) {
            case 1:
                patientManagement();
                break;
            case 2:
                doctorManagement();
                break;
            case 3:
                appointmentManagement();
                break;
            case 4:
                saveData();
                printf("\nData saved successfully. Exiting system...\n");
                printf("Thank you for using our Hospital Management System!\n");
                break;
            default:
                printf("\nInvalid choice. Please try again.\n");
                pressAnyKeyToContinue();
        }
    } while(choice != 4);
    
    return 0;
}

void displayMainMenu() {
    system("cls || clear");
    printHeader("HOSPITAL MANAGEMENT SYSTEM");
    printf("\n1. Patient Management");
    printf("\n2. Doctor Management");
    printf("\n3. Appointment Management");
    printf("\n4. Exit System");
    printf("\n");
    printf("\nPlease select an option to continue...");
}

void patientManagement() 
{
    int choice;
    do {
        system("cls || clear");
        printHeader("PATIENT MANAGEMENT");
        printf("\n1. Add New Patient");
        printf("\n2. View All Patients");
        printf("\n3. Search Patient");
        printf("\n4. Update Patient Record");
        printf("\n5. Return to Main Menu");
        printf("\n\nEnter your choice: ");
        scanf("%d", &choice);
        clearInputBuffer();
        
        switch(choice) {
            case 1: addPatient(); break;
            case 2: viewAllPatients(); break;
            case 3: searchPatient(); break;
            case 4: updatePatient(); break;
            case 5: break;
            default: 
                printf("\nInvalid choice. Please try again.\n");
                pressAnyKeyToContinue();
        }
    } while(choice != 5);
}

void addPatient() 
{
    system("cls || clear");
    printHeader("ADD NEW PATIENT");
    
    if(patientCount >= MAX_PATIENTS) 
	{
        printf("\nMaximum number of patients reached!\n");
        pressAnyKeyToContinue();
        return;
    }
    
    Patient p;
    p.id = 1000 + patientCount + 1;
    
    printf("\nPatient ID: %d\n", p.id);
    printf("\nEnter patient details:\n");
    
    printf("Full Name: ");
    fgets(p.name, sizeof(p.name), stdin);
    p.name[strcspn(p.name, "\n")] = '\0';
    
    printf("Age: ");
    scanf("%d", &p.age);
    clearInputBuffer();
    
    printf("Gender (M/F/O): ");
    scanf("%c", &p.gender);
    clearInputBuffer();
    p.gender = toupper(p.gender);
    
    printf("Contact Number: ");
    fgets(p.contact, sizeof(p.contact), stdin);
    p.contact[strcspn(p.contact, "\n")] = '\0';
    
    printf("Address: ");
    fgets(p.address, sizeof(p.address), stdin);
    p.address[strcspn(p.address, "\n")] = '\0';
    
    printf("Blood Type: ");
    fgets(p.bloodType, sizeof(p.bloodType), stdin);
    p.bloodType[strcspn(p.bloodType, "\n")] = '\0';
    
    patients[patientCount++] = p;
    
    printf("\nPatient added successfully!\n");
    printf("\nPatient Details:");
    printf("\nID: %d", p.id);
    printf("\nName: %s", p.name);
    printf("\nAge: %d", p.age);
    printf("\nGender: %c", p.gender);
    printf("\nContact: %s", p.contact);
    
    saveData();
    pressAnyKeyToContinue();
}

void viewAllPatients()
    {
    system("cls || clear");
    printHeader("ALL PATIENTS");
    
    if(patientCount == 0) {
        printf("\nNo patients found in the system.\n");
        pressAnyKeyToContinue();
        return;
    }
    
    printf("\n%-8s %-25s %-5s %-5s %-15s %-10s %-30s\n", 
           "ID", "Name", "Age", "Gender", "Contact", "Blood Type", "Address");
    printf("===================================================================\n");
    
    for(int i = 0; i < patientCount; i++) 
	{
        printf("%-8d %-25s %-5d %-5c %-15s %-10s %-30s\n", 
               patients[i].id, 
               patients[i].name, 
               patients[i].age,
               patients[i].gender,
               patients[i].contact,
               patients[i].bloodType,
               patients[i].address);
    }
    
    pressAnyKeyToContinue();
}

void searchPatient()
    {
    system("cls || clear");
    printHeader("SEARCH PATIENT");
    
    if(patientCount == 0) {
        printf("\nNo patients found in the system.\n");
        pressAnyKeyToContinue();
        return;
    }
    
    int choice;
    printf("\nSearch by:\n");
    printf("1. ID\n");
    printf("2. Name\n");
    printf("3. Blood Type\n");
    printf("4. Return\n");
    printf("\nEnter your choice: ");
    scanf("%d", &choice);
    clearInputBuffer();
    
    if(choice == 4) return;
    
    char searchTerm[50];
    int found = 0;
    
    switch(choice) {
        case 1: {
            int id;
            printf("\nEnter Patient ID: ");
            scanf("%d", &id);
            clearInputBuffer();
            
            printf("\n%-8s %-25s %-5s %-5s %-15s %-10s\n", 
                   "ID", "Name", "Age", "Gender", "Contact", "Blood Type");
            printf("----------------------------------------------------\n");
            
            for(int i = 0; i < patientCount; i++) 
			{
                if(patients[i].id == id) 
				{
                    printf("%-8d %-25s %-5d %-5c %-15s %-10s\n", 
                           patients[i].id, 
                           patients[i].name, 
                           patients[i].age,
                           patients[i].gender,
                           patients[i].contact,
                           patients[i].bloodType);
                    found = 1;
                    break;
                }
            }
            break;
        }
        case 2:
            printf("\nEnter Patient Name: ");
            fgets(searchTerm, sizeof(searchTerm), stdin);
            searchTerm[strcspn(searchTerm, "\n")] = '\0';
            
            printf("\n%-8s %-25s %-5s %-5s %-15s\n", 
                   "ID", "Name", "Age", "Gender", "Contact");
            printf("--------------------------------------------\n");
            
            for(int i = 0; i < patientCount; i++) 
			{
                if(strstr(patients[i].name, searchTerm) != NULL) 
				{
                    printf("%-8d %-25s %-5d %-5c %-15s\n", 
                           patients[i].id, 
                           patients[i].name, 
                           patients[i].age,
                           patients[i].gender,
                           patients[i].contact);
                    found = 1;
                }
            }
            break;
        case 3:
            printf("\nEnter Blood Type: ");
            fgets(searchTerm, sizeof(searchTerm), stdin);
            searchTerm[strcspn(searchTerm, "\n")] = '\0';
            
            printf("\n%-8s %-25s %-5s %-10s\n", 
                   "ID", "Name", "Age", "Blood Type");
            printf("------------------------------------\n");
            
            for(int i = 0; i < patientCount; i++) 
			{
                if(strstr(patients[i].bloodType, searchTerm) != NULL) 
				{
                    printf("%-8d %-25s %-5d %-10s\n", 
                           patients[i].id, 
                           patients[i].name, 
                           patients[i].age,
                           patients[i].bloodType);
                    found = 1;
                }
            }
            break;
        default:
            printf("\nInvalid choice.\n");
            pressAnyKeyToContinue();
            return;
    }
    
    if(!found) 
	{
        printf("\nNo matching patients found.\n");
    }
    
    pressAnyKeyToContinue();
}

void updatePatient() 
{
    system("cls || clear");
    printHeader("UPDATE PATIENT RECORD");
    
    if(patientCount == 0) 
	{
        printf("\nNo patients found in the system.\n");
        pressAnyKeyToContinue();
        return;
    }
    
    int id;
    printf("\nEnter Patient ID to update: ");
    scanf("%d", &id);
    clearInputBuffer();
    
    int index = -1;
    for(int i = 0; i < patientCount; i++) 
	{
        if(patients[i].id == id) 
		{
            index = i;
            break;
        }
    }
    
    if(index == -1) 
	{
        printf("\nPatient with ID %d not found.\n", id);
        pressAnyKeyToContinue();
        return;
    }
    
    printf("\nCurrent Information:");
    printf("\nID: %d", patients[index].id);
    printf("\nName: %s", patients[index].name);
    printf("\nAge: %d", patients[index].age);
    printf("\nGender: %c", patients[index].gender);
    printf("\nContact: %s", patients[index].contact);
    printf("\nBlood Type: %s", patients[index].bloodType);
    printf("\nAddress: %s", patients[index].address);
    
    printf("\n\nEnter new information (leave blank to keep current):");
    
    char input[100];
    
    printf("\n\nName (%s): ", patients[index].name);
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';
    if(strlen(input) > 0) 
	{
        strcpy(patients[index].name, input);
    }
    
    printf("Age (%d): ", patients[index].age);
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';
    if(strlen(input) > 0) 
	{
        patients[index].age = atoi(input);
    }
    
    printf("Gender (%c): ", patients[index].gender);
    char gender = getchar();
    clearInputBuffer();
    if(gender != '\n') 
	{
        patients[index].gender = toupper(gender);
    }
    
    printf("Contact (%s): ", patients[index].contact);
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';
    if(strlen(input) > 0) 
	{
        strcpy(patients[index].contact, input);
    }
    
    printf("Blood Type (%s): ", patients[index].bloodType);
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';
    if(strlen(input) > 0) 
	{
        strcpy(patients[index].bloodType, input);
    }
    
    printf("Address (%s): ", patients[index].address);
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';
    if(strlen(input) > 0) 
	{
        strcpy(patients[index].address, input);
    }
    
    printf("\nPatient record updated successfully!\n");
    
    saveData();
    pressAnyKeyToContinue();
}
void doctorManagement() 
{
    int choice;
    do {
        system("cls || clear");
        printHeader("DOCTOR MANAGEMENT");
        printf("\n1. Add New Doctor");
        printf("\n2. View All Doctors");
        printf("\n3. Search Doctor");
        printf("\n4. Update Doctor Information");
        printf("\n5. Return to Main Menu");
        printf("\n\nEnter your choice: ");
        scanf("%d", &choice);
        clearInputBuffer();
        
        switch(choice) {
            case 1: addDoctor(); break;
            case 2: viewAllDoctors(); break;
            case 3: searchDoctor(); break;
            case 4: updateDoctor(); break;
            case 5: break;
            default: 
                printf("\nInvalid choice. Please try again.\n");
                pressAnyKeyToContinue();
        }
    } while(choice != 5);
}

void addDoctor() 
{
    system("cls || clear");
    printHeader("ADD NEW DOCTOR");
    
    if(doctorCount >= MAX_DOCTORS) 
	{
        printf("\nMaximum number of doctors reached!\n");
        pressAnyKeyToContinue();
        return;
    }
    
    Doctor d;
    d.id = 2000 + doctorCount + 1;
    d.available = 1;
    
    printf("\nDoctor ID: %d\n", d.id);
    printf("\nEnter doctor details:\n");
    
    printf("Full Name: ");
    fgets(d.name, sizeof(d.name), stdin);
    d.name[strcspn(d.name, "\n")] = '\0';
    
    printf("Specialization: ");
    fgets(d.specialization, sizeof(d.specialization), stdin);
    d.specialization[strcspn(d.specialization, "\n")] = '\0';
    
    printf("Contact Number: ");
    fgets(d.contact, sizeof(d.contact), stdin);
    d.contact[strcspn(d.contact, "\n")] = '\0';
    
    doctors[doctorCount++] = d;
    
    printf("\nDoctor added successfully!\n");
    printf("\nDoctor Details:");
    printf("\nID: %d", d.id);
    printf("\nName: %s", d.name);
    printf("\nSpecialization: %s", d.specialization);
    printf("\nContact: %s", d.contact);
    printf("\nStatus: %s", d.available ? "Available" : "Not Available");
    
    saveData();
    pressAnyKeyToContinue();
}

void viewAllDoctors() 
{
    system("cls || clear");
    printHeader("ALL DOCTORS");
    
    if(doctorCount == 0) 
	{
        printf("\nNo doctors found in the system.\n");
        pressAnyKeyToContinue();
        return;
    }
    
    printf("\n%-8s %-25s %-20s %-15s %s\n", 
           "ID", "Name", "Specialization", "Contact", "Status");
    printf("-----------------------------------------------------------------\n");
    
    for(int i = 0; i < doctorCount; i++) 
	{
        printf("%-8d %-25s %-20s %-15s %s\n", 
               doctors[i].id, 
               doctors[i].name, 
               doctors[i].specialization, 
               doctors[i].contact,
               doctors[i].available ? "Available" : "Not Available");
    }
    
    pressAnyKeyToContinue();
}

void searchDoctor() 
{
    system("cls || clear");
    printHeader("SEARCH DOCTOR");
    
    if(doctorCount == 0) 
	{
        printf("\nNo doctors found in the system.\n");
        pressAnyKeyToContinue();
        return;
    }
    
    int choice;
    printf("\nSearch by:\n");
    printf("1. ID\n");
    printf("2. Name\n");
    printf("3. Specialization\n");
    printf("4. Return\n");
    printf("\nEnter your choice: ");
    scanf("%d", &choice);
    clearInputBuffer();
    
    if(choice == 4) return;
    
    char searchTerm[50];
    int found = 0;
    
    switch(choice) {
        case 1: {
            int id;
            printf("\nEnter Doctor ID: ");
            scanf("%d", &id);
            clearInputBuffer();
            
            printf("\n%-8s %-25s %-20s %-15s\n", 
                   "ID", "Name", "Specialization", "Contact");
            printf("----------------------------------------------------\n");
            
            for(int i = 0; i < doctorCount; i++) 
			{
                if(doctors[i].id == id) {
                    printf("%-8d %-25s %-20s %-15s\n", 
                           doctors[i].id, 
                           doctors[i].name, 
                           doctors[i].specialization,
                           doctors[i].contact);
                    found = 1;
                    break;
                }
            }
            break;
        }
        case 2:
            printf("\nEnter Doctor Name: ");
            fgets(searchTerm, sizeof(searchTerm), stdin);
            searchTerm[strcspn(searchTerm, "\n")] = '\0';
            
            printf("\n%-8s %-25s %-20s\n", 
                   "ID", "Name", "Specialization");
            printf("----------------------------------------\n");
            
            for(int i = 0; i < doctorCount; i++) 
			{
                if(strstr(doctors[i].name, searchTerm) != NULL) 
				{
                    printf("%-8d %-25s %-20s\n", 
                           doctors[i].id, 
                           doctors[i].name, 
                           doctors[i].specialization);
                    found = 1;
                }
            }
            break;
        case 3:
            printf("\nEnter Specialization: ");
            fgets(searchTerm, sizeof(searchTerm), stdin);
            searchTerm[strcspn(searchTerm, "\n")] = '\0';
            
            printf("\n%-8s %-25s %-20s\n", 
                   "ID", "Name", "Specialization");
            printf("----------------------------------------\n");
            
            for(int i = 0; i < doctorCount; i++) 
			{
                if(strstr(doctors[i].specialization, searchTerm) != NULL) 
				{
                    printf("%-8d %-25s %-20s\n", 
                           doctors[i].id, 
                           doctors[i].name, 
                           doctors[i].specialization);
                    found = 1;
                }
            }
            break;
        default:
            printf("\nInvalid choice.\n");
            pressAnyKeyToContinue();
            return;
    }
    
    if(!found) 
	{
        printf("\nNo matching doctors found.\n");
    }
    
    pressAnyKeyToContinue();
}

void updateDoctor() 
{
    system("cls || clear");
    printHeader("UPDATE DOCTOR INFORMATION");
    
    if(doctorCount == 0) {
        printf("\nNo doctors found in the system.\n");
        pressAnyKeyToContinue();
        return;
    }
    
    int id;
    printf("\nEnter Doctor ID to update: ");
    scanf("%d", &id);
    clearInputBuffer();
    
    int index = -1;
    for(int i = 0; i < doctorCount; i++) 
	{
        if(doctors[i].id == id) 
		{
            index = i;
            break;
        }
    }
    
    if(index == -1) 
	{
        printf("\nDoctor with ID %d not found.\n", id);
        pressAnyKeyToContinue();
        return;
    }
    
    printf("\nCurrent Information:");
    printf("\nID: %d", doctors[index].id);
    printf("\nName: %s", doctors[index].name);
    printf("\nSpecialization: %s", doctors[index].specialization);
    printf("\nContact: %s", doctors[index].contact);
    printf("\nStatus: %s", doctors[index].available ? "Available" : "Not Available");
    
    printf("\n\nEnter new information (leave blank to keep current):");
    
    char input[100];
    
    printf("\n\nName (%s): ", doctors[index].name);
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';
    if(strlen(input) > 0) 
	{
        strcpy(doctors[index].name, input);
    }
    
    printf("Specialization (%s): ", doctors[index].specialization);
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';
    if(strlen(input) > 0) {
        strcpy(doctors[index].specialization, input);
    }
    
    printf("Contact (%s): ", doctors[index].contact);
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';
    if(strlen(input) > 0) 
	{
        strcpy(doctors[index].contact, input);
    }
    
    printf("Availability (1 for Available, 0 for Not Available) (%d): ", doctors[index].available);
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';
    if(strlen(input) > 0)
	{
        doctors[index].available = atoi(input);
    }
    
    printf("\nDoctor information updated successfully!\n");
    
    saveData();
    pressAnyKeyToContinue();
}

void appointmentManagement() {
    int choice;
    do {
        system("cls || clear");
        printHeader("APPOINTMENT MANAGEMENT");
        printf("\n1. Schedule New Appointment");
        printf("\n2. View All Appointments");
        printf("\n3. Complete Appointment");
        printf("\n4. Return to Main Menu");
        printf("\n\nEnter your choice: ");
        scanf("%d", &choice);
        clearInputBuffer();
        
        switch(choice) {
            case 1: scheduleAppointment(); break;
            case 2: viewAllAppointments(); break;
            case 3: completeAppointment(); break;
            case 4: break;
            default: 
                printf("\nInvalid choice. Please try again.\n");
                pressAnyKeyToContinue();
        }
    } while(choice != 4);
}

void scheduleAppointment() 
{
    system("cls || clear");
    printHeader("SCHEDULE NEW APPOINTMENT");
    
    if(patientCount == 0 || doctorCount == 0) 
	{
        printf("\nCannot schedule appointment. Need at least one doctor and one patient.\n");
        pressAnyKeyToContinue();
        return;
    }
    
    if(appointmentCount >= MAX_APPOINTMENTS) 
	{
        printf("\nMaximum number of appointments reached!\n");
        pressAnyKeyToContinue();
        return;
    }
    
    Appointment a;
    a.id = 3000 + appointmentCount + 1;
    a.completed = 0;
    
    printf("\nAppointment ID: %d\n", a.id);
    
    printf("\nAvailable Patients:\n");
    printf("%-8s %-25s\n", "ID", "Name");
    printf("-------------------------\n");
    for(int i = 0; i < patientCount; i++) 
	{
        printf("%-8d %-25s\n", patients[i].id, patients[i].name);
    }
    
    printf("\nEnter Patient ID: ");
    scanf("%d", &a.patientId);
    clearInputBuffer();
    
    int patientIndex = -1;
    for(int i = 0; i < patientCount; i++) 
	{
        if(patients[i].id == a.patientId)
		 {
            patientIndex = i;
            break;
        }
    }
    
    if(patientIndex == -1) 
	{
        printf("\nInvalid Patient ID.\n");
        pressAnyKeyToContinue();
        return;
    }
    
    // Select doctor
    printf("\nAvailable Doctors:\n");
    printf("%-8s %-25s %-20s\n", "ID", "Name", "Specialization");
    printf("-------------------------------------------------\n");
    for(int i = 0; i < doctorCount; i++) 
	{
        if(doctors[i].available) 
		{
            printf("%-8d %-25s %-20s\n", doctors[i].id, doctors[i].name, doctors[i].specialization);
        }
    }
    
    printf("\nEnter Doctor ID: ");
    scanf("%d", &a.doctorId);
    clearInputBuffer();
    
    int doctorIndex = -1;
    for(int i = 0; i < doctorCount; i++) 
	{
        if(doctors[i].id == a.doctorId) 
		{
            doctorIndex = i;
            break;
        }
    }
    
    if(doctorIndex == -1)
	{
        printf("\nInvalid Doctor ID.\n");
        pressAnyKeyToContinue();
        return;
    }
    
    if(!doctors[doctorIndex].available) 
	{
        printf("\nSelected doctor is not available.\n");
        pressAnyKeyToContinue();
        return;
    }
    
    printf("\nEnter Date (YYYY-MM-DD): ");
    fgets(a.date, sizeof(a.date), stdin);
    a.date[strcspn(a.date, "\n")] = '\0';
    
    printf("Enter Time (HH:MM): ");
    fgets(a.time, sizeof(a.time), stdin);
    a.time[strcspn(a.time, "\n")] = '\0';
    
    printf("Enter Purpose: ");
    fgets(a.purpose, sizeof(a.purpose), stdin);
    a.purpose[strcspn(a.purpose, "\n")] = '\0';
    
    appointments[appointmentCount++] = a;
    
    printf("\nAppointment scheduled successfully!\n");
    printf("\nAppointment Details:");
    printf("\nID: %d", a.id);
    printf("\nPatient: %s (ID: %d)", patients[patientIndex].name, a.patientId);
    printf("\nDoctor: %s (ID: %d)", doctors[doctorIndex].name, a.doctorId);
    printf("\nDate: %s", a.date);
    printf("\nTime: %s", a.time);
    printf("\nPurpose: %s", a.purpose);
    
    saveData();
    pressAnyKeyToContinue();
}

void viewAllAppointments() {
    system("cls || clear");
    printHeader("ALL APPOINTMENTS");
    
    if(appointmentCount == 0) 
	{
        printf("\nNo appointments found in the system.\n");
        pressAnyKeyToContinue();
        return;
    }
    
    printf("\n%-8s %-8s %-25s %-8s %-25s %-11s %-6s %-20s %s\n", 
           "App ID", "Pat ID", "Patient Name", "Dr ID", "Doctor Name", "Date", "Time", "Purpose", "Status");
    printf("===================================================================================================\n");
    
    for(int i = 0; i < appointmentCount; i++) 
	{
      
        char patientName[50] = "Unknown";
        for(int j = 0; j < patientCount; j++) 
		{
            if(patients[j].id == appointments[i].patientId) {
                strcpy(patientName, patients[j].name);
                break;
            }
        }
        
       
        char doctorName[50] = "Unknown";
        for(int j = 0; j < doctorCount; j++) 
		{
            if(doctors[j].id == appointments[i].doctorId) 
			{
                strcpy(doctorName, doctors[j].name);
                break;
            }
        }
        
        printf("%-8d %-8d %-25s %-8d %-25s %-11s %-6s %-20s %s\n", 
               appointments[i].id,
               appointments[i].patientId,
               patientName,
               appointments[i].doctorId,
               doctorName,
               appointments[i].date,
               appointments[i].time,
               appointments[i].purpose,
               appointments[i].completed ? "Completed" : "Pending");
    }
    
    pressAnyKeyToContinue();
}

void completeAppointment() 
{
    system("cls || clear");
    printHeader("COMPLETE APPOINTMENT");
    
    if(appointmentCount == 0) 
	{
        printf("\nNo appointments found in the system.\n");
        pressAnyKeyToContinue();
        return;
    }
    
    printf("\nPending Appointments:\n");
    printf("%-8s %-8s %-25s %-8s %-25s %-11s %-6s\n", 
           "App ID", "Pat ID", "Patient Name", "Dr ID", "Doctor Name", "Date", "Time");
    printf("-------------------------------------------------------------------------------\n");
    
    int pendingCount = 0;
    for(int i = 0; i < appointmentCount; i++) 
	{
        if(!appointments[i].completed) 
		{
          
            char patientName[50] = "Unknown";
            for(int j = 0; j < patientCount; j++) {
                if(patients[j].id == appointments[i].patientId) {
                    strcpy(patientName, patients[j].name);
                    break;
                }
            }
            
           
            char doctorName[50] = "Unknown";
            for(int j = 0; j < doctorCount; j++) 
			{
                if(doctors[j].id == appointments[i].doctorId) 
				{
                    strcpy(doctorName, doctors[j].name);
                    break;
                }
            }
            
            printf("%-8d %-8d %-25s %-8d %-25s %-11s %-6s\n", 
                   appointments[i].id,
                   appointments[i].patientId,
                   patientName,
                   appointments[i].doctorId,
                   doctorName,
                   appointments[i].date,
                   appointments[i].time);
            pendingCount++;
        }
    }
    
    if(pendingCount == 0) 
	{
        printf("\nNo pending appointments found.\n");
        pressAnyKeyToContinue();
        return;
    }
    
    int id;
    printf("\nEnter Appointment ID to mark as completed: ");
    scanf("%d", &id);
    clearInputBuffer();
    
    int found = 0;
    for(int i = 0; i < appointmentCount; i++) 
	{
        if(appointments[i].id == id && !appointments[i].completed) 
		{
            appointments[i].completed = 1;
            found = 1;
            break;
        }
    }
    
    if(found) 
	{
        printf("\nAppointment marked as completed successfully!\n");
        saveData();
    } 
	else 
	{
        printf("\nAppointment not found or already completed.\n");
    }
    
    pressAnyKeyToContinue();
}

void saveData() {
    FILE *file = fopen("hospital_data.dat", "wb");
    if(file == NULL) 
	{
        printf("Error saving data!\n");
        return;
    }
    
    fwrite(&patientCount, sizeof(int), 1, file);
    fwrite(&doctorCount, sizeof(int), 1, file);
    fwrite(&appointmentCount, sizeof(int), 1, file);
    
    fwrite(patients, sizeof(Patient), patientCount, file);
    fwrite(doctors, sizeof(Doctor), doctorCount, file);
    fwrite(appointments, sizeof(Appointment), appointmentCount, file);
    
    fclose(file);
}

void loadData() {
    FILE *file = fopen("hospital_data.dat", "rb");
    if(file == NULL) 
	{
        return;
    }
    

    fread(&patientCount, sizeof(int), 1, file);
    fread(&doctorCount, sizeof(int), 1, file);
    fread(&appointmentCount, sizeof(int), 1, file);
    
    fread(patients, sizeof(Patient), patientCount, file);
    fread(doctors, sizeof(Doctor), doctorCount, file);
    fread(appointments, sizeof(Appointment), appointmentCount, file);
    
    fclose(file);
}

void clearInputBuffer() 
{
    while(getchar() != '\n');
}

void pressAnyKeyToContinue() 
{
    printf("\nPress Enter to continue...");
    getchar();
}

void printHeader(const char *title) 
{
    printf("\n=== %s ===\n", title);
}

















