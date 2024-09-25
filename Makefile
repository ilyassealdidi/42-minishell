SRCS			= src/builtins/cd.c src/builtins/echo.c src/builtins/env.c src/builtins/exit.c src/builtins/export.c src/builtins/pwd.c src/builtins/unset.c src/environment/append_env.c src/environment/create_env.c src/environment/delete_env.c src/environment/environment.c src/environment/get_env.c src/environment/update_env.c src/environment/utils.c src/events/exit.c src/events/signals.c src/execution/ft_built.c src/execution/ft_dup.c src/execution/ft_exec.c src/execution/ft_fds.c src/execution/ft_fork.c src/execution/ft_pipe.c src/execution/ft_redir.c src/execution/ft_utils.c src/execution/ft_wait.c src/main.c src/parse/command/command.c src/parse/command/create_command.c src/parse/command/utils.c src/parse/expansion.c src/parse/heredoc.c src/parse/parse.c src/parse/redirection.c src/parse/token/create_token.c src/parse/token/insert_token.c src/parse/token/token.c src/parse/token/update_token.c src/parse/token/utils.c src/parse/utils/token_state.c src/parse/utils/token_type.c src/utils/error.c src/utils/free_array.c src/utils/string.c src/utils/utils.c
OBJS_DIR		= obj/
OBJS 			= $(addprefix $(OBJS_DIR), $(SRCS:.c=.o))
INCS_DIR		= include/
INCS			= $(INCS_DIR)minishell.h $(INCS_DIR)types.h $(INCS_DIR)exec.h $(INCS_DIR)parse.h
LIBFT_DIR		= lib/libft/
LIBFT			= $(LIBFT_DIR)libft.a
CFLAGS			= -I$(INCS_DIR) -I$(LIBFT_DIR) 
CFLAGS			+= -Wall -Werror -Wextra
NAME			= minishell
RM				= rm -rf

all:			$(NAME)

$(NAME) : $(OBJS) $(LIBFT)
	$(CC) $(OBJS) $(LIBFT) -lreadline -o $(NAME)

$(OBJS_DIR)%.o : %.c $(INCS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT) :
	@make -C $(LIBFT_DIR) && make clean -C $(LIBFT_DIR)

clean :
	@$(RM) $(OBJS_DIR)

fclean : clean
	@make fclean -C $(LIBFT_DIR)
	@$(RM) $(NAME)

re : fclean all