#include <stdio.h>

struct entry
{
	char *labelName;
	int addres;
	int isE;
	int type;
	struct entry *next;

};

typedef struct entry entry;
