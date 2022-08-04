#!/bin/bash
MAXDEPTH=0
NTREE=0
ARRDEPTH=(2 3 4 5)
#ARRDEPTH=(2 3)
ARRTREE=(10 20 30 40 50 75 100 200 300 400 500 600 700 800)
#ARRTREE=(10 20)
rm totaloutput.txt

for MAXDEPTH in "${ARRDEPTH[@]}"
do
    for NTREE in "${ARRTREE[@]}"
    do
        NameDIR=MD${MAXDEPTH}NTr${NTREE}PU095
        cp -r Origin $NameDIR
        cd $NameDIR
        sed  -e "s/CHANGEMAXDEPTH/${MAXDEPTH}/g" ./TMVAClassification_ori.C > ./TMVAClassification_step1.C
        sed -e "s/CHANGENTREES/${NTREE}/g" ./TMVAClassification_step1.C > ./TMVAClassification.C
        rm TMVAClassification_*.C
        rm output.out
        make clean
        make -j
        ./TMVAClassification > TMVAOutput.out
        root -l -b -q GetFromTMVA.cpp
        root -l -b -q Check.cpp
        root -l -b -q Checkbkg.cpp
        root -l -b -q draw.cpp > output.out
        sh run.sh > output.out
        echo "MaxDepth = ${MAXDEPTH}    NTree = ${NTREE}" >> ../totaloutput.txt
        sed -n '/Max\ Lsig/p' output.out >> ../totaloutput.txt
        cd ..
    done
done
