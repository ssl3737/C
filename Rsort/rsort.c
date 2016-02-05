#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define NAMESIZE 20
#define LINESIZE 256
#define BLOCK 2
#include "rsort.h"
    
typedef struct name {
    char last[NAMESIZE];
    char first[NAMESIZE];
} name;

typedef struct record {
    name name;
    int score;
} record;

typedef struct {
    record **data; /* points to dynamic array of pointers */ 
    size_t nalloc; /* number of pointers allocated */ 
    size_t nused; /* number of pointers used */ 
} record_list;

int is_valid_name(const char s[]){
	int i;
	for(i = 0; s[i] != '\0'; i++);
    if( i < 0 || i >= NAMESIZE){
		return 0;
    }
    return 1;  
}

void lower_name(char s[]) {
	char *p;
	for(p=s; *p != '\0'; p++)
		*p = tolower((int)*p);
}

/* Checks if the score if valid */
int is_valid_score(const int i) {
	/* Score must be between or equal to 0 and 100 */
    if((i > 100 || i < 0)) {
		return 0;
	}
	return 1;
}

void print_record(record_list prec) 
{
    size_t i;
	for(i = 0; i < prec.nused; i++) {
        printf("%s %s", prec.data[i]->name.last, prec.data[i]->name.first);
        printf(" %d\n", prec.data[i]->score);
	}
	for(i = 0; i < prec.nused; i++) {
		free(prec.data[i]);
	}
	free(prec.data);	
}

void init(record_list *p) 
{
    p->data = 0;
    p->nalloc = p->nused = 0;
}
/*
int insert(record_list *p, int n) {
    if (p->nused == p->nalloc) {
        int *tmp = realloc(p->data, (p->nalloc + BLOCK) * sizeof(*p->data));
        if (tmp == 0)
            return 0;
        p->data = tmp;
        p->nalloc += BLOCK;
    }
    P->data[p->nused++] = n;
    
    return 1;
}*/

/* SORTING FUNCTIONS */

/* Name ascending */
int nameAsc(const void *p, const void *q) {
	const record pp = **(const record**)p;
	const record qq = **(const record**)q;
	
	if(strcmp(pp.name.last, qq.name.last) != 0) {
		return strcmp(pp.name.last, qq.name.last);
	}
	else {
		return strcmp(pp.name.first, qq.name.first);
	}
}

/* Name descending */
int nameDesc(const void *p, const void *q) {
	return nameAsc(q, p);
}

/* Score ascending */
int scoreAsc(const void *p, const void *q) {
	const record pp = **(const record**)p;
	const record qq = **(const record**)q;
	return (pp.score - qq.score);
}

/* Score descending */
int scoreDesc(const void *p, const void *q) {
	return scoreAsc(q, p);
}

/* Name ascending & score ascending */
int nameAscScoreAsc(const void *p, const void *q) {
	if(nameAsc(p, q) != 0) {
		return nameAsc(p, q);
	}
	
	else {
		return scoreAsc(p, q);
	}
}

/* Name ascending & score descending */
int nameAscScoreDesc(const void *p, const void *q) {
	if(nameAsc(p, q) != 0) {
		return nameAsc(p, q);
	}
	
	else {
		return scoreAsc(q, p);
	}
}

/* Name descending & score ascending */
int nameDescScoreAsc(const void *p, const void *q) {
	if(nameAsc(q, p) != 0) {
		return nameAsc(q, p);
	}
	else {
		return scoreAsc(p, q);
	}
}

/* Name descending & score descending */
int nameDescScoreDesc(const void *p, const void *q) {
	if(nameAsc(q, p) != 0) {
		return nameAsc(q, p);
	}
	else {
		return scoreAsc(q, p);
	}
}

/* Score ascending & name ascending */
int scoreAscNameAsc(const void *p, const void *q) {
	if(scoreAsc(p, q) != 0) {
		return scoreAsc(p, q);
	}
	else {
		return nameAsc(p, q);
	}
}

/* Score ascending & name descending */
int scoreAscNameDesc(const void *p, const void *q) {
	if(scoreAsc(p, q) != 0) {
		return scoreAsc(p, q);
	}
	else {
		return nameAsc(q, p);
	}
}

/* Score descending & name ascending */
int scoreDescNameAsc(const void *p, const void *q) {
	if(scoreAsc(q, p) != 0) {
		return scoreAsc(q, p);
	}
	else {
		return nameAsc(p, q);
	}
}

/* Score descending & name descending */
int scoreDescNameDesc(const void *p, const void *q) {
	if(scoreAsc(q, p) != 0) {
		return scoreAsc(q, p);
	}
	else {
		return nameAsc(q, p);
	}
}

void sort(record_list *prec, int option1, int option2, int option3) {
    if(option1 == 1) {
        qsort(prec -> data, prec -> nused, sizeof(record*), nameAsc);
    }
    if(option1 == 2) {
        qsort(prec -> data, prec -> nused, sizeof(record*), nameDesc);
    }
    if(option1 == 3) {
        qsort(prec -> data, prec -> nused, sizeof(record*), scoreAsc);
    }
    if(option1 == 4) {
        qsort(prec -> data, prec -> nused, sizeof(record*), scoreDesc);
    }
    if(option2 == 1) {
    qsort(prec -> data, prec -> nused, sizeof(record*), scoreAscNameAsc);
    }
    if(option2 == 2) {
    qsort(prec -> data, prec -> nused, sizeof(record*), scoreAscNameDesc);
    }
    if(option2 == 3) {
    qsort(prec -> data, prec -> nused, sizeof(record*), nameAscScoreAsc);
    }
    if(option2 == 4) {
    qsort(prec -> data, prec -> nused, sizeof(record*), nameAscScoreDesc);
    }
    if(option3 == 1) {
    qsort(prec -> data, prec -> nused, sizeof(record*), scoreDescNameAsc);
    }
    if(option3 == 2) {
    qsort(prec -> data, prec -> nused, sizeof(record*), scoreDescNameDesc);
    }
    if(option3 == 3) {
    qsort(prec -> data, prec -> nused, sizeof(record*), nameDescScoreAsc);
    }
    if(option3 == 4) {
    qsort(prec -> data, prec -> nused, sizeof(record*), nameDescScoreDesc);
    }    
}

/* Appending a record */
int input_record(record_list *prec) 
{
	char buffer[LINESIZE];
	char first[NAMESIZE];
	char last[NAMESIZE];
	int score = -1;
    char dummy[LINESIZE];
    record **tmp;
    /* as long as we can read a line */
	while(fgets(buffer, LINESIZE, stdin)) {
		score = -1;
        if(prec->nused == prec->nalloc) {
			tmp = realloc (prec->data, (prec->nalloc+BLOCK)*sizeof(record*));
			if(tmp ==0){
				fprintf(stderr, "unable to resize memory \n");
				break;
			}
            #ifdef DEBUG
				fprintf(stderr, "%s\n", "#");
			#endif
			prec->data = tmp;
			prec->nalloc += BLOCK;
		}
        #ifdef DEBUG
            fprintf(stderr, "%s\n", "%");
        #endif
        /* If name is empty, return to main menu */
        if(sscanf(buffer, "%s %s %d %s\n", first, last, &score, dummy) > 3 && dummy[0] != '#') 
        {
            continue;
        }
        if(!is_valid_name(first)) {
            continue;
        }
        if(!is_valid_name(last)) {
            continue;
        }
        if(!is_valid_score(score)) {
            continue;
        }
        prec->data[prec->nused] = malloc(sizeof(record));
		if(prec->data[prec->nused] == 0) {
			fprintf(stderr, "unable to allocate memory\n");
			break;
		}
        lower_name(first);
        lower_name(last);
        strcpy(prec->data[prec->nused]->name.last, last);
        strcpy(prec->data[prec->nused]->name.first, first);
        prec->data[prec->nused]->score = score;
        prec->nused++;
    }
    #ifdef DEBUG
		fprintf(stderr, "%s\n", "@");
	#endif
    return 0;
}

int CheckOption(char array[], size_t size)
{
    int nameAsc = 1;
    int nameDesc = 2;
    int scoreAsc = 3;
    int scoreDesc = 4;
    
    if(size == 2)
    {
        if( array[0] == '-')
        {
			if( array[1] == 's' )
			{
                return scoreDesc;
			}
			else if( array[1] == 'n' )
			{
                return nameDesc;
			}
        }
        else if( array[0] == '+')
        {
            if( array[1] == 's' )
			{
                return scoreAsc;
			}
			else if( array[1] == 'n' )
			{
                return nameAsc;
			}
        }
    }
    return 0;
}

int main(int argc,char *argv[])
{   
    record_list prec;
    int option1;
    int option2;
    int option3;
    init(&prec);
    
    if(argc > 3)
    {
        fprintf(stderr, "Too many command line variables\n");
        return 0;
    }
    if(argc == 2)
    {
        option1 = CheckOption(argv[1], strlen(argv[1]));
        if(option1 == 0)
        {
            fprintf(stderr, "Invalid Option at %s\n", argv[1]);
            return 0;
        }
    }
    if(argc == 3)
    {
        if(argv[1][0] == '+')
            option2 = CheckOption(argv[2], strlen(argv[2]));
        if(argv[1][0] == '-')
            option3 = CheckOption(argv[2], strlen(argv[2]));
        if(argv[1][1] == argv[2][1])
        {
            fprintf(stderr, "Invalid Option at %s\n", argv[2]);
            return 0;
        }
    }

/*    while ((currecord=input_record(&prec)) != 0) {*/
     input_record(&prec); 
    sort(&prec, option1, option2, option3);

     print_record(prec);
    
    return 0;
}
