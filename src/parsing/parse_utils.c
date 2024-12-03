
#include "minirt.h"

char	**split_three(char *info)
{
	int		i;
	int		comma_count;
	char	**str_arr;

	i = -1;
	comma_count = 0;
	while (info[++i])
	{
		if (info[i] == ',')
			comma_count++;
	}
	if (comma_count != 2)
		return (NULL);
	str_arr = ft_split(info, ',');
	if (ft_arr_len(str_arr) != 3)
		return (NULL);
	return (str_arr);
}

t_coord	coord(t_float x, t_float y, t_float z)
{
	t_coord	xyz;

	xyz.x = x;
	xyz.y = y;
	xyz.z = z;
	return (xyz);
}

void	assign_xyz(char type, t_data *data, t_coord xyz, char coord_type)
{
	if (data->bonus == 1)
		assign_xyz_bonus(type, data, xyz, coord_type);
	if (coord_type == 'n')
	{
		if (type == 'C')
			data->scene->c.orientation = vec_unit(xyz);
		if (type == 'p')
			object_last_node(data->scene->objects)->pl.normal = vec_unit(xyz);
		if (type == 'c')
			object_last_node(data->scene->objects)->cy.normal = vec_unit(xyz);
	}
	else if (coord_type == 'c')
	{
		if (type == 'C')
			data->scene->c.center = xyz;
		if (type == 'L')
			(light_last_node(data->scene->l))->point = xyz;
		if (type == 's')
			object_last_node(data->scene->objects)->sp.center = xyz;
		if (type == 'p')
			object_last_node(data->scene->objects)->pl.point = xyz;
		if (type == 'c')
			object_last_node(data->scene->objects)->cy.center = xyz;
	}
}

void	assign_rgba(char type, t_data *data, t_color rgba)
{
	if (data->bonus == 1)
		assign_rgba_bonus(type, data, rgba);
	if (type == 'A')
		data->scene->a.color = rgba;
	if (type == 'L')
		(light_last_node(data->scene->l))->color = rgba;
	if (type == 's')
		object_last_node(data->scene->objects)->sp.color = rgba;
	if (type == 'p')
		object_last_node(data->scene->objects)->pl.color = rgba;
	if (type == 'c')
		object_last_node(data->scene->objects)->cy.color = rgba;
}
