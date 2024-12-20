/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkerboard_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbencze <pbencze@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 14:47:10 by vados-sa          #+#    #+#             */
/*   Updated: 2024/12/15 13:58:24 by pbencze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

/**
 * @brief: Maps a point on a 3D plane to 2D UV coordinates for texturing.
 * @param point: The 3D coordinates of the point on the plane.
 * @param normal: The normal vector at the point.
 * @return: A t_coord structure containing the UV coordinates.
 * @details: This function calculates the UV coordinates for
 * a point on a plane using different coordinates depending
 * on the orientation of the plane.
 * To calculate, we use the floor values, so that we get u and v
 * in a range of (-1 - +1).
 */
t_coord	planar_map(t_coord plane, t_coord normal)
{
	t_float	u;
	t_float	v;

	if (fabs(normal.y) > EPSILON)
	{
		u = plane.x - floor(plane.x);
		v = plane.z - floor(plane.z);
	}
	else if (fabs(normal.x) > EPSILON)
	{
		u = plane.z - floor(plane.z);
		v = plane.y - floor(plane.y);
	}
	else if (fabs(normal.z) > EPSILON)
	{
		u = plane.x - floor(plane.x);
		v = plane.y - floor(plane.y);
	}
	return (coord(u, v, 0));
}

/**
 * @brief: Maps a point on a sphere to 2D UV coordinates for texturing.
 * @param point: The 3D coordinates of the relative (because we consider 
 * the sphere to have its center at (0,0,0)) point on the sphere.
 * @param radius: The radius of the sphere.
 * @param normal: The normal vector at the point.
 * @return: A t_coord structure containing the UV coordinates.
 * @details: This function calculates the UV coordinates for
 * a point on a sphere using spherical coordinates.
 * The theta angle is calculated using atan2 for the
 * x and z coordinates, and the phi angle is calculated
 * using acos for the y coordinate.
 * The UV coordinates are then scaled and
 * adjusted to fit the checkerboard pattern.
 */
t_coord	spherical_map(t_coord point, t_float radius, t_coord normal)
{
	t_float	u;
	t_float	v;
	t_float	theta;
	t_float	phi;
	t_float	scale;

	scale = 10;
	theta = atan2(point.x, point.z);
	phi = acos(point.y / radius);
	u = theta / (2.0 * PI);
	u = 1.0 - (u + 0.5);
	v = 1 - phi / PI;
	u *= scale;
	v *= scale;
	return (coord(u, v, 0));
}

/**
 * @brief: determines the color of the intersection point.
 * @return: true if the color should turn into the
 * complementary color, false if the color stays the same.
 * @details: depending on the object type, we call
 * a mapping function that maps the coordinates of the
 * intersection point to a checkerboard grid. The x and y values
 * of uv will be between 0 and 1. We scale them to twice
 * the size, so that we can check if the fields are pair or not pair
 * To do this, we need the "floor" of uv.x and uv.y, which is the
 * closest integer less then or equal to a real number.
 * E.g. floor(1.34) = 1; floor(-1.34) = -2;
 * If both values are pair or both are unpair, they will
 * return true, otherwise they return false.
 */
bool	checker_color(t_intersec *object)
{
	t_coord	uv;
	t_coord	relative_point;

	if (object->type == 'p' && CHECKP == 1)
		uv = planar_map(object->point, object->normal);
	else if (object->type == 's' && CHECKS == 1)
	{
		relative_point = vec_sub(object->point, object->self->sp.center);
		uv = spherical_map(relative_point, \
			object->self->sp.radius, object->normal);
	}
	else
		return (false);
	if (((int)floor(uv.x * 2) % 2) == ((int)floor(uv.y * 2) % 2))
		return (true);
	return (false);
}

/**
 * @brief: checkerboard based on the color of the object in the .rt file and
 * on its complementary color.
 */
t_color	checkerboard(t_intersec *object)
{
	t_color	black;
	t_color	white;

	black = object->color;
	white = col(abs(255 - black.r), abs(255 - black.g), \
				abs(255 - black.b), 255);
	if (checker_color(object))
		return (white);
	return (black);
}
