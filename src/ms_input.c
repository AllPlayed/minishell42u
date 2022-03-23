/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_input.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 13:42:55 by ullorent          #+#    #+#             */
/*   Updated: 2022/03/23 16:56:36 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_input_in(char *str, t_data *data, int k)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		i += ft_main_pass(str + i, i, 7);
		if (str[i] == '<')
		{
			i++;
			if (str[i] == '<')
			{
				data->infile.modes[k] = 1;
				i++;
			}
			else
				data->infile.modes[k] = 0;
			i += ft_pass(str + i);
			j = i;
			i += ft_pass_3(str + i);
			data->infile.files[k] = ft_substr(str, j, i - j);
			k++;
		}
		if (str[i] && (str[i] == ' ' || str[i] == '>' || str[i] == '\''|| str[i] == '\"'))
			i++;
	}
}

void	ft_input_out(char *str, t_data *data, int k)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		i += ft_main_pass(str + i, i, 7);
		if (str[i] == '>')
		{
			i++;
			if (str[i] == '>')
			{
				data->outfile.modes[k] = 1;
				i++;
			}
			else
				data->outfile.modes[k] = 0;
			i += ft_pass(str + i);
			j = i;
			i += ft_pass_3(str + i);
			data->outfile.files[k] = ft_substr(str, j, i - j);
			k++;
		}
		if (str[i] && (str[i] == ' ' || str[i] == '<'|| str[i] == '\''|| str[i] == '\"'))
			i++;
	}
}

void	ft_input_cmd(char *str, t_data *data, int k)
{
	int	i;
	int	j;

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
			i += ft_pass_3(str + i);
		}
		else
		{
			j = i;
			if (str[i] == '\"' || str[i] == '\'')
				i += ft_pass_2(str + i, str[i]);
			else
				i += ft_pass_3(str + i);
			data->cmd[k] = ft_substr(str, j, i - j);
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
	printf("str = [%s]\n", str);
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
	printf("CMD = %d INFILE = %d OUTFILE = %d\n", cmd, infile, outfile);
	ft_allocate(data, infile, outfile, cmd);
	printf("1\n");
	ft_input_cmd(str, data, 0);
	printf("2\n");
	ft_input_in(str, data, 0);
	printf("3\n");
	ft_input_out(str, data, 0);
	printf("4\n");
}
