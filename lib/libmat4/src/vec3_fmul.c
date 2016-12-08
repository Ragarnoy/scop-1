/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_fmul.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwatkins <wwatkins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 11:09:52 by wwatkins          #+#    #+#             */
/*   Updated: 2016/12/08 13:03:38 by wwatkins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmat4.h"

t_vec3 	vec3_fmul(t_vec3 v, float f)
{
	int	i;

	i = -1;
	while (++i < 3)
		v.v[i] *= f;
	return (v);
}
