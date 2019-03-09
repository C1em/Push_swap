/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdiff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/11 11:41:26 by coremart          #+#    #+#             */
/*   Updated: 2018/11/11 11:47:28 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_strdiff(const char *s1, const char *s2)
{
	int i;

	i = 0;
	while (s1[i] == s2[i] && s1[i])
		i++;
	return ((int)s1[i]);
}
