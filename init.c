#include "minirt.h"

bool	set_config(t_config *config, const char *line)
{
	char	**split_line;
	size_t	i;
	char	ident;

	i = 0;
	split_line = ft_split(line, ' ');
	if (split_line == NULL)
		return (false);
	while (split_line[i] != NULL)
	{
		
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
