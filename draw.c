/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shongou <shongou@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 23:33:16 by shongou           #+#    #+#             */
/*   Updated: 2023/01/04 23:33:18 by shongou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_mlx_put_pixel(t_image img, int x, int y, int rgb)
{
	char	*dst;

	dst = img.addr + (y * img.size_line + x * (img.bpp / 8));
	*(unsigned int *)dst = rgb;
}

void	draw(t_color color, int x, int y, t_image img)
{
	int	r;
	int	g;
	int	b;
	int	rgb;

	rgb = 0;
	r = 255 * rounding_num(color.r, 0, 1);
	g = 255 * rounding_num(color.g, 0, 1);
	b = 255 * rounding_num(color.b, 0, 1);
	rgb = (r << 16 | g << 8 | b);
	ft_mlx_put_pixel(img, x, y, rgb);
}
