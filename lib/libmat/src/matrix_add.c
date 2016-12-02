/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_add.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwatkins <wwatkins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 17:13:11 by wwatkins          #+#    #+#             */
/*   Updated: 2016/12/02 12:48:59 by wwatkins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmat.h"

t_mat	matrix_add(t_mat *A, t_mat *B)
{
	int		h;
	int		w;

	if (A->size_h != B->size_h || A->size_w != B->size_w)
		matrix_error(EXIT, MATRIX_ADDITION_ERR);
	h = 0;
	while (h < A->size_h * A->size_w)
	{
		w = -1;
		while (++w < A->size_w)
			A->data[h + w] += B->data[h + w];
		h += A->size_w;
	}
	return (*A);
}