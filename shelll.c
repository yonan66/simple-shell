#include "main.h"

/* Function to handle the execution of non-built-in commands */
void execute_non_builtin(char **av, char **args, char **env)
{
	struct stat check;
	int yemejemeryaw_arg_info;

	yemejemeryaw_arg_info = stat(args[0], &check);
	execute_cmd(av, args, env, yemejemeryaw_arg_info);
}

/* Function to handle the shell loop */
void shell_loop(char **av, char **env)
{
	char *line = NULL;
	char **args = NULL;
	int mestegabir = 0, tezega = 0;

	signal(SIGINT, handle_signal);

	for (; tezega != -1; tezega = 0)
	{
		mestegabir = isatty(0);
		prompt();

		/* Read input from the user. */
		line = read_input(mestegabir);

		/* If the user enters "exit", exit the shell program. */
		if (!strcmp(line, "exit"))
		{
			tezega = -1;
		}
		else
		{
			/* Split the input line into arguments. */
			args = split_str(line, env);

			/*
			 * If the first argument is not empty and is not the "env" command,
			 * execute the command.
			*/
			if (strcmp(args[0], "\n") && strcmp(args[0], "env"))
			{
				execute_non_builtin(av, args, env);
			}

			/* Free the args array. */
			free(args);
		}

		/* Free the line buffer. */
		free(line);
	}
}

/*
 * main - Creates a shell prompt, reads and executes commands, and waits
 *        for another command unless told to exit.
 * @ac: Number of arguments
 * @av: Array of arguments
 * @env: Environment variables
 * Return: 0
 */
int main(int ac __attribute__((unused)), char **av, char **env)
{
	shell_loop(av, env);
	return (0);
}
