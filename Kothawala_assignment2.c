/*

    Name: Mohammad Kothawala
	ID: 1000731739
	Class: CSE-3320-001
	Instructor: Dr. Levine
	Assignment 2

*/


#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<unistd.h>
#include <time.h>
#define col 106125

struct car {
    char make[25];
    int year;
};
struct car getValues(char s[]);
void bubbleSortYearAndMake(struct car d[],int start, int end);
void writeInFile(char *filename, struct car d[], int start, int end);
void readAndMerge(char *file1, char *file2, char *mergedFile, int size1, int size2);
void mergeSort(struct car a1[], struct car a2[], struct car m[] , int size1, int size2);
void store(char *file, struct car f[], int size);
void readFile(char *file, struct car s[], int size);

int main(void) {
    FILE* fp;
    FILE* f;
    int pid;
    clock_t time;
    int size, size1, size2, size3, size4, size5, size6, size7, size8, size9, size10;
    char fileName1[] = "FLAT_RCL.txt";
    char buffer[10000];
    struct car c[col];
    int center;
    int structCount = 0,count = 0, i = 0, unsorted, choice;
    if( (fp = fopen(fileName1, "r")) == NULL ) {
        printf("unable to open %s for reading\n", fileName1);
        exit(1);
    }

    while( fgets(buffer, sizeof(buffer), fp) != NULL ) {
        c[structCount] = getValues(buffer);
        structCount++;
    }
    fclose( fp );


   /* if( (f = fopen(fileName2, "w")) == NULL ) {
        printf("unable to open %s\n", fileName2);
        exit(1);
    }*/

    printf("0 for 1 process, 1 for 2 processes, 2 for 4 processes & 3 for 10 processes!\n");
    printf("Enter 0,1,2 or 3  to choose an operation:\n");
    scanf("%d",&choice);
    int flag = choice;
    while(choice<4) {
        if(choice==0) {
            choice = 4;
            time=clock();
            bubbleSortYearAndMake(c, 0, structCount);
            writeInFile("test1.txt",c,0,structCount);


        } else if( choice == 1 ) {
            choice = 4;
            size = structCount/2;
            count = structCount;
            //printf("size =  %d\n", size);
            time=clock();
            pid = fork();

            if(pid==0) {
                bubbleSortYearAndMake(c, 0, size);
                writeInFile("test1.txt",c,0,size);
            } else {
                bubbleSortYearAndMake(c, size, count);
                writeInFile("test2.txt",c,size,count);
                return 0;
            }

        } else if (choice == 2)/* choice 2: for 4 processes */{
            choice = 4;
            size1 = structCount/4;
            size2 = structCount/2;
            size3 = (structCount/4) * 3;
            time=clock();
            pid=fork();
            if(pid==0) {
                pid = fork();
                if(pid == 0) {
                    bubbleSortYearAndMake(c, 0, size1);
                    writeInFile("test1.txt",c,0,size1);
                } else {
                    bubbleSortYearAndMake(c,size1,size2);
                    writeInFile("test2.txt",c,size1,size2);
                    return 0;
                }
            } else {
                pid=fork();
                if(pid==0) {
                    bubbleSortYearAndMake(c, size2, size3);
                    writeInFile("test3.txt",c,size2,size3);
                    return 0;
                } else {
                    bubbleSortYearAndMake(c, size3, structCount);
                    writeInFile("test4.txt",c,size3,structCount);
                    return 0;
                }

            }


        } else {
            count = structCount;
            choice = 4;
            size1 = structCount/10;
            //printf("size1 = %d\n", size1);
            size2 = (count * 2)/10;
            //printf("size2 = %d\n", size2);
            size3 = (count * 3)/10;
            //printf("size3 = %d\n", size3);
            size4 = (count * 4)/10;
            //printf("size4 = %d\n", size4);
            size5 = (count * 5)/10;
            //printf("size5 = %d\n", size5);
            size6 = (count * 6)/10;
            //printf("size6 = %d\n", size6);
            size7 = (count * 7)/10;
            //printf("size7 = %d\n", size7);
            size8 = (count * 8)/10;
            //printf("size8 = %d\n", size8);
            size9 = (count * 9)/10;
            //printf("size9 = %d\n", size9);
            size10 = (count * 10)/10;
            //printf("size10 = %d\n", size10);
            time=clock();
            pid = fork();
            if(pid==0) {
                pid = fork();
                if(pid==0) {
                    bubbleSortYearAndMake(c, 0, size1);
                    writeInFile("test1.txt",c,0,size1);
                    return 0;
                } else {
                    pid = fork();
                    if(pid==0) {
                        bubbleSortYearAndMake(c, size1, size2);
                        writeInFile("test2.txt",c,size1, size2);
                        return 0;
                    } else {
                        pid = fork();
                        if(pid==0) {
                            bubbleSortYearAndMake(c, size2, size3);
                            writeInFile("test3.txt",c,size2, size3);
                            return 0;
                        } else {
                            pid = fork();
                            if(pid==0) {
                                bubbleSortYearAndMake(c, size3, size4);
                                writeInFile("test4.txt",c,size3, size4);
                                return 0;
                            } else {
                                bubbleSortYearAndMake(c, size4, size5);
                            writeInFile("test5.txt",c,size4, size5);
                                return 0;
                            }
                        }
                    }
                }
            } else {
                pid = fork();

                if(pid==0) {
                    bubbleSortYearAndMake(c, size5, size6);
                    writeInFile("test6.txt",c,size5, size6);
                } else {
                    pid = fork();
                    if(pid==0) {
                        bubbleSortYearAndMake(c, size6, size7);
                        writeInFile("test7.txt",c,size6, size7);
                        return 0;
                    } else {
                        pid = fork();
                        if(pid==0) {
                            bubbleSortYearAndMake(c, size7, size8);
                            writeInFile("test8.txt",c,size7, size8);
                            return 0;
                        } else {
                            pid = fork();
                            if(pid==0) {
                                bubbleSortYearAndMake(c, size8, size9);
                                writeInFile("test9.txt",c,size8, size9);
                                return 0;
                            } else {
                                bubbleSortYearAndMake(c, size9, size10);
                                writeInFile("test10.txt",c,size9, size10);
                                return 0;
                            }
                        }
                    }
                }
            }


           /* time=clock()- time;
            printf("time taken to do sorting using 10 processes concurrently is %f",(float)time/CLOCKS_PER_SEC);*/
        }

    }

    while(1){
        if(flag == 1) {

            time=clock() - time;
            printf("time taken to do sorting using 2 process is %f\n",(float)time/CLOCKS_PER_SEC);
            break;
            readAndMerge("test1.txt","test2.txt","merge1.txt",size,size);


        } else if(flag==2) {

            time=clock()- time;
            printf("time taken to do sorting using 4 process is %f",(float)time/CLOCKS_PER_SEC);
            break;
            readAndMerge("test1.txt", "test2.txt", "merge1.txt", 25000, 25000);
            readAndMerge("test3.txt", "test4.txt", "merge2.txt", 25000, 25000);
            readAndMerge("merge1.txt","merge2.txt","final.txt",50000,50000);
        } else {

            time=clock()- time;
            printf("time taken to do sorting using 10 processes concurrently is %f",(float)time/CLOCKS_PER_SEC);
            break;
            /*
            readAndMerge("test1.txt", "test2.txt", "merge1.txt", 10000, 10000);
            readAndMerge("test3.txt", "test4.txt", "merge2.txt", 10000, 10000);
            readAndMerge("test5.txt", "test6.txt", "merge3.txt", 10000,10000);
            readAndMerge("test7.txt", "test8.txt", "merge4.txt", 10000,10000);
            readAndMerge("test9.txt", "test10.txt", "merge5.txt", 10000,10000);

            readAndMerge("merge1.txt", "merge2.txt", "merge1.txt", 20000,20000);
            readAndMerge("merge3.txt", "merge4.txt", "merge2.txt", 20000, 20000);

            readAndMerge("merge1.txt", "merge2.txt", "merge1.txt", 40000, 40000);

            readAndMerge("merge1.txt", "merge5.txt", "final.txt", 80000, 20000);*/
        }
        //bubbleSortYearAndMake(c, structCount);
    }
   /* printf("----------------------------\n");
    for(i = 0; i < structCount; i++) {
        fprintf(f,"%d    %s\n", c[i].year ,c[i].make);

    }*/

    return 0;
}

//bubblesort(c, structCount);



struct car getValues(char s[])
/*
      input:  char array (line from file)
     output:  struct purchases (filled in structure)
    purpose:  extract name, item, purchase quantity, and per item costs

     sample:  Bob bought 3 pairs of shoes for $6 each.
*/
{
    char* token;
    char* del = "\t";
    int size, value;
    char year1[7];
    struct car temp;
    int tokenCounter;
    token = strtok(s, del);
    tokenCounter = 0;


    while(token != NULL) {
        token = strtok(NULL, del);
        tokenCounter++;
        if(tokenCounter == 2) {
            strcpy(temp.make, token);
            //printf("%s  ", temp.make);
        } else if (tokenCounter == 4) {
            value = atoi(token);
            temp.year = value;
            //printf("%s\n", temp.year);

        } else {
            continue;
        }

    }

    return temp;
}




/*Sort the file by year and by make*/
void bubbleSortYearAndMake(struct car d[],int start, int end) {
    int i, unsorted;
    struct car temp;

    do {
        unsorted = 0;
        for(i = start; i < end-1; i++) {
            if( d[i].year > d[i+1].year) {
                temp = d[i];
                d[i] = d[i+1];
                d[i+1] = temp;
                unsorted = 1;
            }

        }
    } while(unsorted);

    do {
        unsorted = 0;
        for(i = 0; i < end-1; i++) {
            if( d[i].year == d[i+1].year) {
                if(strcmp(d[i].make,d[i+1].make) > 0) {
                    strcpy(temp.make,d[i].make);
                    strcpy(d[i].make, d[i+1].make);
                    strcpy(d[i+1].make, temp.make);
                    unsorted = 1;
                }

            }

        }
    } while(unsorted);


}

void writeInFile(char *filename, struct car d[], int start, int end){
    int i;
    FILE *fpp;
    fpp = fopen(filename,"w");
    for(i=start; i<end; i++) {
           fprintf(fpp,"%d    %s\n", d[i].year ,d[i].make);

    }
    fclose(fpp);
}




void readAndMerge(char *file1, char *file2, char *mergedFile, int size1, int size2) {
    //int array1[size1], array2[size2], mergedArray[size1+size2], i = 0, a;
    struct car d1[size1];
    int i;
    struct car d2[size2];
    struct car mergeStructs[size1+size2];
    printf("Read and Merge\n");
    readFile(file1, d1, size1);
    //for(i = 0; i < size1; i++) {

       // printf("temp\n");
      //  printf("%d    %s\n", d1[i].year, d1[i].make);
        //printf(str);
        //temp.year = atoi(str);
        //s[i] = temp;
    //
    readFile(file2, d2, size2);
    mergeSort(d1, d2, mergeStructs, size1, size2);
    store(mergedFile, mergeStructs, size1+size2);

}
void readFile(char *file, struct car s[], int size) {
    int i;
    char str[25];
    char buffer[255];
    int a;
    struct car temp;
    FILE *fp;
    fp = fopen(file, "r");

    for(i = 0; i < size; i++) {

       // printf("temp\n");
        /*fscanf(fp, "%d    %s\n", &(temp.year), temp.make);
        if (strcmp("FAIRMONT TAMPER", temp.make) == 0){
                printf("Equals %s\n", temp.make);
                    break;
            }
        printf("%s\n",temp.make);
        //temp.year = atoi(str);*/
        s[i] = temp;
    }
    fclose(fp);
}
void store(char *file, struct car f[], int size) {

    /*int i;
    FILE *fpp;
    fpp = fopen(filename,"w");
    for(i=start; i<end; i++) {
           fprintf(fpp,"%d    %s\n", d[i].year ,d[i].make);

    }
    fclose(fpp);*/
    int i;
    FILE *fp;
    printf("store\n");
    fp = fopen(file, "w");
    for(i = 0; i < size; i++)
        fprintf(fp, "%d    %s\n", f[i].year, f[i].make);
    fclose(fp);
}
void mergeSort(struct car a1[], struct car a2[], struct car m[] , int size1, int size2) {
    int i, j = 0, k = 0;

    for(i = 0; i < size1+size2; i++) {
        if(a1[j].year < a2[k].year && j < size1 && k < size2) {
            m[i] = a1[j];
            //printf("mergeSort\n");
            j++;
        } else if(k < size2) {
            m[i] = a2[k];
            k++;
            //printf("mergeSort\n");
        } else if(j < size1) {
            m[i] = m[i] = a1[j];
            j++;

        }

    }
}
