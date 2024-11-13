
#include "minirt.h"

t_color	col_mult(t_color c, t_float scalar)
{
	return (col(c.r * scalar, c.g * scalar, c.b * scalar, c.a));
}

t_color	col_add(t_color c1, t_color c2)
{
	return (col(c1.r + c2.r, c1.g + c2.g, c1.b + c2.b, c1.a));
}

/**
 * This function multiplies the color of an object by the
 * ratio and color of the ambient lighting or "global illumination"
 * in the scene.
 * @param color: pointer to the color of the object or background
 * @param ambient: ambietn light struct containing ratio and color
 */
t_color	ambient_light(t_A ambient)
{
	t_color	light;

	light = col_mult(ambient.color, ambient.ratio);
	return (light);
}

/**
 * the larger θ becomes, the less of an impact
 * the light should have on the fragment's color.
 * to get (only) the cosine of the angle between
 * both vectors we will work with unit vectors (vectors of length 1)
 * so we need to make sure all the vectors are normalized
 * surface_normal: a vector that is perpendicular to the vertex' surface.
 * The directed light ray: a direction vector that is the difference vector
 * between the light's position and the fragment's position. To calculate this light
 * ray we need the light's position vector and the fragment's position vector.
 * @param l: a linked list of light sources
 * @param hit_rec: a t_intersection struct that contains the surface normal and the point where the object was hit
 */
t_color	diffuse_light(t_L *l, t_intersec *hit_rec)
{
	t_coord	light_dir;
	t_float	dot_product;
	t_color	diffuse;
	t_color	temp_diffuse;
	//bool	shadow;

	diffuse = col(0, 0, 0, 0);
	while (l && hit_rec)
	{
		//figure out how to combine multiple lights
		//hit_rec->normal = vec_unit(hit_rec->normal); //do we need it?
		light_dir = vec_unit(vec_sub(hit_rec->point, l->point));
		dot_product = fmax(vec_dot(hit_rec->normal, light_dir), 0.0); //if angle is bigger than 90deg, no light
		//shadow = check_shadow();
		if (dot_product > 0.0) //&& shadow == false)
		{
			temp_diffuse = col_mult(col_mult(l->color, dot_product), l->brightness);
			diffuse = col_add(diffuse, temp_diffuse);
		}
		l = l->next;
	}
	return (diffuse);
}

t_color	calculate_light(t_data *data, t_intersec *hit_rec, t_color color)
{
	t_color	result;
	t_color	ambient;
	t_color	diffuse;

	ambient = ambient_light(data->scene->a);
	diffuse = diffuse_light(data->scene->l, hit_rec);
	result.r = ((t_float)(ambient.r + diffuse.r) / 255.0) * color.r;
	result.g = ((t_float)(ambient.g + diffuse.g) / 255.0) * color.g;
	result.b = ((t_float)(ambient.b + diffuse.b) / 255.0) * color.b;
	if (result.r > 255)
		result.r = 255;
	if (result.g > 255)
		result.g = 255;
	if (result.b > 255)
		result.b = 255;
	result.a = 255;
	return (result);
}