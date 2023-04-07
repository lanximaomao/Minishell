/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linlinsun <linlinsun@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 19:16:30 by linlinsun         #+#    #+#             */
/*   Updated: 2022/11/30 04:12:13 by linlinsun        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

int	ft_printf(const char *str, ...);
int	ft_hexa_deci_big(unsigned int n);
int	ft_hexa_deci_small(unsigned int n);
int	ft_printf_ptr(unsigned long long n);
int	ft_putchar_printf(char c, int fd);
int	ft_putstr_printf(char *s, int fd);
int	ft_putnbr_printf(int n, int fd);
int	ft_putnbr_unsigned_printf(unsigned int n, int fd);

#endif
