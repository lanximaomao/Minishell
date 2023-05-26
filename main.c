#include "minishell.h"
#include "builtin.h"

void rl_clear_history (void);
int g_exitcode = 0;


int	readline_prompt(t_mini *mini)
{
	char	*line;
	struct termios t;

	line = NULL;
	//ascii_art_pattern();
	while (1)
	{
		signal(SIGINT, handle_signal);
		signal(SIGQUIT, SIG_IGN);
		tcgetattr(0, &t);
		t.c_lflag &= ~ECHOCTL; // 禁止终端回显控制字符
		tcsetattr(0, TCSANOW, &t);
		if (!(line = readline("\033[32m\U0001F40C Minishell \033[31m$\033[0;39m ")))
		{
			// CTRL+D gives an EOF signal, and sets line to NULL.
			printf("exit\n");
			g_exitcode = 0;
			exit(g_exitcode);
		}
		//parsing using mini
		add_history(line);
		// execute all the input cmd, while loop for signal processing
		minishell(mini, line); // exitcode is 0, handle in later
	}
	rl_clear_history();
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	t_mini *mini;
	struct termios t;


	if (argc != 1 || argv[1])
		ft_error("Wrong input!", FUNC);
	mini = malloc(sizeof(t_mini) * 1);
	if (!mini)
		ft_error("malloc fail.\n", 1);
	if (env_init(mini, env) != 1)
		ft_error("fail to init env variables.", 3);
	readline_prompt(mini);
	ft_lstfree(mini->env);
	free_str((char *)mini); // 内部cmd_lst在使用结束后已经free了
	tcgetattr(0, &t); // 获取终端stdin属性结构体
	t.c_lflag |= ECHOCTL; // 重新修改回来，否则自身terminal也无法回显控制字符
	tcsetattr(0, TCSANOW, &t);
	return(0);
}

void ascii_art_pattern()
{
	printf("\n\n/* ************************************************************************** */");
	printf("\n/*                                                                            */");
	printf("\n/*                                                        :::      ::::::::   */");
	printf("\n/*   MINISHELL                                          :+:      :+:    :+:   */");
	printf("\n/*                                                    +:+ +:+         +:+     */");
	printf("\n/*   Version: 0.0.1                                 +#+  +:+       +#+        */");
	printf("\n/*                                                +#+#+#+#+#+   +#+           */");
	printf("\n/*   Created: 2023/03/16                               #+#    #+#             */");
	printf("\n/*   Updated: 2023/03/16                              ###   ########.fr       */");
	printf("\n/*                                                                            */");
	printf("\n/* ************************************************************************** */\n\n");
}

/*
\U0001F600 for smily face
\U0001F333 for a tree
\U0001F41A for a shell
\U0001F40C for a snail
*/

// process_signal controls

