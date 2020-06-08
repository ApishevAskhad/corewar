# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: slindgre <slindgre@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/07 20:31:24 by gloras-t          #+#    #+#              #
#    Updated: 2020/06/08 13:47:06 by dtimeon          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

COREWAR 	=	corewar
ASM 		=	asm
TEST_VM 	=	t
TEST_ASM 	=	tt
OBJ_ASM_DIR	=	obj_asm
OBJ_VM_DIR	=	obj_vm

OBJ_VM 		=	$(addprefix $(OBJ_VM_DIR)/, \
				carry_args.o \
				carry_check.o \
				clean_utils.o \
				create_player.o \
				init_game.o \
				list_utils.o \
				main_cycle.o \
				operations_1.o \
				operations_2.o \
				operations_3.o \
				operations_4.o \
				operations_utils.o \
				parse_args.o \
				print_utils_1.o \
				print_utils_2.o \
				verbose_printing.o)

OBJ_ASM		=	$(addprefix $(OBJ_ASM_DIR)/, printer.o \
				file_validation.o \
				options_handling.o\
				initializing_structs.o \
				str_utils.o \
				file_reading.o \
				file_translation.o \
				freeing_memory.o \
				file_parsing.o \
				error_handling.o \
				reading_binary_utils.o \
				parsing_asm_header.o \
				parsing_asm_header_saving_string.o \
				parsing_asm_code.o \
				parsing_asm_utils.o \
				dealing_with_parsing_errors.o \
				parsing_asm_labels.o \
				parsing_asm_op.o \
				parsing_asm_op_finding_op.o \
				parsing_asm_arg.o \
				replacing_labels_with_values.o \
				op_data.o \
				parsing_binary_header.o \
				translating_utils.o \
				parsing_binary_code.o \
				parsing_binary_args.o \
				printing_annotated_file.o)

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
	@gcc $(FLAGS) -o $(ASM) $(OBJ_ASM_DIR)/asm.o $(OBJ_ASM) -I $(INCLUDES) -I $(LIBFTH) -L $(LIBFT)/ -lftp -g
	@echo "$(GREEN)complete:$(EOC) $(ITALIC)ASM$(EOC)"

$(COREWAR): $(OBJ_VM_DIR) $(LIBFTP) $(OBJ_VM_DIR)/corewar.o $(OBJ_VM)
	@gcc $(FLAGS) -o $(COREWAR) $(OBJ_VM_DIR)/corewar.o $(OBJ_VM) -I $(INCLUDES) -I $(LIBFTH) -L $(LIBFT)/ -lftp -g
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
