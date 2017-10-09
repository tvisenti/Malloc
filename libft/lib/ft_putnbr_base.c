/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvisenti <tvisenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 19:04:41 by tvisenti          #+#    #+#             */
/*   Updated: 2017/10/09 15:02:06 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char	digit(int nb)
{
	if (nb < 10)
		return ('0' + nb);
	return ('a' + nb % 10);
}

void	ft_putnbr_base(intmax_t nb, int base)
{
	if (nb > 9)
		ft_putnbr_base(nb / base, base);
	ft_putchar(digit(nb % base));
}
