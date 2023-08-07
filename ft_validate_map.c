/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_validate_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louisnop <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 22:48:35 by louisnop          #+#    #+#             */
/*   Updated: 2020/01/30 07:19:14 by louisnop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

int		ft_validate_1(char **map, t_info *info)
{
	if (!(map[0] && map[1]))
		return (FAIL);
	if (!(map[1][0] == info->empty ||
			map[1][0] == info->obstacle ||
			map[1][0] == info->full))
		return (FAIL);
	return (SUCCESS);
}

int		ft_validate_2(char **map, t_info *info)
{
	int i;
	int j;

	i = 0;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (!(map[i][j] == info->empty || map[i][j] == info->obstacle))
				return (FAIL);
		}
	}
	return (SUCCESS);
}

int		ft_validate_3(char **map, t_info *info)
{
	int i;
	int len;

	i = 1;
	len = ft_strlen(map[i]);
	while (map[i])
	{
		if (len != ft_strlen(map[i]))
			return (FAIL);
		i++;
	}
	if (i - 1 != info->num_rows)
		return (FAIL);
	return (SUCCESS);
}

int		ft_validate_4(char *content)
{
	int		i;

	i = 0;
	while (content[i] != '\0')
		i++;
	if (content[i - 1] != '\n')
		return (FAIL);
	return (SUCCESS);
}

int		ft_validate(char **map, t_info *info)
{
	if (ft_validate_1(map, info) == FAIL)
		return (FAIL);
	if (ft_validate_2(map, info) == FAIL)
		return (FAIL);
	if (ft_validate_3(map, info) == FAIL)
		return (FAIL);
	return (SUCCESS);
}
