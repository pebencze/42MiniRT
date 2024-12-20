/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbencze <pbencze@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 14:36:43 by vados-sa          #+#    #+#             */
/*   Updated: 2024/12/16 12:07:21 by pbencze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <fcntl.h>      // open, O_* constants
# include <unistd.h>     // close, read, write
# include <stdio.h>      // printf, perror
# include <stdlib.h>     // malloc, free, exit
# include <string.h>     // strerror
# include <math.h>       // math functions (link with -lm)
# include "../lib/libft/libft.h"
# include "structs.h"
# include "macros.h"
# if BONUS == 1
#  include "minirt_bonus.h"
# endif

/*init*/
t_data		*init(void);
void		setup_viewport(t_data *data, t_c camera);

/*lists*/
t_object	*new_object_node(void);
t_object	*object_last_node(t_object *head);
void		add_object_node(t_object **object, t_object	*new);
void		delete_object_list(t_object **objects);
t_l			*new_light_node(void);
t_l			*light_last_node(t_l *light);
void		add_light_node(t_l **light, t_l	*new);
void		delete_light_list(t_l **lights);

/*error-handling*/
void		ft_exit(int exit_code, t_data *data, char *message);
void		free_data(t_data *data);

/*utils*/
ssize_t		ft_arr_len(char **arr);
char		**free_arr(char **arr1, char **arr2);
char		**split_three(char *info);
int			float_check(char *info);
int			int_check(char *info);
t_color		col(int r, int g, int b, int a);
t_coord		coord(t_float x, t_float y, t_float z);

/*parsing*/
void		parse(t_data *data, char *filename);
void		read_file(char *filename, t_data *data);
int			parse_a(t_data *data, char *line);
int			parse_l(t_data *data, char *line);
int			parse_c(t_data *data, char *line);
int			parse_cy(t_data *data, char *line);
int			parse_pl(t_data *data, char *line);
int			parse_sp(t_data *data, char *line);
int			check_color(char *info, t_data *data, char type);
int			check_identifier(char *info, t_data *data, char *type);
//int			check_ratio(char *info, t_data *data, char type);
int			check_coordinates(char *info, t_data *data, char type);
int			check_normal(char *info, t_data *data, char type);
int			check_dimension(char *line, t_dimension type, t_data *data);
int			check_fov(char *info, t_data *data);
void		assign_xyz(char type, t_data *data, t_coord xyz, char coord_type);
void		assign_rgba(char type, t_data *data, t_color rgba);

/*vector operations*/
t_float		vec_dot(t_coord v1, t_coord v2);
t_float		vec_len(t_coord v);
t_coord		vec_cross(t_coord v1, t_coord v2);
t_coord		vec_add(t_coord v1, t_coord v2);
t_coord		vec_sub(t_coord v1, t_coord v2);
t_coord		vec_mult(t_coord v1, t_float scalar);
t_coord		vec_unit(t_coord v);
t_color		col_mult(t_color c, t_float scalar);
t_color		col_add(t_color c1, t_color c2);

/*rendering*/
void		render(t_data *data);
t_coord		ray_at(t_ray r, t_float t);
t_ray		create_ray(uint32_t x, uint32_t y, t_coord origin, t_data *data);
t_color		gradient(t_ray r, t_coord camera_up, t_data *data);
void		put_color(uint32_t x, uint32_t y, t_data *data, t_ray ray);

/*intersections*/
t_intersec	*sphere_intersect(t_data *data, t_ray ray, t_object *obj);
t_intersec	*plane_intersect(t_ray ray, t_object *obj);
t_intersec	*cylinder_intersect(t_ray ray, t_object *obj);
t_intersec	*intersect_cap(t_ray ray, t_object *obj);
t_intersec	*intersection(t_data *data, t_ray ray);
t_intersec	*obj_intersection(t_data *data, t_ray ray, t_object *object);
t_intersec	*compare_distance(t_intersec *obj_1, t_intersec *obj_2, \
								t_coord origin);
uint32_t	create_color(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

/*light*/
t_color		diffuse_light(t_l *l, t_intersec *hit_rec, t_data *data);
bool		check_shadow(t_ray light, t_coord point, t_data *data, \
							t_coord normal);
t_color		calculate_light(t_data *data, t_intersec *hit_rec, t_color color);

/*hook functions*/
void		resize(int32_t width, int32_t height, t_data *data);
void		my_keyhook(mlx_key_data_t keydata, t_data *data);
void		move(mlx_key_data_t keydata, t_data *data, t_c camera);
void		zoom(mlx_key_data_t keydata, t_data *data, t_c camera);
void		rotate(mlx_key_data_t keydata, t_data *data, t_c camera);

#endif
