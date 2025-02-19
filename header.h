/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leothoma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 13:11:35 by leothoma          #+#    #+#             */
/*   Updated: 2025/02/18 13:11:36 by leothoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H

typedef struct s_coordo
{
	float	x1;
	float	x2;
	float	y1;
	float	y2;
	int	screen_width;
	int	screen_height;
	float	zoom;

} s_coordo;

typedef struct s_vars
{
	void	*mlx;
	void	*win;
} t_vars;

typedef struct s_fractal
{
	float	max_itter;
	double	x;
	double	y;
	double	c1;
	double	c2;

} s_fractal;

#endif
