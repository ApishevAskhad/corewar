#!/bin/bash
GREEN='\033[0;32m'
RED='\033[0;31m'
EOC='\033[0m'

ex_1="./corewar"
ex_2="resources/corewar -a"

${ex_1} $@ > o1
${ex_2} $@ > o2
DIFF=$(diff <(cat o1) <(cat o2))
if [ "$DIFF" != "" ]
then
    printf "${RED}KO${EOC}: "
    echo "${ex_1} $@ $ARGS"
    git diff --no-index --unified=0 o1 o2
else
    printf "${GREEN}OK${EOC}: "
    echo "${ex_1} $@ $ARGS"
fi
