#include "builtin.h"
#include "minishell.h"
#include "executor.h"

int		g_exitcode = 0;

int	main(int argc, char **argv, char **env)
{
	t_mini			*mini;
	struct termios	t;

	if (argc != 1 || argv[1])
		ft_error("Wrong input!", FUNC);
	mini = malloc(sizeof(t_mini) * 1);
	if (!mini)
		ft_error("malloc fail.\n", 1);
	if (env_init(mini, env) != 1)
		ft_error("fail to init env variables.", 3);
	readline_prompt(mini);
	ft_lstfree(mini->env);
	free_str((char *)mini);
	tcgetattr(0, &t);
	t.c_lflag |= ECHOCTL;
	tcsetattr(0, TCSANOW, &t);
	return (0);
}

int	readline_prompt(t_mini *mini)
{
	char			*line;
	struct termios	t;

	line = NULL;
	//ascii_art_pattern();
	while (1)
	{
		signal(SIGINT, handle_signal);
		signal(SIGQUIT, SIG_IGN);
		tcgetattr(0, &t);
		t.c_lflag &= ~ECHOCTL;
		tcsetattr(0, TCSANOW, &t);
		line = readline("\033[32m\U0001F40C Minishell \033[31m$\033[0;39m ");
		if (!line)
		{
			printf("exit\n");
			g_exitcode = 0;
			exit(g_exitcode);
		}
		add_history(line);
		minishell(mini, line);
	}
	rl_clear_history();
	return (0);
}

void	minishell(t_mini *mini, char *line)
{
	int		i;
	t_list	*line_lst;
	int		size;

	line_lst = NULL;
	line_lst = get_linelst(line, line_lst, -1);
	free(line);
	line = NULL;
	if (handle_args_expand(line_lst, mini->env) == -1)
		return ;
	mini->cmd_lst = parse_cmds(line_lst, mini->env);
	ft_lstfree(line_lst);
	signal(SIGQUIT, handle_cmd);
	signal(SIGINT, handle_cmd);
	size = ft_lstsize(mini->cmd_lst);
	if (size == 0)
		return ;
	executor(mini, size);
}

void ascii_art_pattern()
{
	printf("\n\n*********************************************************");
	printf("\n*                                                       *");
	printf("\n*               Enter Minishell's Charm!                *");
	printf("\n*                                                       *");
	printf("\n*********************************************************\n\n");
}
