#!/bin/bash

# Path to your 'corewar' executable. Example: "vm/corewar"
vm="./../../corewar"

# Path to reference 'corewar' executable. Example: "resources/corewar"
ref_vm="./../../resources/corewar"

# Path to folder with test cases"
cases="test_cases/*"

# Path to valid chamption
player_1="../../resources/champs/Gagnant.cor"

#Path to another valid champion
player_2="../../resources/champs/maxidef.cor"

GREEN='\033[0;32m'
YELLOW='\033[1;33m'
RED='\033[0;31m'
EOC='\033[0m'

echo "${YELLOW}Exit code tests:${EOC}"
for file in $cases
do
    file_name="${file##*/}"
    printf "\n$file_name"
    ERROR=0
    ERR_NBR=${file_name%\.*}
    while IFS="" read -r ARGS
    do
        out=`${vm} $ARGS`
        ret=$?
        if [ "$ret" -ne ${ERR_NBR} ]
        then
            printf "\n${RED}[KO rv=$ret]${EOC} ${ARGS}"
            ERROR=1
        fi
    done <$file

    if [ "$ERROR" -eq 0 ]
    then
        printf " ${GREEN}[OK]${EOC}\n"
    fi
done


ARGS=("$player_1" "$player_1 $player_2" "$player_2 $player_1 $player_2" "$player_2 $player_1 $player_2 $player_1")

echo "\n${YELLOW}Introducing tests:${EOC}\n"
ERROR=0
head=2
for ARG in "${ARGS[@]}"
do
    out_1=`${vm} $ARG`
    out_2=`${ref_vm} $ARG | head -$head`
    if [ "$out_1" != "$out_2" ]
    then
        printf "${RED}[KO]${EOC} ${vm} $ARG\n"
        echo "Your output:\n$out_1"
        echo "-------------"
        echo "Reference output:\n$out_2"
        ERROR=1
    fi
    head=$((head+1))
done

if [ "$ERROR" -eq 0 ]
then
    printf "All introducing tests passed ${GREEN}[OK]${EOC}\n"
fi
