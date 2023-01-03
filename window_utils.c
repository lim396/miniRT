#include "minirt.h"

#define NO_ERROR 0
#define MLX_INIT_ERR 1
#define NEW_WINDOW_ERR 2
#define NEW_IMAGE_ERR 4

int	rendering(t_status *status)
{
	mlx_put_image_to_window(status->mlx, status->mlx_win, \
			status->img.img_ptr, 0, 0);
	return (0);
}

int	delete_window(t_status *status)
{
	mlx_destroy_image(status->mlx, status->img.img_ptr);
	mlx_destroy_window(status->mlx, status->mlx_win);
	mlx_destroy_display(status->mlx);
	status->img.img_ptr = NULL;
	status->mlx_win = NULL;
	status->mlx = NULL;
	exit(0);
}

void	free_list(t_config config)
{
	while (config.shape_list)
	{
		free(config.shape_list);
		config.shape_list = config.shape_list->next;
	}
}

int	key_hook(int key, t_status *status)
{
	if (key == 65307)
	{
		free_list(status->config);
		delete_window(status);
	}
//	mlx_clear_window(status->mlx, status->mlx_win);
	mlx_put_image_to_window(status->mlx, status->mlx_win, \
			status->img.img_ptr, 0, 0);
	return (0);
}

//void	init_image(t_status *status)
//{
//	status->img.img_ptr = mlx_new_image(status->mlx, WIDTH, HEIGHT);
//	if (status->img.img_ptr == NULL)
//		mlx_error(status, config, NEW_IMAGE_ERR);
//	status->img.addr = \
//		mlx_get_data_addr(status->img.img_ptr, \
//				&status->img.bpp, &status->img.size_line, &status->img.endian);
//}

void	print_mlx_error(int flag)
{
	if (flag & MLX_INIT_ERR)
		printf("mlx_init_error\n");
	if (flag & NEW_WINDOW_ERR)
		printf("mlx_new_window_error\n");
	if (flag & NEW_IMAGE_ERR)
		printf("mlx_new_image_error\n");
}

void	mlx_error(t_status *status, t_config config, int flag)
{
	free_list(config);
	if (status == NULL)
		before_set_config_err_handler(flag);
	print_mlx_error(flag);
	if (status->img.img_ptr)
		mlx_destroy_image(status->mlx, status->img.img_ptr);
	if (status->mlx_win)
		mlx_destroy_window(status->mlx, status->mlx_win);
	if (status->mlx)
		mlx_destroy_display(status->mlx);
	exit(1);
}

t_status	*mlx_run(t_config config)
{
	t_status	*status;

	status = (t_status *)malloc(sizeof(t_status) * 1);
	if (status == NULL)
		mlx_error(status, config, MALLOC_ERROR);
//		printf("ERROR\n");
	status->mlx = mlx_init();
	if (status->mlx == NULL)
		mlx_error(status, config, MLX_INIT_ERR);
//		printf("ERROR\n");
	status->mlx_win = mlx_new_window(status->mlx, WIDTH, HEIGHT, "miniRT");
	if (status->mlx_win == NULL)
		mlx_error(status, config, NEW_WINDOW_ERR);
	status->img.img_ptr = mlx_new_image(status->mlx, WIDTH, HEIGHT);
	if (status->img.img_ptr == NULL)
		mlx_error(status, config, NEW_IMAGE_ERR);
	status->img.addr = \
		mlx_get_data_addr(status->img.img_ptr, \
				&status->img.bpp, &status->img.size_line, &status->img.endian);
//		printf("ERROR\n");
	return (status);
}
