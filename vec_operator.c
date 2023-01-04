/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_operator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shongou <shongou@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 23:34:51 by shongou           #+#    #+#             */
/*   Updated: 2023/01/04 23:34:52 by shongou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec	add(t_vec a, t_vec b)
{
	t_vec	vec;

	vec.x = a.x + b.x;
	vec.y = a.y + b.y;
	vec.z = a.z + b.z;
	return (vec);
}

t_vec	sub(t_vec a, t_vec b)
{
	t_vec	vec;

	vec.x = a.x - b.x;
	vec.y = a.y - b.y;
	vec.z = a.z - b.z;
	return (vec);
}

t_vec	mul(double t, t_vec a)
{
	t_vec	vec;

	vec.x = a.x * t;
	vec.y = a.y * t;
	vec.z = a.z * t;
	return (vec);
}

t_vec	div_vec(t_vec a, double t)
{
	t_vec	vec;

	vec.x = a.x / t;
	vec.y = a.y / t;
	vec.z = a.z / t;
	return (vec);
}
