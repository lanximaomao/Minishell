#include "minishell.h"

void	ascii_art_pattern(void)
{
	ft_printf("\n\n*********************************************************");
	ft_printf("\n*                                                       *");
	ft_printf("\n*               Enter Minishell's Charm!                *");
	ft_printf("\n*                                                       *");
	ft_printf("\n*********************************************************\n\n");
}

void	exit_with_empty_line(char *msg, int exit_code)
{
	printf("\033[1A\033[32m\U0001F40C Minishell \033[31m$\033[0;39m %s", msg);
	g_exitcode = exit_code;
	exit(g_exitcode);
}

void	remove_tmp_file(int size)
{
	int		i;
	char	*tmp_itoa;
	char	*tmp_file;

	i = 0;
	while (i < size)
	{
		tmp_itoa = ft_itoa(i);
		tmp_file = ft_strjoin("tmp_file", tmp_itoa);
		if (!tmp_file)
			ft_error("strjoin fail", MALLOC, 0);
		unlink(tmp_file);
		free_str(tmp_itoa);
		free_str(tmp_file);
		i++;
	}
}
