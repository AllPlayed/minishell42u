/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_checker2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ullorent <ullorent@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 09:11:33 by ullorent          #+#    #+#             */
/*   Updated: 2022/06/13 10:55:54 by ullorent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_inout_check2(char *str, int *error, int *i)
{
	if (ft_pass(str + (*i)))
		(*i) += ft_pass(str + (*i));
	else if (str[(*i)] == '<' || str[(*i)] == '>')
		(*i) += ft_pass_6(str + (*i), str[(*i)]);
	else if (str[(*i)] == '\"' || str[(*i)] == '\'')
	{
		(*i) += ft_pass_2(str + (*i), str[(*i)]);
		*error = 2;
	}
	else if (ft_pass_3(str + (*i)))
	{
		(*i) += ft_pass_3(str + (*i));
		*error = 2;
	}
	else
		return (1);
	return (0);
}

int	ft_inout_check(char *str, t_data *data, int i, int error)
{
	while (str[i])
	{
		if (ft_inout_check2(str, &error, &i))
		{
			if ((str[i] == '|' || str[i] == '\0'
					|| str[i] == '>' || str[i] == '<') && error == 0)
			{
				printf("bashie: syntax error near unexpected token `newline'\n");
				data->status = 258;
				return (1);
			}
			error = 0;
			if (str[i] != '\0')
				i++;
		}
		if ((str[i] == '|' || str[i] == '\0'
				|| str[i] == '>' || str[i] == '<') && error == 0)
		{
			printf("bashie: syntax error near unexpected token `newline'\n");
			data->status = 258;
			return (1);
		}
	}
	return (0);
}
