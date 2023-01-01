#include "minirt.h"

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

void	display_error(int error_flag)
{
	if (error_flag & OPEN_ERROR)
		printf("open error\n");
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

void	error_handler(char *line, size_t line_n, int error_flag)
{
	printf("ERROR\n");
	printf("line %zu: %s\n", line_n, line);
	display_error(error_flag);
	display_usage();
	exit(1);
}

void	before_set_config_err_handler(int err_flag)
{
	printf("ERROR\n");
	display_error(err_flag);
	exit(1);
}

void	check_obj(int scene_objs)
{
	printf("%d\n", scene_objs);
	if ((scene_objs & C) && (scene_objs & A) && (scene_objs & L) \
		&& ((scene_objs & SP) || (scene_objs & PL) || (scene_objs & CY)))
		return ;
	printf("ERROR\n");
	printf("not enough objects\n");
	exit(1);
}
