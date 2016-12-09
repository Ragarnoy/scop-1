/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   callback.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwatkins <wwatkins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 13:51:00 by wwatkins          #+#    #+#             */
/*   Updated: 2016/12/09 17:55:53 by wwatkins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	key_handle(t_env *env)
{
	int	i;

	if (glfwGetKey(env->win.ptr, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(env->win.ptr, GL_TRUE);
	i = -1;
	while (++i < MAX_KEYS)
		env->key[i].code = glfwGetKey(env->win.ptr, i) == GLFW_PRESS ? 1 : 0;
	key_toggle(&env->key[MW], &env->mod.wireframe, GL_FILL, GL_LINE);
	key_toggle(&env->key[MF], &env->mod.focus, 0, 1);
	key_toggle(&env->key[MS], &env->mod.shading, 0, 1);
	key_toggle(&env->key[MC], &env->mod.color, 0, 1);
	key_toggle(&env->key[MT], &env->mod.texture, 0, 1);
	key_action(env);
}

void	key_action(t_env *env)
{
	if (env->key[ZP].code || env->key[ZM].code)
		camera_zoom(env);
	if (env->mod.focus)
		camera_recenter(env);
	if (env->key[ALT].code && env->key[RM].code)
		env->cam.velocity -= 0.05;
	if (env->key[ALT].code && env->key[RP].code) // NOPE
		env->cam.velocity += 0.05;
	model_move_demo(env);
	camera_move_inertia(env, 0.93, FREE);
	camera_look_at_target(env);
	model_move_inertia(env, 0.9);
	if (env->key[MW].code)
		glPolygonMode(GL_FRONT_AND_BACK, env->mod.wireframe);
}

void	key_toggle(t_key *key, short *var, int v0, int v1)
{
	key->cooldown > 1 ? key->cooldown -= 1 : 0;
	if (key->code && key->cooldown <= 1)
	{
		if (*var == v1)
			*var = v0;
		else if (*var == v0)
			*var = v1;
		key->cooldown = 20;
	}
}
