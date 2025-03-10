SRC_DIR=src
INC_DIR=include
BUILD_DIR=.build
OBJ_DIR=$(BUILD_DIR)/.obj
LIBFT_DIR=libft
BONUS_FILE=$(BUILD_DIR)/.bonus_flag

GREEN=\033[0;32m
END_COLOR=\033[0m

CC=cc
CFLAGS=-Wall -Wextra -Werror -I$(INC_DIR)

MAKEFLAGS += --no-print-directory

SRC_FILES =	main.c \
			frees.c \
			output.c \
			env_check.c \
			close.c \
			utils.c \
			children.c \
			parent.c \
			inits2.c \
			here_doc.c \
			inits.c

SRCS = $(addprefix $(SRC_DIR)/, $(SRC_FILES))

OBJS = ${SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o}

NAME=pipex

BONUS=0

all: libs $(BUILD_DIR) check_bonus $(NAME)
	@echo "$(GREEN)Pipex ready$(END_COLOR)"

libs:
	@$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJS) $(LIBFT_DIR)/libft.a
	@$(CC) $(OBJS) -o $(NAME) $(LIBFT_DIR)/libft.a -D BONUS=$(BONUS) -g3
	@if [ $(BONUS) -eq 1 ]; then \
		echo "$(GREEN)Compiled pipex with bonus$(END_COLOR)"; \
	else \
		echo "$(GREEN)Compiled pipex without bonus$(END_COLOR)"; \
	fi

check_bonus:
	@if [ -f $(BONUS_FILE) ] && [ "`cat $(BONUS_FILE)`" != "$(BONUS)" ]; then \
		if [ $(BONUS) -eq 1 ]; then \
			echo "$(GREEN)Recompiling with bonus:$(END_COLOR)"; \
		else \
			echo "$(GREEN)Recompiling without bonus:$(END_COLOR)"; \
		fi; \
		$(MAKE) clean_pipex; \
	fi
	@echo $(BONUS) > $(BONUS_FILE)

bonus:
	@$(MAKE) BONUS=1 all

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c $(INC_DIR)/pipex.h Makefile | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@ -D BONUS=$(BONUS) -g3
	@echo "Compiled $<"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@echo "Created $(OBJ_DIR)/ "

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)
	@echo "Created $(BUILD_DIR)/ "

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	@rm -rf $(OBJ_DIR) $(BUILD_DIR)
	@rm -f $(BONUS_FILE)
	@echo "Cleaned pipex"

fclean: 
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@rm -rf $(OBJ_DIR) $(NAME) $(BUILD_DIR)
	@rm -f $(BONUS_FILE)
	@echo "Full cleaned pipex"

clean_pipex:
	@rm -rf $(OBJ_DIR) $(NAME)
	@echo "Cleaned pipex (not libft)"

re : fclean all

.PHONY : all clean fclean re bonus clean_pipex check_bonus