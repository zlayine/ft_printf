/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlayine <zlayine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 10:34:09 by zlayine           #+#    #+#             */
/*   Updated: 2019/11/26 20:38:05 by zlayine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		push_str(char *s)
{
	char	str[17];
	int		i;
	int		j;

	i = 0;
	j = 0;
	ft_strlcpy(str, ".-cspdiuxX%nlh", 17);
	while ((!ft_isdigit(*s) || *s == '0'))
	{
		i = 0;
		while (str[i])
		{
			if (str[i] == *s)
				return (j);
			i++;
		}
		s++;
		j++;
	}
	return (j);
}

int		str_nblen(char *s)
{
	char	str[19];
	int		i;
	int		j;

	j = 0;
	i = -1;
	ft_strlcpy(str, " cspdiuxX%n-.+lh", 19);
	while (s[j])
	{
		i = -1;
		while (str[++i])
			if (str[i] == s[j])
				return (j);
		j++;
	}
	return (0);
}

int		is_command(char c, char x)
{
	char	fl[15];
	char	sec[3];
	char	str[13];
	char	*tmp;
	int		i;

	ft_strlcpy(fl, " -*lh123456789", 15);
	ft_strlcpy(str, "cspdiuxX%n", 13);
	ft_strlcpy(sec, "0.", 3);
	if (x == 'p')
		tmp = fl;
	else if (x == 'c')
		tmp = str;
	else
		tmp = sec;
	i = 0;
	while (tmp[i])
		if (tmp[i++] == c)
		{
			if (x == 'p' && i < 15 && i > 5)
				return (-1);
			return (i);
		}
	return (0);
}

int		flag_star(t_printf *sprint, int len)
{
	sprint->sp = va_arg(*sprint->ap, int);
	if (sprint->prime != 1)
		sprint->prime = (sprint->sp < 0) ? 1 : -1;
	sprint->sp = (sprint->sp < 0) ? -sprint->sp : sprint->sp;
	return (len + 1);
}

void	alloc_manager(t_printf *sprint, int step)
{
	char	*tmp;

	if (step == 1)
	{
		if (!sprint->str)
		{
			sprint->str = ft_strdup("(null)");
			sprint->mal = 1;
		}
	}
	else if (step == 2)
	{
		if (sprint->pr != -1 && sprint->point)
		{
			if (sprint->mal)
				tmp = sprint->str;
			sprint->str = ft_substr(sprint->str, 0, sprint->pr);
			if (sprint->mal)
				free(tmp);
			sprint->mal = 1;
		}
	}
	else if (step == 3)
		if (sprint->mal)
			free(sprint->str);
}
