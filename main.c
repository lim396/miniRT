#include "minirt.h"

int	main(int argc, char **argv)
{
	t_config	config;
	t_status	*status;

	if (argc != 2)
		return (1);
	config = init_config(argv);
	status = mlx_run(config);
	ray_trace(config, status);
	return (0);
}
