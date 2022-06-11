/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_checker.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ullorent <ullorent@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 13:22:20 by ecamara           #+#    #+#             */
/*   Updated: 2022/06/11 14:26:47 by ullorent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_checker(char *str, t_data *data)
{
	if (ft_void_checker(str))
		return (1);
	printf("aaa\n");
	if (ft_pipe_inout_checker(str, data))
		return (1);
	printf("bbb\n");
	if (ft_inout_check(str, data))
		return (1);
	printf("ccc\n");
	if (ft_pipe_check(str, data))
		return (1);
	printf("ddd\n");
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
{/*
	int	c;
	int	i;
	int	check;

	c = 0;
	i = 0;
	check = 1;
	while (str[c])
	{
		printf("[%d]\n", c);
		if (ft_pass(str + c))
			c += ft_pass(str + c);
		else if (str[c] == '\'' || str[c] == '\"')
		{
			check = 0;
			c += ft_pass_2(str + c, str[c]);
		}
		else if (str[c] == '<' || str[c] == '>')
		{
			c += ft_pass_6(str + c, str[c]);
			c += ft_pass(str + c);
			printf("[%d] [%c] [%d]\n", c, str[c], check);
			if ((str[c] == '|' || str[c] == '\0') && check != 0)
			{
				printf("bashie: syntax error near unexpected token `newline'\n");
				data->status = 258;
				return (1);
			}
			c++;
			check = 0;
		}
		else
		{
			check = 0;
			c++;
		}
		
	}
	return (0);*/

	int	i;
	int	error;

	i = 0;
	error = 0;
	while (str[i])
	{
		if ((str[c] == '|' || str[i] == '\0') && error)
		{
			printf("bashie: syntax error near unexpected token `newline'\n");
			data->status = 258;
			return (1);
		}
		else
		{
			if (str[c] == '\'' || str[c] == '\"')
				c += ft_pass_2(str + c, str[c]);
			else if (str[c] == '<' || str[c] == '>')
			{
				c += ft_pass_6(str + c, str[c]);
				c += ft_pass(str + c);
				check = 1;
			}
			else if ()
			{
				
			}
		}
	}
	return (0);
}

int	ft_pipe_check(char *str, t_data *data)
{
	int	c;

	c = 0;
	//printf("[%s]\n", str);
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
