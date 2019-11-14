# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gloras-t <gloras-t@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/07 20:31:24 by gloras-t          #+#    #+#              #
#    Updated: 2019/11/14 21:43:26 by gloras-t         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

COREWAR 	=	corewar
ASM 		=	asm
TEST_VM 	=	t
TEST_ASM 	=	tt
OBJ_ASM_DIR	=	obj_asm
OBJ_VM_DIR	=	obj_vm

OBJ_VM 		=	$(addprefix $(OBJ_VM_DIR)/, print_utils.o \
				check_utils_01.o \
				create_player.o \
				clean_utils.o \
				utils_01.o \
				place_players.o \
				parse_args.o \
				list_utils.o)
OBJ_ASM		=	$(addprefix $(OBJ_ASM_DIR)/, foo.o)

INCLUDES	=	includes
LIBFT 		=	$(INCLUDES)/ft_printf
LIBFTP 		=	$(LIBFT)/libftp.a
LIBFTH		=	$(INCLUDES)/libft
FLAGS 		=	-Wall -Wextra -Werror

ITALIC 		=	\033[3m
GREEN 		=	\033[0;32m
YELLOW 		=	\033[1;33m
EOC 		= 	\033[0m

all: $(COREWAR) $(ASM)

$(OBJ_ASM_DIR):
	@mkdir $(OBJ_ASM_DIR)

$(OBJ_VM_DIR):
	@mkdir $(OBJ_VM_DIR)

$(ASM): $(OBJ_ASM_DIR) $(LIBFTP) $(OBJ_ASM_DIR)/asm.o $(OBJ_ASM)
	@gcc -o $(ASM) $(OBJ_ASM_DIR)/asm.o $(OBJ_ASM) -I $(INCLUDES) -I $(LIBFTH) -L $(LIBFT)/ -lftp -g
	@echo "$(GREEN)complete:$(EOC) $(ITALIC)ASM$(EOC)"

$(COREWAR): $(OBJ_VM_DIR) $(LIBFTP) $(OBJ_VM_DIR)/corewar.o $(OBJ_VM)
	@gcc -o $(COREWAR) $(OBJ_VM_DIR)/corewar.o $(OBJ_VM) -I $(INCLUDES) -I $(LIBFTH) -L $(LIBFT)/ -lftp -g
	@echo "$(GREEN)complete:$(EOC) $(ITALIC)COREWAR$(EOC)"

$(TEST_VM): $(OBJ_VM_DIR) $(OBJ_VM) $(LIBFTP) $(T)
	@gcc -o $(TEST_VM) $(T) $(OBJ_VM) -I $(INCLUDES) -I $(LIBFTH) -L $(LIBFT)/ -lftp -g
	@echo "$(GREEN)complete:$(EOC) $(ITALIC)$(T)$(EOC)"

$(TEST_ASM): $(OBJ_ASM_DIR) $(OBJ_ASM) $(LIBFTP) $(T)
	@gcc -o $(TEST_ASM) $(T) $(OBJ_ASM) -I $(INCLUDES) -I $(LIBFTH) -L $(LIBFT)/ -lftp -g
	@echo "$(GREEN)complete:$(EOC) $(ITALIC)$(T)$(EOC)"

$(LIBFTP):
	@make -C $(LIBFT)/

%.o: test_vm/%.c includes/corewar.h
	@gcc -c $(FLAGS) -I$(INCLUDES) -I$(LIBFTH) $< -g

%.o: test_asm/%.c includes/asm.h
	@gcc -c $(FLAGS) -I$(INCLUDES) -I$(LIBFTH) $< -g

$(OBJ_ASM_DIR)/%.o: src_asm/%.c includes/asm.h
	@gcc -c $(FLAGS) -I $(INCLUDES) -I $(LIBFTH) $< -o $@ -g

$(OBJ_VM_DIR)/%.o: src_vm/%.c includes/corewar.h
	@gcc -c $(FLAGS) -I $(INCLUDES) -I $(LIBFTH) $< -o $@ -g

clean:
	@make -C $(LIBFT)/ clean
	@rm -f *.o
	@rm -rf $(OBJ_ASM_DIR) $(OBJ_VM_DIR)

fclean: clean
	@make -C $(LIBFT)/ fclean
	@rm -f $(COREWAR) $(ASM) $(TEST_VM) $(TEST_ASM)

re: fclean all
