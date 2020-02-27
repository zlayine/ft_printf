/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex_helper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlayine <zlayine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 10:32:47 by zlayine           #+#    #+#             */
/*   Updated: 2019/11/26 10:43:46 by zlayine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

long	get_reverse_hex_dec(long d, int step)
{
	int		i;
	long	r;

	r = 0;
	i = 0;
	if (!d / 16)
		d = 0;
	while (i < step)
	{
		r = r + (15 - (d % 16)) * ft_pow(16, i);
		d = d / 16;
		i++;
	}
	return (r + 1);
}

char	*convert_to_hex_p(unsigned long long d2, int step)
{
	static char *hex_tab;
	static int	l = 0;

	if (step == 0)
	{
		hex_tab = (char *)ft_calloc(15, sizeof(char));
		l = 0;
	}
	if (d2 / 16 > 0)
		convert_to_hex_p(d2 / 16, ++step);
	hex_tab[l++] = hex_digit(d2 % 16, 0);
	return (hex_tab);
}

char	*convert_to_hex(long long d, char c, int step)
{
	static char *hex_tab;
	static int	l = 0;
	int			maj;

	if (step == 0)
	{
		hex_tab = (char *)ft_calloc(15, sizeof(char));
		l = 0;
	}
	maj = 0;
	if (c == 'X')
		maj = 1;
	if (d < 0)
		d = get_reverse_hex_dec(-d, 8);
	if (d / 16 > 0)
		convert_to_hex(d / 16, c, ++step);
	hex_tab[l++] = hex_digit(d % 16, maj);
	return (hex_tab);
}

void	hex_init(char c, t_printf *sprint)
{
	if (c == 'x' || c == 'X')
	{
		if (sprint->islong == 1)
			sprint->n = (long)va_arg(*sprint->ap, long);
		else if (sprint->islong == 2)
			sprint->n = (long long)va_arg(*sprint->ap, long long);
		else
			sprint->n = (long)va_arg(*sprint->ap, int);
		sprint->str = convert_to_hex(sprint->n, c, 0);
	}
	else if (c == 'p')
	{
		sprint->un = (unsigned long long)va_arg(*sprint->ap, void*);
		sprint->hash = 1;
		sprint->str = convert_to_hex_p(sprint->un, 0);
	}
	sprint->c = c;
	flag_setter_hex(sprint);
	hex_printer(c, sprint);
	if (sprint->str)
		free(sprint->str);
}

void	hex_printer(char c, t_printf *sprint)
{
	if (sprint->prime < 1)
		print_flag(' ', sprint->sp);
	if ((sprint->hash && sprint->str[0] != '0') || c == 'p')
	{
		if (c == 'X')
			ft_putstr("0X");
		else
			ft_putstr("0x");
	}
	print_flag('0', sprint->pr);
	if (sprint->str[0] == '0' && sprint->pr == 0)
		sprint->len = sprint->len;
	else
		ft_putstr(sprint->str);
	if (sprint->prime == 1)
		print_flag(' ', sprint->sp);
	sprint->total += sprint->len;
}
