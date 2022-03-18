/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_input.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 13:42:55 by ullorent          #+#    #+#             */
/*   Updated: 2022/03/18 14:20:07 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_input_4(char *str, t_data *data, int index)
{
	int	i;
	int	j;
	int	in;
	int	out;

	i = 0;
	in = 0;
	out = 0;
	while (str[i] && str[i] != '|')
	{
		i += ft_pass(str + i);
		if (str[i] == '\"' || str[i] == '\'')
		{
			j = i;
			i += ft_pass_2(str + i, str[i]);
			ft_substr(str, j, i - j);
		}
		else if (str[i] == '<')
		{
			j = i;
			if (str[i + 1] == '<')
			{
				data->in_modes[index][in] = 1;
				i++;
			}
			else
				data->in_modes[index][in] = 0;
			i++;
			in++;
			j = i;
			i += ft_pass_3(str + i);
			ft_substr(str, j, i - j);
		}
		else if (str[i] == '>')
		{
			j = i;
			if (str[i + 1] == '>')
			{
				data->out_modes[index][out] = 1;
				i++;
			}
			else
				data->out_modes[index][out] = 0;
			i++;
			out++;
			j = i;
			i += ft_pass_3(str + i);
			ft_substr(str, j, i - j);
		}
		else
		{
			i += ft_pass_3(str + i);
		}
		i++;
	}
}

void	ft_input_in(char *str, t_data *data, int index, int k)
{
	int	i;
	int	j;

	i = 0;
	while (str[i] && str[i] != '|')
	{
		i += ft_pass(str + i);
		if (str[i] == '\"' || str[i] == '\'')
		{
			j = i;
			i += ft_pass_2(str + i, str[i]);
		}
		else if (str[i] == '<' || str[i] == '>')
			i++;
		else
		{
			j = i;
			i += ft_pass_3(str + i);
			data->cmd[index][k] = ft_substr(str, j, i - j);
			k++;
		}
		i++;
	}
}

void	ft_input_cmd(char *str, t_data *data, int index, int k)
{
	int	i;
	int	j;

	i = 0;
	while (str[i] && str[i] != '|')
	{
		i += ft_pass(str + i);
		if (str[i] == '<' || str[i] == '>')
		{
			if (str[i + 1] == '<')
				i++;
			i++;
			i += ft_pass_3(str + i);
		}
		else if (str != '|')
		{
			j = i;
			if (str[i] == '\"' || str[i] == '\'')
				i += ft_pass_2(str + i, str[i]);
			i += ft_pass_3(str + i);
			data->cmd[index][k] = ft_substr(str, j, i - j);
			k++;
		}
	}
}

static int	ft_input_3(char *str, t_data *data, int index)
{
	int	i;
	int	infile;
	int	outfile;
	int	cmd;

	i = 0;
	infile = 0;
	outfile = 0;
	cmd = 0;
	while (str[i] && str[i] != '|')
	{
		i += ft_pass(str + i);
		if (str[i] == '<')
			i += ft_case(str, i, &cmd, &infile);
		else
			i += ft_case(str, i, &cmd, &outfile);
	}
	ft_allocate_2(data, index, infile, outfile);
	ft_allocate_3(data, index, cmd);
	//printf("infile = %d\noutfile = %d\ncmd = %d\n", infile, outfile, cmd);
	return (i);
}

void	ft_input(char *str, t_data *data)
{
	int	i;
	int	index;
	int	pipes;

	i = 0;
	pipes = 0;
	while (str[i] != '\0')
	{
		i += ft_pass(str + i);
		if (str[i] == '\"' || str[i] == '\'')
			i += ft_pass_2(str + 1, str[i]);
		if (str[i] == '|')
			pipes++;
		i++;
	}
	data->pipes = pipes;
	data->cmd = malloc((pipes + 2) * sizeof(char **));
	data->cmd[pipes + 1] = NULL;
	data->infile = malloc((pipes + 2) * sizeof(char **));
	data->infile[pipes + 1] = NULL;
	data->in_modes = malloc((pipes + 2) * sizeof(int *));
	data->outfile = malloc((pipes + 2) * sizeof(char **));
	data->out_modes = malloc((pipes + 2) * sizeof(int *));
	data->outfile[pipes + 1] = NULL;
	printf("pipes= %d\n", pipes);
	i = 0;
	index = 0;
	while (i < data->pipes + 1)
	{
		index = ft_input_2(str + index, data, i);
		ft_input3(str, data, i);
		index++;
		i++;
	}
}

void	ft_input_2(t_data *data)
{
	int	i;
	int	index;
	int	hold;

	i = 0;
	index = 0;
	while (i < data->pipes + 1)
	{
		hold = ft_input_2(str + index, data, i);
		ft_input_cmd(str + index, data, i);
		ft_input_in(str + index, data, i);
		ft_input_out(str + index, data, i);
		index = hold + 1;
		i++;
	}
	ft_input_3()
}

void	ft_input(char *str, t_data *data)
{
	int	i;
	int	index;
	int	pipes;

	i = 0;
	pipes = 0;
	while (str[i] != '\0')
	{
		i += ft_pass(str + i);
		if (str[i] == '\"' || str[i] == '\'')
			i += ft_pass_2(str + 1, str[i]);
		if (str[i] == '|')
			pipes++;
		i++;
	}
	ft_allocate(data, pipes);
	ft_input_2(t_data);
}
