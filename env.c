#include <stdio.h>
#include <unistd.h>
#include <libft.h>

int main(int ac, char **av, char **envp)
{
	char	**cmd1;
	char	**cmd2;
	int 	env1;
	int 	env2;

	(void)ac;
	// if (ac != 5)
	// 	return (0);
	cmd1 = ft_split(av[1], ' ');
	cmd2 = ft_split(av[2], ' ');
	env1 = execve("/usr/bin/ls", cmd1, envp);
	env2 = execve("/usr/sbin/wc", cmd2, envp);
	printf("%d\n", env1);
	printf("%d\n", env2);
	return (1);
}
