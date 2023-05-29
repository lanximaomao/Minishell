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

1. remove the heredoc file
2. test the signals
3. check for memory leak
4. error handel
5. remove printf in the signal handeler
6. env_convert returned char** to be freed!
7. update the error code for malloc fail etc, since it will be overlapping with other erros?
8. memory?


/*
export TEST --> no change
export TEST --> TEST=
export TEST=WHATEVER --> TEST=WHATEVER
export TEST=YES,MINIHELL --> TEST=YES,MINIHELL
export TEST=YES MINIHELL --> TEST=YES
*/

valid arg for export:
/*
first character should be a letter or _
- is not allowed anywhere
 no space before or after equal sign?
 first character should be a letter or _
 */

bug:
1. running cat and ctrl + \ results prints ^\^\Quit: 3 in terminal
2. >> or << or > ' leads to segfault. check out lexer-> handle token
3. by given ", syntax error will be printing nonstop....
4. grep oi | ls cannot terminate after one ctrl + d but two??

5. FIXED! echo hello > test/stljs,  prints hello anyway..
6. export HELLO=123, why this does not show up in env??
