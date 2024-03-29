/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shongou <shongou@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 23:34:47 by shongou           #+#    #+#             */
/*   Updated: 2023/01/04 23:34:48 by shongou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	valid_float(char *str)
{
	bool	dot_flag;
	size_t	i;

	if (!str)
		return (false);
	dot_flag = false;
	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] && ft_isdigit(str[i]))
	{
		i++;
		if (!dot_flag && str[i] == '.')
		{
			i++;
			dot_flag = true;
		}
	}
	if (str[i] == '\0')
		return (true);
	return (false);
}

bool	valid_vector(char *str)
{
	size_t	i;
	char	**split_str;

	split_str = ft_split(str, ',');
	if (!split_str || !(*split_str))
		return (false);
	i = 0;
	while (split_str[i])
	{
		if (!valid_float(split_str[i]))
		{
			free_strs(split_str);
			return (false);
		}
		i++;
	}
	free_strs(split_str);
	if (i == 3)
		return (true);
	return (false);
}

bool	valid_digit(char *str)
{
	size_t	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] && ft_isdigit(str[i]))
	{
		i++;
	}
	if (str[i] == '\0')
		return (true);
	return (false);
}

bool	valid_color(char *str)
{
	size_t	i;
	char	**split_str;

	split_str = ft_split(str, ',');
	if (!split_str || !(*split_str))
		return (false);
	i = 0;
	while (split_str[i])
	{
		if (!valid_float(split_str[i]))
		{
			free_strs(split_str);
			return (false);
		}
		i++;
	}
	free_strs(split_str);
	if (i == 3)
		return (true);
	return (false);
}
