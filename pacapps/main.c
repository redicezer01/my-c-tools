/*
 * Name: pacapps
 * Description : list all explicitly installed apps
 * Package managers: pacman
 * 
 * P.S.: just for c programming practice
 * P.S.2.: shell script for that purpose more practical
 *	   and easier
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXEXECSIZ 1000
#define MAXLINE 1000

char cmd[] = "pacman -Qei";
char out[] = "out.txt";
char exec[MAXEXECSIZ];

int catcmd(char *exec, char c1[], char catc[], char c2[]);
int isprefix(char *s, char *p);
int getval(char *s, char *v);

int main()
{
	/* save list of all explicitly installed apps */
	catcmd(exec, cmd, " > ", out);
	system(exec);
	
	/* read list */
	FILE *fp;
	fp = fopen(out, "r");

	/* parse Name and Description */
	char line[MAXLINE];
	int t = 0;
	char name[MAXEXECSIZ];
	char desc [MAXEXECSIZ];
	while (fgets(line, MAXLINE, fp) != NULL) {
		if (strlen(line) > 3 && isprefix(line, "Name")) {
			getval(line,name);	
			++t;
		}
		if (strlen(line) > 9 && isprefix(line, "Description")) {
			getval(line, desc);	
			++t;
		}
		if (line[0] == '\n') {
			printf("%s - %s\n",name, desc);
			t = 0;
		}
		
	}
	
	return (0);
}

/* catcmd: concatenates command c1 and c2 with catc delimiter between them */ 
int catcmd(char *exec, char c1[], char catc[], char c2[])
{
	strcat(exec, c1);
	strcat(exec, catc);
	strcat(exec, c2);

	return 0;
}

/* getval: copy to v value after colon (:) from s */
int getval(char *s, char *v)
{
	int i = 0;
	int prev = '\0';
	while (*s++ != ':')
		;
	s++;
	while (*s != '\0') {
		if ((prev == ' ' && *s == ' ') || *s == '\n')
			break;
		v[i++] = *s;
		prev = *s++;
	}
	v[i] = '\0';	

	return 0;
}

/* isprefix: is p prefix for s */
int isprefix(char *s, char *p)
{
	int len, i = 0;
	len = strlen(p);

	if (strlen(s) < len || len == 0)
		return 0;

	while (*p != '\0' && *s++ == *p++)
		--len;

	return !len;
}
