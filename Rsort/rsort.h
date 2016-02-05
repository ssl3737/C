#ifndef RECODE_H

	#define RECODE_H

	/* Declaring functions */
	int nameAsc(const void *p, const void *q);

	int nameDesc(const void *p, const void *q);

	int scoreAsc(const void *p, const void *q);

	int scoreDesc(const void *p, const void *q);

	int nameAscScoreAsc(const void *p, const void *q);

	int nameAscScoreDesc(const void *p, const void *q);

	int nameDescScoreAsc(const void *p, const void *q);

	int nameDescScoreDesc(const void *p, const void *q);

	int scoreAscNameAsc(const void *p, const void *q);

	int scoreAscNameDesc(const void *p, const void *q);

	int scoreDescNameAsc(const void *p, const void *q);

	int scoreDescNameDesc(const void *p, const void *q);
    

#endif