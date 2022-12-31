#include "minirt.h"

double	rounding_num(double num, double min, double max)
{
	double	n;

	n = num;
	if (num < min)
		n = min;
	if (num > max)
		n = max;
	return (n);
}
/*
bool	is_overflow(double ret, int n, double base, bool dot_flag)
{
	if (dot_flag)
	{
		if (DBL_MAX
	}
	else {
	}
}

double atod(char *str)
{
	double	ret;
	double	base;
	bool	dot_flag;
	int		sign;

	base = 10;
	sign = 1;
	if (*str == '+' || *str == '-')
		sign = 44 - *str++;
	while (*str && is_digit(*str))
	{
		if (is_overflow(ret, *str - '0', base, dot_flag))
			return (sign * DBL_MAX);
		if (dot_flag)
			ret += sign * base * (*str - '0');
		else
			ret = ret * base + sign * (*str - '0');
		str++;
		if (*str == '.' && !dot_flag)
		{
			str++;
			dot_flag = true;
			base = 0.1;
		}
	}
	return (ret);
}*/

//size_t	count_valid(char *str)
//{
//	int		i;
//	bool	dot_flag;
//
//	dot_flag = 0;
//	i = 0;
//	while (str[i] && ft_isdigit(str[i]))
//	{
//		i++;
//		if (!dot_flag && str[i] == '.')
//		{
//			dot_flag = 1;
//			i++;
//		}
//	}
//	return (i - dot_flag);
//}

//double	atod(char *str)
//{
//	// overflow checkしろよ
//	int		n1;
//	int		n2;
//	size_t	cnt;
//	double	ret;
//	size_t	valid_len;
//	int		sign;
//
//	sign = 1;
//	if (*str == '-')
//	{
//		str++;
//		sign = -1;
//	}
//	valid_len = count_valid(str);
//	cnt = 0;
//	n1 = ft_atoi(str);
//	while (*str && *str != '.')
//	{
//		cnt++;
//		str++;
//	}
//	str++;
//	n2 = ft_atoi(str);
//	if (valid_len == cnt)
//		ret = sign * (double)n1;
//	else
//		ret = sign * (double)n1 + sign * ((double)n2 / pow(10,(valid_len - cnt)));
//	return (ret);
//}

t_shape	*list_last(t_shape *list)
{		
	if (list == NULL)
		return (NULL);
	while (list->next != NULL)
	{
		list = list->next;
	}
	return (list);
}

void	add_list_last(t_shape **shape_list, t_shape *node)
{
	t_shape	*last;
	t_shape	*head;

	if (shape_list == NULL)
		return ;
	if (*shape_list == NULL)
	{
		*shape_list = node;
		return ;
	}
	head = *shape_list;
	last = list_last(*shape_list);
	*shape_list = head;
	if (last == NULL)
		return ;
	last->next = node;
}
