/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shongou <shongou@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 23:33:10 by shongou           #+#    #+#             */
/*   Updated: 2023/01/04 23:33:12 by shongou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	add_color(t_color n, t_color m)
{
	t_color	color;

	color.r = n.r + m.r;
	color.g = n.g + m.g;
	color.b = n.b + m.b;
	return (color);
}

//t_color	set_color(char *rgb)
t_color	set_color(char *rgb, int *err_flag)
{
	char	**split_rgb;
	t_color	color;

	color.r = 0;
	color.g = 0;
	color.b = 0;
	split_rgb = ft_split(rgb, ',');
	if (split_rgb == NULL)
	{
		*err_flag = MALLOC_ERROR;
		return (color);
	}
	if (split_rgb[0])
		color.r = atod(split_rgb[0]) / 255.0;
	if (split_rgb[1])
		color.g = atod(split_rgb[1]) / 255.0;
	if (split_rgb[2])
		color.b = atod(split_rgb[2]) / 255.0;
	free_strs(split_rgb);
	return (color);
}
