# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gloras-t <gloras-t@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/07 20:31:24 by gloras-t          #+#    #+#              #
#    Updated: 2019/11/09 19:03:33 by gloras-t         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

COREWAR 	= corewar
ASM 		= asm
TEST_VM 	= t
OBJ_VM 		=	print_utils.o \
				check_utils_01.o \
				create_player.o \
				clean_utils.o \
				utils_01.o
INCLUDES	= includes
LIBFT 		= $(INCLUDES)/ft_printf
LIBFTP 		= $(LIBFT)/libftp.a
LIBFTH		= $(INCLUDES)/libft
FLAGS 		= -Wall -Wextra -Werror

ITALIC 		= \033[3m
GREEN 		= \033[0;32m
YELLOW 		= \033[1;33m
EOC 		= \033[0m

all: $(COREWAR)
$(COREWAR): $(LIBFTP) corewar.o $(OBJ_VM)
	@gcc -o $(COREWAR) corewar.o $(OBJ_VM) -I$(INCLUDES) -I$(LIBFTH) -L $(LIBFT)/ -lftp -g
	@echo "$(GREEN)complete:$(EOC) $(ITALIC)COREWAR$(EOC)"

$(TEST_VM): $(OBJ_VM) $(LIBFTP) $(T)
	@gcc -o $(TEST_VM) $(T) $(OBJ_VM) -I$(INCLUDES) -I$(LIBFTH) -L $(LIBFT)/ -lftp -g
	@echo "$(GREEN)complete:$(EOC) $(ITALIC)$(T)$(EOC)"

$(LIBFTP):
	@make -C $(LIBFT)/

%.o: test/%.c includes/corewar.h
	@gcc -c $(FLAGS) -I$(INCLUDES) -I$(LIBFTH) $< -g
	
%.o: src/%.c includes/corewar.h
	@gcc -c $(FLAGS) -I$(INCLUDES) -I$(LIBFTH) $< -g

clean:
	@make -C $(LIBFT)/ clean
	@rm -f *.o

fclean: clean
	@make -C $(LIBFT)/ fclean
	@rm -f $(COREWAR) $(TEST_VM)

re: fclean all
