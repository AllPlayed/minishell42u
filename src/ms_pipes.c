/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pipes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 11:51:58 by ecamara           #+#    #+#             */
/*   Updated: 2022/05/18 14:43:44 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_init_pipes(t_data *data)
{
	pipe(data->fd[0]);
	pipe(data->fd[1]);
	//close (data->fd[0][1]);
	//close (data->fd[1][1]);
}

void	ft_start_pipes(t_data *data)
{
	write(2,"start\n",6);
	dup2(data->fd[1][1], STDOUT_FILENO);
	close(data->fd[0][1]);
	//close(data->fd[1][0]);
	//close(data->fd[0][0]);
	close(data->fd[1][1]);
	//write(2,"start\n",6);
}

void	ft_mid_pipes(t_data *data)
{
	write(2,"mid\n",4);
	close(data->fd[1][1]);
	data->fd[0][0] = data->fd[1][0];
	pipe(data->fd[1]);
	dup2(data->fd[0][0], STDIN_FILENO);
	dup2(data->fd[1][1], STDOUT_FILENO);
	//close(data->fd[0][1]);
	//close(data->fd[1][0]);
	//close(data->fd[0][0]);
	//close(data->fd[1][1]);
	write(2,"mid\n",4);
}

void	ft_end_pipes(t_data *data)
{
	(void)data;
	write(2,"end\n",4);
	dup2(2, STDOUT_FILENO);
	close(data->fd[0][1]);
	close(data->fd[1][0]);
	close(data->fd[0][0]);
	close(data->fd[1][1]);
	write(2,"end\n",4);
}

void	ft_close_pipes(t_data *data)
{
	close(data->fd[0][1]);
	close(data->fd[1][0]);
	close(data->fd[0][0]);
	close(data->fd[1][1]);
}
