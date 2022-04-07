/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 13:20:32 by ullorent          #+#    #+#             */
/*   Updated: 2022/04/07 12:49:12 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_ms(char *s, char c)
{
	int	i;
	int	j;
	int	k;

	k = 0;
	i = 1;
	j = 0;
	c = 0;
	while (s[k] != '\0')
	{
		if (s[k] == '\'' || s[k] == '\"')
			k += ft_pass_2(s + k, s[k]);
		if (s[k] == '|')
			i++;
		if (s[k] != '\0')
			k++;
	}
	return (i);
}

void	ft_bridge(char *str, t_data *data, int i, int j)
{
	int	index;
	int	r;

	r = 0;
	while (j < count_ms(str, '|'))
	{
		if ((str[i] == '\'' || str[i] == '\"') && r == 1)
				i += ft_pass_2(str + i, str[i]);
		else if (str[i] != '|' && r == 0)
		{
			index = i;
			r = 1;
			if (str[i] == '\'' || str[i] == '\"')
				i += ft_pass_2(str + i, str[i]);
		}
		else if ((str[i] == '|' || str[i] == '\0') && r == 1)
		{
			ft_process(ft_substr(str, index, (i - index)), data, str[i]);
			r = 0;
			j++;
		}
		if (str[i] != '\0' && str[i] != '|')
			i++;
	}
}

int	main(int argc, char *argv[], char *env[])
{
	char	*str;
	t_data	data;

	(void)argc;
	(void)argv;
	data.env = ft_dup_2d(env);
	data.path = ft_split(getenv("PATH"), ':');
	while (1)
	{
		str = readline("bashie > ");
		//printf("[%s]", str);
		if (str == NULL || str[0] == '\0')
		{
			printf("estoy liberandome");
			free (str);
			continue ;
		}
		ft_bridge(str, &data, 0, 0);
		ft_close_pipes(&data);
		free (str);
	}
	ft_freeo(data.env, 1);
	return (0);
}
