/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_checker2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 09:11:33 by ullorent          #+#    #+#             */
/*   Updated: 2022/06/13 10:34:45 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
/*
int	ft_inout_check(char *str, t_data *data)
{
	int	i;
	int	error;

	error = 0;
	i = 0;
	while (str[i])
	{
		i = ft_inout_check1(str, i);
		if (str[i] == '\"' || str[i] == '\'' || ft_pass_3(str + i))
		{
			i = ft_inout_check2(str, i);
			error = 2;
		}
		else
		{
			if (ft_inout_check3(str, i, error, data))
				return (1);
			error = ft_inout_check3(str, i, error, data);
		}
		if (ft_inout_check3(str, i, error, data))
			return (1);
	}
	return (0);
}

int	ft_inout_check1(char *str, int i)
{
	if (ft_pass(str + i))
		i += ft_pass(str + i);
	else if (str[i] == '<' || str[i] == '>')
		i += ft_pass_6(str + i, str[i]);
	return (i);
}

int	ft_inout_check2(char *str, int i)
{
	if (str[i] == '\"' || str[i] == '\'')
		i += ft_pass_2(str + i, str[i]);
	else if (ft_pass_3(str + i))
		i += ft_pass_3(str + i);
	return (i);
}

int	ft_inout_check3(char *str, int i, int error, t_data *data)
{
	if ((str[i] == '|' || str[i] == '\0') && error == 0)
	{
		printf("bashie: syntax error near unexpected token `newline'\n");
		data->status = 258;
		return (1);
	}
	error = 0;
	if (str[i] != '\0')
		i++;
	return (error);
}
*/
/*
int	ft_inout_check(char *str, t_data *data, int i, int error)
{
	while (str[i])
	{
		if (ft_pass(str + i))
			i += ft_pass(str + i);
		else if (str[i] == '<' || str[i] == '>')
			i += ft_pass_6(str + i, str[i]);
		else if (str[i] == '\"' || str[i] == '\'')
		{
			i += ft_pass_2(str + i, str[i]);
			error = 2;
		}
		else if (ft_pass_3(str + i))
		{
			i += ft_pass_3(str + i);
			error = 2;
		}
		else
		{
			if ((str[i] == '|' || str[i] == '\0') && error == 0)
			{
				printf("bashie: syntax error near unexpected token `newline'\n");
				data->status = 258;
				return (1);
			}
			error = 0;
			if (str[i] != '\0')
				i++;
		}
		if ((str[i] == '|' || str[i] == '\0') && error == 0)
		{
			printf("bashie: syntax error near unexpected token `newline'\n");
			data->status = 258;
			return (1);
		}
	}
	return (0);
}*/

int	ft_check2(char *str, int *error, int *i)
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

int	ft_inout_check(char *str, t_data *data, int i, int error)//0 0 
{
	while (str[i])
	{
		
		if (ft_check2(str, &error, &i))
		{
			if ((str[i] == '|' || str[i] == '\0' || str[i] == '>' || str[i] == '<') && error == 0)
			{
				printf("bashie: syntax error near unexpected token `newline'\n");
				data->status = 258;
				return (1);
			}
			error = 0;
			if (str[i] != '\0')
				i++;
		}
		if ((str[i] == '|' || str[i] == '\0' || str[i] == '>' || str[i] == '<') && error == 0)
		{
			printf("bashie: syntax error near unexpected token `newline'\n");
			data->status = 258;
			return (1);
		}
	}
	return (0);
}