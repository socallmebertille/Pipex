/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 13:56:26 by saberton          #+#    #+#             */
/*   Updated: 2024/09/20 16:47:20 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../includes/pipex.h"
# include <fcntl.h>
# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_pipe
{
	int	infile;
	int	outfile;
	int	fd[2];
}		t_pipe;

void	exec(char **path, char **envp, char *av);
void	child_bonus(char **av, char **envp, int i);
void	parent_bonus(char **av, char **envp, int ac);
void	ft_free(char **path, char **cmd, char *tmp);
void	free_and_exit(char **path, char **cmd, char *tmp);
void	error_exit(int *fds, char *av, char **path);
int		open_file(char *av, int id);
size_t	ft_strlen(const char *s);
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*ft_strdup(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*valid_cmd(char **path, char *cmd, char *tmp);
char	**ft_split(char const *s, char c);
char	**recup_path(char **envp);

// void	exec_command(char **av, t_pipe *pipe_info, char **envp, int cmd_idx);
// void	child_bonus(char **av, t_pipe *pipe_info, char **envp, int cmd_idx);
// void	parent_bonus(char **av, t_pipe *pipe_info, char **envp, int ac);
// void	run_pipeline(char **av, char **envp, int ac, int infile);

#endif