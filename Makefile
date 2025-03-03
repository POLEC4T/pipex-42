SRC_DIR=src
INC_DIR=include
OBJ_DIR=.obj
LIBFT_DIR=libft

CC=cc
CFLAGS=-Wall -Wextra -Werror -I$(INC_DIR)

SRCS =	$(SRC_DIR)/main.c \
		$(SRC_DIR)/frees.c \
		$(SRC_DIR)/output.c \
		$(SRC_DIR)/utils.c \
		$(SRC_DIR)/inits.c


OBJS = ${SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o}

NAME=pipex

all: libs $(NAME)

libs:
	@$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME) $(LIBFT_DIR)/libft.a

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c $(INC_DIR)/pipex.h Makefile | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	rm -rf $(OBJ_DIR)

fclean: 
	@$(MAKE) -C $(LIBFT_DIR) fclean
	rm -rf $(OBJ_DIR) $(NAME)

re : fclean all

.PHONY : all clean fclean re