NAME  = shell

LIBFT_DIR = lib/libft

LIBFT = $(LIBFT_DIR)/libft.a

CC = cc
RM = rm -f
CFLAGS = -Wall -Werror -Wextra -Wunused -g3

SRC_DIR = src

SRC = 	main.c		\
		env.c		\
		env2.c		\
		lexer.c

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