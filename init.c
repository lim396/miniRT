#include "minirt.h"

void	free_strs(char **strs)
{
	size_t	i;

	i = 0;
	while (strs[i] != NULL)
		free(strs[i++]);
	free(strs);
}

//bool	set_config(t_config *config, const char *line)
int	set_config(t_config *config, const char *line)
{
	char	**split_line;
	int		err_flag;

	err_flag = 0;
	split_line = ft_split(line, ' ');
	if (split_line == NULL || split_line[0] == NULL)

		return (NULL_STR);

	if (split_line[0][0] == 'A')
		set_ambient(split_line, config, &err_flag);
	else if (split_line[0][0] == 'L')
		set_light(split_line, config, &err_flag);
	else if (split_line[0][0] == 'C')
		set_camera(split_line, config, &err_flag);
	else if (split_line[0][0] == 's' && split_line[0][1] == 'p')
		set_sphere(split_line, config, &err_flag);
	else if (split_line[0][0] == 'p' && split_line[0][1] == 'l')
		set_plane(split_line, config, &err_flag);
	else if (split_line[0][0] == 'c' && split_line[0][1] == 'y')
		set_cylinder(split_line, config, &err_flag);
	else
		err_flag |= IDENTIFIER_ERROR;
	free_strs(split_line);
//	}
//	free_split(split_line);
	//printf("err_flag %d\n", err_flag);
	return (err_flag);
}

char	*remove_nl(char *str)
{
	char	*s;
	size_t	len;

	if (str == NULL)
		return (NULL);
	len = ft_strlen(str);
	if (str[len - 1] == '\n')
		len -= 1;
	s = (char *)malloc(sizeof(char) * (len + 1));
	if (s == NULL)
	{
		free(str);
		return (NULL);
	}
	ft_strlcpy(s, str, len + 1);
	free(str);
	return (s);
}

void	display_error(int error_flag)
{
	if (error_flag & MALLOC_ERROR)
		printf("malloc error\n");
	if (error_flag & IDENTIFIER_ERROR)
		printf("identifier error\n");
	if (error_flag & NUMBER_OF_ELEMENT_ERROR)
		printf("number of elements is incorrect\n");
	if (error_flag & NULL_STR)
		printf("str is null\n");
	if (error_flag & INVALID_COLOR)
		printf("color is incorrect\n");
	if (error_flag & INVALID_VECTOR)
		printf("vector is incorrect\n");
	if (error_flag & INVALID_ORIENTATION)
		printf("orientation is incorrect\n");
	if (error_flag & INVALID_FOV)
		printf("fov is incorrect\n");
	if (error_flag & INVALID_RATIO)
		printf("ratio is incorrect\n");
	if (error_flag & INVALID_SIZE)
		printf("size is incorrect\n");
	if (error_flag & INVALID_FILE)
		printf("file ext is incorrect\n");
}

void	display_usage(void)
{
	printf("Identifier [A] ambient lighting ratio [0.0,1.0] \
			RGB [0,255],[0,255],[0,255]\n");
	printf("Identifier [C] x,y,z coordinates [x],[y],[z]\
			3d normalized orientation vector [-1,1],[-1,1],[-1,1] \
			FOV [0,180]\n");
	printf("Identifier [L] x,y,z coordinates [x],[y],[z]\
			light brightness ratio[0.6], RGB [0,255],[0,255],[0,255]\n");
	printf("Identifier [sp] x,y,z coordinates [x],[y],[z]\
			shape diameter [d], RGB [0,255],[0,255],[0,255]\n");
	printf("Identifier [pl] x,y,z coordinates [x],[y],[z]\
			normalized orientation vector [-1,1], \
			RGB [0,255],[0,255],[0,255]\n");
	printf("Identifier [cy] x,y,z coordinates [x],[y],[z]\
			normalized orientation vector [-1,1], cylinder diameter [d],\
			cylinder height [h], RGB [0,255],[0,255],[0,255]\n");
}

void	error_handler(char *line, size_t line_n, int error_flag)
{
	printf("ERROR\n");
	printf("line %zu: %s\n", line_n, line);
	display_error(error_flag);
	display_usage();
	exit(1);
}

void	ext_check(char *filename)
{
	char	**strs;

	strs = ft_split(filename, '.');
	if (strs == NULL || strs[0] == NULL)
	{
		free_strs(strs);
		error_handler("", 0, INVALID_FILE);
	}
	else if (strs[1] && !ft_strncmp(strs[1], "rt", ft_strlen(strs[1]) + 1))
	{
		free_strs(strs);
		return ;
	}
	free_strs(strs);
	error_handler("", 0, INVALID_FILE);
}

t_config	read_map(char *filename)
{
	char		*line;
	t_config	config;
	int			fd;
	size_t		line_n;
	int			error_flag;

	ext_check(filename);
	fd = open(filename, 0644);
	config.shape_list = (t_shape *)malloc(sizeof(t_shape));
	config.shape_list->next = NULL;
	config.shape_list->type = ST_NONE;
	line_n = 1;
	while (true)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		line = remove_nl(line);
		error_flag = set_config(&config, line);
		if (error_flag)
			error_handler(line, line_n, error_flag);
		line_n++;

	}
	return (config);
}

t_config	init_config(char **argv)
{
	t_config	config;

	config = read_map(argv[1]);
	return (config);
}
