/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chars_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlayine <zlayine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 10:28:49 by zlayine           #+#    #+#             */
/*   Updated: 2019/11/28 15:28:26 by zlayine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	chars_printer(char c, t_printf *sprint)
{
	if (sprint->prime < 1 && !sprint->zero)
		print_flag(' ', sprint->sp);
	alloc_manager(sprint, 2);
	if (c == 's')
	{
		if (sprint->pr && !sprint->point)
			print_flag('0', sprint->pr);
		ft_putstr(sprint->str);
		alloc_manager(sprint, 3);
	}
	else if (c == 'c')
	{
		if (!sprint->point)
			print_flag('0', sprint->pr);
		if (sprint->zero && sprint->point)
			print_flag('0', sprint->sp);
		ft_putchar(sprint->c);
	}
	if (sprint->prime == 1)
		print_flag(' ', sprint->sp);
}

void	chars_init(char c, t_printf *sprint)
{
	if (c == 's')
	{
		sprint->str = va_arg(*sprint->ap, char*);
		alloc_manager(sprint, 1);
	}
	else if (c == 'c')
	{
		sprint->c = (char)va_arg(*sprint->ap, int);
		sprint->special = 1;
	}
	else if (c == '%')
	{
		sprint->special = 1;
		sprint->c = '%';
		c = 'c';
	}
	flag_setter_char(sprint);
	chars_printer(c, sprint);
	sprint->total += sprint->len;
}

void	random_char(char c, t_printf *sprint)
{
	ft_putchar(c);
	sprint->total++;
}
