/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochenna <mochenna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 17:08:54 by ybouyzem          #+#    #+#             */
/*   Updated: 2025/03/23 22:21:24 by mochenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub.h"

void	*free_all(void **ptr_list, int *i)
{
	int	j;

	j = 0;
	if (!ptr_list || (*i) == 0)
		return (NULL);
	while (ptr_list[j])
	{
		free(ptr_list[j]);
		ptr_list[j] = NULL;
		j++;
	}
	*i = 0;
	return (NULL);
}

void	*ft_malloc(size_t size, int mode)
{
	static void	*ptr_list[100000000];
	static int	i;
	void		*ptr;

	if (!mode)
		return (free_all(ptr_list, &i));
	ptr = malloc(size);
	if (!ptr)
	{
		free_all(ptr_list, &i);
		ft_putstr_fd("Error\nMalloc failed\n", 1);
		exit(1);
	}
	ptr_list[i++] = ptr;
	return (ptr);
}
