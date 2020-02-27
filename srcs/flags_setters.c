/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags_setters.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlayine <zlayine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 20:16:41 by zlayine           #+#    #+#             */
/*   Updated: 2019/11/26 15:16:14 by zlayine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_flag(char flag, int len)
{
	int i;

	i = -1;
	while (++i < len)
		ft_putchar(flag);
}

void	flag_setter_dec(t_printf *sprt)
{
	int reset;

	sprt->sign = (sprt->c == 'u') ? 0 : sprt->sign;
	sprt->csign = (sprt->c == 'u') ? 0 : sprt->csign;
	if (sprt->c == 'd')
		sprt->len = (sprt->n) ? ft_nblen(sprt->n) : 1;
	else
		sprt->len = (sprt->un) ? ft_nblen_un(sprt->un) : 1;
	sprt->len = (sprt->grp) ? sprt->len + ((sprt->len - 1) / 3) : sprt->len;
	if (sprt->n == 0 && sprt->pr == 0 && sprt->c == 'd')
		sprt->len = 0;
	else if (sprt->un == 0 && sprt->pr == 0 && sprt->c == 'u')
		sprt->len = 0;
	reset = (sprt->pr != 0) ? sprt->pr : 0;
	(sprt->sign) ? flag_setter_sign(sprt) : 0;
	sprt->len += ((sprt->csign || sprt->sign) && !sprt->point) ? 1 : 0;
	sprt->pr = CALC_PREC_DEC(sprt->pr, sprt->len, sprt->sign);
	sprt->len += ((sprt->csign || sprt->sign) && sprt->point) ? 1 : 0;
	if (sprt->prime)
		sprt->sp = CALC_SPACE_DEC(sprt->sp, sprt->pr, sprt->len, sprt->sign);
	if (sprt->sp && sprt->point && sprt->sign)
		sprt->sp++;
	sprt->len = sprt->sp + sprt->pr + sprt->len;
	if (reset && sprt->pr == 0)
		sprt->pr = -1;
}

void	flag_setter_char(t_printf *sprt)
{
	if (sprt->str)
		sprt->len = ft_strlen(sprt->str);
	else
		sprt->len = 1;
	if (sprt->special && !sprt->point)
		sprt->pr = (sprt->pr > 1) ? sprt->pr - 1 : -1;
	else if (sprt->special && sprt->point)
		sprt->pr = -1;
	else if (!sprt->point)
		sprt->pr = (sprt->pr > sprt->len) ? sprt->pr - sprt->len : -1;
	else
		sprt->pr = (sprt->pr > sprt->len) ? sprt->len : sprt->pr;
	if (sprt->special)
		sprt->len = ((sprt->pr != -1) ? sprt->pr + 1 : sprt->len);
	else if (!sprt->point)
		sprt->len = ((sprt->pr != -1) ? sprt->pr + sprt->len : sprt->len);
	else
		sprt->len = ((sprt->pr != -1) ? sprt->pr : sprt->len);
	sprt->sp = CALC_SPACE_CHAR(sprt->sp, sprt->len);
	sprt->len += sprt->sp;
}

void	flag_setter_hex(t_printf *sprt)
{
	int reset;

	reset = 0;
	sprt->n = 0;
	sprt->un = 0;
	if (sprt->pr != 0)
		reset = sprt->pr;
	sprt->len = ft_strlen(sprt->str);
	if (sprt->hash && !sprt->point && (sprt->str[0] != '0' || sprt->c == 'p'))
		sprt->len += 2;
	sprt->pr = (sprt->pr > sprt->len) ? sprt->pr - sprt->len : 0;
	if (sprt->hash && sprt->point && (sprt->str[0] != '0' || sprt->c == 'p'))
		sprt->len += 2;
	if (sprt->pr == 0 && sprt->len && sprt->str[0] == '0' && sprt->point
		&& sprt->c != 'p')
		sprt->len = 0;
	else if (sprt->str[0] == '0' && sprt->point && sprt->c == 'p')
		sprt->len--;
	sprt->sp = CALC_SPACE_HEX(sprt->sp, sprt->len, sprt->pr);
	sprt->len = sprt->sp + sprt->pr + sprt->len;
	if (reset && sprt->pr == 0)
		sprt->pr = -1;
}

void	flag_setter_sign(t_printf *sprt)
{
	sprt->sp = (sprt->sp > 1 && sprt->point) ? sprt->sp - 1 : sprt->sp;
	if (sprt->sign == 1)
		if (!sprt->csign || sprt->csign == ' ')
			sprt->csign = '+';
}
