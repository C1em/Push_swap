/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_array.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 01:31:18 by coremart          #+#    #+#             */
/*   Updated: 2019/03/09 02:42:46 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static void	ft_swap(int *restrict const a, int *restrict const b)
{
	int tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

static int	partition(int arr[], int low, int high)
{
	int	swapable;

	swapable = low;
	while (low < high)
	{
		if (arr[low] < arr[high])
			ft_swap(&arr[low], &arr[swapable++]);
		low++;
	}
	ft_swap(&arr[low], &arr[swapable]);
	return (swapable);
}

void		ft_quicksort(int arr[], int low, int high)
{
	int	pivot_index;

	if (low >= high)
		return ;
	pivot_index = partition(arr, low, high);
	ft_quicksort(arr, low, pivot_index - 1);
	ft_quicksort(arr, pivot_index + 1, high);
}
