/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsun <lsun@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 17:19:46 by lliu              #+#    #+#             */
/*   Updated: 2023/07/31 16:12:35 by lsun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "../libft_42/inc/ft_printf.h"
# include "minishell.h"

/* builtin */
int		is_builtin(t_token *token);
int		run_builtin(t_token *token, t_list **env);
int		is_equal_sign(char *arg, int i, char c);
int		printf_error(char *msg, int code);

/* functions */
int		my_env(t_list *env);
void	my_exit(char **args, int num_args, int cmd_id);
void	my_pwd(void);
void	my_cd(char **args, t_list **env);
void	my_echo(char **arg);
void	my_export(char **arg, t_list **env);
void	my_unset(char **arg, t_list **env);

#endif
