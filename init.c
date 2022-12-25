#include "minirt.h"

size_t	count_valid(char *str)
{
	int		i;
	bool	dot_flag;

	dot_flag = 0;
	i = 0;
	while (str[i] && ft_isdigit(str[i]))
	{
		i++;
		if (!dot_flag && str[i] == '.')
		{
			dot_flag = 1;
			i++;
		}
	}
	return (i - dot_flag);
}

double	atod(char *str)
{
	// overflow checkしろよ
	int	n1;
	int	n2;
	size_t	cnt;
//	size_t	len;
	double	ret;
	size_t		valid_len;
	
	valid_len = count_valid(str);
	cnt = 0;
	n1 = ft_atoi(str);
	while (*str && *str != '.')
	{
		cnt++;
		str++;
	}
	str++;
	n2 = ft_atoi(str);
	if (valid_len == cnt)
		ret = (double)n1;
	else
		ret = (double)n1 + ((double)n2 / pow(10,(valid_len - cnt)));
	return (ret);
}
/*
int	main () {

	printf("12.34 %lf\n", 12.34001234);
	printf("1234 %lf\n", atod("1234"));

	printf("12.34 %lf\n", atod("12.34"));
	printf("1.234 %lf\n", atod("1.234"));
	printf("0.1234 %lf\n", atod("0.1234"));
	printf("0.01234 %lf\n", atod("0.01234"));
	printf("1234.0 %lf\n", atod("1234.0"));
	printf("1.234.0 %lf\n", atod("1.234.0"));
}*/

t_vec	set_vec(char *xyz)
{
	char	**split_xyz;
	t_vec	vec;

	split_xyz = ft_split(xyz, ',');
	if (split_xyz[0])
		vec.x = atod(split_xyz[0]); //set color
	else
		printf("ERROR\n");
	if (split_xyz[1])
		vec.y = atod(split_xyz[1]);
	else
		printf("ERROR\n");
	if (split_xyz[2])
		vec.z = atod(split_xyz[2]);
	else
		printf("ERROR\n");
	return (vec);
}

t_color	set_color(char *rgb)
{
	char	**split_rgb;
	t_color	color;

	split_rgb = ft_split(rgb, ',');
	if (split_rgb[0])
		color.r = atod(split_rgb[0]) / 255.0; //set color
	else
		printf("ERROR\n");
	if (split_rgb[1])
		color.g = atod(split_rgb[1]) / 255.0;
	else
		printf("ERROR\n");
	if (split_rgb[2])
		color.b = atod(split_rgb[2]) / 255.0;
	else
		printf("ERROR\n");
	return (color);
}

void	set_ambient(char **split_line, t_config *config)
{
	size_t	i;

	i = 1;
	while (split_line[i])
	{
		if (i == 1)
		{
			config->ambient.ambient_ref.r = atod(split_line[i]);
			config->ambient.ambient_ref.g = atod(split_line[i]);
			config->ambient.ambient_ref.b = atod(split_line[i]);
		}
		else if (i == 2)
			config->ambient.ambient_illuminance = set_color(split_line[i]);
		else
			printf("ERROR\n");
		i++;
	}
//	printf("ambi ref\n");
//	printf("%lf\n", config->ambient.ambient_ref.r);
//	printf("%lf\n", config->ambient.ambient_ref.g);
//	printf("%lf\n", config->ambient.ambient_ref.b);
//	printf("\n");
//	printf("ambi illu\n");
//	printf("%lf\n", config->ambient.ambient_illuminance.r);
//	printf("%lf\n", config->ambient.ambient_illuminance.g);
//	printf("%lf\n", config->ambient.ambient_illuminance.b);
//	printf("\n");
}

void	set_light(char **split_line, t_config *config)
{
	size_t	i;
	
	i = 1;
	while (split_line[i])
	{
		if (i == 1)
			config->light.vec = set_vec(split_line[i]);
		else if (i == 2)
			config->light.brightness_ratio = atod(split_line[i]);
		else if (i == 3)
			config->light.illuminance = set_color(split_line[i]);
		else
			printf("ERROR\n");
		i++;
	}
//	printf("light ill\n");
//	printf("%lf\n", config->light.illuminance.r);
//	printf("%lf\n", config->light.illuminance.g);
//	printf("%lf\n", config->light.illuminance.b);
//	printf("\n");
}

void	set_camera(char **split_line, t_config *config)
{
	size_t	i;

	i = 1;
	while (split_line[i])
	{
		if (i == 1)
			config->camera.pos = set_vec(split_line[i]);
		else if (i == 2)
			config->camera.orientation = set_vec(split_line[i]);
		else if (i == 3)
			config->camera.fov = atoi(split_line[i]);
		else
			printf("ERROR\n");
		i++;
	}
}

t_shape	*list_last(t_shape *list)
{		
//	printf("list %d\n", list->type);
	if (list == NULL)
		return (NULL);
	while (list->next != NULL)
	{
//		printf("next %d\n", list->type);
//		printf("%d\n", list->type);
		list = list->next;
	}
	return (list);
}

void	add_list_last(t_shape **shape_list, t_shape *node)
{
	t_shape	*last;
	t_shape *head;

	if (shape_list == NULL)
		return ;
	if (*shape_list == NULL)
	{
//		printf("ko\n");
		*shape_list = node;
		return ;
	}
//	printf("ok\n");
	head = *shape_list;
	last = list_last(*shape_list);
	*shape_list = head;
	if (last == NULL)
		return ;
	last->next = node;
//	node->next = NULL;
}

void	set_sphere(char **split_line, t_shape **shape_list)
{
//	printf("ok\n");
	size_t	i;

	t_shape	*shape_node;

	shape_node = (t_shape *)malloc(sizeof(t_shape) * 1);
	shape_node->type = ST_SPHERE;
	shape_node->next = NULL;
	i = 1;
	while (split_line[i])
	{
		if (i == 1)
			shape_node->sphere.center = set_vec(split_line[i]);
		else if (i == 2)
			shape_node->sphere.radius = atod(split_line[i]) / 2.0;
		else if (i == 3)
			shape_node->material.diffuse_ref = set_color(split_line[i]);
		else
			printf("ERROR\n");
		i++;
	}
	add_list_last(shape_list, shape_node);

						//tmp index
//	shape_list->type = ST_SPHERE;
//	i = 1;
//	while (split_line[i])
//	{
//		if (i == 1)
//			shape_list->sphere.center = set_vec(split_line[i]);
//		else if (i == 2)
//			shape_list->sphere.radius = atod(split_line[i]) / 2.0;
//		else if (i == 3)
//			shape_list->material.diffuse_ref = set_color(split_line[i]);
//		else
//			printf("ERROR\n");
//		i++;
//	}
//	printf("sph diffu\n");
//	printf("%lf\n", shape_list->material.diffuse_ref.r);
//	printf("%lf\n", shape_list->material.diffuse_ref.g);
//	printf("%lf\n", shape_list->material.diffuse_ref.b);
//	printf("\n");
//	t_shape *last;
//
//	last = list_last(shape_list);
//	printf("in set_sph\n");
//	printf("%lf\n", last->sphere.center.x);
//	printf("%lf\n", last->sphere.center.y);
//	printf("%lf\n", last->sphere.center.z);
//	printf("%lf\n", config->shape_list[0].sphere.center.x);
//	printf("%lf\n", config->shape_list[0].sphere.center.y);
//	printf("%lf\n", config->shape_list[0].sphere.center.z);
}

//void	set_sphere(char **split_line, t_config *config)
//{
////	printf("ok\n");
//	size_t	i;
//
//						//tmp index
//	config->shape_list[0].type = ST_SPHERE;
//	i = 1;
//	while (split_line[i])
//	{
//		if (i == 1)
//			config->shape_list[0].sphere.center = set_vec(split_line[i]);
//		else if (i == 2)
//			config->shape_list[0].sphere.radius = atod(split_line[i]) / 2.0;
//		else if (i == 3)
//			config->shape_list[0].material.diffuse_ref = set_color(split_line[i]);
//		else
//			printf("ERROR\n");
//		i++;
//	}
////	printf("%lf\n", config->shape_list[0].sphere.center.x);
////	printf("%lf\n", config->shape_list[0].sphere.center.y);
////	printf("%lf\n", config->shape_list[0].sphere.center.z);
//}

void	set_cylinder(char **split_line, t_shape **shape_list)
{	
	size_t	i;
	t_shape	*shape_node;

	shape_node = (t_shape *)malloc(sizeof(t_shape) * 1);
	shape_node->type = ST_CYLINDER;
	shape_node->next = NULL;
	i = 1;
	while (split_line[i])
	{
		if (i == 1)
			shape_node->cylinder.pos = set_vec(split_line[i]);
		else if (i == 2)
			shape_node->cylinder.normal= set_vec(split_line[i]);
		else if (i == 3)
			shape_node->cylinder.radius= atod(split_line[i]) / 2.0;
		else if (i == 4)
			shape_node->cylinder.height = atod(split_line[i]);
		else if (i == 5)
			shape_node->material.diffuse_ref = set_color(split_line[i]);
		else
			printf("ERROR\n");
		i++;
	}
	add_list_last(shape_list, shape_node);
}

void	set_plane(char **split_line, t_shape **shape_list)
{	
	size_t	i;
	t_shape	*shape_node;

	shape_node = (t_shape *)malloc(sizeof(t_shape) * 1);

						//tmp index
	shape_node->type = ST_PLANE;
	shape_node->next = NULL;
	i = 1;
	while (split_line[i])
	{
		if (i == 1)
			shape_node->plane.pos = set_vec(split_line[i]);
		else if (i == 2)
			shape_node->plane.normal = set_vec(split_line[i]);
		else if (i == 3)
			shape_node->material.diffuse_ref = set_color(split_line[i]); //set_color
		else
			printf("ERROR\n");
		i++;
	}
	add_list_last(shape_list, shape_node);
}

//void	set_plane(char **split_line, t_config *config)
//{	
//	size_t	i;
//
//						//tmp index
//	config->shape_list[1].type = ST_PLANE;
//	i = 1;
//	while (split_line[i])
//	{
//		if (i == 1)
//			config->shape_list[1].plane.pos = set_vec(split_line[i]);
//		else if (i == 2)
//			config->shape_list[1].plane.normal = set_vec(split_line[i]);
//		else if (i == 3)
//			config->shape_list[1].material.diffuse_ref = set_color(split_line[i]); //set_color
//		else
//			printf("ERROR\n");
//		i++;
//	}
//}

//void	set_cylinder(char **split_line, t_config *config)
//{	
//	size_t	i;
//
//						//tmp index
//	config->shape_list[2].type = ST_CYLINDER;
//	i = 1;
//	while (split_line[i])
//	{
//		if (i == 1)
//			config->shape_list[2].cylinder.pos = set_vec(split_line[i]);
//		else if (i == 2)
//			config->shape_list[2].cylinder.orientation = set_vec(split_line[i]);
//		else if (i == 3)
//			config->shape_list[2].cylinder.diameter = atod(split_line[i]);
//		else if (i == 4)
//			config->shape_list[2].cylinder.height = atod(split_line[i]);
//		else if (i == 5)
//			config->shape_list[2].material.diffuse_ref = set_color(split_line[i]);
//		else
//			printf("ERROR\n");
//		i++;
//	}
//	return (config);
//}

bool	set_config(t_config *config, const char *line)
{
	char	**split_line;
//	size_t	i;
//	char	ident;
	
//	i = 0;
	split_line = ft_split(line, ' ');
	if (split_line == NULL)
		return (false);
	if (split_line[0] != NULL)
	{
//		printf("%c\n", *split_line[0]);
		if (split_line[0][0] == 'A')
			set_ambient(split_line, config);
		else if (split_line[0][0] == 'L')
			set_light(split_line, config);
		else if (split_line[0][0] == 'C')
			set_camera(split_line, config);
		else if (split_line[0][0] == 's' && split_line[0][1] == 'p')
		{
			set_sphere(split_line, &config->shape_list);
//			printf("%d\n", config->shape_list->type);
//			printf("%d\n", config->shape_list->next->type);
		}
//			set_sphere(split_line, config);
		else if (split_line[0][0] == 'p' && split_line[0][1] == 'l')
		{
			set_plane(split_line, &config->shape_list);
//			printf("%d\n", config->shape_list->type);
//			printf("%d\n", config->shape_list->next->type);
		}
		/*
		t_shape *last;

		last = list_last(config->shape_list);
		printf("set_config(sph)\n");
		printf("%lf\n", last->sphere.center.x);
		printf("%lf\n", last->sphere.center.y);
		printf("%lf\n", last->sphere.center.z);

		printf("set_config(pla)\n");
		printf("%lf\n", last->plane.center.x);
		printf("%lf\n", last->plane.center.y);
		printf("%lf\n", last->plane.center.z);
		*/
//			set_plane(split_line, config);
		else if (split_line[0][0] == 'c' && split_line[0][1] == 'y')
			set_cylinder(split_line, &config->shape_list);
//		else
//			printf("ERROR1\n");
	}
	return (true);
}

t_config	read_map(char *filename)
{
	char		*line;
	t_config	config;
	int			fd;

	fd = open(filename,0644);
	config.shape_list = (t_shape *)malloc(sizeof(t_shape));
	config.shape_list->next = NULL;
	config.shape_list->type = ST_NONE;
	while (true)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break;
		set_config(&config, line);
	}
	return (config);
}

t_config	init_config(char **argv)
{
	t_config	config;

	config = read_map(argv[1]);
//	printf("%lf\n", config.camera.pos.x);
//	printf("%lf\n", config.camera.pos.y);
//	printf("%lf\n", config.camera.pos.z);
//	printf("%d\n", config.shape_list[0].type);
//	printf("in init_config\n");
//	printf("%lf\n", config.&(shape_list[0])->sphere.center.x);
//	printf("%lf\n", config.&shape_list[0]->sphere.center.y);
//	printf("%lf\n", config.&shape_list[0]->sphere.center.z);
//	printf("\n");
//	printf("diffuse\n");
//	printf("%lf\n", config.shape_list[0].material.diffuse_ref.r);
//	printf("%lf\n", config.shape_list[0].material.diffuse_ref.g);
//	printf("%lf\n", config.shape_list[0].material.diffuse_ref.b);
//	printf("%lf\n", config.shape_list[1].sphere.center.x);
//	printf("%lf\n", config.shape_list[1].sphere.center.y);
//	printf("%lf\n", config.shape_list[1].sphere.center.z);
//	printf("%lf\n", config.&shape_list[1]->plane.pos.x);
//	printf("%lf\n", config.&shape_list[1]->plane.pos.y);
//	printf("%lf\n", config.&shape_list[1]->plane.pos.z);
	return (config);
}
