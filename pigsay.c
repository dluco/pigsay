#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER_LENGTH 256
#define MAX_LINES 100

void chomp(char *s)
{
	if (s != NULL) {
		size_t last = strlen(s) - 1;
		if (s[last] == '\n') s[last] = '\0';
	}
}

char **read_input (char *s[][], size_t length, FILE *f)
{
	char **temp_s;
	char buffer[length];
	char *line;
	int i;

	temp_s = (char **) malloc(sizeof(char *) * MAX_LINES);
	if (temp_s == NULL) {
		fprintf(stderr, "Error allocating memory in read_input\n");
		exit(1);
	}
	
	for (i = 0; fgets(buffer, length, f) && i < MAX_LINES; i++) {
		line = (char *) malloc(sizeof(char) * (strlen(buffer) + 1));
		if (line == NULL) {
			fprintf(stderr, "Error allocating memory in read_inpput\n");
			exit(1);
		}
		strncpy(line, buffer, strlen(buffer) + 1);
		chomp(line);
		temp_s[i] = line;
	}

	temp_s[i] = NULL;

	if (feof(f)) {
		*s = temp_s;
	} else {
		/* an error occured */
		fprintf(stderr, "Error reading input\n");
		exit(1);
	}
	
	return temp_s;
}

void prompt (char *s[][])
{
	printf("Enter your input: ");
	fflush(stdout);
	read_input(s, BUFFER_LENGTH, stdin);
}

void draw_cat ()
{
	char *s = " /\\     /\\\n{  `---'  }\n{  O   O  }\n~~>  V  <~~\n \\  \\|/  /\n  `-----'____\n  /     \\    \\_\n {       }\\  )_\\_   _\n |  \\_/  |/ /  \\_\\_/ )\n  \\__/  /(_/     \\__/\n    (__/\n";
	printf("%s\n", s);
}

int get_pig (char *filename, char **pig[])
{
	FILE *f;
	char buffer[BUFFER_LENGTH];
	char *line;
	char **temp_pig;
	int i;

	f = fopen(filename, "r");
	if (f == NULL) {
		return -1;
	}

	temp_pig = (char **) malloc(sizeof(char *) * (MAX_LINES + 1));
	if (temp_pig == NULL) {
		fprintf(stderr, "Error allocating memory in get_pig\n");
		exit(1);
	}

	for (i = 0; fgets(buffer, BUFFER_LENGTH, f) && i < MAX_LINES; i++) {
		line = (char *) malloc(sizeof(char) * (strlen(buffer) + 1));
		if (line == NULL) {
			fprintf(stderr, "Error allocating memory in get_pig\n");
			exit(1);
		}
		strncpy(line, buffer, strlen(buffer) + 1);
		chomp(line);
		temp_pig[i] = line;
	}
	
	temp_pig[i] = NULL;
	
	*pig = temp_pig;

	fclose(f);

	return 0;
}

int print_pig (char ***text, char ***pig)
{
	int num_printed;
	int i;

	if (text == NULL || pig == NULL) {
		return -1;
	}

	num_printed = 0;

	for (i = 0; (*text)[i] != NULL; i++) {
		printf("%s\n", (*text)[i]);
		num_printed += strlen((*text)[i]) + 1;
	}

	for (i = 0; (*pig)[i] != NULL; i++) {
		printf("%s\n", (*pig)[i]);
		num_printed += strlen((*pig)[i] + 1);
	}

	return num_printed;
}

int main (int argc, char *argv[])
{
	char text[MAX_LINES][BUFFER_LENGTH];
	char **pig;

	prompt(&text);

	/* draw_cat(); */

	if (get_pig("default.pig", &pig) < 0) {
		fprintf(stderr, "%s: Could not find %s\n", argv[0], "default.pig");
		exit(1);
	}
	
	if (print_pig(&text, &pig) < 0) {
		fprintf(stderr, "%s: Output failed\n", argv[0]);
	}

	exit(0);
}
