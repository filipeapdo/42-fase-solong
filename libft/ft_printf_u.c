/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_u.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiaparec <fiaparec@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 15:44:57 by fiaparec          #+#    #+#             */
/*   Updated: 2022/04/02 11:47:26 by fiaparec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	pf_u_default_handler(t_print *tab)
{
	tab->hash = 0;
	tab->sign = 0;
	tab->spce = 0;
	if (tab->prec == -1)
		tab->prec = 1;
}

int	printf_u(t_print *tab, unsigned int n)
{
	char	*str;

	if (n == 0 && tab->prec == 0)
		str = ft_strdup("");
	else
	{
		str = pf_itoa_base_ul(n, 10, 'u');
		pf_u_default_handler(tab);
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
