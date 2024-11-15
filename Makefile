NAME  = minishell

LIBFT_DIR = lib/libft

LIBFT = $(LIBFT_DIR)/libft.a

CC = cc
RM = rm -f
CFLAGS = -Wall -Werror -Wextra -I./include

SRC_DIR = src

SRC 	= 	main.c						\
			init.c						\
			env/env.c					\
			env/env2.c					\
			lexer/lexer.c				\
			lexer/lexer_utils.c			\
			builtins/cd.c				\
			builtins/pwd.c				\
			builtins/env.c				\
			builtins/export.c			\
			builtins/export_utils.c		\
			builtins/unset.c			\
			builtins/echo.c				\
			builtins/exit.c				\
			parse/parse_cmd.c			\
			parse/parse_cmd_utils.c		\
			parse/parse_cmd_utils2.c	\
			expand/expand.c				\
			expand/expand_redir.c		\
			expand/expand_utils.c		\
			expand/expand_utils2.c		\
			expand/split_expand.c		\
			expand/split_expand_utils.c \
			expand/quote.c				\
			expand/prepare_quote.c		\
			minishell_utils.c			\
			exec/exec.c					\
			exec/exec_utils.c			\
			exec/process_builtin.c		\
			exec/redirection.c			\
			exec/exec_cmd.c				\
			exec/here_doc.c				\
			exec/here_doc_utils.c		\
			handler.c					\
			free.c						\
			error.c

OBJ_DIR = obj
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

all: $(LIBFT) $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME) -lreadline

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I $(LIBFT_DIR)/include -c $< -o $@

$(LIBFT):
	make -sC $(LIBFT_DIR)

clean:
	$(RM) -r $(OBJ_DIR)
	@make -sC $(LIBFT_DIR) clean

fclean: clean
	@$(RM) $(NAME)
	@make -sC $(LIBFT_DIR) fclean

re:	fclean all

.PHONY: all clean fclean re