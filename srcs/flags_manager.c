/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlayine <zlayine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 10:31:23 by zlayine           #+#    #+#             */
/*   Updated: 2019/11/26 14:59:13 by zlayine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	flag_signs(char *s, t_printf *sprint)
{
	if (*s == '+')
		sprint->sign = 1;
	else if (*s == '#')
		sprint->hash = 1;
	else if (*s == '\'')
		sprint->grp = 1;
}

char		*flag_checker(char *s, t_printf *sprint)
{
	int		j;

	init_printf(sprint);
	while (*s)
	{
		if (is_command(*s, 'c'))
			break ;
		else if (*s == *(s + 1) && (!ft_isdigit(*s) ||
			*s == '0') && *s != 'l' && *s != 'h')
		{
			sprint->sp = 0;
			while (*(s + 1) == *s)
				s++;
		}
		else
		{
			if ((j = is_command(*s, 'p')) < 6 && j != 0)
				s = flag_primary(s, j, sprint);
			else if ((j = is_command(*s, 's')) < 3 && j != 0)
				s = flag_secondary(s, sprint);
			flag_signs(s, sprint);
			s++;
		}
	}
	return (s);
}

int			flag_width(char *s, int j, t_printf *sprint)
{
	int		len;

	if (j == 2)
	{
		if (*(s + 1) == '*')
			len = flag_star(sprint, 0);
		else
		{
			len = push_str(s + 1);
			sprint->sp = (j == -1) ? (ft_atoi(s)) : (ft_atoi(s + len + 1));
			len += ft_nblen(sprint->sp);
		}
	}
	else
	{
		sprint->sp = (j == -1) ? (ft_atoi(s)) : (ft_atoi(s + 1));
		len = ft_nblen(sprint->sp);
	}
	return (len);
}

char		*flag_primary(char *s, int j, t_printf *sprint)
{
	int len;

	len = 1;
	if (*s == 'l')
		sprint->islong++;
	else if (*s == 'h')
		sprint->isshort++;
	if (*s == 'l' || *s == 'h')
		return (s);
	sprint->prime = (j > 0) ? j - 1 : -1;
	if (j == 3)
		len = flag_star(sprint, 0);
	else if (j == 2 || j == -1)
		len = flag_width(s, j, sprint);
	else
		sprint->csign = ' ';
	s += (*s != '*') ? FLAG_RES(len, sprint->prime) : 0;
	return (s);
}

char		*flag_secondary(char *s, t_printf *sprt)
{
	if (sprt->pr > 0)
	{
		sprt->sp = sprt->pr;
		sprt->prime = -1;
	}
	if (*(s + 1) != ' ')
	{
		if (*s == '.')
			sprt->point = 1;
		if (*(s + 1) == '*')
			sprt->pr = va_arg(*sprt->ap, int);
		else if (ft_isdigit(*(s + 1)) || sprt->point)
			sprt->pr = ft_atoi(s + push_str(s + 1) + 1);
		if (*s == '0' && !sprt->point)
			sprt->zero = 1;
		sprt->pr = (sprt->pr < 0) ? -1 : sprt->pr;
		if (*(s + 1) != '*' || sprt->pr != 0)
			s += (*(s + 1) == '*') ? 1 : str_nblen(s + 1);
		else
			s++;
	}
	else
		s++;
	return (s);
}
