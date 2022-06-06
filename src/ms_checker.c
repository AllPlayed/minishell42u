/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_checker.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ullorent <ullorent@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 13:22:20 by ecamara           #+#    #+#             */
/*   Updated: 2022/06/06 15:17:09 by ullorent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_checker(char *str, t_data *data)
{
	if (ft_void_checker(str))
		return (1);
	// else if (ft_pipe_inout_checker(str, data))
	// 	return (1);
	// else if (ft_inout_check(str, data))
	// 	return (1);
	else if (ft_pipe_check(str, data))
		return (1);
	else if (ft_quotes_checker(str, data))
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

int	ft_pipe_check(char *str, t_data *data)
{
	int	c;

	c = 0;
	while (str[c] && str[c] == ' ')
		c++;
	if (str[c] == '|')
	{
		printf("bashie: syntax error near unexpected token `|'\n");
		data->status = 258;
		return (1);
	}
	c = 0;
	while (str[c])
	{
		if (str[c] == '|' && str[c + 1] == '\0')
		{
			printf("bashie: syntax error near unexpected token `|'\n");
			data->status = 258;
			return (1);
		}
		c++;
	}
	return (0);
}

int	ft_quotes_checker(char *str, t_data *data)
{
	int	c;

	c = 0;
	while (str[c])
	{
		if (str[c] == '\'' || str[c] == '\"')
		{
			c += ft_pass_6(str + c, str[c]);
			if (str[c] == '\0')
			{
				printf("bashie: quote its not correctly closed\n");
				data->status = 258;
				return (1);
			}
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
		if (str[i] == c)
			break ;
		i++;
	}
	return (i);
}
