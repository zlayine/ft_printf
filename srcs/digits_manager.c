/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   digits_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlayine <zlayine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 10:30:10 by zlayine           #+#    #+#             */
/*   Updated: 2019/11/26 10:47:58 by zlayine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		group_printer(unsigned long long r)
{
	char	comma[26];
	int		i;
	int		l;
	int		o;

	i = 0;
	l = ft_nblen_un(r);
	o = l + ((l - 1) / 3);
	comma[o--] = '\0';
	while (r / 10)
	{
		comma[o--] = (r % 10) + '0';
		if (!(++i % 3))
			comma[o--] = ',';
		r /= 10;
	}
	comma[o] = (r % 10) + '0';
	ft_putstr(comma);
}

void		digits_printer(t_printf *sprint)
{
	if (sprint->prime < 1 || sprint->prime == 2)
		print_flag(' ', sprint->sp);
	if (sprint->csign)
		print_flag(sprint->csign, 1);
	print_flag('0', sprint->pr);
	if ((sprint->pr != 0 && sprint->un == 0) || sprint->n != 0)
	{
		if (sprint->grp)
			group_printer(sprint->n);
		else
			ft_putnbr(sprint->n);
	}
	else if (sprint->pr != 0 || sprint->un != 0)
	{
		if (sprint->grp)
			group_printer(sprint->un);
		else
			ft_putnbr_un(sprint->un);
	}
	if (sprint->prime == 1)
		print_flag(' ', sprint->sp);
	sprint->total += sprint->len;
}

static int	unsigned_init(t_printf *sp)
{
	if (sp->islong == 1)
		sp->un = (unsigned long long)va_arg(*sp->ap, unsigned long);
	else if (sp->islong == 2)
		sp->un = (unsigned long long)va_arg(*sp->ap, unsigned long long);
	else
		sp->un = (unsigned long long)va_arg(*sp->ap, unsigned int);
	return (1);
}

void		dec_init(char c, t_printf *sp)
{
	if (c == 'd' || c == 'i')
	{
		if (sp->islong == 1)
			sp->n = (long long)va_arg(*sp->ap, long);
		else if (sp->islong == 2)
			sp->n = (long long)va_arg(*sp->ap, long long);
		else if (sp->isshort == 1)
			sp->n = (short)va_arg(*sp->ap, int);
		else if (sp->isshort == 2)
			sp->n = (char)va_arg(*sp->ap, int);
		else if (sp->isshort != 2)
			sp->n = (long long)va_arg(*sp->ap, int);
		sp->csign = (sp->n < 0) ? '-' : sp->csign;
		sp->n = (sp->n < 0) ? -sp->n : sp->n;
	}
	else if (c == 'u')
		unsigned_init(sp);
	sp->c = (c == 'd' || c == 'i') ? 'd' : 'u';
	flag_setter_dec(sp);
	digits_printer(sp);
}
