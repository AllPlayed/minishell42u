/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_checker.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ullorent <ullorent@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 13:22:20 by ecamara           #+#    #+#             */
/*   Updated: 2022/05/18 18:01:30 by ullorent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_checker(char *str)
{
	int	i;
	char hold;

	i = 0;
	i += ft_pass(str + i);
	if (str[i] == '|')
		ft_error(2);
	while (str[i])
	{
		i += ft_pass(str + i);
		if (str[i] == '\'' || str[i] == '\"')
		{
			if (str[ft_pass(str + i, str[i]] != str[i])
				ft_error(1);
			else
				i += ft_pass(str + i, str[i]);
		else if ()
	}
	
}
