#!/bin/bash
GREEN='\033[0;32m'
RED='\033[0;31m'
EOC='\033[0m'

pl_1="resources/champs/Gagnant.cor"
pl_2="resources/champs/maxidef.cor"

ex_1="./t"
ex_2="./resources/corewar"

ARGS="${pl_1}"
out_1=`${ex_1} $ARGS`
out_2=`${ex_2} $ARGS | head -2`
DIFF=$(diff <(echo "${out_1}") <(echo "${out_2}")) 
if [ "$DIFF" != "" ]
then
    printf "${RED}KO${EOC}: "
else
    printf "${GREEN}OK${EOC}: "
fi
echo "${ex_1} $ARGS"
echo "$DIFF"

ARGS="${pl_1} ${pl_2}"
out_1=`${ex_1} $ARGS`
out_2=`${ex_2} $ARGS | head -3`
DIFF=$(diff <(echo "${out_1}") <(echo "${out_2}")) 
if [ "$DIFF" != "" ]
then
    printf "${RED}KO${EOC}: "
else
    printf "${GREEN}OK${EOC}: "
fi
echo "${ex_1} $ARGS"
echo "$DIFF"

ARGS="${pl_1} ${pl_2} ${pl_2}"
out_1=`${ex_1} $ARGS`
out_2=`${ex_2} $ARGS | head -4`
DIFF=$(diff <(echo "${out_1}") <(echo "${out_2}")) 
if [ "$DIFF" != "" ]
then
    printf "${RED}KO${EOC}: "
else
    printf "${GREEN}OK${EOC}: "
fi
echo "${ex_1} $ARGS"
echo "$DIFF"

ARGS="${pl_1} ${pl_2} ${pl_2} ${pl_1}"
out_1=`${ex_1} $ARGS`
out_2=`${ex_2} $ARGS | head -5`
DIFF=$(diff <(echo "${out_1}") <(echo "${out_2}")) 
if [ "$DIFF" != "" ]
then
    printf "${RED}KO${EOC}: "
else
    printf "${GREEN}OK${EOC}: "
fi
echo "${ex_1} $ARGS"
echo "$DIFF"