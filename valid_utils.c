#include "minirt.h"

bool	valid_float(char *str)
{
	bool	dot_flag;
	size_t	i;

	if (!str)
		return (false);
	dot_flag = false;
	i = 0;
	while (str[i] && ft_isdigit(str[i]))
	{
		i++;
		if (!dot_flag && str[i] == '.')
		{
			i++;
			dot_flag = true;
		}
	}
	if (str[i] == '\0')
		return (true);
	return (false);
}

bool	valid_vector(char *str)
{
	size_t	i;
	char	split_str;

	split_str = ft_split(str, ',');
	if (!split_str || !(*split_str))
		return (false);
	i = 0;
	while (i < 3)
	{
		if (!valid_float(split_str[i]))
			return (false);
		i++;
	}
	return (true);
}

bool	valid_digit(char *str)
{
	while(str[i] && ft_isdigit(str[i]))
		i++;
	if (str[i] == '\0')
		return (true);
	return (false);
}

bool	valid_color(char *str)
{
	size_t	i;
	char	split_str;

	split_str = ft_split(str, ',');
	if (!split_str || !(*split_str))
		return (false);
	i = 0;
	while (i < 3)
	{
		if (!valid_digit(split_str[i]))
				return (false);
		i++;
	}
	return (true);
}