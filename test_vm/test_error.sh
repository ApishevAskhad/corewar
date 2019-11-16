#!/bin/bash

# Path to your 'corewar' executable. Example: "vm/corewar"
vm="./corewar"

# Path to reference 'corewar' executable. Example: "resources/corewar"
ref_vm="./resources/corewar"

# Path to 'champs' folder with references of .cor files. Example: "resources/champs"
champs="resources/champs/"

# Path to folder with test cases"
tests_KO="test_vm/vm_unit_tests/KO/*"
tests_OK="test_vm/vm_unit_tests/OK/*"

GREEN='\033[0;32m'
RED='\033[0;31m'
EOC='\033[0m'

echo "KO tests:"
for file in $tests_KO
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
            printf "\n${RED}[KO]${EOC} ${ARGS}"
            ERROR=1
        fi
    done <$file
    if [ "$ERROR" -eq 0 ]
    then
        printf " ${GREEN}[OK]${EOC}\n"
    fi
done
