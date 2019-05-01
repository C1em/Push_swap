/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/10 16:47:00 by coremart          #+#    #+#             */
/*   Updated: 2019/04/26 22:42:13 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char *uc_dst;
	unsigned char *uc_src;

	uc_dst = (unsigned char*)dst;
	uc_src = (unsigned char*)src;
	if (uc_src == uc_dst)
		return (dst);
	if (uc_src < uc_dst && uc_src + len - uc_dst > 0)
	{
		uc_src += uc_src + len - uc_dst;
		uc_dst += uc_src + len - uc_dst;
	}
	else if (uc_src > uc_dst && uc_dst + len - uc_src > 0)
	{
		uc_dst += uc_dst + len - uc_src;
		uc_src += uc_dst + len - uc_src;
	}
	uc_dst = ft_memcpy(uc_dst, uc_src, len);
	return (dst);
}
