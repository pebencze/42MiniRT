
#include "minirt.h"

void	init(t_data *data)
{
	data = ft_calloc(1, sizeof(t_data));
	if (!data)
		ft_exit(1, data, ALLOC_ERR);
	data->scene = ft_calloc(1, sizeof(t_scene));
	if (!data->scene)
		ft_exit(1, data, ALLOC_ERR);
	/* data->scene->l = ft_calloc(1, sizeof(t_L));
	if (!data->scene->l)
		ft_exit(1, data, ALLOC_ERR);
	data->scene->objects = ft_calloc(1, sizeof(t_object));
	if (!data->scene->objects)
		ft_exit(1, data, ALLOC_ERR); */
}