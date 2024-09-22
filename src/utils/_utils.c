#include <minishell.h>

void	print_content(void *content)
{
	printf("%s\n", ((t_token *)content)->content);
}

void	print_env(void *content)
{
	t_dictionnary	*tmp = content;

	printf("key		: %s%s%s\n", YELLOW, tmp->key, RESET);
	printf("value		: %s%s%s\n", WHITE, tmp->value, RESET);
	printf("________________________________\n");
}

void	display_token(void *content)
{
	t_token	*tmp = content;

	printf(RED"_____________________________\n\n"RESET);

	printf("type		: %s%s\n", tmp->type == PIPE ? CYAN"PIPE"
										: tmp->type == BUILTIN ? BLUE"BUILTIN"
										: tmp->type == CMD ? MAGENTA"CMD"
										// : tmp->type == FILE ? UKN"FILE"
										: tmp->type == DELIMITER ? UKN"DELIMITER"
										: tmp->type == REDIR_IN ? CYAN"REDIR_IN"
										: tmp->type == REDIR_OUT ? CYAN"REDIR_OUT"
										: tmp->type == APPEND ? CYAN"APPEND"
										: tmp->type == HEREDOC ? CYAN"HEREDOC"
										: YELLOW"ARG", RESET);

	if (tmp->type != PIPE && tmp->type != DELIMITER && tmp->type != APPEND
		&& tmp->type != HEREDOC && tmp->type != REDIR_IN && tmp->type != REDIR_OUT)
		printf("content		: %s%s%s\n", WHITE, tmp->content, RESET);
		
	if (tmp->type != PIPE && tmp->type != APPEND && tmp->type != HEREDOC
		&& tmp->type != REDIR_IN && tmp->type != REDIR_OUT)
	{
		if (tmp->state)
		{
			printf("state\t\t: ");
			if (is_joinable(tmp))
				printf("Joinable, ");
			if (tmp->type != DELIMITER && is_expandable(tmp))
				printf("Expandable, ");
			if (is_quoted(tmp))
				printf("Quoted");
			printf("\n");
		}
	}
	printf(RED"_____________________________\n"RESET);
}

void	display_command(void *content)
{
	t_command	*tmp = content;
	int			i;

	printf("cmd		: %s%s%s\n", YELLOW, tmp->cmd, RESET);
	i = 0;
	if (tmp->argv)
	{
		while (tmp->argv[i])
		{
			printf("args[%d]		: %s%s%s\n", i, WHITE, tmp->argv[i], RESET);
			i++;
		}
	}
	printf("in		: %d\n", tmp->in);
	printf("out		: %d\n", tmp->out);
	printf("argc	: %d\n", tmp->argc);

	printf("_____________________________\n");
}

void	leaks_func(void)
{
	system("leaks minishell");
}
