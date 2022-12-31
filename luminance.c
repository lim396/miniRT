#include "minirt.h"
#define SPECULAR_REF 0.3

t_color	add_ambient_luminance(t_config config)
{
	t_color	color;

	color.r = config.ambient.ambient_illuminance.r \
		* config.ambient.ambient_ref.r;
	color.g = config.ambient.ambient_illuminance.g \
		* config.ambient.ambient_ref.g;
	color.b = config.ambient.ambient_illuminance.b \
		* config.ambient.ambient_ref.b;
	return (color);
}

//t_color	add_diffuse_luminance(t_shape shape, t_color illuminance, \
//		double normal_light_dir_dot)
t_color	add_diffuse_luminance(t_shape shape, t_light light, \
		double normal_light_dir_dot)
{
	t_color	color;

	color.r = shape.material.diffuse_ref.r * light.illuminance.r \
		* light.brightness_ratio * normal_light_dir_dot;
	color.g = shape.material.diffuse_ref.g * light.illuminance.g \
		* light.brightness_ratio * normal_light_dir_dot;
	color.b = shape.material.diffuse_ref.b * light.illuminance.b \
		* light.brightness_ratio * normal_light_dir_dot;
	return (color);
}

//t_color	add_specular_luminance(t_nearest nearest, t_color illuminance, \
//		t_vec light_dir, t_ray camera_ray)
t_color	add_specular_luminance(t_nearest nearest, t_light light, \
		t_vec light_dir, t_ray camera_ray)
{
	t_vec	specular_dir;
	t_vec	rev_camera_to_screen_dir;
	float	rev_camera_to_screen_specular_dot;
	t_color	color;
	double	normal_light_dir_dot;

	normal_light_dir_dot = dot(nearest.i_point.normal, light_dir);
	normal_light_dir_dot = rounding_num(normal_light_dir_dot, 0, 1);
	specular_dir = normalize(sub(mul(2 * normal_light_dir_dot, \
					nearest.i_point.normal), light_dir));
	rev_camera_to_screen_dir = normalize(mul(-1.0, camera_ray.direction));
	rev_camera_to_screen_specular_dot \
		= dot(specular_dir, rev_camera_to_screen_dir);
	rev_camera_to_screen_specular_dot \
		= rounding_num(rev_camera_to_screen_specular_dot, 0, 1);
	color.r = SPECULAR_REF * light.illuminance.r * light.brightness_ratio \
		* pow(rev_camera_to_screen_specular_dot, SHININESS);
	color.g = SPECULAR_REF * light.illuminance.g * light.brightness_ratio \
		* pow(rev_camera_to_screen_specular_dot, SHININESS);
	color.b = SPECULAR_REF * light.illuminance.b * light.brightness_ratio\
		* pow(rev_camera_to_screen_specular_dot, SHININESS);
//	color.r = SPECULAR_REF * illuminance.r \
//		* pow(rev_camera_to_screen_specular_dot, SHININESS);
//	color.g = SPECULAR_REF * illuminance.g \
//		* pow(rev_camera_to_screen_specular_dot, SHININESS);
//	color.b = SPECULAR_REF * illuminance.b \
//		* pow(rev_camera_to_screen_specular_dot, SHININESS);
//	color.r = nearest.shape.material.specular_ref.r * illuminance.r \
//		* pow(rev_camera_to_screen_specular_dot, SHININESS);
//	color.g = nearest.shape.material.specular_ref.g * illuminance.g \
//		* pow(rev_camera_to_screen_specular_dot, SHININESS);
//	color.b = nearest.shape.material.specular_ref.b * illuminance.b \
//		* pow(rev_camera_to_screen_specular_dot, SHININESS);
	return (color);
}

t_color	get_luminance(t_config config, t_nearest nearest, t_ray ray)
{
	t_color		color;
	t_vec		light_dir;
	double		normal_light_dir_dot;
	t_nearest	i_point_near;

	color = add_ambient_luminance(config);
	light_dir = normalize(sub(config.light.vec, nearest.i_point.pos));
	i_point_near = get_shadow_ray(config, nearest, light_dir);
	if (i_point_near.flag)
		return (color);
	normal_light_dir_dot = dot(nearest.i_point.normal, light_dir);
	normal_light_dir_dot = rounding_num(normal_light_dir_dot, 0, 1);
	color = add_color(color, add_diffuse_luminance(nearest.shape, \
				config.light, normal_light_dir_dot));
//	color = add_color(color, add_diffuse_luminance(nearest.shape, \
///				config.light.illuminance, normal_light_dir_dot));
	if (normal_light_dir_dot > 0)
	{
		(void)ray;
//		color = add_color(color, add_specular_luminance(nearest, \
//					config.light.illuminance, light_dir, ray));
//		color = add_color(color, add_specular_luminance(nearest, \
					config.light, light_dir, ray));
	}
	return (color);
}
