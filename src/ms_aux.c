/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_aux.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ullorent <ullorent@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 13:58:31 by ullorent          #+#    #+#             */
/*   Updated: 2022/03/17 14:38:04 by ullorent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pass(char *str)
{
	int	i;

	i = 0;
	while (str)
	{
		if (str[i] != ' ')
			break ;
		i++;
	}
	return (i);
}

int	ft_pass_2(char *str, char c)
{
	int	i;

	i = 0;
	while (str)
	{
		if (str[i] == c)
			break ;
		i++;
	}
	return (i);
}

int	ft_pass_3(char *str)
{
	int	i;

	i = 0;
	while (ft_isalpha(str[i]) || str[i] == '-')
		i++;
	return (i);
}
