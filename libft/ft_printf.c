/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiaparec <fiaparec@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 08:01:56 by fiaparec          #+#    #+#             */
/*   Updated: 2022/04/02 12:18:54 by fiaparec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	return_size(t_print *tab, int size)
{
	if (tab->size < 0)
		return (-1);
	return (size + tab->size);
}

static int	conversion_handler(t_print *tab, const char *format, int pos)
{
	if (tab->wdth < 0 || tab->prec < -1)
		return (-1);
	if (*(format + pos) == 'c')
		printf_c(tab, (char)va_arg(tab->args, int));
	else if (*(format + pos) == 's')
		printf_s(tab, va_arg(tab->args, char *));
	else if (*(format + pos) == 'p')
		printf_p(tab, va_arg(tab->args, unsigned long int));
	else if (*(format + pos) == 'd')
		printf_d(tab, va_arg(tab->args, int));
	else if (*(format + pos) == 'i')
		printf_i(tab, va_arg(tab->args, int));
	else if (*(format + pos) == 'u')
		printf_u(tab, va_arg(tab->args, unsigned int));
	else if (*(format + pos) == 'x')
		printf_x(tab, va_arg(tab->args, unsigned int));
	else if (*(format + pos) == 'X')
		printf_uppx(tab, va_arg(tab->args, unsigned int));
	else if (*(format + pos) == '%')
		printf_percent(tab);
	return (tab->size);
}

static int	format_evaluation(t_print *tab, const char *format, int pos)
{
	if (!ft_strchr("-0+ #123456789.cspdiuxX\%", *(format + pos)))
	{
		tab->size = -1;
		return (-1);
	}
	while (!ft_strchr("cspdiuxX\%", *(format + pos)))
	{
		if (ft_strchr("-0+ #", *(format + pos)))
			pos = pf_flags_identifier(tab, pos, *(format + pos));
		if (ft_strchr("123456789", *(format + pos)))
			pos = pf_wdth_prec_identifier(tab, format,
					pos, *(format + pos));
		if (*(format + pos) == '.')
			pos = pf_wdth_prec_identifier(tab, format,
					pos + 1, *(format + pos));
	}
	if (conversion_handler(tab, format, pos++) < 0)
	{
		tab->size = -1;
		return (-1);
	}
	return (pos);
}

int	ft_printf(const char *format, ...)
{
	int		pos;
	int		size;
	t_print	*tab;

	tab = NULL;
	tab = pf_init_reset_tab(tab, TAB_INIT);
	va_start(tab->args, format);
	pos = 0;
	size = 0;
	while (*(format + pos))
	{
		pf_init_reset_tab(tab, TAB_RESET);
		if (*(format + pos) == '%')
			pos = format_evaluation(tab, format, pos + 1);
		else
		{
			ft_putchar_fd(*(format + pos++), 1);
			size++;
		}
	}
	va_end(tab->args);
	size = return_size(tab, size);
	free(tab);
	return (size);
}
