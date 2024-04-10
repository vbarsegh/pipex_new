#include "pipex.h"

char    *ft_strstr(char *str, char *to_find)
{
    int        i;
    int        j;

    i = 0;
    if (*to_find == '\0')
        return (str);
    while (str[i] != '\0')
    {
        j = 0;
        while (to_find[j] != '\0' && str[i + j] == to_find[j])
        {
            if (to_find[j + 1] == 0)
                return (&str[i]);
            j++;
        }
        i++;
    }
    return (0);
}


int	found_which_line_was_start_with_path(char **envp, t_pipex *pipex)
{
	int	i;

	i = 0;
	while(envp[i])
	{
		if (ft_strstr(envp[i], "PATH="))
			break;
		i++;
	}
	if (!envp[i])
	{
		close_fds_in_parent_proces(pipex);
		exit(write(2, "Cannot found PATH= in envp\n", 27));
	}
	return (i);
}

char *check_if_cmd_is_X_OK(char *envpi, char **split_cmd, t_pipex *pipex)
{
	char *cmd;
	char **matrix;
	int  i;
	char *arr;

	arr = split_cmd[0];
	printf("ee%s\n",arr);
	matrix = ft_split(envpi + 5, ':');
	if(!matrix)
		split_matrix_failed(pipex, split_cmd);
	cmd = arr;
	if (access(cmd, X_OK) != -1)
	    return(cmd);//esi en depqna vor pathov tvac ylni cmd-@
	i = 0;
	while(matrix[i])
	{
	    cmd = ft_strjoin(matrix[i++], arr);
	    if (!cmd)
		    join_failed(pipex, split_cmd, matrix);
	    if (access(cmd,X_OK) != -1)
		    break;
	    free(cmd);
	}
	//perror_exit(ACCESS_ERR, pipex)
	if (!matrix[i])
	{

		cannot_found_cmd(pipex, split_cmd, matrix, "serrrr");
	}
	return (cmd);
}
