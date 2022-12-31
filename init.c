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
//int	set_config(t_config *config, const char *line)
void	set_config(t_config *config, const char *line, t_err *err)
{
	char	**split_line;
	//int		err_flag;
	//t_err	err;

	//err_flag = 0;
	err->err_flag = 0;
	split_line = ft_split(line, ' ');
	if (split_line == NULL || split_line[0] == NULL)
	{
		err->err_flag = NULL_STR;
		//return (NULL_STR);
	}
	//if (split_line[0][0] == 'A')
	else if (!ft_strncmp(split_line[0], "A", ft_strlen(split_line[0]) + 1))
		set_ambient(split_line, config, &err->err_flag, &err->scene_obj);
	//else if (split_line[0][0] == 'L')
	else if (!ft_strncmp(split_line[0], "L", ft_strlen(split_line[0]) + 1))
		set_light(split_line, config, &err->err_flag, &err->scene_obj);
	//else if (split_line[0][0] == 'C')
	else if (!ft_strncmp(split_line[0], "C", ft_strlen(split_line[0]) + 1))
		set_camera(split_line, config, &err->err_flag, &err->scene_obj);
	//else if (split_line[0][0] == 's' && split_line[0][1] == 'p')
	else if (!ft_strncmp(split_line[0], "sp", ft_strlen(split_line[0]) + 1))
		set_sphere(split_line, config, &err->err_flag, &err->scene_obj);
	//else if (split_line[0][0] == 'p' && split_line[0][1] == 'l')
	else if (!ft_strncmp(split_line[0], "pl", ft_strlen(split_line[0]) + 1))
		set_plane(split_line, config, &err->err_flag, &err->scene_obj);
	//else if (split_line[0][0] == 'c' && split_line[0][1] == 'y')
	else if (!ft_strncmp(split_line[0], "cy", ft_strlen(split_line[0]) + 1))
		set_cylinder(split_line, config, &err->err_flag, &err->scene_obj);
	else
		err->err_flag |= IDENTIFIER_ERROR;
	//if (!(err_flag & IDENTIFIER_ERROR))
	//{
		
	//}
	free_strs(split_line);
//	}
	//return (err_flag);
	//return (err);
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

void	check_obj(int scene_objs)
{
	printf("%d\n",scene_objs);
	if ((scene_objs & C) && (scene_objs & A) && (scene_objs & L) \
		&& ((scene_objs & SP) || (scene_objs & PL) || (scene_objs & CY)))
		return ;
	printf("ERROR\n");
	printf("not enough objects\n");
	exit(1);
}

t_config	read_map(char *filename)
{
	char		*line;
	t_config	config;
	int			fd;
	size_t		line_n;
	//int			error_flag;
	t_err		err;

	ext_check(filename);
	fd = open(filename, 0644);
	config.shape_list = (t_shape *)malloc(sizeof(t_shape));
	config.shape_list->next = NULL;
	config.shape_list->type = ST_NONE;
	line_n = 1;
	err.scene_obj = 0;
	while (true)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		line = remove_nl(line);
		//error_flag = set_config(&config, line);
		//err = set_config(&config, line, scene_objs);
		set_config(&config, line, &err);
		//if (error_flag)
		//if (err.error_flag)
		if (err.err_flag)
			error_handler(line, line_n, err.err_flag);
		line_n++;

	}
	check_obj(err.scene_obj);
	return (config);
}

t_config	init_config(char **argv)
{
	t_config	config;

	config = read_map(argv[1]);
	return (config);
}
