/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwatkins <wwatkins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/06 16:53:07 by wwatkins          #+#    #+#             */
/*   Updated: 2016/12/07 12:39:56 by wwatkins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	print_debug_vertices(t_env *env)
{
	int j;

	j = -1;
	while (++j < env->model.size_vertices / sizeof(GLfloat))
	{
		(j + 1) % 3 == 1 ? printf("( ") : 0;
		printf("%f ", env->model.vertices[j]);
		(j + 1) % 3 == 0 ? printf(")\n") : 0;
	}
}

void	print_debug_indices(t_env *env)
{
	int j;

	j = -1;
	while (++j < env->model.num_indices)
	{
		(j + 1) % 3 == 1 ? printf("( ") : 0;
		printf("%u ", env->model.indices[j]);
		(j + 1) % 3 == 0 ? printf(")\n") : 0;
	}
}

GLfloat	*append_vertices(GLfloat *array, char *line, int length)
{
	int		i;
	int		j;
	char	**tab;
	GLfloat	*new;

	tab = ft_strsplit(&line[1], ' ');
	new = (GLfloat*)malloc(sizeof(GLfloat) * length);
	i = -1;
	while (++i < length - 3)
		new[i] = array[i];
	free(array);
	array = new;
	j = -1;
	while (tab[++j] != NULL)
	{
		array[length - 3 + j] = (GLfloat)ft_atof(tab[j]);
		ft_strdel(&tab[j]);
	}
	ft_strdel(&tab[j]);
	free(tab);
	tab = NULL;
	return (array);
}

GLuint	*append_indices(GLuint *array, char *line, int length)
{
	int		i;
	int		j;
	char	**tab;
	GLuint	*new;

	tab = ft_strsplit(&line[1], ' ');
	new = (GLuint*)malloc(sizeof(GLuint) * length);
	i = -1;
	while (++i < length - 3)
		new[i] = array[i];
	free(array);
	array = new;
	j = -1;
	while (tab[++j] != NULL)
	{
		array[length - 3 + j] = (GLuint)ft_atoi(tab[j]) - 1;
		ft_strdel(&tab[j]);
	}
	ft_strdel(&tab[j]);
	free(tab);
	tab = NULL;
	return (array);
}

// t_vec4	compute_center_axis(GLfloat	*vertices, unsigned int num_vertices)
// {
// 	int		i;
// 	t_vec4	center;
//
// 	i = 0;
// 	while (i < num_vertices - 3)
// 	{
// 		center.x += vertices[i];
// 		center.y += vertices[i + 1];
// 		center.z += vertices[i + 2];
// 		i += 3;
// 	}
// 	center.x /= num_vertices;
// 	center.y /= num_vertices;
// 	center.z /= num_vertices;
// 	center.w = 1;
// 	printf("(%f, %f, %f, %f)\n", center.x, center.y, center.z, center.w);
// 	return (center);
// }

t_vec4	compute_center_axis(GLfloat	*vertices, unsigned int num_vertices)
{
	int		i;
	t_vec4	max;
	t_vec4	min;
	t_vec4	center;

	i = 0;
	max = (t_vec4) {0, 0, 0, 1};
	min = (t_vec4) {0, 0, 0, 1};
	while (i < num_vertices - 3)
	{
		vertices[i] > max.x ? max.x = vertices[i] : 0;
		vertices[i] < min.x ? min.x = vertices[i] : 0;
		vertices[i + 1] > max.y ? max.y = vertices[i + 1] : 0;
		vertices[i + 1] < min.y ? min.y = vertices[i + 1] : 0;
		vertices[i + 2] > max.z ? max.z = vertices[i + 2] : 0;
		vertices[i + 2] < min.z ? min.z = vertices[i + 2] : 0;
		i += 3;
	}
	center = vec3_fmul(vec3_add(min, max), 0.5);
	printf("(%f, %f, %f, %f)\n", center.x, center.y, center.z, center.w);
	return (center);
}

void	parse_obj(t_env *env, char *filename)
{
	int		fd;
	int		v;
	int		f;
	char	*line;

	v = 0;
	f = 0;
	fd = open(filename, O_RDWR);
	while (get_next_line(fd, &line) > 0)
	{
		if (line[0] == 'v' && line[1] == ' ')
		{
			v += 3;
			env->model.vertices = append_vertices(env->model.vertices, line, v);
		}
		else if (line[0] == 'f' && line[1] == ' ')
		{
			f += 3;
			env->model.indices = append_indices(env->model.indices, line, f);
		}
		ft_strdel(&line);
	}
	ft_strdel(&line);
	env->model.size_vertices = v * sizeof(GLfloat);
	env->model.size_indices = f * sizeof(GLuint); // nope
	env->model.num_indices = f; // nope
	env->model.center_axis = compute_center_axis(env->model.vertices, v);
	// print_debug_vertices(env);
	// print_debug_indices(env);
}

void	load_mtl(char *filename)
{

}

void	parse_model(t_env *env)
{
	parse_obj(env, "../resources/teapot.obj");
}