/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouyzem <ybouyzem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 00:54:36 by ybouyzem          #+#    #+#             */
/*   Updated: 2025/03/21 00:54:38 by ybouyzem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*array;
	size_t			i;

	i = 0;
	array = (unsigned char *)ft_malloc(count * size, 1);
	if (array == NULL)
		return (NULL);
	ft_bzero(array, count * size);
	return ((void *)(array));
}
