# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gloras-t <gloras-t@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/07 20:31:24 by gloras-t          #+#    #+#              #
#    Updated: 2019/10/26 22:22:38 by gloras-t         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

COREWAR = corewar
ASM = asm
SRC = src
TEST = t
OBJ = corewar.o
LIBFT = includes/ft_printf
LIBFTP = $(LIBFT)/libftp.a
HEADER = includes/corewar.h
TEST_HEADER = includes/test_filler.h
FLAGS = -Wall -Wextra -Werror

ITALIC = \033[3m
GREEN = \033[0;32m
YELLOW = \033[1;33m
EOC = \033[0m

all: $(COREWAR)
$(COREWAR): $(LIBFTP) $(OBJ) $(HEADER)
	@gcc -o $(COREWAR) $(OBJ) -I $(HEADER) -L $(LIBFT)/ -lftp -g
	@echo "$(GREEN)complete:$(EOC) $(ITALIC)COREWAR$(EOC)"

test: $(TEST)
$(TEST): $(LIBFTP) $(T) $(OBJ) $(TEST_HEADER)
	@gcc -o $(TEST) $(T) $(OBJ) -I $(TEST_HEADER) -L $(LIBFT)/ -lftp -g

$(LIBFTP):
	@make -C $(LIBFT)/

%.o: $(SRC)/%.c
	@gcc -c $(FLAGS) -I $(HEADER) $< -o $@ -g

%.o: test/%.c
	@gcc -c $(FLAGS) -I $(TEST_HEADER) $< -o $@ -g

clean:
	@make -C $(LIBFT)/ clean
	@rm -f *.o

fclean: clean
	@make -C $(LIBFT)/ fclean
	@rm -f $(COREWAR) $(TEST)

re: fclean all
