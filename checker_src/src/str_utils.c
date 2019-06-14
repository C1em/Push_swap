/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 03:30:30 by coremart          #+#    #+#             */
/*   Updated: 2019/06/15 03:35:52 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "checker.h"
#include <unistd.h>

void				write_str(t_str *str)
{
	write(1, str->str, str->index);
	str->index = 0;
}

void				add_string_to_str(t_str *str, char *string)
{
	while (*string)
	{
		str->str[str->index] = *string;
		++string;
		if (++str->index == 2048)
			write_str(str);
	}
}

void				add_nb_to_str(char *nb, t_str *str, int eol)
{
	int i;

	i = ft_strlen(nb);
	add_string_to_str(str, nb);
	if (eol)
		add_string_to_str(str, "\n");
	else
	{
		while (i < 12)
		{
			add_string_to_str(str, " ");
			++i;
		}
	}
	nb[0] = '\0';
}

static inline int	log2(int nb)
{
	int res;

	res = 0;
	while (nb > 1)
	{
		nb >>= 1;
		++res;
	}
	return (res);
}

void				add_header(t_str *str, int op)
{
	int index;

	add_string_to_str(str, "\n");
	if (!op)
		return (add_string_to_str(str, "Pile a:     Pile b:\n"));
	index = (log2(op) << 1) + (op >= 512) + (op == 1024);
	str->str[str->index] = "sasbsspapbrarbrrrrarrbrrr"[index];
	if (++str->index == 2048)
		write_str(str);
	str->str[str->index] = "sasbsspapbrarbrrrrarrbrrr"[index + 1];
	if (++str->index == 2048)
		write_str(str);
	if (op >= 256)
	{
		str->str[str->index] = "sasbsspapbrarbrrrrarrbrrr"[index + 2];
		if (++str->index == 2048)
			write_str(str);
	}
	add_string_to_str(str, "\nPile a:     Pile b:\n");
}
