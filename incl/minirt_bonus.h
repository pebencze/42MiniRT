/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbencze <pbencze@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 14:36:40 by vados-sa          #+#    #+#             */
/*   Updated: 2024/12/16 16:24:55 by pbencze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_BONUS_H
# define MINIRT_BONUS_H

# define CHECKP 1
# define CHECKS 0
# define SPECULAR 1
# define ANTIALIAS 1

# include "minirt.h"

t_color		checkerboard(t_intersec *object);
t_color		specular_light(t_l *light, t_intersec *hit_rec, t_data *data);
t_coord		vec_reflect(t_coord incident, t_coord normal);
uint32_t	calculate_color(uint32_t x, uint32_t y, t_data *data, t_ray ray);

#endif
