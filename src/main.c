/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwatkins <wwatkins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 17:20:21 by wwatkins          #+#    #+#             */
/*   Updated: 2016/12/06 14:34:56 by wwatkins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

GLfloat cubeVertices[] = {
	/* Positions */        /* Colors */
	-0.1f,  0.1f, -0.1f,  0.0f, 1.0f, 0.0f, // 0
	 0.1f,  0.1f, -0.1f,  0.0f, 0.0f, 1.0f, // 1
	 0.1f, -0.1f, -0.1f,  1.0f, 0.0f, 0.0f, // 2
	-0.1f, -0.1f, -0.1f,  0.0f, 1.0f, 1.0f, // 3
	-0.1f,  0.1f,  0.1f,  0.0f, 1.0f, 0.0f, // 4
	 0.1f,  0.1f,  0.1f,  0.0f, 0.0f, 1.0f, // 5
	 0.1f, -0.1f,  0.1f,  1.0f, 0.0f, 0.0f, // 6
	-0.1f, -0.1f,  0.1f,  0.0f, 1.0f, 1.0f  // 7
};

GLuint	cubeIndices[] = {
	/*	A cube has 6 faces, with 2 triangles/face, so 12 triangles total. */
	0, 1, 2,  0, 3, 2,  0, 4, 5,  0, 1, 5,  0, 4, 7,  0, 3, 7,
	6, 2, 1,  6, 5, 1,  6, 5, 4,  6, 7, 4,  6, 2, 3,  6, 7, 3
};

int		main(void)
{
	t_env	env;

	init(&env);

	/*	Build and compile our shader program */
	build_shader_program(&env, "../shader/vertex.glsl", "../shader/fragment.glsl");
	/*	Create the objects buffers for the differents objects
		(vertex_buffer, vertex_array, element_buffer) */
	env.data.size_vertices = sizeof(cubeVertices);
	env.data.size_indices = sizeof(cubeIndices);
	create_buffers(&env, cubeVertices, cubeIndices, GL_DYNAMIC_DRAW);
	/*	Prevents stange bugs */
	glBindVertexArray(0);

	set_model_matrix(&env.sim.model);
	set_view_matrix(&env.sim.view);
	set_projection_matrix(&env.sim.projection, env.cam.fov, env.win.ratio, 0.001f, 100.0f);

	mat4_set(&env.model.rotation, IDENTITY);
	mat4_set(&env.model.translation, IDENTITY);
	mat4_set(&env.model.scale, IDENTITY);

	glEnable(GL_DEPTH_TEST);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	while(!glfwWindowShouldClose(env.win.ptr))
	{
		/*	Events handler */
		glfwPollEvents();

		key_pressed(&env);
		key_action(&env);
		/*	Clears the color buffer */
		glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		/*	Uniform test for color changing of the fragment shader */
		GLfloat	epoch = glfwGetTime();
		GLfloat B = (sin(epoch) / 2) + 0.5;
		GLfloat G = (sin(epoch - 1.5) / 2) + 0.5;
		GLfloat	R = (cos(epoch) / 2) + 0.5;
		GLint	vertexColorLocation = glGetUniformLocation(env.shader.program, "mod_color");

		// rotate(&env.model.rotation, (t_vec3) { 0, 0.5, 0.5 });
		// scale(&env.model.scale, (t_vec3) { sin(epoch)*0.01, sin(epoch)*0.01, sin(epoch)*0.01 });
		// translate(&env.model.translation, (t_vec3) { sin(epoch) * 0.1, cos(epoch) * 0.1, (sin(epoch) + cos(epoch * 2)) * 0.1});

		/*	Camera simulation */
		env.sim.view = look_at(&env, &env.cam.pos, &env.cam.target, &env.cam.up);

		env.sim.model = mat4_mul(env.model.rotation,
						mat4_mul(env.model.translation, env.model.scale));
		mat4_print(&env.sim.model);


		/*	Activate the shader program */
		glUseProgram(env.shader.program);
		/*	Updates the uniform variable in the fragment shader */
		glUniform4f(vertexColorLocation, R, G, B, 1.0f);
		glUniformMatrix4fv(env.shader.mloc, 1, GL_FALSE, env.sim.model.m);
		glUniformMatrix4fv(env.shader.vloc, 1, GL_FALSE, env.sim.view.m);
		glUniformMatrix4fv(env.shader.ploc, 1, GL_FALSE, env.sim.projection.m);

		/*	Draw our rectangle using the shader program */
		glBindVertexArray(env.buffer.VAO);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0); // 36 is num of indices
		glBindVertexArray(0);

		/*	Swap the screen buffers (to display on screen the computed image) */
		glfwSwapBuffers(env.win.ptr);
	}
	clean_glfw(&env);
	return (0);
}
