HEADER_FILE = libft.h
SRC_DIR = src
INC_DIR = include
BUILD_DIR = .build
OBJ_DIR = ${BUILD_DIR}/obj
DEPS_DIR = ${BUILD_DIR}/deps

GREEN = \033[0;32m
END_COLOR = \033[0m

SRC_FILES = ft_atoi_improved.c \
	  ft_atoui_base.c \
	  ft_bzero.c \
	  ft_calloc.c \
	  ft_isalnum.c \
	  ft_isalpha.c \
	  ft_isascii.c \
	  ft_isdigit.c \
	  ft_is_digitbase.c \
	  ft_isprint.c \
	  ft_memchr.c \
	  ft_memcmp.c \
	  ft_memcpy.c \
	  ft_memmove.c \
	  ft_memset.c \
	  ft_strchr.c \
	  ft_strrchr.c \
	  ft_strdup.c \
	  ft_strlcat.c \
	  ft_strlcpy.c \
	  ft_strlen.c \
	  ft_strncmp.c \
	  ft_strnstr.c \
	  ft_substr.c \
	  ft_tolower.c \
	  ft_toupper.c \
	  ft_str_toupper.c \
	  ft_substr.c \
	  ft_strjoin.c \
	  ft_strtrim.c \
	  ft_split.c \
	  ft_itoa.c \
	  ft_strmapi.c \
	  ft_putchar_fd.c \
	  ft_putstr_fd.c \
	  ft_putendl_fd.c \
	  ft_putnbr_fd.c \
	  ft_striteri.c \
	  get_next_line.c \
	  get_next_line_utils.c \
	  pos_in_str.c

B_SRC_FILES = ft_lstnew_bonus.c \
		ft_lstaddfront_bonus.c \
		ft_lstsize_bonus.c \
		ft_lstlast_bonus.c \
		ft_lstaddback_bonus.c \
		ft_lstdelone_bonus.c \
		ft_lstclear_bonus.c \
		ft_lstiter_bonus.c \
		ft_lstmap_bonus.c

SRCS = $(addprefix ${SRC_DIR}/, ${SRC_FILES})
B_SRCS = $(addprefix ${SRC_DIR}/, ${B_SRC_FILES})
OBJS = $(addprefix ${OBJ_DIR}/, ${SRC_FILES:.c=.o})
DEPS = $(addprefix ${DEPS_DIR}/, ${SRC_FILES:.c=.d} ${B_SRC_FILES:.c=.d})

NAME = libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror -I $(INC_DIR)

all: ${NAME}
	@echo "${GREEN}Libft ready${END_COLOR}"

-include ${DEPS}
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c Makefile | $(BUILD_DIR)
	@${CC} ${CFLAGS} -MMD -MF $(DEPS_DIR)/$*.d -MP -c $< -o $@
	@echo "Compiled $<"

${NAME}: ${OBJS}
	@ar rcs ${NAME} ${OBJS}
	@echo "libft.a created"

$(BUILD_DIR):
	@mkdir -p ${DEPS_DIR} ${OBJ_DIR} ${BUILD_DIR}
	@echo "Created ${BUILD_DIR}/ ${OBJ_DIR}/ ${DEPS_DIR}/"

bonus:
	$(MAKE) ${NAME} SRC_FILES="${SRC_FILES} ${B_SRC_FILES}"

clean:
	@rm -rf $(BUILD_DIR)
	@echo "Cleaned libft"

fclean:
	@rm -rf $(BUILD_DIR) $(NAME)
	@echo "Full cleaned libft"

re: fclean all

.PHONY: all clean fclean re bonus
