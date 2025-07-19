#include <stdio.h>
#include<stdlib.h>
#include <string.h>

struct User
{
    char username[100];
    char password[100];
};

void save_password(struct User x) {
    FILE *file;
    int i = 0;

    file = fopen("passwor.txt", "w");

    if (file != NULL)
	{
        
        while (x.username[i] != '\0') {
            if (x.username[i] == '\n') {
                x.username[i] = '\0';
                break;
            }
            i++;
        }
        i=0;
        while (x.password[i] != '\0') {
            if (x.password[i] == '\n') {
                x.password[i] = '\0';
                break;
            }
            i++;
        }

        fprintf(file, "%s\n%s\n", x.username, x.password);
        fclose(file);
        printf("Username and Password saved successfully!\n");
    } else {
        printf("Failed to save password!\n");
    }
}

void check_password() {
    FILE *file;
    char savedu[100];
    char savedp[100];
    char enteredu[100];
    char enteredp[100];
    int i = 0;
    int resultu,resultp;

    file = fopen("passwor.txt", "r");

    if (file != NULL) {
    	fgets(savedu, 100, file);
        fgets(savedp, 100, file);
        fclose(file);
        
        while (savedu[i] != '\0') {
            if (savedu[i] == '\n') {
                savedu[i] = '\0';
                break;
            }
            i++;
        }
			i=0;
        while (savedp[i] != '\0') {
            if (savedp[i] == '\n') {
                savedp[i] = '\0';
                break;
            }
            i++;
        }
        
		printf("Enter username: ");
        fgets(enteredu, 100, stdin);
        i = 0;
        while (enteredu[i] != '\0') {
            if (enteredu[i] == '\n') {
                enteredu[i] = '\0';
                break;
            }
            i++;
        }

        printf("Enter password to continue: ");
        fgets(enteredp, 100, stdin);

        i = 0;
        while (enteredp[i] != '\0') {
            if (enteredp[i] == '\n') {
                enteredp[i] = '\0';
                break;
            }
            i++;
        }
 		resultu = strcmp(savedu, enteredu);
        resultp = strcmp(savedp, enteredp);

        if (resultu == 0 && resultp == 0)
		{
            printf("Access granted!\n");
        } 
		else 
		{
            printf("Access denied. Wrong password.\n");
        }
    } 
	else
	 {
        printf("Password file not found.\n");
    }
}

int main() {
    struct User user;
    FILE *file;

    file = fopen("passwor.txt", "r");

    if (file == NULL)
	{
        printf("First time setup\n");
        printf("Enter username: ");
        fgets(user.username, 100, stdin);
        printf("Create password: ");
        fgets(user.password, 100, stdin);
        save_password(user);
    } 
	else
	 {
        check_password();
    } 


    return 0;
}