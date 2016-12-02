/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwatkins <wwatkins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 17:01:52 by wwatkins          #+#    #+#             */
/*   Updated: 2016/12/02 18:45:06 by wwatkins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmat.h"

int	main(void)
{
	t_mat	A;
	t_mat	B;
	t_mat	C;

	A = matrix_create(4, 4, 0);
	matrix_set(&A, IDENTITY);
	A.data[1] = 42;
	matrix_print(&A);
	A = matrix_transpose(&A);
	matrix_print(&A);

	return (0);
}
