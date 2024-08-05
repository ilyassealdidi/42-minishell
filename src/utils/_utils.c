#include <minishell.h>

void	print_content(void *content)
{
	ft_printf("%s\n", ((t_token *)content)->content);
}

void	print_env(void *content)
{
	t_dictionnary	*tmp = content;

	ft_printf("key		: %s%s%s\n", YELLOW, tmp->key, RESET);
	ft_printf("value		: %s%s%s\n", WHITE, tmp->value, RESET);
	ft_printf("________________________________\n");
}

void	display_token(void *content)
{
	t_token	*tmp = content;

	ft_printf("\ncontent		: %s%s%s\n", WHITE, tmp->content, RESET);
	ft_printf("type		: %s%s%s\n", YELLOW, tmp->type == PIPE ? "PIPE"
										: tmp->type == BUILTIN ? "BUILTIN"
										: tmp->type == OUTFILE ? "OUTFILE"
										: tmp->type == DELIMITER ? "DELIMITER"
										: tmp->type == REDIR_IN ? "REDIR_IN"
										: tmp->type == REDIR_OUT ? "REDIR_OUT"
										: tmp->type == APPEND ? "APPEND"
										: tmp->type == CMD ? "CMD"
										: tmp->type == HEREDOC ? "HEREDOC"
										: "ARG", RESET);
	ft_printf("joinable	: %s\n", tmp->is_joinable ? TRUE : FALSE);
	ft_printf("expandable	: %s\n", tmp->is_expandable ? TRUE : FALSE);
	ft_printf("quoted		: %s\n", tmp->is_quoted ? TRUE : FALSE);
	ft_printf("________________________________\n");
}

void	leaks_func(void)
{
	system("leaks minishell");
}
