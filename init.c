#include "minirt.h"

/*
int	main () {

	printf("12.34 %lf\n", 12.34001234);
	printf("1234 %lf\n", atod("1234"));

	printf("12.34 %lf\n", atod("12.34"));
	printf("0.3 %lf\n", atod("0.3"));
	printf("-0.3 %lf\n", atod("-0.3"));
	printf("0.5 %lf\n", atod("0.5"));
	printf("-0.5 %lf\n", atod("-0.5"));
	printf("0.12 %lf\n", atod("0.12"));
	printf("-0.12 %lf\n", atod("-0.12"));
	printf("12.3 %lf\n", atod("12.3"));
	printf("-12.3 %lf\n", atod("-12.3"));
	printf("1.234 %lf\n", atod("1.234"));
	printf("0.1234 %lf\n", atod("0.1234"));
	printf("0.01234 %lf\n", atod("0.01234"));
	printf("1234.0 %lf\n", atod("1234.0"));
	printf("1.234.0 %lf\n", atod("1.234.0"));
}
*/

//bool	set_config(t_config *config, const char *line)
int	set_config(t_config *config, const char *line)
{
	char	**split_line;
	int		err_flag;

	err_flag = 0;
	split_line = ft_split(line, ' ');
	if (split_line == NULL || split_line[0] == NULL)
		return (false);
//	if (split_line[0] != NULL)
//	{
		if (split_line[0][0] == 'A')
			set_ambient(split_line, config, &err_flag);
		else if (split_line[0][0] == 'L')
			set_light(split_line, config, &err_flag);
		else if (split_line[0][0] == 'C')
			set_camera(split_line, config, &err_flag);
		else if (split_line[0][0] == 's' && split_line[0][1] == 'p')
			set_sphere(split_line, config, &err_flag);//&config->shape_list);
		else if (split_line[0][0] == 'p' && split_line[0][1] == 'l')
			set_plane(split_line, config, &err_flag);//&config->shape_list);
		else if (split_line[0][0] == 'c' && split_line[0][1] == 'y')
			set_cylinder(split_line, config, &err_flag);//&config->shape_list);
//		else
//			printf("ERROR1\n");
//	}
	free_split(split_line);
	return (err_flag);
//	return (true);
}

t_config	read_map(char *filename)
{
	char		*line;
	t_config	config;
	int			fd;

	fd = open(filename, 0644);
	config.shape_list = (t_shape *)malloc(sizeof(t_shape));
	config.shape_list->next = NULL;
	config.shape_list->type = ST_NONE;
	while (true)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		set_config(&config, line);
	}
	return (config);
}

t_config	init_config(char **argv)
{
	t_config	config;

	config = read_map(argv[1]);
	return (config);
}
