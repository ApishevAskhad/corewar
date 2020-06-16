# *************************************************************************** #
#                                                                             #
#                                                         :::      ::::::::   #
#    tester_config.py                                   :+:      :+:    :+:   #
#                                                     +:+ +:+         +:+     #
#    By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        #
#                                                 +#+#+#+#+#+   +#+           #
#    Created: 2020/06/15 13:46:08 by dtimeon           #+#    #+#             #
#    Updated: 2020/06/16 12:16:03 by student          ###   ########.fr       #
#                                                                             #
# *************************************************************************** #

tested_asm = 'asm'
school_asm = 'test_asm/school_asm_mac'
empty_main = 'test_asm/empty_main_sleep'
temp_tested_asm_file = 'test_asm/temp_tested.s'
temp_school_asm_file = 'test_asm/temp_school.s'
temp_tested_bin_file = 'test_asm/temp_tested.cor'
temp_school_bin_file = 'test_asm/temp_school.cor'
generated_asm_file = 'test_asm/source_by_tested_program.s'

tests_dirs = ['test_asm/assets/file_validation',
              'test_asm/assets/file_reading',
              'test_asm/assets/file_parsing',
              'test_asm/assets/file_parsing/incorrect']
large_files_dir = 'test_asm/assets/big_files'

no_leaks_line_linux = 'no leaks are possible'
no_leaks_line_mac_1 = 'definitely lost: 0 bytes in 0 blocks'
no_leaks_line_mac_2 = 'indirectly lost: 0 bytes in 0 blocks'
no_error_line = '0 errors from 0 contexts (suppressed: 0 from 0)'
definitely_line = "definitely lost: "
indirectly_line = "indirectly lost: "
error_summary_line = "ERROR SUMMARY: "

blue = "\u001b[34;1m"
red = "\u001b[31;1m"
green = "\u001b[32;1m"
some_color = "\u001b[35;1m"
color_clear = "\033[0m"
