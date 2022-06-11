/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_checker.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ullorent <ullorent@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 13:22:20 by ecamara           #+#    #+#             */
/*   Updated: 2022/06/11 15:09:22 by ullorent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_checker(char *str, t_data *data)
{
	if (ft_void_checker(str))
		return (1);
	if (ft_pipe_inout_checker(str, data))
		return (1);
	if (ft_inout_check(str, data))
		return (1);
	if (ft_pipe_check(str, data))
		return (1);
	if (ft_quotes_checker(str, data))
		return (1);
	return (0);
}

int	ft_pipe_inout_checker(char *str, t_data *data)
{
	int	c;
	int	i;

	c = 0;
	i = 0;
	while (str[c])
	{
		if (str[c] == '\'' || str[c] == '\"')
			c += ft_pass_2(str + c, str[c]);
		else if (str[c] == '<' || str[c] == '>')
		{
			i = ft_pass_6(str + c, str[c]);
			if (i == 3)
			{
				printf("bashie: input error: '%s'\n", str);
				data->status = 258;
				return (1);
			}
			c++;
		}
		else if (str[c] != '\0')
			c++;
	}
	return (0);
}

int	ft_void_checker(char *str)
{
	int	c;

	c = 0;
	while (str[c] && str[c] == ' ')
		c++;
	if (str[c] == '\0')
		return (1);
	return (0);
}

int	ft_inout_check(char *str, t_data *data)
{
	int	i;
	int	error;

	error = 0;
	i = 0;
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
}

int	ft_pipe_check(char *str, t_data *data)
{
	int	c;

	c = 0;
	while (str[c])
	{
		if (str[c] == '|')
		{
			c += ft_pass(str + c + 1) + 1;
			if (str[c] == '\0')
			{
				printf("bashie: pipes error\n");
				data->status = 258;
				return (1);
			}
			else if (str[c] == '|')
			{
				printf("bashie: syntax error near unexpected token: '%s'\n", str);
				data->status = 258;
				return (1);
			}
		}
		else
			c++;
	}
	return (0);
}

int	ft_quotes_checker(char *str, t_data *data)
{
	int	c;
	int	i;

	i = 0;
	c = 0;
	while (str[c])
	{
		if (str[c] == '\'' || str[c] == '\"')
		{
			i = ft_pass_7(str + c, str[c]);
			if (i == -1)
			{
				printf("bashie: quote its not correctly closed\n");
				data->status = 258;
				return (1);
			}
			c += i;
		}
		c++;
	}
	return (0);
}

int	ft_pass_6(char *str, char c)
{
	int	i;

	i = 1;
	while (str[i] != '\0')
	{
		if (str[i] != c)
			break ;
		i++;
	}
	return (i);
}


int	ft_pass_7(char *str, char c)
{
	int	i;

	i = 1;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}
