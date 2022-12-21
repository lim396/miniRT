#include "minirt.h"

t_config	set_ambient(char **split_line)
{
	size_t	i;

	i = 1;
	while (split_line[i])
	{
//		if (i == 1)
			split_line[i];
//		if (i == 2)
//		{
//			split(split_line[i]);
//		}
		i++;
	}
	return (config);
}

t_config	set_light(char **split_line)
{
	size_t	i;
	
	i = 1;
	while ()
	return (config);
}

t_config	set_camera(char **split_line)
{
	i = 1;
	while ()
	return (config);
}

t_config	set_sphere(char **split_line)
{
	i = 1;
	while ()
	return (config);
}

t_config	set_plane(char **split_line)
{
	i = 1;
	while ()
	return (config);
}

t_config	set_cylinder(char **split_line)
{
	i = 1;
	while ()
	return (config);
}

bool	set_config(t_config *config, const char *line)
{
	char	**split_line;
	size_t	i;
	char	ident;

	i = 0;
	split_line = ft_split(line, ' ');
	if (split_line == NULL)
		return (false);
	if (split_line[0] != NULL)
	{
		if (*split_line[0] == 'A')
			config = set_ambient(split_line);
		else if (*split_line[0] == 'L')
			config = set_light(split_line);
		else if (*split_line[0] == 'C')
			config = set_camera(split_line);
		else if (*split_line[0] == 's' && *split_line[1] == 'p')
			config = set_sphere(split_line);
		else if (*split_line[0] == 'p' && *split_line[1] == 'l')
			config = set_plane(split_line);
		else if (*split_line[0] == 'c' && *split_line[1] == 'y')
			config = set_cylinder(split_line);
		else
			printf("ERROR\n");
	}
	return (true);
}

t_config	read_map(char *filename)
{
	char		*line;
	t_config	config;
	int			fd;

	fd = open(filename);
	while (true)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break;
		set_config(&config, line);
	}
	return (config);
}

void	init(char **argv)
{
	read_map(argv[1]);
}
