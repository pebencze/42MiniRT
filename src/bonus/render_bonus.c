/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbencze <pbencze@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 14:47:00 by vados-sa          #+#    #+#             */
/*   Updated: 2024/12/13 10:14:48 by pbencze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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

void	put_color(uint32_t x, uint32_t y, t_data *data, t_ray ray)
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
	mlx_put_pixel(data->image, x, y, col_int);
}

void	render(t_data *data)
{
	uint32_t	x;
	uint32_t	y;
	t_ray		ray;
	uint32_t	color;
	t_color		rgba;

	y = -1;
	while (++y < data->image_height)
	{
		x = -1;
		while (++x < data->image_width)
		{
			ray = create_ray(x, y, data->scene->c.center, data);
			put_color(x, y, data, ray);
		}
	}
}
