/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_aux.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 13:58:31 by ullorent          #+#    #+#             */
/*   Updated: 2022/03/23 14:09:03 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pass(char *str)
{
	int	i;

	i = 0;
	while (str)
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

	i = 0;
	while (str)
	{
		if (str[i] == c)
			break ;
		i++;
	}
	return (i);
}

int	ft_pass_3(char *str)
{
	int	i;

	i = 0;
	while (ft_isalpha(str[i]) || str[i] == '-')
	{
		//printf("me sumo mas veces\n");
		i++;
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
		printf("[%d]cmd = [%s]\n", i, data->infile.files[i]);
		i++;
	}
	i = 0;
	printf("---------output--------\n");
	while (data->outfile.files[i])
	{
		printf("[%d]cmd = [%s]\n", i, data->outfile.files[i]);
		i++;
	}
}