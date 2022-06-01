/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_checker.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ullorent <ullorent@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 13:22:20 by ecamara           #+#    #+#             */
/*   Updated: 2022/06/01 12:44:50 by ullorent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_checker(char *str, t_data *data)
{
	int	c;
	int	i;

	c = 0;
	i = 0;
	while (str[c])
	{
		if (str[c] && (str[c] == '|' && str[c + 1] == '|'))
		{
			printf("bashie: input error: '%s'\n", str);
			data->status = 258;
			return (1);
		}
		if (str[c] && (str[c] == '<' || str[c] == '>'))
			i++;
		if (i == 3)
		{
			printf("bashie: input error: '%s'\n", str);
			data->status = 258;
			return (1);
		}
		c++;
	}
	if (ft_inout_check(str, data))
		return (1);
	return (0);
}

int	ft_inout_check(char *str, t_data *data)
{
	int	c;
	int	i;

	c = 0;
	i = 0;
	while (str[c])
	{
		if (!ft_strncmp(&str[c], ">>", 3) || !ft_strncmp(&str[c], ">", 2)
			|| !ft_strncmp(&str[c], "<", 2) || !ft_strncmp(&str[c], "<<", 2))
		{
			printf("bashie: syntax error near unexpected token `newline'\n");
			data->status = 258;
			return (1);
		}
		c++;
	}
	return (0);
}
