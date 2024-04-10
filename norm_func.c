#include "pipex.h"

void    split_matrix_failed(t_pipex *pipex, char **split_cmd)
{
    free_split_line(split_cmd);
	close_fds_in_parent_proces(pipex);
	//free(pipex->fd);
	exit(1);
}

void    join_failed(t_pipex *pipex, char **split_cmd, char **matrix)
{
    free_split_line(split_cmd);
	free_split_line(matrix);
    close_fds_in_parent_proces(pipex);
	//free(pipex->fd);
	write(2, "JOIN was failed\n", 16);
	exit(1);
}

void	cannot_found_cmd(t_pipex *pipex, char **split_cmd, char **matrix, char *arr)
{
	free_split_line(split_cmd);
	free_split_line(matrix);
	close_fds_in_parent_proces(pipex);
	//free(pipex->fd);
	printf_str(arr);
	write(2, "command not found\n", 18);
	exit(1);
}

void	printf_str(char *arr)
{
	int	i;

	i = 0;
	printf("arr=%s\n", arr);
	while (arr[i])
	{
		write(2, &arr[i], 1);
		i++;
	}
	write(2, ": ", 2);
}