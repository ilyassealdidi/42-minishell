SRCS			= $(shell find src -type f -name "*.c")
OBJS_DIR		= obj/
OBJS 			= $(addprefix $(OBJS_DIR), $(SRCS:.c=.o))
INCS_DIR		= include/
INCS			= $(INCS_DIR)minishell.h $(INCS_DIR)types.h
LIBFT_DIR		= lib/libft/
LIBFT			= $(LIBFT_DIR)libft.a
CFLAGS			= -I$(INCS_DIR) -I$(LIBFT_DIR) 
#CFLAGS			+= -Wall -Werror -Wextra
CFLAGS			+= -fsanitize=address
NAME			= minishell
RM				= rm -rf

all:			$(NAME)

$(NAME) : $(OBJS) $(LIBFT)
	cc $(OBJS) $(LIBFT) -lreadline -o $(NAME)

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
