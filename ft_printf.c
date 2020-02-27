/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlayine <zlayine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 10:34:44 by zlayine           #+#    #+#             */
/*   Updated: 2019/11/26 15:13:09 by zlayine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			init_printf(t_printf *sprint)
{
	sprint->prime = 0;
	sprint->sp = 0;
	sprint->pr = -1;
	sprint->sign = 0;
	sprint->hash = 0;
	sprint->len = 0;
	sprint->point = 0;
	sprint->csign = 0;
	sprint->special = 0;
	sprint->zero = 0;
	sprint->n = 0;
	sprint->un = 0;
	sprint->grp = 0;
	sprint->islong = 0;
	sprint->isshort = 0;
	sprint->str = 0;
	sprint->c = 0;
	sprint->mal = 0;
}

char			*mand_manager(char *s, t_printf *sprint)
{
	if (*s == 'd' || *s == 'i' || *s == 'u')
		dec_init(*s, sprint);
	else if (*s == 's' || *s == 'c')
		chars_init(*s, sprint);
	else if (*s == 'x' || *s == 'X' || *s == 'p')
		hex_init(*s, sprint);
	else if (*s == 'n')
		*(va_arg(*sprint->ap, int *)) = sprint->total;
	else if (*s == '%')
		chars_init('%', sprint);
	return (s);
}

static int		check_if_valid(const char *s)
{
	int		i;
	int		sp;

	i = -1;
	sp = 0;
	if (ft_strlen(s) <= 1 && s[0] == '%')
		return (0);
	else
		s++;
	while (s[++i])
		if (s[i] == ' ' && sp == 0)
			sp = 1;
		else if (s[i] == ' ' && sp)
			return (-i);
		else
		{
			sp = 0;
			if (!is_command(s[i], 'c') && !is_command(s[i], 'p') &&
				!is_command(s[i], 's') && s[i] != '\'' && s[i] != '+' &&
				s[i] != '#')
				return (-i);
			else if (is_command(s[i], 'c'))
				return (1);
		}
	return (0);
}

static void		init_ap(t_printf *sprt, va_list *ap)
{
	sprt->ap = ap;
	sprt->total = 0;
}

int				ft_printf(const char *s, ...)
{
	va_list		ap;
	t_printf	*sprt;
	int			r;

	if (!(sprt = malloc(sizeof(t_printf))))
		return (0);
	va_start(ap, s);
	init_ap(sprt, &ap);
	while (*s)
	{
		if (*s == '%')
		{
			if ((r = check_if_valid(s)) > 0)
				s = mand_manager(flag_checker((char *)s + 1, sprt), sprt);
			else
				s += -r;
		}
		else
			random_char(*s, sprt);
		s++;
	}
	va_end(ap);
	r = sprt->total;
	free(sprt);
	return (r);
}
