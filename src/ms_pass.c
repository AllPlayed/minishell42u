/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pass.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ullorent <ullorent@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 13:58:31 by ullorent          #+#    #+#             */
/*   Updated: 2022/06/11 15:06:53 by ullorent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pass(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
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

	i = 1;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			break ;
		i++;
	}
	if (str[i] != '\0')
		i++;
	return (i);
}

int	ft_pass_3(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != ' ' && str[i] != '<'
		&& str[i] != '>' && str[i] != '\"'
		&& str[i] != '\'' && str[i] != '|')
		i++;
	return (i);
}

int	ft_pass_4(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != ' ' && str[i] != '<'
		&& str[i] != '>' && str[i] != '|')
	{
		if (str[i] == '\'' || str[i] == '\"')
			i += ft_pass_2(str + i, str[i]);
		else
			i++;
	}
	return (i);
}

int	ft_pass_5(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != ' ' && str[i] != '<'
		&& str[i] != '>' && str[i] != '\"'
		&& str[i] != '\'' && str[i] != '|'
		&& str[i] != '$')
		i++;
	return (i);
}
