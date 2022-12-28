#include "minirt.h"

void	print_vector(t_vec vec, char *msg)
{
	printf("%s\n", msg);
	printf("x: %lf\n", vec.x);
	printf("y: %lf\n", vec.y);
	printf("z: %lf\n", vec.z);
}
