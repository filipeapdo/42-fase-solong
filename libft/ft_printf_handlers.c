/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_handlers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiaparec <fiaparec@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 06:18:32 by fiaparec          #+#    #+#             */
/*   Updated: 2022/04/02 11:50:39 by fiaparec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*pf_dash_or_zero_handler(t_print *tab, char *s, char *fill)
{
	char	*str_dash_zero;

	str_dash_zero = ft_strdup(s);
	if ((tab->sign || tab->spce) && tab->wdth >= 1)
		tab->wdth -= 1;
	if (tab->hash && tab->wdth >= 2)
		tab->wdth -= 2;
	if (tab->dash)
		while (ft_strlen(str_dash_zero) < (size_t)tab->wdth)
			str_dash_zero = pf_joinswap(str_dash_zero, " ", RIGHT);
	else if (tab->zero)
		while (ft_strlen(str_dash_zero) < (size_t)tab->wdth)
			str_dash_zero = pf_joinswap(fill, str_dash_zero, LEFT);
	free(s);
	return (str_dash_zero);
}

char	*pf_sign_or_spce_handler(t_print *tab, char *s)
{
	char	*str_sign_spce;

	str_sign_spce = ft_strdup(s);
	if (tab->sign == (int) '-')
		str_sign_spce = pf_joinswap("-", str_sign_spce, LEFT);
	else if (tab->sign == (int) '+')
		str_sign_spce = pf_joinswap("+", str_sign_spce, LEFT);
	else if (tab->spce)
		str_sign_spce = pf_joinswap(" ", str_sign_spce, LEFT);
	free(s);
	return (str_sign_spce);
}

char	*pf_hash_handler(char *s, char x)
{
	char	*str_hash;

	str_hash = ft_strdup(s);
	if (x == 'x')
		str_hash = pf_joinswap("0x", str_hash, LEFT);
	else if (x == 'X')
		str_hash = pf_joinswap("0X", str_hash, LEFT);
	free(s);
	return (str_hash);
}

char	*pf_prec_handler(t_print *tab, char *s)
{
	char	*str_prec;

	str_prec = ft_strdup(s);
	if (tab->sign == (int) '-')
		str_prec = pf_substrswap(str_prec, 1, ft_strlen(str_prec));
	while (ft_strlen(str_prec) < (size_t)tab->prec)
		str_prec = pf_joinswap("0", str_prec, LEFT);
	free(s);
	return (str_prec);
}

char	*pf_wdth_handler(t_print *tab, char *s)
{
	char	*str_wdth;

	str_wdth = ft_strdup(s);
	while (ft_strlen(str_wdth) < (size_t)tab->wdth)
		str_wdth = pf_joinswap(" ", str_wdth, LEFT);
	free(s);
	return (str_wdth);
}
