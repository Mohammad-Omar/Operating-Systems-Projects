/*

    Name: Mohammad Kothawala
	ID: 1000731739
	Class: CSE-3320-001
	Instructor: Dr. Levine
	Assignment 3

*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#define col 106125
pthread_t tid[2];
pthread_t tId[4];
pthread_t tID[10];


struct car {
    char make[25];
    int year;
};
struct car getValues(char s[]);
void bubbleSortYearAndMake(struct car d[],int start, int end);
void *run_thread1( void *ptr );
void *run_thread2( void *ptr );
void *run_thread4( void *ptr );
void *run_thread10( void *ptr );
void bubbleSortYearAndMake(struct car d[],int start, int end);
void writeInFile(char *filename, struct car d[], int start, int end);
void readAndMerge(char *file1, char *file2, char *mergedFile, int size1, int size2);
void mergeSort(struct car a1[], struct car a2[], struct car m[] , int size1, int size2);
void store(char *file, struct car f[], int size);
void readFile(char *file, struct car s[], int size);


int main(void) {
    FILE* fp;
    FILE* f;
    int pid, t1, t2;
    int sizee;
    pthread_t thread_1;
    clock_t tEnd, tStart, total_time, time;
    int size, size1, size2, size3, size4, size5, size6, size7, size8, size9, size10;
    char fileName1[] = "FLAT_RCL.txt";
    char buffer[10000];
    struct car c[col];
    struct car *ptr = c;
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



    printf("#################################\n");
    printf("########### MAIN MENU ###########\n");
    printf("##   Enter '0' for  1 thread   ##\n");
    printf("##   Enter '1' for  2 threads  ##\n");
    printf("##   Enter '2' for  4 threads  ##\n");
    printf("##   Enter '3' for 10 threads  ##\n");
    printf("########### END MENU ############\n");
    printf("#################################\n");

    printf("Please Enter your choice: ");
    scanf("%d",&choice);
    int flag = choice;
    while(choice < 4) {
        if(choice == 0) {
            choice = 4;
            time=clock();
            t1 = pthread_create(&thread_1, NULL, run_thread1, (void *)c);
            if(t1) {
                fprintf(stderr,"Error - pthread_create() return code: %d\n",t1);
                exit(EXIT_FAILURE);
            }
            pthread_join(thread_1, NULL);
            time = clock() - time ;
            printf("time taken to do sorting using 1 thread is %f\n",(float)time/CLOCKS_PER_SEC);

        } else if( choice == 1 ) {
            choice = 4;
            time = clock();
            i = 0;

            while(i < 2) {
                t2 = pthread_create(&tid[i], NULL, run_thread2, (void*)c);
                if(t2) {
                    fprintf(stderr,"Error - pthread_create() return code: %d\n",t2);
                    exit(EXIT_FAILURE);
                }
                i++;
            }
            for (i = 0; i < 2; i = i + 1)
                pthread_join(tid[i], NULL);
            size = 106125/2;
            size1 = size +1;
            fp = fopen("test1.txt", "r");
            i = 0;
            readAndMerge("test1.txt","test2.txt","merge1.txt",size,size1);

            time = clock() - time ;
            printf("time taken to do sorting using 2 thread is %f\n",(float)time/CLOCKS_PER_SEC);
            pthread_exit(NULL);

        } else if (choice == 2) { /* choice 2: for 4 processes */
            choice = 4;
            time = clock();
            i = 0;

            while(i < 4) {
                t2 = pthread_create(&tId[i], NULL, run_thread4, (void*)c);
                if(t2) {
                    fprintf(stderr,"Error - pthread_create() return code: %d\n",t2);
                    exit(EXIT_FAILURE);
                }
                i++;
            }
            for (i = 0; i < 4; i = i + 1)
                pthread_join(tId[i], NULL);
            size1 = col/4;
            size2 = col/2;
            size3 = size1+size2;
            size4 = size1+size1;
            size5 = size1+size1+1;
            readAndMerge("test1.txt","test2.txt","merge1.txt",size1,size1);
            readAndMerge("test3.txt","test4.txt","merge2.txt",size1,size1);
            readAndMerge("merge1.txt","merge2.txt","final.txt",size4,size5);

            time = clock() - time ;
            printf("time taken to do sorting using 4 thread is %f\n",(float)time/CLOCKS_PER_SEC);
            pthread_exit(NULL);


        } else {
            choice = 4;
            time = clock();
            i = 0;

            while(i < 10) {
                t2 = pthread_create(&tID[i], NULL, run_thread10, (void*)c);
                if(t2) {
                    fprintf(stderr,"Error - pthread_create() return code: %d\n",t2);
                    exit(EXIT_FAILURE);
                }
                i++;
            }
            for (i = 0; i < 10; i = i + 1)
                pthread_join(tID[i], NULL);
            size1 = col/10;//10612
            size2 = size1+size1;//21225
            size3 = size2+size1;//31836
            size4 = size3+size1;//42449
            size5 = size4+size1+1;//53062
            size6 = size5+size1;// 63674
            size7 = size6+size1; //74286
            size8 = size7+size1+1; // 84899
            size9 = size8+size1+1; //95512
            size10 = size9+size1+1; //106125

            readAndMerge("test1.txt", "test2.txt", "merge1.txt", size1, size1);
            readAndMerge("test3.txt", "test4.txt", "merge2.txt", size1, size1);
            readAndMerge("test5.txt", "test6.txt", "merge3.txt", size1,size1);
            readAndMerge("test7.txt", "test8.txt", "merge4.txt", size1,size1);
            readAndMerge("test9.txt", "test10.txt", "merge5.txt", size1,size1);
            readAndMerge("merge1.txt", "merge2.txt", "merge1.txt", size2,size2);
            readAndMerge("merge3.txt", "merge4.txt", "merge2.txt", size2, size2);
            readAndMerge("merge1.txt", "merge2.txt", "merge1.txt", size4, size4);
            readAndMerge("merge1.txt", "merge5.txt", "final.txt", size8, size2);

            time = clock() - time ;
            printf("time taken to do sorting using 2 thread is %f\n",(float)time/CLOCKS_PER_SEC);
            pthread_exit(NULL);



        }
    }

    while(1) {
        if(flag == 0) {
            pthread_exit(NULL);
            break;
        } else if(flag == 1) {

            pthread_exit(NULL);
            break;


        } else if(flag==2) {
            pthread_exit(NULL);
            break;
        } else {

            pthread_exit(NULL);
            break;

        }

    }
    return 0;

}


void *run_thread1( void *ptr ) {
    struct car *data = (struct car*) ptr;

    bubbleSortYearAndMake(data, 0, col);
    writeInFile("test1.txt",data,0,col);

    pthread_exit(NULL);
}
void *run_thread2( void *ptr ) {
    struct car *data = (struct car*) ptr;
    pthread_t id = pthread_self();
    int size1 = col/2;
    int size2 = col - size1;
    int flag;

    if(pthread_equal(id,tid[0])) {
        bubbleSortYearAndMake(data, 0, size1);
        writeInFile("test1.txt", data, 0, size1);
    } else {
        bubbleSortYearAndMake(data, size2, col);
        writeInFile("test2.txt", data, size2, col);
    }

    pthread_exit(NULL);
}
void *run_thread4( void *ptr ) {
    struct car *data = (struct car*) ptr;
    pthread_t id = pthread_self();
    int size1 = col/4;
    int size2 = col/2;
    int size3 = size1+size2;

    //int size2 = col - size1;
    int flag;

    if(pthread_equal(id,tId[0])) {
        bubbleSortYearAndMake(data, 0, size1);
        writeInFile("test1.txt", data, 0, size1);
    } else if (pthread_equal(id,tId[1])){
        bubbleSortYearAndMake(data, size1, size2);
        writeInFile("test2.txt", data, size1, size2);
    } else if (pthread_equal(id,tId[2])){
        bubbleSortYearAndMake(data, size2, size3);
        writeInFile("test3.txt", data, size2, size3);
    } else{
        bubbleSortYearAndMake(data, size3, col);
        writeInFile("test4.txt", data, size3, col);
    }
    pthread_exit(NULL);
}
void *run_thread10( void *ptr ) {
    struct car *data = (struct car*) ptr;
    pthread_t id = pthread_self();
    int size1 = col/10;//10612
    int size2 = size1+size1;//21224
    int size3 = size2+size1;//31836
    int size4 = size3+size1;//42449
    int size5 = size4+size1;//53062
    int size6 = size5+size1;// 63674
    int size7 = size6+size1; //74286
    int size8 = size7+size1; // 84899
    int size9 = size8+size1; //95512
    int size10 = size9+size1; //106125

    if(pthread_equal(id,tID[0])) {
        bubbleSortYearAndMake(data, 0, size1);
        writeInFile("test1.txt", data, 0, size1);
    } else if (pthread_equal(id,tID[1])){
        bubbleSortYearAndMake(data, size1, size2);
        writeInFile("test2.txt", data, size1, size2);
    } else if (pthread_equal(id,tID[2])){
        bubbleSortYearAndMake(data, size2, size3);
        writeInFile("test3.txt", data, size2, size3);
    } else if (pthread_equal(id,tID[3])){
        bubbleSortYearAndMake(data, size3, size4);
        writeInFile("test4.txt", data, size3, size4);
    } else if (pthread_equal(id,tID[4])){
        bubbleSortYearAndMake(data, size4, size5);
        writeInFile("test5.txt", data, size4, size5);
    } else if (pthread_equal(id,tID[5])){
        bubbleSortYearAndMake(data, size5, size6);
        writeInFile("test6.txt", data, size5, size6);
    } else if (pthread_equal(id,tID[6])){
        bubbleSortYearAndMake(data, size6, size7);
        writeInFile("test7.txt", data, size6, size7);
    } else if (pthread_equal(id,tID[7])){
        bubbleSortYearAndMake(data, size7, size8);
        writeInFile("test8.txt", data, size7, size8);
    } else if (pthread_equal(id,tID[8])){
        bubbleSortYearAndMake(data, size8, size9);
        writeInFile("test9.txt", data, size8, size9);
    } else {
        bubbleSortYearAndMake(data, size9, col);
        writeInFile("test10.txt", data, size9, col);
    }
    pthread_exit(NULL);
}

struct car getValues(char s[]) {
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

void writeInFile(char *filename, struct car d[], int start, int end) {
    int i;
    FILE *fpp;
    fpp = fopen(filename,"w");
    for(i=start; i<end; i++) {
        fprintf(fpp,"%d %s\n", d[i].year ,d[i].make);

    }
    fclose(fpp);
}




void readAndMerge(char *file1, char *file2, char *mergedFile, int size1, int size2) {
    struct car d1[size1];
    int i;
    struct car d2[size2];
    struct car mergeStructs[size1+size2];
    readFile(file1, d1, size1);
   /* for(i = 0; i < 50; i++) {
        printf("%d    %s\n", d1[i].year, d1[i].make);
    }*/
    readFile(file2, d2, size2);
   /* for(i = 0; i < 50; i++) {
        printf("%d    %s\n", d2[i].year, d2[i].make);
    }*/
    mergeSort(d1, d2, mergeStructs, size1, size2);
    store(mergedFile, mergeStructs, size1+size2);

}
void readFile(char *file, struct car s[], int size) {
    int n;
    char str[25];
    char buffer[255];
    int b;
    int a = 0;
    int i;
    int x;
    struct car temp;
    FILE *fp;
    fp = fopen(file, "r");
    i = 0;

    while( fgets(buffer, sizeof(buffer), fp) != NULL ){
        fscanf(fp, "%d    %s",&b, str);
        strcpy(s[i].make, str);
        s[i].year = b;
        i++;
    }
    /*printf("\n\n\n");*/

    fclose(fp);
}
void store(char *file, struct car f[], int size) {

    int i;
    FILE *fpp;
    fpp = fopen(file,"w");
    for(i=0; i<size; i++) {
           fprintf(fpp,"%d    %s\n", f[i].year ,f[i].make);


    }
    /*for(i = 0; i < 20; i++){
        printf("%d   %s\n", f[i].year ,f[i].make);

    }*/
    fclose(fpp);

}

void mergeSort(struct car a1[], struct car a2[], struct car m[] , int size1, int size2) {
    int i, j = 0, k = 0;

    for(i = 0; i < size1+size2; i++) {
        if(a1[j].year < a2[k].year && j < size1 && k < size2) {
            m[i] = a1[j];
            j++;
        } else if(k < size2) {
            m[i] = a2[k];
            k++;
        } else if(j < size1) {
            m[i] = a1[j];
            j++;

        }

    }
}

