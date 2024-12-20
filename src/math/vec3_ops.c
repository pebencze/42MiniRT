/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_ops.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbencze <pbencze@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 14:46:31 by vados-sa          #+#    #+#             */
/*   Updated: 2024/12/12 17:11:11 by pbencze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_coord	vec_add(t_coord v1, t_coord v2)
{
	return (coord(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z));
}

t_coord	vec_sub(t_coord v1, t_coord v2)
{
	return (coord(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z));
}

/**
 * @brief: function to scale a vector (make it longer or shorter)
 * without changing its direction.
 */
t_coord	vec_mult(t_coord v1, t_float scalar)
{
	return (coord(v1.x * scalar, v1.y * scalar, v1.z * scalar));
}

t_float	vec_len(t_coord v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

/**
 * @brief: calculates a unit vector, which has the length of 1 
 * by dividing each coordinate by the length of the vector.
 */
t_coord	vec_unit(t_coord v)
{
	t_float	len;

	len = vec_len(v);
	return (coord(v.x / len, v.y / len, v.z / len));
}
