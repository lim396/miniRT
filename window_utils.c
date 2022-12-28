#include "minirt.h"

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
	mlx_clear_window(status->mlx, status->mlx_win);
	//draw(status);
	return (0);
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
