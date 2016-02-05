#include <stdio.h>
#include <ctype.h>
#include <string.h>
#define WORDSIZE 256

int CharacterByCharacter(FILE *file1, FILE *file2, int i, int skip1, int skip2, char file1Name[], char file2Name[]);
int WordByWord(FILE *file1, FILE *file2, int i, int skip1, int skip2, char file1Name[], char file2Name[]);
int CountCharacterByCharacter(FILE *file1, FILE *file2, int i, int skip1, int skip2, int count, char file1Name[], char file2Name[]);
int CountWordByWord(FILE *file1, FILE *file2, int i, int skip1, int skip2, int count, char file1Name[], char file2Name[]);
int main( int argc, char *argv[]) {
    FILE *file1;
    FILE *file2;
    int i;
    char c[WORDSIZE];
    int insensitive = 0;
    int wordbyword = 0;
    int return_type1;
    int return_type2;
    int return_type3;
    int return_type4;
    int count = 0;
    int countNumber;
    int skipNumber1=0;
    int skipNumber2=0;
    char file1Name[WORDSIZE];
    char file2Name[WORDSIZE];
    int figureSkip=0;
    
	for(i=1; i < argc; i++){
        if((sscanf(argv[i], "%s ", c)) == 1) {
            if(c[0] == '-') {
                switch (c[1]) {
                    case ('w'):
                        wordbyword = 1;
                        break;
                    case ('i'):
                        insensitive = 1;
                        break;
                    case ('c'):
                        count = 1;
                        sscanf(c, "-c%d", &countNumber);
                        break;
                    case ('s'):
                        if((figureSkip = sscanf(c, "-s%d:%d", &skipNumber1 ,&skipNumber2)) < 2){
                        skipNumber2 = skipNumber1;
                        }
                        break;
                    default:
                        break;
                }
            }
        }
    } 
    file1 = fopen(argv[argc-2], "rb");
    file2 = fopen(argv[argc-1], "rb");
    strcpy(file1Name, argv[argc-2]);
    strcpy(file2Name, argv[argc-1]);
    
    if(file1 == 0) {    /* opens the file*/
        perror("fopen");
        /*additional error-handling if needed */
        printf("Terminating program.\n");
        return 3;
    }
    else if(file2 == 0) {
        perror("fopen");
        /*additional error-handling if needed */
        printf("Terminating program.\n");
        return 3;
    }
    /* charbychar, compare all files */
    if(count != 1 && wordbyword  != 1) {

        return_type1 = CharacterByCharacter(file1, file2, insensitive, skipNumber1, skipNumber2, file1Name, file2Name);
        
        if(return_type1 == 0) {
            return 0;
        }
        if(return_type1 == 1) {
            return 1;
        }
    }
    
    /* wordbyword, compare all files */
    else if(count != 1 && wordbyword  == 1) {
        return_type2 = WordByWord(file1, file2, insensitive, skipNumber1, skipNumber2, file1Name, file2Name);
        if(return_type2 == 0) {
            return 0;
        }
        if(return_type2 == 1) {
            return 1;
        }
    }
    /* charbychar, compare some characters */
    else if(count == 1 && wordbyword  != 1) {
    return_type3 = CountCharacterByCharacter(file1, file2, insensitive, skipNumber1, skipNumber2, countNumber, file1Name, file2Name);
        if(return_type3 == 0) {
            return 0;
        }
        if(return_type3 == 1) {
            return 1;
        }
    }
    /* wordbyword, compare some characters */
    else if(count == 1 && wordbyword  == 1) {
    return_type4 = CountWordByWord(file1, file2, insensitive, skipNumber1, skipNumber2, countNumber, file1Name, file2Name);
       if(return_type4 == 0) {
            return 0;
        }
        if(return_type4 == 1) {
            return 1;
        }
    }
    fclose(file1);
    fclose(file2);
return 0;
}
int CharacterByCharacter(FILE *file1, FILE *file2, int i, int skip1, int skip2, char file1Name[], char file2Name[]) {

    int characterF1 = 0;
    int characterF2 = 0;
    int numChar = 0;
    int insensitive = i;
    int checkEOF = 0;
    
    fseek(file1, skip1, SEEK_SET);
    fseek(file2, skip2, SEEK_SET);
    do
    {
   
            characterF1 = fgetc(file1);
            characterF2 = fgetc(file2);
            if( characterF1 == EOF || characterF2 == EOF)
            {
                checkEOF = 1;
            }
            else
            {
                ++numChar;
                if(insensitive){
                    if( toupper(characterF1) != toupper(characterF2))
                    {
                        printf("ranges differ: char %d\n", numChar);
                        
                        return 1;
                    }
                }
                else
                {
                    if( characterF1 != characterF2)
                    {
                        printf("ranges differ: char %d\n", numChar);
                        return 1;
                    }
                }
            }
    } while(checkEOF == 0);
       
    if(characterF1 == EOF && characterF2 != EOF)
    {
        printf("EOF on %s\n", file1Name);
        return 1;
    }
    if (characterF1 != EOF && characterF2 == EOF)
    {
        printf("EOF on %s\n", file2Name);
        return 1;
    }
    else {
    printf("ranges are equal\n");
    return 0;
    }
}
int WordByWord(FILE *file1, FILE *file2, int i, int skip1, int skip2, char file1Name[], char file2Name[])
{
    int characterF1= ' ';
    int characterF2 = ' ';
    int numWord = 0;
    int insensitive = i;
    int k=0;
    int j=0;
    
    if(skip1!=0) {
    do
    {
        characterF1 = fgetc(file1);
        if(isspace(characterF1)) 
            k++;
    }while(k<skip1);
    }
    if(skip2 !=0){
    do
    {
        characterF2 = fgetc(file2);
        if(isspace(characterF2)) 
            j++;
    }while(j<skip2);
    }
    do
    {
		numWord++;     
        while( isspace(characterF1) && characterF1 != EOF)
        {
            characterF1 = fgetc(file1);
        }
    
        while( isspace(characterF2) && characterF2 != EOF)
        {
            characterF2 = fgetc(file2);
        }		
		if( characterF1 == EOF || characterF2 == EOF )
        {
			break;
        }
        do
        {
            if(insensitive){
                if( toupper(characterF1) != toupper(characterF2))
                {
                    printf("ranges differ: word %d\n", numWord);
                    return 1;
                }
            }
            else
            {
                if( characterF1 != characterF2)
                {
                    printf("ranges differ: word %d\n", numWord);
                    return 1;
                }

            }
            characterF1 = fgetc(file1);
            characterF2 = fgetc(file2);
        }while((!(isspace(characterF1)) && characterF1 != EOF)||
               (!(isspace(characterF2)) && characterF2 != EOF));

    }while ( characterF1 != EOF || characterF2 != EOF);
    
    
    if(characterF1 == EOF && characterF2 == EOF)
    {
        printf("ranges are equal\n");            
        return 0;
    }
    else if(characterF1 == EOF)
    {
        printf("EOF on %s\n", file1Name);
        return 1;
    }
    else
    {
        printf("EOF on %s\n", file2Name);
        return 1;
    }
}

int CountCharacterByCharacter(FILE *file1, FILE *file2, int i, int skip1, int skip2, int count, char file1Name[], char file2Name[]) {
    int characterF1 = 0;
    int characterF2 = 0;
    int numChar = 0;
    int insensitive = i;
    int checkEOF = 0;

    fseek(file1, skip1, SEEK_SET);
    fseek(file2, skip2, SEEK_SET);
    do
    {       
        if(numChar < count) {
            characterF1 = fgetc(file1);
            characterF2 = fgetc(file2);
            if( characterF1 == EOF || characterF2 == EOF)
            {
                checkEOF = 1;
            }
            else
            {
                ++numChar;
                if(insensitive){
                    if( toupper(characterF1) != toupper(characterF2))
                    {
                        printf("ranges differ: char %d\n", numChar);
                        return 1;
                    }
                }
                else
                {
                    if( characterF1 != characterF2)
                    {
                        printf("ranges differ: char %d\n", numChar);
                        return 1;
                    }
                }
            }
        }
        else {
            checkEOF = 1;
        }
    }
    while(checkEOF == 0);
       
    if(characterF1 == EOF && characterF2 != EOF)
    {
        printf("EOF on %s\n", file1Name);
        return 1;
    }
    if (characterF1 != EOF && characterF2 == EOF)
    {
        printf("EOF on %s\n", file2Name);
        return 1;
    }
    else {
    printf("ranges are equal\n");
    return 0;
    }
}

int CountWordByWord(FILE *file1, FILE *file2, int i, int skip1, int skip2, int count, char file1Name[], char file2Name[])
{
    char wordF1[WORDSIZE];
    char wordF2[WORDSIZE];
    int numWord = 0;
    int insensitive = i;
    int k=0;
    int j=0;
    size_t zf1;
    size_t zf2;
    int scanfile1=0;
    int scanfile2=0;

    if(skip1!=0) {
    do
    {
        scanfile1= fscanf(file1, "%s", wordF1);
        k++;
    }while(k<skip1);
    }
    
    if(skip2 !=0){
    do
    {
        scanfile2= fscanf(file2, "%s", wordF2);
        j++;
    }while(j<skip2);
    }

    do
    {
      if (numWord < count) {
        numWord++;
        scanfile1= fscanf(file1, "%s", wordF1); 
        scanfile2= fscanf(file2, "%s", wordF2);

        if( scanfile1 == 0 && scanfile2 == 0 )
        {
            break;
        }
        if (insensitive) {
            for(zf1=0; wordF1[zf1]!='\0'; zf1++) {
                   wordF1[zf1] = tolower((int)wordF1[zf1]);
            }
            for(zf2=0; wordF2[zf2]!='\0'; zf2++) {
                   wordF2[zf2] = tolower((int)wordF2[zf2]);
            }
        }
        if (strcmp(wordF1, wordF2) != 0) {
             printf("ranges differ: word %d\n", numWord);
            return 1;
        }

      }
    } while( (numWord < count));
      
    if(scanfile1 != 1  && scanfile2 == 1)
    {
        printf("EOF on %s\n", file1Name);
        return 1;
    }
    if (scanfile1 == 1 && scanfile2 != 1)
    {
        printf("EOF on %s\n", file2Name);
        return 1;
    }
    else {
    printf("ranges are equal\n");
    return 0;
    }
}