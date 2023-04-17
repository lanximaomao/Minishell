void parser(t_mini *mini)
{
	char	*line;
	char	buf[256];

	//ascii_art_pattern();
	while (1)
	{
		if (getcwd(buf, sizeof(buf)) == NULL) // getcwd get the pwd show frond of the input
			error("Error: getcwd failed\n", 1);
		ft_printf("\033[32m\U0001F40C %s \033[31m>\033[0;39m", buf);
		if (!(line = readline(" ")))
			error("Error: readline failed\n", 1);
		if (ft_strncmp(line, "exit", 4) == 0)
		{
			free(line);
			break ;
		}
		//parsing using mini
		//
		//
		add_history(line);
		minishell(line);
	
