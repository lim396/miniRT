#include <stdio.h>
#include <float.h>
#include <stdbool.h>
#include <limits.h>
#include "libft.h"
#include <math.h>
#define __GNU_SOURCE 1
#define	INF 1e400
#define NEG_INF (-INF)
#define NEG_ZERO (-1.0/INF)
double atod(char *str)
{
	double	ret;
	double	base;
	bool	dot_flag;

	base = 10;
	while (*str && ft_isdigit(*str))
	{
		if (dot_flag)
			ret += base * (*str - '0');
		else
			ret = ret * base + (*str - '0');
		str++;
		if (dot_flag)
			base *= 0.1;
		if (*str == '.' && !dot_flag)
		{
			str++;
			dot_flag = true;
			base = 0.1;
		}
	}
	return (ret);
}

typedef union	s_my_double {
	unsigned long long	ulnum;
	double	dnum;
} t_my_double;
/*
void printb(unsigned long long v) {
	unsigned long long mask = (long long) 1 << (sizeof(v) * CHAR_BIT - 1);
	size_t	cnt;
	cnt = 0;
	do {
		putchar(mask & v ? '1' : '0');
		cnt += 1;
	}while (mask >>=1);
	printf("\n");
	printf("put %zu\n", cnt);
}
*/
double	is_number(double num)
{
	unsigned long long	valid_bit1;
	unsigned long long	valid_bit2;
	t_my_double	my_dbl;

	my_dbl.dnum = num;
	valid_bit1 = ((1ull << 11) - 1ull) << 52;
	//printf("valid_bit1: %llu\n", valid_bit1);
	printb(valid_bit1);
	//printf("valid_bit1: %llu\n", ULONG_MAX & (1ull << 50));
	valid_bit2 = (ULONG_MAX - 1)  >> 12;
	printb(valid_bit2);
	if ((valid_bit1 & my_dbl.ulnum) == valid_bit1)
	{
		printf("valid2: %llu\n", valid_bit2);
		printf("valid2: %llu\n", 1ull << 51);
		if ((valid_bit2 | my_dbl.ulnum) != 0)
			return (NAN);
		return (INFINITY);
	}
	return (num);
}

double	ft_atod(char *str)
{
	double	num;
	int		sign;

	sign = 1;
	if (*str == '-' || *str == '+')
		sign = 44 - *str++;
	num = sign * atod(str);
	num = is_number(num);
	return (num);
}

/*
int main() 
{
	char *str;

	str = "0";
	printf("%s: %lf\n",str, ft_atod(str));
	str = "0.0";
	printf("%s: %lf\n",str, ft_atod(str));
	str = "1234";
	printf("%s: %lf\n",str, ft_atod(str));
	str = "-1234";
	printf("%s: %lf\n",str, ft_atod(str));
	str = "1234.23";
	printf("%s: %lf\n",str, ft_atod(str));
	str = "-1234.23";
	printf("%s: %lf\n",str, ft_atod(str));
}
*/
