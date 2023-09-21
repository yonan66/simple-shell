#include "main.h"

/**
 * read_input - Reads user input from stdin.
 * @mestegabir: Flag indicating interactive or non-interactive input.
 *
 * Return: A dynamically allocated string containing user input.
 *         NULL is returned on certain conditions, such as empty input or exit.
 */
/* Function declarations */
char *read_input(int mestegabir);
void handle_eof(char **line);
void remove_extra_spaces(char **line);
int is_empty_line(char *line);
char *read_input(int mestegabir)
{
	char *line = NULL;
	size_t buf_size = 0;
	int bytes_read;

	if (mestegabir == 1)
	{
		if (getline(&line, &buf_size, stdin) == -1)
		{
			exit(1);
		}
	}
	else
	{
		bytes_read = getline(&line, &buf_size, stdin);

		if (_strcmp(line, "exit") == 0)
		{
			return (line);
		}

		if (bytes_read == 1)
		{
			free(line);
			return (NULL);
		}

		if (bytes_read == EOF)
		{
			handle_eof(&line);
		}
	}

	remove_extra_spaces(&line);

	if (is_empty_line(line))
	{
		free(line);
		return (NULL);
	}

	return (line);
}

/**
 * handle_eof - Handles the EOF condition.
 * @line: Pointer to the input string.
 */
void handle_eof(char **line)
{
	prints("\n");
	free(*line);
	exit(0);
}

/**
 * remove_extra_spaces - Removes extra leading spaces from a string.
 * @line: Pointer to the input string.
 */
void remove_extra_spaces(char **line)
{
	while ((*line)[0] == ' ' && (*line)[1] == ' ')
	{
		(*line)++;
	}
}

/**
 * is_empty_line - Checks if a line is empty (contains only newline).
 * @line: Pointer to the input string.
 *
 * Return: 1 if the line is empty, 0 otherwise.
 */
int is_empty_line(char *line)
{
	return (!line[0] && line[1] == '\n');
}
