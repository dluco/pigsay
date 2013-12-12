#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER_LENGTH 256
#define MAX_LINES 50

void chomp(char *s)
{
	if (s != NULL) {
		size_t last = strlen(s) - 1;
		if (s[last] == '\n') s[last] = '\0';
	}
}

char *read_input (char *s, size_t length, FILE *f)
{
	char *p = fgets(s, length, f);
	chomp(s);
	return p;
}

char *prompt (char *s)
{
	char *p;

	printf("Enter your input: ");
	fflush(stdout);
	p = read_input(s, BUFFER_LENGTH, stdin);
	
	return p;
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

	return i;
}

int print_pig (char *text, char ***pig, int lines)
{
	int num_printed = 0;
	int i;

	if (text == NULL || pig == NULL) {
		return -1;
	}

	printf("%s\n", text);
	num_printed += strlen(text) + 1;

	for (i = 0; i < lines; i++) {
		printf("%s\n", (*pig)[i]);
		num_printed += strlen((*pig)[i] + 1);
	}

	return num_printed;
}

int main (int argc, char *argv[])
{
	char buffer[BUFFER_LENGTH];
	char *text;
	char **pig;
	int lines;
	int test;

	text = prompt(buffer);

	/* draw_cat(); */

	lines = get_pig("default.pig", &pig);
	if (lines == -1) {
		fprintf(stderr, "%s: Could not find %s\n", argv[0], "default.pig");
		exit(1);
	}
	
	test = print_pig(text, &pig, lines);
	if (test < 0) {
		fprintf(stderr, "%s: Output failed\n", argv[0]);
	}

	exit(0);
}
