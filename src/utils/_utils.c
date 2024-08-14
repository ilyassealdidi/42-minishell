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

	ft_printf(RED"_____________________________\n\n"RESET);

	ft_printf("type		: %s%s\n", tmp->type == PIPE ? CYAN"PIPE"
										: tmp->type == BUILTIN ? BLUE"BUILTIN"
										: tmp->type == CMD ? MAGENTA"CMD"
										: tmp->type == OUTFILE ? UKN"OUTFILE"
										: tmp->type == DELIMITER ? UKN"DELIMITER"
										: tmp->type == INFILE ? UKN"INFILE"
										: tmp->type == REDIR_IN ? CYAN"REDIR_IN"
										: tmp->type == REDIR_OUT ? CYAN"REDIR_OUT"
										: tmp->type == APPEND ? CYAN"APPEND"
										: tmp->type == HEREDOC ? CYAN"HEREDOC"
										: YELLOW"ARG", RESET);

	if (tmp->type != PIPE && tmp->type != DELIMITER && tmp->type != APPEND
		&& tmp->type != HEREDOC && tmp->type != REDIR_IN && tmp->type != REDIR_OUT)
		ft_printf("content		: %s%s%s\n", WHITE, tmp->content, RESET);
		
	if (tmp->type != PIPE && tmp->type != APPEND && tmp->type != HEREDOC
		&& tmp->type != REDIR_IN && tmp->type != REDIR_OUT)
	{
		if (tmp->is_expandable || tmp->is_quoted || tmp->is_joinable)
		{
			ft_printf("state\t\t: ");
			if (tmp->is_joinable)
				ft_printf("Joinable, ");
			if (tmp->type != DELIMITER && tmp->is_expandable)
				ft_printf("Expandable, ");
			if (tmp->is_quoted)
				ft_printf("Quoted\n");
		}
	}
	ft_printf(RED"_____________________________\n"RESET);
}

void	leaks_func(void)
{
	system("leaks minishell");
}
