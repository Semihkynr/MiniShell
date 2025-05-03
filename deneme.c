
////////////////////////////////////// CD NİN TEMEL İŞLEYİŞİ /////////////////////////////////////////
// #include <stdio.h>
// #include <dirent.h>   // opendir, readdir, closedir
// #include <unistd.h>   // chdir, getcwd
// #include <stdlib.h>   // malloc, free
// #include <string.h>   // strerror
// #include <errno.h>    // errno

// int main(void)
// {
//     DIR *dir;
//     struct dirent *entry;
//     char cwd[1024];

//     // Mevcut çalışma dizinini al
//     if (getcwd(cwd, sizeof(cwd)) != NULL)
//         printf("Şu anki dizin: %s\n\n", cwd);
//     else
//         perror("getcwd error");

//     // "./" dizinini aç
//     dir = opendir(".");
//     if (!dir)
//     {
//         perror("opendir error");
//         return (1);
//     }

//     printf("Bulunan dosyalar:\n");
//     // Dizin içindeki tüm dosyaları oku
//     while ((entry = readdir(dir)) != NULL)
//         printf("→ %s\n", entry->d_name);

//     // Dizin akışını kapat
//     if (closedir(dir) == -1)
//         perror("closedir error");

//     // Başka bir dizine geç (örnek: /tmp)
//     if (chdir("/tmp") == -1)
//         perror("chdir error");
//     else
//     {
//         if (getcwd(cwd, sizeof(cwd)) != NULL)
//             printf("\nYeni dizin: %s\n", cwd);
//     }

//     return (0);
// }
///////////////////////////////////////////CD DOSYA MI DEĞİL Mİ /////////////////////
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>

void	cmd_export(t_shell *shell, char *arg)
{
	int		i;
	char	**new_env;
	int		size;
    
	if (!arg)
        return ;
	size = 0;
	while (shell->env[size])
		size++;
	new_env = malloc(sizeof(char *) * (size + 2));
	if (!new_env)
		return ;
	i = 0;
	while (i < size)
	{
		new_env[i] = strdup(shell->env[i]);
		i++;
	}
	new_env[i++] = strdup(arg);
	new_env[i] = NULL;
	i = 0;
	while (shell->env[i])
		free(shell->env[i++]);
	free(shell->env);
	shell->env = new_env;
	sort_env(shell->env);
	i = 0;
	while (shell->env[i])
	{
		printf("declare -x %s\n", shell->env[i]);
		i++;
	}
}
