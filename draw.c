#include "minirt.h"

void	ft_mlx_put_pixel(t_image img, int x, int y, int rgb)
{
	char	*dst;

	dst = img.addr + (y * img.size_line + x * (img.bpp / 8));
	*(unsigned int *)dst = rgb;
}

void	draw(t_color color, int x, int y, t_image img)
{
//	unsigned char	r;
//	unsigned char	g;
//	unsigned char	b;
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
//	printf("%d %d %d\n", r, g, b);
}
