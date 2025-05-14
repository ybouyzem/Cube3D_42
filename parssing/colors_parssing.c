/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_parssing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouyzem <ybouyzem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 01:32:13 by ybouyzem          #+#    #+#             */
/*   Updated: 2025/03/23 21:49:26 by ybouyzem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

int	count_char(char *str, char c)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (str[i])
	{
		if (str[i] == c)
			n++;
		i++;
	}
	return (n);
}

int	check_colors(t_data *data, char **line, int *check)
{
	char	**rgb;

	line[1] = ft_strtrim(line[1], "\n");
	rgb = ft_split(line[1], ',');
	if (ft_strslen(rgb) != 3 || count_char(line[1], ',') != 2)
		return (-1);
	if (is_number(rgb[0]) == 0
		|| is_number(rgb[1]) == 0 || is_number(rgb[2]) == 0)
		return (-1);
	if (is_number(rgb[0]) && (ft_atoi(rgb[0]) < 0 || ft_atoi(rgb[0]) > 255))
		return (-1);
	if (is_number(rgb[1]) && (ft_atoi(rgb[1]) < 0 || ft_atoi(rgb[1]) > 255))
		return (-1);
	if (is_number(rgb[2]) && (ft_atoi(rgb[2]) < 0 || ft_atoi(rgb[2]) > 255))
		return (-1);
	if (ft_strcmp(line[0], "C") == 0)
		check[4]++;
	else if (ft_strcmp(line[0], "F") == 0)
		check[5]++;
	data->colors = join_double_with_str(data->colors, line[0]);
	data->colors = join_double_with_str(data->colors, line[1]);
	return (0);
}

int	check_directions_colors(char **file, t_data *data)
{
	int		i;
	int		check[6];

	i = 0;
	while (i < 6)
		(1) && (check[i] = 0, i++);
	i = 0;
	while (file[i])
	{
		if (ft_checker(file, data, i, check) < 0)
			return (-1);
		if (ft_check_num(check) == 0)
			return (i);
		i++;
	}
	if (ft_check_num(check) == 0)
		return (i);
	return (-1);
}
