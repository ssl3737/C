#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#define NAMESIZE 20
#define LINESIZE 512

/* Check valid name */
int is_valid_name(const char s[]) {
	int i;
	for(i = 0; s[i] != '\0'; i++) {
		if(!isalpha((int)s[i]) && s[i] != '-'){
			printf("Invalid name.\n");
            printf("problem 1-1:\n");
			return 0;
		}
	}
	if( i < 2 || i >= NAMESIZE) {
        printf("Invalid name.\n");
		printf("problem 1-2:\n");
		return 0;
    }
	if(!isalpha((int) s[0]) || !isalpha((int)s[i - 1])){
		printf("Invalid name.\n");
        printf("problem 1-3:\n");
		return 0;
	}
	return 1;
}

/* Check valid score */
int is_valid_score(const int s){

    if( s< 0 || s > 100){
        printf("Invalid name.\n");
        printf("problem 2-3\n");
        return 0;
    }
    else{
        return 1;
    }
}
/* Get valid score and append firstname, lastname, and score into file*/
int get_valid_all(FILE *fp, char first[], char last[]) {
	char line[LINESIZE];
	int score;
        char* result ;
	printf("Please enter the score: \n");
         result = fgets(line,LINESIZE,stdin);

	while(result) {
        if(sscanf(line, " %d ", &score) == 1) {
             
			if(is_valid_score(score)){
                printf("after %p\n", (void*)fp);
                fprintf(fp, "%-20s%-20s%-4d", first, last, score);			
                return 2;
			}
		} else {
			printf("\nInvalid score.\n");
			return 0;
		}
	}
return 0;
}

/* Get valid score and append firstname, lastname, and score into file*/
int get_valid_all(FILE *fp, char first, char last, int score) {
	char line[LINESIZE];
	int score;
    
	printf("Please enter the score: \n");
    if(sscanf(line, " %d ", &score) == 1) {
             if(is_valid_score(score)) || 
                 is_valid_name(first) || 
                  is_valid_name(last)){
                 fprintf(fp, "%-20s%-20s%-4d", first, last, score);			
                 return 2;
			}
		} else {
			return 0;
		}
	}
return 0;
}

/* Get valid firstname and lastname */
int get_all(FILE *fp){
	char line[LINESIZE];
	char first[NAMESIZE];
	char last[NAMESIZE];
    int scan = 0;
    char* result ;
	printf("Please enter student's firstname and lastname: \n");	
    if( (fgets(line,LINESIZE,stdin) != '\0'){ 
        if(sscanf(line,"%s %s\n",first,last) == 2){
           
            printf("Please enter the score: \n");
             if(fgets(line,LINESIZE,stdin) != '\0'){
                 if(sscanf(line, " %d ", &score) == 1) {
                        get_valid_all(fp, first, last, score);
                return 2;
                }
            }
        }
    }
                
        else { 
    return 0;
    }
return 0;
}

/* Display one recorde number n */
int display (FILE *fp, int integer){
	char line[LINESIZE];
    char first[NAMESIZE];
    char last[NAMESIZE];
    int score;
    if ((integer*44)>(int)sizeof(fp)){
        printf("There is no more data\n");
    return 2;
    }
    else{
        fseek(fp, ((integer-1)*44), SEEK_SET);       
        fgets(line,LINESIZE,fp);
        sscanf(line, "%s%s%d", first, last, &score); 
        fprintf(stderr, "%s, %s: %d\n", last, first, score);
        return 2;
    }
return 2;
}

/* Display all recorde starting from record number n */
int display_records (FILE *fp, int integer){
	char line[LINESIZE];
    char first[NAMESIZE];
    char last[NAMESIZE];
    int score;
    integer= integer * (-1);
    
    while(integer > 0) {
        fseek(fp, ((integer-1)*44), SEEK_SET);
        fgets(line,LINESIZE,fp);
        sscanf(line, "%s%s%d", first, last, &score); 
         --integer;
    }
return 2;
}

/* Menu */
int menu(FILE *fp) {
    int integer;
    char line[LINESIZE];
    while(fgets(line,LINESIZE,stdin) != '\0') {
        if (sscanf(line, "%d", &integer) == 1) {
            if (integer == 0) {
                if(get_all(fp) == 2){
                    integer =0;
                }  
            }
            else if (integer > 0) {
                if(display(fp, integer) == 2) {
                    integer = 0;
                }
            }
            else if (integer < 0 ) {
                if(display_records(fp, integer) == 2) {
                    integer = 0;
                }
            }
        }
        else {
            printf("It is not integer. Try again\n");
        }
    printf("*******************************************************\n");
    printf("* +n (a positive integer) display record number n.    *\n");
    printf("*  0 append record.                                   *\n");
    printf("* -n (a negative integer) display all records.        *\n");
    printf("*******************************************************\n");    
    }
    printf("EOF received, program terminated.\n");
    return 0;
}

int main(int argc, char *argv[]) {
    FILE *fp; 
    printf("*******************************************************\n");
    printf("* +n (a positive integer) display record number n.    *\n");
    printf("*  0 append record.                                   *\n");
    printf("* -n (a negative integer) display all records.        *\n");
    printf("*******************************************************\n");
    if(argc != 2)
        return 1;
    if((fp = fopen(argv[1], "ab+")) == 0) {
        perror("fopen");
    	/*additional error-handling if needed */
		printf("Terminating program.\n");
		return 0;
	}
    printf("before %p\n", (void*)fp);

    menu(fp);
	
    if(fclose(fp) != 0) {
		perror("fclose");
		printf("Terminating program.\n");
		return 0;
	}
	return 0;
}