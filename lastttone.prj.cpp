#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct {
    int id;
    char name[50];
    int age;
    char gender;
} Patient;

typedef struct {
    int id;
    char name[50];
    char specialization[50];
} Doctor;

typedef struct {
    int id;
    int patientId;
    int doctorId;
    char date[11]; 
    char time[6];   
} Appointment;

Patient patients[MAX];
Doctor doctors[MAX];
Appointment appointments[MAX];
int patientCount = 0, doctorCount = 0, appointmentCount = 0;

void clearInputBuffer() {
    while(getchar() != '\n');
}

void pressAnyKey() {
    printf("\nPress Enter to continue...");
    getchar();
}

void saveData() {
    FILE *file = fopen("hospital.dat", "wb");
    if(file) {
        fwrite(&patientCount, sizeof(int), 1, file);
        fwrite(&doctorCount, sizeof(int), 1, file);
        fwrite(&appointmentCount, sizeof(int), 1, file);
        fwrite(patients, sizeof(Patient), patientCount, file);
        fwrite(doctors, sizeof(Doctor), doctorCount, file);
        fwrite(appointments, sizeof(Appointment), appointmentCount, file);
        fclose(file);
    }
}

void loadData() {
    FILE *file = fopen("hospital.dat", "rb");
    if(file) {
        fread(&patientCount, sizeof(int), 1, file);
        fread(&doctorCount, sizeof(int), 1, file);
        fread(&appointmentCount, sizeof(int), 1, file);
        fread(patients, sizeof(Patient), patientCount, file);
        fread(doctors, sizeof(Doctor), doctorCount, file);
        fread(appointments, sizeof(Appointment), appointmentCount, file);
        fclose(file);
    }
}

void addPatient() {
    if(patientCount >= MAX) {
        printf("Patient limit reached!\n");
        return;
    }
    
    Patient p;
    p.id = 1000 + patientCount + 1;
    
    printf("\nPatient ID: %d\n", p.id);
    printf("Name: ");
    fgets(p.name, 50, stdin);
    p.name[strcspn(p.name, "\n")] = '\0';
    
    printf("Age: ");
    scanf("%d", &p.age);
    clearInputBuffer();
    
    printf("Gender (M/F): ");
    scanf("%c", &p.gender);
    clearInputBuffer();
    
    patients[patientCount++] = p;
    printf("Patient added successfully!\n");
    saveData();
}

void viewPatients() {
    if(patientCount == 0) {
        printf("No patients found!\n");
        return;
    }
    
    printf("\nID\tName\t\tAge\tGender\n");
    printf("--------------------------------\n");
    for(int i = 0; i < patientCount; i++) {
        printf("%d\t%s\t%d\t%c\n", 
              patients[i].id, patients[i].name, 
              patients[i].age, patients[i].gender);
    }
}

void patientPanel() {
    int choice;
    do {
        printf("\n=== PATIENT MANAGEMENT ===\n");
        printf("1. Add Patient\n");
        printf("2. View Patients\n");
        printf("3. Back to Main\n");
        printf("Choice: ");
        scanf("%d", &choice);
        clearInputBuffer();
        
        switch(choice) {
            case 1: addPatient(); break;
            case 2: viewPatients(); break;
            case 3: return;
            default: printf("Invalid choice!\n");
        }
        pressAnyKey();
    } while(1);
}


void addDoctor() {
    if(doctorCount >= MAX) {
        printf("Doctor limit reached!\n");
        return;
    }
    
    Doctor d;
    d.id = 2000 + doctorCount + 1;
    
    printf("\nDoctor ID: %d\n", d.id);
    printf("Name: ");
    fgets(d.name, 50, stdin);
    d.name[strcspn(d.name, "\n")] = '\0';
    
    printf("Specialization: ");
    fgets(d.specialization, 50, stdin);
    d.specialization[strcspn(d.specialization, "\n")] = '\0';
    
    doctors[doctorCount++] = d;
    printf("Doctor added successfully!\n");
    saveData();
}

void viewDoctors() {
    if(doctorCount == 0) {
        printf("No doctors found!\n");
        return;
    }
    
    printf("\nID\tName\t\tSpecialization\n");
    printf("--------------------------------\n");
    for(int i = 0; i < doctorCount; i++) {
        printf("%d\t%s\t%s\n", 
              doctors[i].id, doctors[i].name, 
              doctors[i].specialization);
    }
}

void doctorPanel() {
    int choice;
    do {
        printf("\n=== DOCTOR MANAGEMENT ===\n");
        printf("1. Add Doctor\n");
        printf("2. View Doctors\n");
        printf("3. Back to Main\n");
        printf("Choice: ");
        scanf("%d", &choice);
        clearInputBuffer();
        
        switch(choice) {
            case 1: addDoctor(); break;
            case 2: viewDoctors(); break;
            case 3: return;
            default: printf("Invalid choice!\n");
        }
        pressAnyKey();
    } while(1);
}


void scheduleAppointment() {
    if(patientCount == 0 || doctorCount == 0) {
        printf("Need at least 1 patient and 1 doctor!\n");
        return;
    }
    
    if(appointmentCount >= MAX) {
        printf("Appointment limit reached!\n");
        return;
    }
    
    Appointment a;
    a.id = 3000 + appointmentCount + 1;
    
    printf("\nAvailable Patients:\n");
    viewPatients();
    printf("\nEnter Patient ID: ");
    scanf("%d", &a.patientId);
    clearInputBuffer();
    
    printf("\nAvailable Doctors:\n");
    viewDoctors();
    printf("\nEnter Doctor ID: ");
    scanf("%d", &a.doctorId);
    clearInputBuffer();
    
    printf("Enter Date (YYYY-MM-DD): ");
    fgets(a.date, 11, stdin);
    a.date[strcspn(a.date, "\n")] = '\0';
    
    printf("Enter Time (HH:MM): ");
    fgets(a.time, 6, stdin);
    a.time[strcspn(a.time, "\n")] = '\0';
    
    appointments[appointmentCount++] = a;
    printf("Appointment scheduled successfully!\n");
    saveData();
}

void viewAppointments() {
    if(appointmentCount == 0) {
        printf("No appointments found!\n");
        return;
    }
    
    printf("\nID\tPatient\t\tDoctor\t\tDate\t\tTime\n");
    printf("------------------------------------------------\n");
    
    for(int i = 0; i < appointmentCount; i++) {
        char patientName[50] = "Unknown";
        char doctorName[50] = "Unknown";
        
   
        for(int j = 0; j < patientCount; j++) {
            if(patients[j].id == appointments[i].patientId) {
                strcpy(patientName, patients[j].name);
                break;
            }
        }
        
      
        for(int j = 0; j < doctorCount; j++) {
            if(doctors[j].id == appointments[i].doctorId) {
                strcpy(doctorName, doctors[j].name);
                break;
            }
        }
        
        printf("%d\t%s\t%s\t%s\t%s\n",
              appointments[i].id,
              patientName,
              doctorName,
              appointments[i].date,
              appointments[i].time);
    }
}

void appointmentPanel() {
    int choice;
    do {
        printf("\n=== APPOINTMENT MANAGEMENT ===\n");
        printf("1. Schedule Appointment\n");
        printf("2. View Appointments\n");
        printf("3. Back to Main\n");
        printf("Choice: ");
        scanf("%d", &choice);
        clearInputBuffer();
        
        switch(choice) {
            case 1: scheduleAppointment(); break;
            case 2: viewAppointments(); break;
            case 3: return;
            default: printf("Invalid choice!\n");
        }
        pressAnyKey();
    } while(1);
}


int main() {
    loadData();
    
    int choice;
    do {
        printf("\n=== HOSPITAL MANAGEMENT SYSTEM ===\n");
        printf("1. Patient Panel\n");
        printf("2. Doctor Panel\n");
        printf("3. Appointment Panel\n");
        printf("4. Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);
        clearInputBuffer();
        
        switch(choice) {
            case 1: patientPanel(); break;
            case 2: doctorPanel(); break;
            case 3: appointmentPanel(); break;
            case 4: 
                saveData();
                printf("Goodbye!\n");
                exit(0);
            default: printf("Invalid choice!\n");
        }
    } while(1);
    
    return 0;
}