/*
    Name: Mohammad Kothawala
	ID: 1000731739
	Class: CSE-3320-001
	Instructor: Dr. Levine
	Assignment 1

*/
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <time.h>
#include <curses.h>
#define CWD_BUFFER 256
#define BUFFER 2048
#define NUMBER_STRINGS 2000
char returnChoice();
void runProgram(char* file[]);
void editProgram(char* file[]);
void changeDirectory();
int main(void) {
    pid_t child;
    DIR * dir;
    struct dirent* de;
    int i, count, k;
    char s[BUFFER], cmd[BUFFER];
    char choice, c;
    char *array[NUMBER_STRINGS];
    /*char[] token = "./";*/
    int row = 0;
    char* run;
    time_t t;
    int flag = 1;
    int state;
    int event = 1;
    int cond = 1;
    int size = 0;
    char* str[size];
    int incr = 0;
    int j = 0;
    int range;
    int index;
    int number;
    int result;
    int quan;


    /*get current date and time*/
    t = time(NULL);

    /*Print current time and date*/
    printf("\nCurrent Date and Time: %s", ctime(&t));

    /*"getcwd" gets the name of the current directory and stores it into s*/
    getcwd(s, 200);
    dir = opendir(".");
    while((de = readdir(dir))) {
        if ((de->d_type) == DT_REG) {
            array[size] = de->d_name;
            size++;
        }
    }
    closedir(dir);

    /*prints the name of current directory*/
    printf("Current Directory: %s \n\n", s);
    printf("\n\n-----------------------------------------------\n");

    while(1) {
        i = 0;
        flag = 1;

        /*Function call to show the available operation
        and to retrieve the user choice*/
        choice = returnChoice();


        /*'L': List all directories and Files*/
        if(choice == 'L' || choice == 'l') {

            /*Open Directory*/
            dir = opendir(".");
            printf("DIRECTORIES:\n");
            count = 0;
            while(de = readdir(dir)) {

                if (((de->d_type) & DT_DIR))
                    printf( "\t%02d. Directory: %s\n", count++, de->d_name);

            }
            closedir(dir);
            if(count = 0)
                printf("Directories do not exist\n\n");

            /*Reset Counter*/
            count = 0;
            state = 1;

            dir = opendir(".");
            printf("FILES:\n");
            while(state) {
                if(flag == 1) {
                    while(de = readdir(dir)) {
                        if (count <8) {
                            if ((de->d_type) == DT_REG) {
                                printf("\t%03d. File: %s\n", count, array[count]);
                                count++;
                            }
                        } else {
                            printf("Hit ('N' or 'n') for Next 8 files\n");
                            printf("Hit ('P' or 'p') for Previous 8 files\n");
                            printf("Hit ('X' or 'x') for main menu\n");
                            printf("Hit ('R' or 'r') to run a program\n");
                            printf("Hit ('E' or 'e' to edit a file\n");
                            printf("Hit ('C' or 'c' to change Directory\n\n");
                            printf("Please enter your choice: ");

                            break;
                        }
                    }
                    flag = 0;
                }
                if(flag == 0) {
                    while(event) {
                        scanf(" %c", &c);
                        getchar();
                        if (c == 'R' || c == 'r') {
                            runProgram(array);
                            printf("\nU have returned to the original program(currently running)\n");
                            printf("Hit ('N' or 'n') for Next\n");
                            printf("Hit ('P' or 'p') for Previous 8 files\n");
                            printf("Hit ('X' or 'x') for main menu\n");
                            printf("Hit ('E' or 'e' to edit a file\n");
                            printf("Hit ('C' or 'c' to change Directory\n\n");
                            printf("Enter your choice: ");
                            scanf(" %c", &c);
                            getchar();
                        }
                        else if (c == 'E' || c == 'e') {
                            editProgram(array);
                            printf("Hit ('N' or 'n') for Next\n");
                            printf("Hit ('X' or 'x') for main menu\n");
                            printf("Hit ('R' or 'r') to run a program\n");
                            printf("Hit ('E' or 'e' to edit a file\n");
                            printf("Hit ('C' or 'c' to change Directory\n\n");
                            printf("Enter your choice: ");
                            scanf(" %c", &c);
                            getchar();
                        }

                        else if (c == 'C' || c == 'c') {
                            changeDirectory();
                            printf("Hit ('N' or 'n') for Next\n");
                            printf("Hit ('X' or 'x') for main menu\n");
                            printf("Hit ('R' or 'r') to run a program\n");
                            printf("Hit ('E' or 'e' to edit a file\n");
                            printf("Hit ('C' or 'c' to change Directory\n\n");
                            printf("Enter your choice: ");
                            scanf(" %c", &c);
                            getchar();
                        }

                        else if (c == 'X' || c == 'x') {
                            /*closedir(dir);*/
                            break;
                        }
                        else if (c == 'N' || c == 'n') {
                            result = count + 8;
                            if(result > size) {
                                printf("No more files beyond this point\n");
                            } else {
                                while (count < result) {
                                    printf("\t%03d. File: %s\n", count, array[count]);
                                    count++;
                                }
                            }
                            printf("Hit ('N' or 'n') for Next\n");
                            printf("Hit ('R' or 'r') to run a program\n");
                            printf("Hit ('E' or 'e' to edit a file\n");
                            printf("Hit ('C' or 'c' to change Directory\n");
                            printf("Hit ('X' or 'x') for main menu\n\n");
                            printf("Please enter your choice: ");

                        }
                        else if(c == 'P' || c == 'p') {

                            count = count - 8;
                            if (count == 0 || count < 0) {
                                printf("No nmore files to show\n");
                                count += 8;
                            } else {
                                quan = count - 8;
                                for(j = quan; j < count; j++) {
                                    printf("\t%03d. File: %s\n", j, array[j]);
                                }
                            }
                            printf("Hit ('N' or 'n') for Next 8 files\n");
                            printf("Hit ('P' or 'p') for Previous 8 files\n");
                            printf("Hit ('X' or 'x') for main menu\n");
                            printf("Hit ('R' or 'r') to run a program\n");
                            printf("Hit ('E' or 'e' to edit a file\n");
                            printf("Hit ('C' or 'c' to change Directory\n\n");
                            printf("Please enter your choice: ");

                        } else {
                            printf("Command Does not exist.\n");
                            printf("Hit ('N' or 'n') for Next\n");
                            printf("Hit ('R' or 'r') to run a program\n");
                            printf("Hit ('E' or 'e' to edit a file\n");
                            printf("Hit ('C' or 'c' to change Directory\n");
                            printf("Hit ('X' or 'x') for main menu\n\n");
                            printf("Please enter your choice: ");
                            /*printf("Please Enter again ");*/


                        }
                        /*if ((count > 167) || (count == 167)){

                            event = 0;
                            break;
                        }*/
                    }/* end event*/

                }/*end if flaf*/
                state = 0;
                break;
            }/*end state*/
            closedir(dir);
        }/*end choice*/
        /*'E': Edit a file*/
        else if(choice == 'E' || choice == 'e') {
            printf("Edit what? ");
                        scanf("%d",&index);
                        strcpy(cmd, "pico ");
                        strcat(cmd, array[index]);
                        system(cmd);
                        continue;
           /* scanf("%s", s);
            //getchar();
            strcpy(cmd, "pico ");
            strcat(cmd, s);
            system(cmd);*/

        }
        /*'R': Runs a file or program*/
        else if(choice == 'R' || choice == 'r') {
            char token[BUFFER] = "./";

            printf("Press '1' to enter a file name or '0' to enter a file number: \n");
            printf("Enter your choice: ");
            scanf("%d", &number);

            if(number == 1){
                printf("\nRun what?(ENter name):");
                scanf( "%s", cmd);
                strcat(token,cmd);
                system(token);

            } else{
                printf("\nRun what?(ENter number):");
                scanf("%d",&index);
                system(array[index]);

            }


          /*
            printf("Run what?:");
            scanf( "%s", cmd);
            getchar();
            strcat(token,cmd);

            system(token);*/
        }

        else if(choice == 'C' || choice == 'c') {
            int found = 0; /* Mark if directory is found*/

            /* Get directory name */
            printf("Change To? (Enter directory name): ");
            scanf("%s", cmd);
            //getchar();
            dir = opendir(".");
            char direc[BUFFER] = "./";
            strcat(direc, cmd);

            /* Find the directory*/
            while (de = readdir(dir)) {
                char count[BUFFER] = "./";
                strcat(count, de->d_name);
                int result = strncmp(count, direc, CWD_BUFFER);
                if (result == 0)
                    found = 1;
            }

            /* If found */
            if (found == 1)
                chdir(direc);	/* Go to the directory*/
            else
                printf("No such directory.\n");
        }


        /*'Q': Exits the program*/
        else if(choice == 'Q' || choice == 'q') {
            printf("\n###################################################\n");
            printf("######## You are about to exit the program ########\n");
            printf("############# Have a nice day!!!!!!################\n");
            printf("###################################################\n");
            exit(0);
        }

        else {
            printf("\n######################################\n");
            printf("##### invalid command. Try again #####\n");
            printf("######################################\n");
        }

    }

}

char returnChoice() {

    int l;
    char c1;
    printf("\nList of available commands or operations:\n");
    printf("\t'L': lists all directories and files\n");
    printf("\t'E': edit a file\n");
    printf("\t'R': run or execute a program\n");
    printf("\t'C': change directory to\n");
    printf("\t'Q': quit/exit the program\n");
    printf("please enter your choice(upper or lower case): ");
    scanf(" %c", &c1);
    getchar();
    //l = getchar();
    c1 = tolower(c1);
    return c1;
}

void runProgram(char* file[]) {
    int number;
    int counter = 1;
    int index;
    char cmd[BUFFER];
    char token[BUFFER] = "./";
    printf("Press '1' to enter a file name or '0' to enter a file number: \n");
    printf("Enter your choice: ");
    scanf("%d", &number);

        if(number == 1){
            printf("\nRun what?(ENter name):");
            scanf( "%s", cmd);
            strcat(token,cmd);
            system(token);

        } else if(number == 0){
            printf("\nRun what?(ENter number):");
            scanf("%d",&index);
            system(file[index]);

        }



    return;

}
void editProgram(char* file[]) {
    int index;
    char s[BUFFER];
    char cmd[BUFFER];
    printf("Enter the file number you want to edit: ");
    scanf("%d",&index);
    //getchar();
                        strcpy(cmd, "pico ");
                        strcat(cmd, file[index]);
                        system(cmd);


    /*
    printf("Edit what? ");
    scanf("%s", s);
    getchar();
    strcpy(cmd, "pico ");
    strcat(cmd, s);
    system(cmd);
    return;*/
}
void changeDirectory() {
    DIR * dir;
    struct dirent* de;
    int found = 0; /*Mark if directory is found*/
    char cmd[BUFFER];
    /*Get directory name */
    printf("Change To? (Enter directory name): ");
    scanf("%s", cmd);
    //getchar();
    dir = opendir(".");
    char direc[BUFFER] = "./";
    strcat(direc, cmd);

    /* Find the directory */
    while (de = readdir(dir)) {
        char count[BUFFER] = "./";
        strcat(count, de->d_name);
        int result = strncmp(count, direc, CWD_BUFFER);
        if (result == 0)
            found = 1;
    }

    /* If found */
    if (found == 1)
        chdir(direc);	/* Go to the directory */
    else
        printf("No such directory.\n");
    return;

}
