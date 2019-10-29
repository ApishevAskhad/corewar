# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: slindgre <slindgre@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/07 20:31:24 by gloras-t          #+#    #+#              #
#    Updated: 2019/10/29 16:22:28 by slindgre         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

COREWAR 	= corewar
ASM 		= asm
TEST_VM 	= t
OBJ_VM 		=	print_utils.o \
				check_utils_01.o
LIBFT 		= includes/ft_printf
LIBFTP 		= $(LIBFT)/libftp.a
HEADER 		= includes/corewar.h
TEST_HEADER	= includes/test_corewar.h
FLAGS 		= -Wall -Wextra -Werror

ITALIC 		= \033[3m
GREEN 		= \033[0;32m
YELLOW 		= \033[1;33m
EOC 		= \033[0m

all: $(COREWAR)
$(COREWAR): $(LIBFTP) corewar.o $(OBJ_VM) $(HEADER)
	@gcc -o $(COREWAR) corewar.o $(OBJ_VM) -I $(HEADER) -L $(LIBFT)/ -lftp -g
	@echo "$(GREEN)complete:$(EOC) $(ITALIC)COREWAR$(EOC)"

test: $(TEST_VM)
$(TEST_VM): $(LIBFTP) $(T) $(OBJ_VM) $(TEST_HEADER)
	@gcc -o $(TEST_VM) $(T) $(OBJ_VM) -I $(TEST_HEADER) -L $(LIBFT)/ -lftp -g

$(LIBFTP):
	@make -C $(LIBFT)/

%.o: src/%.c
	@gcc -c $(FLAGS) -I $(HEADER) $< -o $@ -g

%.o: test/%.c
	@gcc -c $(FLAGS) -I $(TEST_HEADER) $< -o $@ -g

clean:
	@make -C $(LIBFT)/ clean
	@rm -f *.o

fclean: clean
	@make -C $(LIBFT)/ fclean
	@rm -f $(COREWAR) $(TEST_VM)

re: fclean all
