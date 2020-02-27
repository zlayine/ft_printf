/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlayine <zlayine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 10:34:38 by zlayine           #+#    #+#             */
/*   Updated: 2019/11/26 12:14:39 by zlayine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <stdarg.h>
# include <stdio.h>

typedef struct		s_printf
{
	va_list				*ap;

	int					prime;
	int					pr;
	int					sign;
	int					hash;
	int					point;
	int					sp;
	int					len;
	int					total;
	int					special;
	int					islong;
	int					isshort;
	int					grp;
	int					mal;
	int					zero;

	char				csign;

	long long			n;
	unsigned long long	un;
	char				*str;
	char				c;
}					t_printf;

# define ABS(v) ((v < 0) ? -v : v)
# define ABS_PREC(v) ((v < 0) ? 0 : v)
# define GET_RES(x, y) ((y <= 0) ? x - 1 : x)
# define FLAG_RES(x, y) ((x < 2 && y < 0) ? ABS(y) - 1 : GET_RES(x,y))
# define CALC_SPACE_DEC(x, y, z, s) ((x > y + z) ? x - y - z : 0)
# define CALC_PREC_DEC(x, y, s) ((x > y) ? x - y : 0)
# define CALC_SPACE_CHAR(x, y) ((x > y) ? x - y : 0)
# define CALC_SPACE_HEX(x, y, z) ((x > y) ? x - y - z : 0)

void				init_printf(t_printf *sprint);
long				get_reverse_hex_dec(long d, int step);
char				*convert_to_hex(long long d, char c, int step);
char				*convert_to_hex_p(unsigned long long d2, int step);
int					is_command(char c, char x);
int					str_nblen(char *s);
int					push_str(char *s);
char				*flag_checker(char *s, t_printf *sprint);
char				*flag_primary(char *s, int j, t_printf *sprint);
char				*flag_secondary(char *s, t_printf *sprint);
int					flag_star(t_printf *sprint, int len);
void				flag_setter_char(t_printf *sprint);
void				flag_setter_dec(t_printf *sprint);
void				flag_setter_hex(t_printf *sprint);
void				flag_setter_sign(t_printf *sprint);
void				alloc_manager(t_printf *sprint, int	step);
void				print_flag(char flag, int len);
void				digits_printer(t_printf *sprint);
void				hex_printer(char c, t_printf *sprint);
void				chars_printer(char c, t_printf *sprint);
void				chars_init(char c, t_printf *sprint);
void				make_strchar(char x, char **str);
void				random_char(char c, t_printf *sprint);
void				hex_init(char c, t_printf *sprint);
void				dec_init(char c, t_printf *sprint);
char				*mand_manager(char *s, t_printf *sprint);
int					ft_printf(const char *str, ...);

#endif
