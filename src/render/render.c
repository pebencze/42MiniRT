/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbencze <pbencze@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 14:45:10 by vados-sa          #+#    #+#             */
/*   Updated: 2024/12/16 16:14:43 by pbencze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
/**
 * @brief: shifts the rgba values (0-255) to a uint32_t integer
 */
uint32_t	create_color(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

/**
 * @brief: draws a background of gradient pink colour,
 * depending on the angle between the camera's up vector and
 * on the direction of the ray.
 */
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

/**
 * @brief: calculates and puts the pixel color for
 * the window´s pixel (x,y). If there is no intersection
 * with an object, but there is a camera, it simply renders
 * the gradient background.
 */
void	put_color(uint32_t x, uint32_t y, t_data *data, t_ray ray)
{
	uint32_t	col_int;
	t_color		col_rgb;
	t_intersec	*hit_rec;

	hit_rec = intersection(data, ray);
	if (hit_rec)
		col_rgb = calculate_light(data, hit_rec, hit_rec->color);
	else
		col_rgb = gradient(ray, data->scene->c.up, data);
	col_int = create_color(col_rgb.r, col_rgb.g, col_rgb.b, col_rgb.a);
	mlx_put_pixel(data->image, x, y, col_int);
}

/**
 * @brief: renders looping through each pixel of the window
 * @var ray: the ray originating at the camera´s position and
 * going through the windows pixel at width x and height y,
 * translated into viewport dimensions
 */
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
			ray = create_ray(x, y, data->scene->c.center, data);
			put_color(x, y, data, ray);
		}
	}
}
