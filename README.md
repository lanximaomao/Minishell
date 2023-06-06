# minishell

## comments

at least add for the functions

## The commit format

type: subject
\newline
body (optional)

type: feat/fix/perf/refactor/style/test/docs/built, just pick one.

##

tester:
cd minishell
git clone https://github.com/LucasKuhn/minishell_tester.git
cd minishell_tester && ./tester


to do list:

1. remove the heredoc file --> done!
2. test the signals
3. check for memory leak
4. error handel
5. remove printf in the signal handeler
6. env_convert returned char** to be freed!
7. update the error code for malloc fail etc, since it will be overlapping with other erros?
8. function name? comment?


/*
export TEST --> no change
export TEST= --> TEST=
export TEST= --> TEST=
export TEST=WHATEVER --> TEST=WHATEVER
export TEST=YES,MINIHELL --> TEST=YES,MINIHELL
export TEST=YES MINIHELL --> TEST=YES
*/

valid arg for export:
/*
first character should be a letter or _
- is not allowed anywhere
 no space before or after equal sign?
 */

bug:
1. running cat and ctrl + \ results prints ^\^\Quit: 3 in terminal
2. >> or << or > ' leads to segfault. check out lexer-> handle token
3. by given ", syntax error will be printing nonstop....
4. handle oldpwd


Note:

In Bash, exit status codes in the range 126-255 are typically used for specific purposes,
but they are not reserved exclusively for those purposes. However, here are some commonly
used exit status codes that are generally not used by Bash itself:

0: Success. The command or script completed successfully.
1: General error. This code is used for generic errors that don't have a specific code assigned.
2: Misuse of shell built-ins. This code is used when there is a misuse of shell built-in commands or shell options.
126: Command not executable. This code is used when the command is found but is not executable.
127: Command not found. This code is used when the command is not found.
128: Invalid argument to exit. This code is used when the exit command is called with an invalid argument.
130: Script terminated by Ctrl+C. This code is used when the script is terminated by the user pressing Ctrl+C.
255: Exit status out of range. This code is used when the exit status specified is outside the valid range of 0-255.


After Eval by Carlos:

1. .vscode/.DS_store;
2. ~~echo -nnnn -nnn hello;~~

3. echo "he"'llo';

4. ~~exit dshadk 254 / echo 254 dse; exit or not exit, exitcode = 255~~
5. ~~^D, print exit after prompt not newline;~~

6. export PATH+=$HOME, append the value;
7. export lin=world dsds; export should ouput dsds, env not ouput;

8. ~~unset OLDPWD, export not output OLDPWD;~~
9.  ~~unset $HOME -> cd -> HOME is not set;~~
10. ~~./pipex "" "" "" ""; syntax error!!~~
11. ~~ls | | echo hello; should syntax error;~~
12. ~~ls >outfile; fd leaks;~~
13. ~~exit | exit shouldn't output exit;~~
14. ~~<|, ignore the pipe;~~

