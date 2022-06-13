/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ullorent <ullorent@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 13:21:46 by ullorent          #+#    #+#             */
/*   Updated: 2022/06/13 10:15:26 by ullorent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <dirent.h>
# include <sys/types.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/types.h>
# include "libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

int	g_child;

typedef struct s_file
{
	int		*modes;
	char	**files;
}t_file;

typedef struct s_data
{
	char	**o_env;
	char	*str;
	char	**cmd;
	char	**env;
	char	**path;
	t_file	infile;
	t_file	outfile;
	int		inpipe;
	int		outpipe;
	int		fd2[2];
	int		cmd_n;
	int		infile_n;
	int		outfile_n;
	int		status;
	int		stdin;
	int		stdout;
}t_data;

void	ft_minishell(t_data *data);
char	*ft_spacesremover(char *str, int frnt, int bck, int fill);

void	minishell(t_data *data);
void	sighandler(int signal, siginfo_t *a, void *b);
void	ft_new_line(void);
void	ft_bridge(t_data *data, int i, int j, int r);
char	*ft_spacesremover(char *str, int frnt, int bck, int fill);

/* -------- INPUT -------- */

void	ft_input_type(char *str, t_data *data, int k, int boo);
void	ft_input_cmd(char *str, t_data *data, int k);
void	ft_input(char *str, t_data *data, int infile, int outfile);
void	ft_expansion(char **str, t_data *data, int n, int i);
char	*ft_dollar_v2(char *str, t_data *data);
void	ft_expand2(char *str, t_data *data, int *i, char **temp2);

/* --------- AUX ---------- */

int		ft_pass(char *str);
int		ft_pass_2(char *str, char c);
int		ft_pass_3(char *str);
int		ft_pass_4(char *str);
int		ft_pass_5(char *str);
int		ft_pass_6(char *str, char c);
int		ft_pass_7(char *str, char c);
int		ft_main_pass(char *str, int i, int comb);
void	ft_print_fd(int fd);

/*-------- ALLOCATE -------*/

void	ft_allocate(t_data *data, int infile, int outfile, int cmd);

/* --------- FREE --------- */

void	ft_free_data(t_data *data);
void	ft_freeo(char **list, int boo);

/* ------- INPUT CASES -------*/

int		ft_case(char *str, int i, int *cmd, int *counter);
int		ft_case_1(char *str, int i, int *cmd);
int		ft_case_2(char *str, int i, int *counter);
int		ft_case_3(char *str, int i, int *counter);
int		ft_case_4(char *str, int i, int *cmd);

/* -------- BUILTINS --------- */

int		ft_cmd_cases(t_data *data);

void	ft_echo(t_data *data, int boo);
void	ft_env(t_data *data);
void	ft_cd(t_data *data, int index1, int index2, int boo);
void	ft_pwd(void);
void	ft_exit(t_data *data);

void	ft_unset(t_data *data);
void	ft_export(t_data *data);
void	ft_exitstatus(t_data *data);

/* -------- UTILS ---------*/

char	**ft_dup_2d(char **str);
char	*ft_ms_join(char *str1, char *str2, int len1, int len2);
char	*ft_substr_ms(const char *s, unsigned int start, size_t len);
char	*ft_super_join(char **str);
int		ft_str_compare(char **str1, char *str2);
void	ft_close_builtinpipe(t_data *data);

int		ft_strlen2d(char **str);

/* ------- CHECKER ------- */

int		ft_checker(char *str, t_data *data);

int		ft_inout_simple_check(char *str, t_data *data);
int		ft_inout_check(char *str, t_data *data);
int		ft_inout_check1(char *str, int i);
int		ft_inout_check2(char *str, int i);
int		ft_inout_check3(char *str, int i, int error, t_data *data);
int		ft_pipe_check(char *str, t_data *data);
int		ft_void_check(char *str);
int		ft_quotes_check(char *str, t_data *data);

/* ------- PROCESS -------*/

void	ft_search_cmd(t_data *data);
void	ft_process(char *str, t_data *data, int index, int end);
int		ft_outfile(t_data *data, int i);
void	ft_infile(t_data *data, int i);

/* -------- UNSET EXPORT -----*/

void	ft_unset3(t_data *data, char *str);
int		ft_export_error(t_data *data, char *str);
int		ft_unset_error(t_data *data, char *str);
int		check_unset(t_data *data, char *temp);
int		check_export(t_data *data, char *temp);
void	ft_export(t_data *data);
void	ft_unset2(t_data *data, int index);
void	ft_unset(t_data *data);
int		ft_findequal(char *str);

/* -------- PIPES --------*/

void	ft_close_pipes(t_data *data);
void	ft_start_pipes(t_data *data);
void	ft_mid_pipes(t_data *data);
void	ft_end_pipes(t_data *data);
void	ft_builtinpipe(t_data *data);

/* -------- ERROR --------*/

void	ft_error_child(int w);

#endif