/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurd <mhurd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/23 17:27:59 by mhurd             #+#    #+#             */
/*   Updated: 2016/12/02 18:19:59 by mhurd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include "libft.h"
# include <stdarg.h>
# include <stdlib.h>
# include <limits.h>
# include <stdint.h>

# define SIZET_MAX (~(size_t)0)

typedef unsigned int	t_u32;

enum
{
	none,
	hh,
	h,
	l,
	ll,
	L,
	q,
	j,
	z,
	t,
	p
}					length;

typedef struct		s_arg
{
	int				alternative : 1;
	int				left_justify : 1;
	int				force : 1;
	int				blank : 1;
	int				pad_zeroes : 1;
	int				grouping : 1;
	int				got_width : 1;
	int				got_precis : 1;
	int				asterisk : 1;
	unsigned int	width;
	unsigned int	precision;
	char			length;
}					t_arg;

typedef struct		s_output
{
	char	*str;
	int		len;
}					t_output;

typedef struct		s_conv
{
	char	*conv;
	void	(*ft)(char, t_output *, t_arg *, va_list *);
}					t_conv;

void				ft_conv_unimp(char in, t_output *out, t_arg *flags,
						va_list *ap);
void				ft_conv_s(char in, t_output *out, t_arg *flags,
						va_list *ap);
void				ft_conv_nums(char in, t_output *out, t_arg *flags,
						va_list *ap);
t_arg				*find_flags(char *in, int len, va_list *ap);
int					ft_printf(char *in, ...);
int					ft_asprintf(char **out, char *in, ...);
int					ft_dprintf(int fd, char *in, ...);

void				handle_padding(char **str, t_arg *flags, char type);
void				handle_precision(char **str, t_arg *flags, char type);
void				ft_conv_c(char in, t_output *out, t_arg *flag, va_list *ap);
char				*ft_num_to_base(uintmax_t value, t_u32 base, char unsign,
						char type);
void				ft_conv_percent(char in, t_output *out, t_arg *flags,
						va_list *ap);
size_t				wcharp_len(wchar_t *in);
int					wchar_len(wchar_t chr);
void				ft_conv_n(char in, t_output *out, t_arg *flag, va_list *ap);
void				wchar_to_str(wchar_t in, char *str);
int					find_base(char in);
int					find_sign(char in);

#endif
