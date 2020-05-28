#!/bin/bash
GREEN='\033[0;32m'
RED='\033[0;31m'
EOC='\033[0m'

pl_1="resources/champs/Gagnant.cor"
pl_2="resources/champs/aff.cor"
pl_3=""
pl_4=""

ex_1="./corewar"
ex_2="./resources/corewar"

ARGS="${pl_1} ${pl_2} ${pl_3} ${pl_4}"
${ex_1} $1 $2 $3 $4 $5 $ARGS > o1
${ex_2} $1 $2 $3 $4 $5 $ARGS > o2
DIFF=$(diff <(cat o1) <(cat o2))
if [ "$DIFF" != "" ]
then
    printf "${RED}KO${EOC}: "
    echo "${ex_1} $1 $2 $3 $4 $5 $ARGS"
    git diff --no-index --unified=0 o1 o2
else
    printf "${GREEN}OK${EOC}: "
    echo "${ex_1} $1 $2 $3 $4 $5 $ARGS"
fi
