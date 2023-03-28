/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   huipark-v2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huipark <huipark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:48:17 by huipark           #+#    #+#             */
/*   Updated: 2023/03/28 17:06:23 by huipark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

//zone
int		wight;
int		height;
char	back_char;
char	*map;

//info
char	type;
float		X;
float		Y;
float	radius;
char	color;

FILE	*file;

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while(s[i])
		i++;
	return (i);
}

int	str_err(char *s)
{
	write(1, s, ft_strlen(s));
	return (1);
}

int	clear_all(char *s)
{
	if (file)
		fclose(file);
	if (map)
		free(map);
	if (s)
		str_err(s);
	return (1);
}

int in_circle(float x, float y)
{
	float distance;

	distance = sqrtf(powf(x - X, 2.) + powf(y - Y, 2.));
	if (distance <= radius)
	{
		if (radius - distance < 1.00000000)
			return (2);
		return (1);
	}
	return (0);
}

int main(int argc, char **argv)
{
	int	i;

	i = 0;
	if (argc != 2)
		return (str_err("Error: argument\n"));
	if (!(file = fopen(argv[1], "r")))
		return (str_err("Error: Operation file corrupted\n"));
	if (fscanf(file, "%d %d %c\n", &wight, &height, &back_char) != 3)
		return (clear_all("Error: Operation file corrupted\n"));
	if (wight <= 0 || wight > 300 || height <= 0 || height > 300)
		return (clear_all("Error: Operation file corrupted\n"));
	if (!(map = (char *)malloc(sizeof(char) * (wight * height))))
		return (1);
	while (i < wight * height)
		map[i++] = back_char;

	int	x;
	int	y;
	int flag;
	i = 0;
	while ((i = fscanf(file, "%c %f %f %f %c\n", &type, &X, &Y, &radius, &color)) == 5)
	{
		y = 0;
		if ((type != 'c' && type != 'C') || radius <= 0.00000000)
			return (clear_all("Error: Operation file corrupted\n"));
		while (y < height)
		{
			x = 0;
			while (x < wight)
			{
				flag = in_circle((float)x, (float)y);
				if ((type == 'c' && flag == 2) || (type == 'C' && flag))
					map[(y * wight) + x] = color;
				x++;
			}
			y++;
		}
	}
	if (i != -1)
		return (clear_all("Error: Operation file corrupted"));
	i = 0;
	while (i < height)
	{
		write(1, map + (wight * i), wight);
		write(1, "\n", 1);
		i++;
	}
}
