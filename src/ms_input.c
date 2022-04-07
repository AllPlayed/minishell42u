/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_input.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 13:42:55 by ullorent          #+#    #+#             */
/*   Updated: 2022/04/06 11:32:01 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_input_type_2(char *str, t_file *file, int *k, int boo)
{
	int		j;
	int		i;
	char	c;

	i = 0;
	j = 0;
	c = '<';
	if (boo)
		c = '>';
	if (str[i] == c)
	{
		file->modes[(*k)] = 1;
		i++;
	}
	else
		file->modes[(*k)] = 0;
	i += ft_pass(str + i);
	j = i;
	if (str[i] == '\"' || str[i] == '\'')
		i += ft_pass_2(str + i, str[i]);
	else
		i += ft_pass_3(str + i);
	file->files[(*k)] = ft_substr(str, j, i - j);
	(*k)++;
	return (i);
}

void	ft_input_type(char *str, t_data *data, int k, int boo)
{
	int		i;
	char	c;

	i = 0;
	c = '<';
	if (boo)
		c = '>';
	while (str[i])
	{
		if (str[i] == c)
		{
			if (boo)
				i += ft_input_type_2(str + i + 1, &data->outfile, &k, boo);
			else
				i += ft_input_type_2(str + 1 + i, &data->infile, &k, boo);
		}
		else if (str[i] == '\'' || str[i] == '\"')
			i += ft_pass_2(str + i, str[i]);
		else
			i++;
	}
}

static int	ft_input_cmd_2(char *str, t_data *data, int k)
{
	int	i;

	i = 0;
	if (str[i] == '\"' || str[i] == '\'')
		i += ft_pass_2(str + i, str[i]);
	else
		i += ft_pass_3(str + i);
	data->cmd[k] = ft_substr(str, 0, i);
	return (i);
}

void	ft_input_cmd(char *str, t_data *data, int k)
{
	int	i;

	i = 0;
	while (str[i])
	{
		i += ft_pass(str + i);
		if (str[i] == '<' || str[i] == '>')
		{
			i++;
			if (str[i] == '<' || str[i] == '>')
				i++;
			i += ft_pass(str + i);
			if (str[i] == '\"' || str[i] == '\'')
				i += ft_pass_2(str + i, str[i]);
			else
				i += ft_pass_3(str + i);
		}
		else
		{
			i += ft_input_cmd_2(str + i, data, k);
			k++;
		}
		if (str[i] && str[i] == ' ')
			i++;
	}
}

void	ft_input(char *str, t_data *data)
{
	int	i;
	int	infile;
	int	outfile;
	int	cmd;

	i = 0;
	infile = 0;
	outfile = 0;
	cmd = 0;
	while (str[i])
	{
		i += ft_pass(str + i);
		if (str[i] == '<')
			i = ft_case(str, i, &cmd, &infile);
		else if (str[i])
			i = ft_case(str, i, &cmd, &outfile);
	}
	ft_allocate(data, infile, outfile, cmd);
	ft_input_cmd(str, data, 0);
	ft_input_type(str, data, 0, 1);
	ft_input_type(str, data, 0, 0);
	ft_expansion(data);
	free(str);
}
