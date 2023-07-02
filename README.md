# <center>Minishell - as beautiful as a shell</center>

## Description

Minishell is a shell programme written in C.

<bt>


## Language used
[![Language used](https://skills.thijs.gg/icons?i=c)](https://skills.thijs.gg)

<bt>

## Functionality

It minics the behavior of bash:

- Display a prompt when waiting for a new command.
- Implement pipes and redirections.
- Search and launch the right executable based on the PATH variable or using a relative or an absolute path.
- Handle both single and double quotes.
- Handle $? which should expand to the exit status of the most recently executed foreground pipeline.
- Handle ctrl-C, ctrl-D and ctrl-\ which should behave like in bash.

<bt>
	In interactive mode:

		- ctrl-C displays a new prompt on a new line.
		- ctrl-D exits the shell.
		- ctrl-\ does nothing.

<bt>
	It implements the following builtins:

		- echo with option -n
		- cd with only a relative or absolute path ◦ pwd with no options
		- export with no options
		- unset with no options
		- env with no options or arguments
		- exit with no options

<br>

## Usage
**1- To compile the programme:**

    Make

**2- Run your program with arguments:**

	./minishell

## Testing

*External testers:*

+ [minishell_tester by LucasKuhn](https://github.com/LucasKuhn/minishell_tester.git)


## General info about Exit code

In Bash, exit status codes in the range 126-255 are typically used for specific purposes, but they are not reserved exclusively for those purposes. However, here are some commonly used exit status codes that are generally not used by Bash itself:

| exitcode | descriptions |
| :---| :----------- |
| 0   |Success. The command or script completed successfully.|
| 1   |General error. This code is used for generic errors that don't have a specific code assigned.|
| 2   |Misuse of shell built-ins. This code is used when there is a misuse of shell built-in commands or shell options.|
| 126 |Command not executable. This code is used when the command is found but is not executable.|
| 127 |Command not found. This code is used when the command is not found.|
| 128 |Invalid argument to exit. This code is used when the exit command is called with an invalid argument.|
| 130 |Script terminated by Ctrl+C. This code is used when the script is terminated by the user pressing Ctrl+C.|
| 255 |Exit status out of range. This code is used when the exit status specified is outside the valid range of 0-255.|

