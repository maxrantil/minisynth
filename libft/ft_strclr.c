/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strclr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 12:03:56 by dmalesev          #+#    #+#             */
/*   Updated: 2021/11/23 12:08:56 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strclr(char *s)
{
	size_t	len;

	len = 0;
	if (s)
	{
		while (s[len])
			len++;
		ft_bzero(s, len);
	}
}
