/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_i.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiaparec <fiaparec@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 15:22:27 by fiaparec          #+#    #+#             */
/*   Updated: 2022/04/02 11:41:21 by fiaparec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	pf_i_default_handler(t_print *tab, char *str)
{
	tab->hash = 0;
	if (*str == '-')
		tab->sign = (int) '-';
	else if (tab->sign == 1)
		tab->sign = (int) '+';
	if (tab->prec == -1)
		tab->prec = 1;
}

int	printf_i(t_print *tab, int n)
{
	char	*str;

	if (n == 0 && tab->prec == 0)
		str = ft_strdup("");
	else
	{
		str = ft_itoa(n);
		pf_i_default_handler(tab, str);
	}
	str = pf_prec_handler(tab, str);
	if (tab->dash || (tab->zero && tab->prec == 1))
		str = pf_dash_or_zero_handler(tab, str, "0");
	if (tab->sign || tab->spce)
		str = pf_sign_or_spce_handler(tab, str);
	str = pf_wdth_handler(tab, str);
	ft_putstr_fd(str, 1);
	tab->size += ft_strlen(str);
	free(str);
	return (tab->size);
}
