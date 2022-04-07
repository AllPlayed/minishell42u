/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pipes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 11:51:58 by ecamara           #+#    #+#             */
/*   Updated: 2022/04/06 13:17:05 by ecamara          ###   ########.fr       */
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

void	ft_close_pipes(t_data *data)
{
	close(data->fd[0][1]);
	close(data->fd[1][0]);
	close(data->fd[0][0]);
	close(data->fd[1][1]);
/*	dup2(1, STDIN_FILENO);
	dup2(0, STDOUT_FILENO);*/
}
