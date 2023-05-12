#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define typeS 1
#define typeI 0

struct datat
{
	char *ch;// a way to save chars for strings
	int x;//a way to save int for data
};

typedef struct datat datat;

struct datal
{
	int DC;
	int type;
	datat *value;
	struct datal *next;

}; 

typedef struct datal datal;
