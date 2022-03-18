/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ullorent <ullorent@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 13:21:46 by ullorent          #+#    #+#             */
/*   Updated: 2022/03/18 13:18:44 by ullorent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <dirent.h>
# include <sys/types.h>
# include <signal.h>
# include <stdio.h>
# include <sys/wait.h>
# include <sys/types.h>
# include "libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_data
{
	char	***cmd;
	char	***infile;
	char	***outfile;
	int		**in_modes;
	int		**out_modes;
	int		pipes;
}	t_data;

/* -------- INPUT -------- */

void	ft_input(char *str, t_data *data);

/* -------- AUX -------- */

int		ft_pass(char *str);
int		ft_pass_2(char *str, char c);
int		ft_pass_3(char *str);

/* -------- FREE --------- */

void	ft_free_data(t_data *data);

#endif