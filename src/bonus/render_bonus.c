/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbencze <pbencze@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 14:47:00 by vados-sa          #+#    #+#             */
/*   Updated: 2024/12/16 16:45:50 by pbencze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

uint32_t	create_color(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

t_color	gradient(t_ray r, t_coord camera_up, t_data *data)
{
	t_coord	unit_direction;
	t_float	a;
	t_color	color;

	unit_direction = vec_unit(r.direction);
	a = 0.5 * (vec_dot(unit_direction, camera_up) + 1.0);
	color.r = ((1.0 - a) * 255 + a * 255);
	color.g = ((1.0 - a) * 255 + a * 182);
	color.b = ((1.0 - a) * 255 + a * 193);
	color.a = 255;
	return (color);
}

uint32_t	calculate_color(uint32_t x, uint32_t y, t_data *data, t_ray ray)
{
	uint32_t	col_int;
	t_color		col_rgb;
	t_intersec	*hit_rec;
	t_color		obj_color;

	hit_rec = intersection(data, ray);
	if (hit_rec)
	{
		obj_color = checkerboard(hit_rec);
		col_rgb = calculate_light(data, hit_rec, obj_color);
	}
	else
		col_rgb = gradient(ray, data->scene->c.up, data);
	col_int = create_color(col_rgb.r, col_rgb.g, col_rgb.b, col_rgb.a);
	return (col_int);
}

void	antialias(uint32_t x, uint32_t y, t_data *data)
{
	uint32_t			color;
	uint32_t			i;
	uint32_t			j;
	t_ray				ray;

	i = -1;
	color = 0;
	while (++i < 8)
	{
		j = -1;
		while (++j < 8)
		{
			ray = create_ray(x + (j / 8.0), y + (i / 8.0), data->scene->c.center, data);
			color += calculate_color(x + (j / 8.0), y + (i / 8.0), data, ray);
		}
	}
	color = color / 64;
	mlx_put_pixel(data->image, x, y, color);
}

void	render(t_data *data)
{
	uint32_t	x;
	uint32_t	y;
	t_ray		ray;

	y = -1;
	while (++y < data->image_height)
	{
		x = -1;
		while (++x < data->image_width)
		{
			if (ANTIALIAS == 1)
			{
				antialias(x, y, data);
			}
			else
			{
				ray = create_ray(x, y, data->scene->c.center, data);
				mlx_put_pixel(data->image, x, y, \
				calculate_color(x, y, data, ray));
			}
		}
	}
}
