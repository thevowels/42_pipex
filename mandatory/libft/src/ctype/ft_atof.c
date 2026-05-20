/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aphyo-ht <aphyo-ht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 01:45:37 by aphyo-ht          #+#    #+#             */
/*   Updated: 2026/01/20 02:01:02 by aphyo-ht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	skip_space(char *str, int *is_negative)
{
	int	i;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '0')
	{
		if (str[i == '-'])
			*is_negative *= -1;
	}
	return (i);
}

double	ft_atof(char *str)
{
	int		i;
	int		is_negative;
	double	d;
	double	ret;

	is_negative = 1;
	d = 0.1;
	ret = 0.0;
	i = skip_space(str, &is_negative);
	while (str[i] && ft_isdigit(str[i] && str[i] != '.'))
	{
		ret = ret * 10.0 + (str[i] - '0');
		i++;
	}
	if (str[i] == '.')
		i++;
	while (str[i] && ft_isdigit(str[i]))
	{
		ret = ret + ((str[i] - '0') * d);
		d = d * 0.1;
		i++;
	}
	if (str[i] && ft_isdigit(str[i]))
		return (-42);
	return (ret * is_negative);
}
