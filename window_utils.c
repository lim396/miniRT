#include "minirt.h"

int	rendering(t_status *status)
{
	mlx_put_image_to_window(status->mlx, status->mlx_win, \
			status->img.img_ptr, 0, 0);
	return (0);
}

int	delete_window(t_status *status)
{
	mlx_destroy_window(status->mlx, status->mlx_win);
	status->mlx_win = NULL;
	exit(0);
}

int	key_hook(int key, t_status *status)
{
	if (key == 65307)
		delete_window(status);
//	mlx_clear_window(status->mlx, status->mlx_win);
	mlx_put_image_to_window(status->mlx, status->mlx_win, \
			status->img.img_ptr, 0, 0);
	//draw(status);
	return (0);
}

void	init_image(t_status *status)
{
	status->img.img_ptr = mlx_new_image(status->mlx, WIDTH, HEIGHT);
	status->img.addr = \
		mlx_get_data_addr(status->img.img_ptr, \
				&status->img.bpp, &status->img.size_line, &status->img.endian);
}

t_status	*mlx_run()
{
	t_status	*status;

	status = (t_status *)malloc(sizeof(t_status) * 1);
	if (status == NULL)
		printf("ERROR\n");
	status->mlx = mlx_init();
	if (status->mlx == NULL)
		printf("ERROR\n");
	status->mlx_win = mlx_new_window(status->mlx, WIDTH, HEIGHT, "miniRT");
	if (status->mlx_win == NULL)
		printf("ERROR\n");
	return (status);
}
