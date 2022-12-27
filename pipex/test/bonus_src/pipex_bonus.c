#include "../include/pipex_bonus.h"
#include <string.h>

char	*get_vaild_cmd(char **path, char *cmd)
{
	int	i;
	char	*temp_address;
	char	*temp_path;
	char	*temp_cmd;

	i = 0;
	temp_path = NULL;
	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	temp_cmd = ft_strjoin("/", cmd);
	if (!temp_cmd)
		return (0);
	while (path[i])
	{
		temp_address = temp_path;
		temp_path = ft_strjoin(path[i], temp_cmd);
		free (temp_address);
		if (access(temp_path, X_OK) != -1)
			break ;
		i++;
	}
	return (temp_path);
}

void	get_path(t_files *files, char *envp[])
{
	int	i = 0;
	
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH", 4))
		{
			envp[i] += 5;
			break;
		}
		i++;
	}
	files->path = ft_split(envp[i], ':');
}

void	init(t_files *files, int argc, char *argv[], char *envp[])
{
	files->infile = open(argv[1], O_RDONLY);
	files->outfile = open(argv[argc - 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (files->outfile == -1 || files->infile == -1)
		ft_perror();
	files->argc = argc;
	files->proc_cnt = 2;
	if (pipe(files->read_fd) == -1)
		ft_perror();
	get_path(files, envp);
}

void	execute(t_files *files, char *argv[], char *envp[])
{
	files->cmd_options = ft_split(argv[files->proc_cnt], ' ');
	if (!files->cmd_options)
		exit(1);
	files->cmd = get_vaild_cmd(files->path, files->cmd_options[0]);
	if (!files->cmd)
		exit(1);
	if (files->proc_cnt == 2)
	{
		dup2(files->infile, STDIN_FILENO);
		dup2(files->read_fd[WRITE], STDOUT_FILENO);
		ft_close(files->infile, files->read_fd[WRITE]);
		execve(files->cmd, files->cmd_options, envp);
	}
	else if (files->proc_cnt == files->argc - 2)
	{

		dup2(files->read_fd[READ], STDIN_FILENO);
		dup2(files->outfile, STDOUT_FILENO);
		ft_close(files->read_fd[READ], files->outfile);
		execve(files->cmd, files->cmd_options, envp);
	}
	else
	{
		dup2(files->read_fd[READ], STDIN_FILENO);
		dup2(files->read_fd[WRITE], STDOUT_FILENO);
		ft_close(files->read_fd[READ], files->read_fd[WRITE]);
		execve(files->cmd, files->cmd_options, envp);
	}
}

void	run_command(t_files *files, char *argv[], char *envp[])
{
	char *str;

	str = malloc(1000);
	memset(str,  0, 1000);
	while (files->proc_cnt < files->argc - 1)
	{
		if (pipe(files->read_fd) == -1)
			ft_perror();
		write(files->read_fd[1], str, 1000);
		printf("1\n");
		files->pid = fork();
		if (files->pid == -1)
			ft_perror();
		else if (files->pid == 0)
			execute(files, argv, envp);
		else
		{
			wait(0);
			close(files->read_fd[WRITE]);
			int size = read(files->read_fd[0], str, 10);
			str[size] = '\0';
			printf("%s\n", str);
			// ft_close(files->read_fd[READ], files->write_fd[WRITE]);

			// files->read_fd[0] = files->write_fd[0];
			files->proc_cnt++;
		}
	}
}

int main(int argc, char *argv[], char *envp[])
{
	t_files	files;

	if (argc < 5)
		exit(1);
	init(&files, argc, argv, envp);
	run_command(&files, argv, envp);
	exit(0);
}