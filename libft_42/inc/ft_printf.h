/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliu <lliu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 18:10:14 by lliu              #+#    #+#             */
/*   Updated: 2023/02/22 14:18:12 by lliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# include "libft.h"

int		ft_printchr(int c);
int		ft_printstr(char *str);
int		ft_printnbr(int nb);
int		ft_printunsigned(unsigned int n);
int		ft_printpercent(void);

int		ft_printptr(unsigned long int ptr);
int		ft_printhex(unsigned int n, char cur_ch);

char	*ft_uitoa(unsigned int n);
int		ft_printf(const char *str, ...);
#endif
