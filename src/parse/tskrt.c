#include <minishell.h>

void	print_content(void *content)
{
	ft_printf("%s\n", ((t_token *)content)->content);
}

void	func()
{
	system("leaks minishell");
}
