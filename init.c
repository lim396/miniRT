/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shongou <shongou@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 23:33:47 by shongou           #+#    #+#             */
/*   Updated: 2023/01/04 23:33:49 by shongou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	set_config(t_config *config, const char *line, t_err *err)
{
	char	**split_line;

	err->err_flag = 0;
	split_line = ft_split(line, ' ');
	if (split_line == NULL || split_line[0] == NULL)
		err->err_flag = NULL_STR;
	else if (!ft_strncmp(split_line[0], "A", ft_strlen(split_line[0]) + 1))
		set_ambient(split_line, config, &err->err_flag, &err->scene_obj);
	else if (!ft_strncmp(split_line[0], "L", ft_strlen(split_line[0]) + 1))
		set_light(split_line, config, &err->err_flag, &err->scene_obj);
	else if (!ft_strncmp(split_line[0], "C", ft_strlen(split_line[0]) + 1))
		set_camera(split_line, config, &err->err_flag, &err->scene_obj);
	else if (!ft_strncmp(split_line[0], "sp", ft_strlen(split_line[0]) + 1))
		set_sphere(split_line, config, &err->err_flag, &err->scene_obj);
	else if (!ft_strncmp(split_line[0], "pl", ft_strlen(split_line[0]) + 1))
		set_plane(split_line, config, &err->err_flag, &err->scene_obj);
	else if (!ft_strncmp(split_line[0], "cy", ft_strlen(split_line[0]) + 1))
		set_cylinder(split_line, config, &err->err_flag, &err->scene_obj);
	else
		err->err_flag |= IDENTIFIER_ERROR;
	free_strs(split_line);
}

static void	ext_check(char *filename)
{
	char	**strs;

	strs = ft_split(filename, '.');
	if (strs == NULL || strs[0] == NULL)
	{
		free_strs(strs);
		error_handler(-1, ft_strdup(""), 0, INVALID_FILE);
	}
	else if (strs[1] && !ft_strncmp(strs[1], "rt", ft_strlen(strs[1]) + 1))
	{
		free_strs(strs);
		return ;
	}
	free_strs(strs);
	error_handler(-1, ft_strdup(""), 0, INVALID_FILE);
}

static void	pre_init(char *filename, int *fd, t_config *config, t_err *err)
{
	err->err_flag = 0;
	err->scene_obj = 0;
	*fd = open(filename, O_RDONLY);
	if (*fd < 0)
		err->err_flag |= OPEN_ERROR;
	config->shape_list = (t_shape *)malloc(sizeof(t_shape));
	if (config->shape_list == NULL)
		err->err_flag |= MALLOC_ERROR;
	if (err->err_flag)
		before_set_config_err_handler(err->err_flag);
	config->shape_list->next = NULL;
	config->shape_list->type = ST_NONE;
}

static t_config	read_map(char *filename)
{
	char		*line;
	t_config	config;
	int			fd;
	size_t		line_n;
	t_err		err;

	pre_init(filename, &fd, &config, &err);
	line_n = 1;
	while (true)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		line = remove_nl(line, &err);
		if (line != NULL && line[0] == '\0')
			continue ;
		set_config(&config, line, &err);
		if (err.err_flag)
			error_handler(fd, line, line_n, err.err_flag);
		free(line);
		line_n++;
	}
	close(fd);
	check_obj(err.scene_obj);
	return (config);
}

t_config	init_config(char **argv)
{
	t_config	config;
	char		*filename;

	filename = argv[1];
	ext_check(filename);
	config = read_map(filename);
	return (config);
}
