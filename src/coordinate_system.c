/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coordinate_system.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwatkins <wwatkins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 16:27:51 by wwatkins          #+#    #+#             */
/*   Updated: 2016/12/08 14:46:28 by wwatkins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	set_projection_matrix(t_mat4 *m, float fov, float ratio, float near, float far)
{
	float	s;

	s = 1 / (tan(fov * 0.5 * M_PI / 180.0));
	mat4_set(m, 0);
	m->m[0] = s / ratio;
	m->m[5] = s;
	m->m[10] = -(far + near) / (far - near);
	m->m[11] = -1;
	m->m[14] = -2 * far * near / (far - near);
}

void	compute_mvp_matrix(t_env *env)
{
	env->sim.mvp = mat4_mul(mat4_transpose(env->sim.model),
		mat4_mul(env->sim.view, env->sim.projection));
}
