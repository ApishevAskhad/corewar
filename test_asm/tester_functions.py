# *************************************************************************** #
#                                                                             #
#                                                         :::      ::::::::   #
#    tester_functions.py                                :+:      :+:    :+:   #
#                                                     +:+ +:+         +:+     #
#    By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        #
#                                                 +#+#+#+#+#+   +#+           #
#    Created: 2020/06/15 13:46:13 by dtimeon           #+#    #+#             #
#    Updated: 2020/06/16 12:42:23 by student          ###   ########.fr       #
#                                                                             #
# *************************************************************************** #

import os
import filecmp
from subprocess import run, PIPE
from shutil import copy as copy_file
from platform import system
from time import time

import tester_config as tc


def run_program(program, file, file_copy_name, measure_time):
    if not os.path.isfile(file):
        file_copy_name = file
    else:
        copy_file(file, file_copy_name)
    run_time = 0.0
    if measure_time:
        run_time = time()
    output = run(f"./{program} {file_copy_name}",
                 stdout=PIPE, stderr=PIPE, shell=True)
    if measure_time:
        run_time = time() - run_time
    return(output.returncode, (output.stdout + output.stderr).decode('utf-8'),
           run_time)


def compare(file_1, file_2, filename="", name="tested",
            comparing_with_original=False):
    if not filecmp.cmp(file_1, file_2):
        print('\r', flush=True, end='')
        print(tc.red, '*' * 82, tc.color_clear)
        if comparing_with_original:
            print(f" Binary by {name} program differs "
                  f"with original '{file_2}'")
        else:
            print(f" With '{filename}' binary files differ")
        print(tc.red, '*' * 82, tc.color_clear, "\n")


def print_output(output, name="tested"):
    print(f" {name.capitalize()} program returned error, output:")
    print(' ', output.replace('\n', '\n '), sep='')


def test_both_programs(file_path, file_to_compare=None, print_errors=False,
                       measure_time=False):
    tested_code, tested_output, tested_time = run_program(
                                                tc.tested_asm,
                                                file_path,
                                                tc.temp_tested_asm_file,
                                                measure_time)
    school_code, school_output, school_time = run_program(
                                                tc.school_asm,
                                                file_path,
                                                tc.temp_school_asm_file,
                                                measure_time)

    if tested_code == 0 and school_code == 0:
        compare(tc.temp_tested_bin_file, tc.temp_school_bin_file,
                filename=file_path)
        if file_to_compare:
            compare(tc.temp_tested_bin_file, file_to_compare,
                    comparing_with_original=True)
            compare(tc.temp_school_bin_file, file_to_compare, name="school",
                    comparing_with_original=True)
    elif tested_code != school_code:
        print('\r', flush=True, end='')
        print(tc.blue, '*' * 82, tc.color_clear)
        if file_to_compare:
            file_path = file_to_compare
        print(f" For file '{os.path.basename(file_path)}' exit codes differ: "
              f"{tested_code} and {school_code}")
        if (tested_code != 0 and print_errors):
            print_output(tested_output)
        if (school_code != 0 and print_errors):
            print_output(school_output, name="school")
        print(tc.blue, '*' * 82, tc.color_clear, "\n")
    return (tested_time, school_time)


def test_program_on_binary(file_path, print_errors=False):
    code, output, _ = run_program(tc.tested_asm, file_path,
                                  tc.temp_tested_bin_file, False)
    if code != 0 and print_errors:
        color = tc.blue if code == 1 else tc.red
        print('\r', flush=True, end='')
        print(color, '*' * 82, tc.color_clear, ' ' * 42)
        print(f" Tested program returned {code} while converting binary file "
              f"'{os.path.basename(file_path)}', output:")
        print(' ', output.replace('\n', '\n '), sep='')
        print(color, '*' * 82, '\n', tc.color_clear)
    elif code == 0:
        copy_file(tc.temp_tested_asm_file, tc.generated_asm_file)
        test_both_programs(tc.generated_asm_file,
                           file_to_compare=file_path,
                           print_errors=print_errors)


def gather_files(tests_dirs):
    files = []
    try:
        for tests_dir in tests_dirs:
            for file in os.listdir(tests_dir):
                file_path = f"{tests_dir}/{file}"
                files.append(file_path)
    except FileNotFoundError as error:
        print(f"Tests directory not found: {error}")
    return(files)


def check_leaks_on_empty_program():
    command = f"valgrind ./{tc.empty_main}"
    valgrind_output = run(command, stderr=PIPE, shell=True)
    valgrind_output = valgrind_output.stderr.decode('utf-8')
    leaks_pos = valgrind_output.find(tc.definitely_line)
    if leaks_pos >= 0:
        leaks_part = valgrind_output[leaks_pos:].splitlines()
        tc.no_leaks_line_mac_1 = leaks_part[0]
        leaks_pos = leaks_part[1].find(tc.indirectly_line)
        tc.no_leaks_line_mac_2 = leaks_part[1][leaks_pos:]
        error_summary_pos = leaks_part[8].find(tc.error_summary_line)
        offset = error_summary_pos + len(tc.error_summary_line)
        tc.no_error_line = leaks_part[8][offset:]


def check_valgrind_output(output, program, file):
    if (system() == 'Linux' and tc.no_leaks_line_linux not in output) or \
       (system() == 'Darwin' and (tc.no_leaks_line_mac_1 not in output or
                                  tc.no_leaks_line_mac_2 not in output)):
        print('\r', flush=True, end='')
        print(tc.red, '*' * 82, tc.color_clear)
        print(f" Found memory leaks in {program} with file {file}:")
        print(' ' + output.replace('\n', '\n '))
        print(tc.red, '*' * 82, tc.color_clear)
    if tc.no_error_line not in output:
        print('\r', flush=True, end='')
        print(tc.red, '*' * 82, tc.color_clear)
        print(f" Found memory errors in {program} with file {file}")
        print(tc.red, '*' * 82, tc.color_clear)


def run_leak_check(program, options, file):
    ext = os.path.splitext(file)[1]
    temp_file = f"temp_file{ext}"
    if os.path.isfile(file):
        copy_file(file, temp_file)
    else:
        temp_file = file
    for option in options:
        if not option == "":
            option = f" -{option}"
        command = f"valgrind ./{program}{option} {temp_file}"
        valgrind_output = run(command, stdout=PIPE, stderr=PIPE, shell=True)
        valgrind_output = valgrind_output.stderr.decode('utf-8')
        print_cur_task(f"Checking for leaks '{tc.some_color}"
                       f"{program}{option} {temp_file}{tc.color_clear}'")
        check_valgrind_output(valgrind_output, program, file)
    if os.path.isfile(temp_file):
        os.remove(temp_file)


def perf_check():
    print('\r', flush=True, end='')
    print(tc.green, "** Performance check **", tc.color_clear, ' ' * 100)
    print()
    for file in os.listdir(tc.large_files_dir):
        file_path = f"{tc.large_files_dir}/{file}"
        tested_time, school_time = test_both_programs(file_path,
                                                      measure_time=True)
        print(f"{file}:\ntested: ", tc.green, f"{tested_time:.3f} sec",
              tc.color_clear)
        print(f"school: ", tc.green, f"{school_time:.3f} sec",
              tc.color_clear, "\n")


def print_cur_task(task):
    print("\r", end="   ")
    print(f"{task}", " " * (125 - len(task)), end='', flush=True)


def remove_temp_files():
    for file in (tc.temp_school_asm_file,
                 tc.temp_school_bin_file,
                 tc.temp_tested_asm_file,
                 tc.temp_tested_bin_file,
                 tc.generated_asm_file):
        if os.path.exists(file):
            os.remove(file)
