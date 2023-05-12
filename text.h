#include <stdio.h>
#define Z 0
#define D 1
#define S 2
#define En 3
#define Ex 4
#define Yflag 1 //if there is a label
#define Nflag 0//if there's no label
#define Dflag 0
#define Sflag 1
#define EXflag 2
#define ENflag 3
#define ICflag 4
#define maxLabelSize 31
#define maxLineSize 80
#define yBlank 1
#define nBlank 0

int blankLine;
int labFlag;
int insFlag;

struct line_s
{
	char * line;
	char *dsex; /*data , string , entry , extern*/
	char *labName;
	int lineNum;
	int labFlag;
	int insFlag;
	struct line_s *next;

} ;

typedef struct line_s line_s;


