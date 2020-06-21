#!/bin/bash

# Specify all pathes from 'corewar' directory
# Path to your 'corewar' executable. Example: "./corewar"
vm="./../../corewar"

# Path to reference 'corewar' executable. Example: "./resources/corewar"
ref_vm="./../../resources/corewar"

# Path to folder with test cases"
cases=test_cases/*

# Path to valid chamption
player_1="../../resources/champs/Gagnant.cor"

#Path to another valid champion
player_2="../../resources/champs/maxidef.cor"

GREEN='\033[0;32m'
YELLOW='\033[1;33m'
RED='\033[0;31m'
EOC='\033[0m'

printf "${YELLOW}Exit code tests:${EOC}\n"
for file in $cases
do
    file_name="${file##*/}"
    printf "$file_name\n"
    ERROR=0
    ERR_NBR=${file_name%\.*}
    i=1
    while IFS="" read -r ARGS
    do
        out=$(${vm} $ARGS 2>/dev/null )
        ret=$?
        if [ "$ret" -ne ${ERR_NBR} ]
        then
            printf "line $i ${RED}[KO rv=$ret]${EOC} ${ARGS}\n"
            ERROR=1
        fi
        i=$((i+1))
    done <$file

    if [ "$ERROR" -eq 0 ]
    then
        printf "${GREEN}[OK]${EOC}\n\n"
    fi
done


ARGS=("$player_1" "$player_1 $player_2" "$player_2 $player_1 $player_2" "$player_2 $player_1 $player_2 $player_1")

printf "\n${YELLOW}Introducing tests:${EOC}\n"
ERROR=0
for ARG in "${ARGS[@]}"
do
    out_1=`${vm} $ARG`
    out_2=`${ref_vm} $ARG`

    printf "$ARG\n"
    if [ "$out_1" != "$out_2" ]
    then
        printf "${RED}[KO]${EOC} ${vm} $ARG\n"
        printf "Your output:\n$out_1\n"
        printf "/////////////////////\n"
        printf "Reference output:\n$out_2\n"
        ERROR=1
    fi
done

if [ "$ERROR" -eq 0 ]
then
    printf "All introducing tests passed ${GREEN}[OK]${EOC}\n"
fi
