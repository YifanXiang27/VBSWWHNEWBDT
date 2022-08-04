rm Read*.cpp
cp Copy_Read.cpp Readsig.cpp
for data in tt1l tt2l ttX ttbb WJet
do
    sed -e "s/sig/$data/g" Readsig.cpp > Read${data}.cpp
    root -l -q Read${data}.cpp
done
