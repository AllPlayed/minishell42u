/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_aux.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 13:58:31 by ullorent          #+#    #+#             */
/*   Updated: 2022/06/06 13:13:02 by ecamara          ###   ########.fr       */
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

int	ft_main_pass(char *str, int i, int comb)
{
	int	boo;

	boo = 1;
	while (str[i] && boo)
	{
		boo = 0;
		if (comb == 1 || comb == 3 || comb == 5 || comb == 7)
		{
			boo = ft_pass(str + i);
			i += boo;
		}
		else if ((comb == 2 || comb == 3 || comb == 6 || comb == 7)
			&& (str[i] == '\'' || str[i] == '\"'))
		{			
			boo = ft_pass_2(str + i, str[i]);
			i += boo;
		}
		else if (comb == 3 || comb == 5 || comb == 6 || comb == 7)
		{
			boo = ft_pass_3(str + i);
			i += boo;
		}
	}
	return (i);
}

void	ft_print_data(t_data *data)
{
	int	i;

	i = 0;
	printf("---------CMD--------\n");
	while (data->cmd[i])
	{
		printf("[%d]cmd = [%s]\n", i, data->cmd[i]);
		i++;
	}
	i = 0;
	printf("---------INPUT--------\n");
	while (data->infile.files[i])
	{
		printf("[%d]infile = [%s]\n", i, data->infile.files[i]);
		i++;
	}
	i = 0;
	printf("---------output--------\n");
	while (data->outfile.files[i])
	{
		printf("[%d]outfile = [%s]\n", i, data->outfile.files[i]);
		i++;
	}
}

void	ft_print_fd(int fd)
{
	char	str[1000];

	read(fd, str, 999);
}
