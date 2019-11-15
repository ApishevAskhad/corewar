#!/bin/bash
GREEN='\033[0;32m'
RED='\033[0;31m'
EOC='\033[0m'
ex="./corewar"

make corewar &> dev null

ARGS=""
out=`${ex} $ARGS`
ret=$?
if [ "$ret" -ne 1 ]
then
    printf "${RED}KO${EOC}"
else
    printf "${GREEN}OK${EOC}"
fi
echo " no args"


ARGS=".cort"
out=`${ex} $ARGS`
ret=$?
if [ "$ret" -ne 2 ]
then
    printf "${RED}KO${EOC}"
else
    printf "${GREEN}OK${EOC}"
fi
echo " not .cor file"