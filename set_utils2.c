/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shongou <shongou@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 23:34:40 by shongou           #+#    #+#             */
/*   Updated: 2023/01/04 23:34:42 by shongou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	set_fov(char *str, int *err_flag)
{
	double	fov;

	if (!valid_digit(str))
	{
		*err_flag |= INVALID_FOV;
		return (0);
	}
	fov = atod(str);
	if (fov < 0.0 || 180.0 < fov)
		*err_flag |= INVALID_FOV;
	return (fov);
}

double	set_ratio(char *str, int *err_flag)
{
	double	ratio;

	if (!valid_float(str))
	{
		*err_flag |= INVALID_RATIO;
		return (0);
	}
	ratio = atod(str);
	if (ratio < 0.0 || 1.0 < ratio)
		*err_flag |= INVALID_RATIO;
	return (ratio);
}

double	set_size(char *str, int *err_flag)
{
	double	size;

	if (!valid_float(str))
	{
		*err_flag |= INVALID_SIZE;
		return (0);
	}
	size = atod(str);
	if (size <= 0.0)
		*err_flag |= INVALID_SIZE;
	return (size);
}
