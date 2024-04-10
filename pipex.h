#ifndef PIPEX_H
# define PIPEX_H

#  define MIN_ARGC 5
#  define SPLIT_ERR 4
#  define EXECVE_ERR 3
#  define JOIN_ERR 2
#  define ACCESS_ERR 6
#  define DUP2 8
#  define FD1 9
#  define FD_OUT 10

#include <fcntl.h>
#include <unistd.h>
#include<stdio.h>
#include<stdlib.h>

typedef struct s_pipex
{
	int	(*fd)[2];
	int	cmd_count;
	int	current_cmd;
	int	pid;
}   t_pipex;

void    pipe_function(char **argv, char **envp, t_pipex *pipex);
void fork_function(char **argv, char **envp, t_pipex *pipex);
void	wait_function(t_pipex *pipex);
void fork_for_1st_cmd(char **argv, char **envp, t_pipex *pipex, int i);
void fork_for_middle_cmds(char **argv, char **envp, t_pipex *pipex, int i);
void fork_for_last_cmd(char **argv, char **envp, t_pipex *pipex, int i);
char    *ft_strstr(char *str, char *to_find);
int	found_which_line_was_start_with_path(char **envp, t_pipex *pipex);
char *check_if_cmd_is_X_OK(char *envpi, char **split_cmd, t_pipex *pipex);
void	close_fds_1st_cmd(t_pipex *pipex);
void	close_fds_mid_cmds(t_pipex *pipex);
void	close_fds_last_cmd(t_pipex *pipex);
void	close_fds_in_parent_proces(t_pipex *pipex);
void    split_matrix_failed(t_pipex *pipex, char **split_cmd);
void    join_failed(t_pipex *pipex, char **split_cmd, char **matrix);
void	cannot_found_cmd(t_pipex *pipex, char **split_cmd, char **matrix, char *arr);
char	**ft_split(char const *s, char c);
void    perror_exit(int err_num, t_pipex *pipex, char **split_cmd, char *path_plus_cmd);
void    free_split_cmd_and_path(char **split_cmd, char *path_plus_cmd);
void    free_split_line(char **matrix);
char	*ft_strjoin(const char *s1, const char *s2);
void	ft_strncpy(char *dest, const char *src, unsigned int n);
void	printf_str(char *arr);

#endif