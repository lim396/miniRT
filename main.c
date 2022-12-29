#include "minirt.h"



int	main(int argc, char **argv)
{
	t_config	config;
//	t_status	*status;

	if (argc != 2)
		return (1);
	//tmp
	printf("P3\n");
	printf("%d %d\n", WIDTH, HEIGHT);
	printf("255\n");
	//////
	config = init_config(argv);
//	status = mlx_run();
	ray_trace(config);
//	destroy();
	return (0);
}
