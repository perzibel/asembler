#include <stdio.h>


struct label
{
	char *labelName;
	int addres;
	int isE;
	int type;
	struct label *next;

};

typedef struct label label;
