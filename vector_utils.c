#include "minirt.h"

void	print_vector(t_vec vec, char *msg)
{
	printf("%s\n", msg);
	printf("x: %lf\n", vec.x);
	printf("y: %lf\n", vec.y);
	printf("z: %lf\n", vec.z);
}

//t_vec	set_vec(char *xyz)
t_vec	set_vec(char *xyz, int *err_flag)
{
	char	**split_xyz;
	t_vec	vec;

	vec.x = 0;
	vec.y = 0;
	vec.z = 0;
	split_xyz = ft_split(xyz, ',');
	if (split_xyz == NULL)
	{
		*err_flag = MALLOC_ERROR;
		return (vec);
	}
	if (split_xyz[0])
		vec.x = atod(split_xyz[0]);
	if (split_xyz[1])
		vec.y = atod(split_xyz[1]);
	if (split_xyz[2])
		vec.z = atod(split_xyz[2]);
	free_strs(split_xyz);
	return (vec);
}

double	squred_norm(t_vec a)
{
	return (a.x * a.x + a.y * a.y + a.z * a.z);
}

double	norm(t_vec a)
{
	return (sqrt(squred_norm(a)));
}

t_vec	normalize(t_vec a)
{
	t_vec	vec;
	double	vnorm;

	vnorm = norm(a);
	vec.x = a.x / vnorm;
	vec.y = a.y / vnorm;
	vec.z = a.z / vnorm;
	return (vec);
}
