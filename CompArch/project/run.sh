#!/bin/bash
c1="8 4 32 256"
c2="8 16 32 256"
c3="8 4 64 256"
c4="8 16 64 256"

c5="8 4 32 1024"
c6="8 16 32 1024"
c7="8 4 64 1024"
c8="8 16 64 1024"


n1="432256"
n2="1632256"
n3="464256"
n4="1664256"

# n1="432"
# n2="1632"
# n3="464"
# n4="1664"

n5="4321024"
n6="16321024"
n7="4641024"
n8="16641024"

currentFile="099.go"

./exec $c1 < /local/classes/cs4431/trace/$currentFile > $n1$currentFile &
./exec $c2 < /local/classes/cs4431/trace/$currentFile > $n2$currentFile &
./exec $c3 < /local/classes/cs4431/trace/$currentFile > $n3$currentFile &
./exec $c4 < /local/classes/cs4431/trace/$currentFile > $n4$currentFile &

./exec $c5 < /local/classes/cs4431/trace/$currentFile > $n5$currentFile &
./exec $c6 < /local/classes/cs4431/trace/$currentFile > $n6$currentFile &
./exec $c7 < /local/classes/cs4431/trace/$currentFile > $n7$currentFile &
./exec $c8 < /local/classes/cs4431/trace/$currentFile > $n8$currentFile &

currentFile="124.m88ksim"

./exec $c1 < /local/classes/cs4431/trace/$currentFile > $n1$currentFile &
./exec $c2 < /local/classes/cs4431/trace/$currentFile > $n2$currentFile &
./exec $c3 < /local/classes/cs4431/trace/$currentFile > $n3$currentFile &
./exec $c4 < /local/classes/cs4431/trace/$currentFile > $n4$currentFile &

./exec $c5 < /local/classes/cs4431/trace/$currentFile > $n5$currentFile &
./exec $c6 < /local/classes/cs4431/trace/$currentFile > $n6$currentFile &
./exec $c7 < /local/classes/cs4431/trace/$currentFile > $n7$currentFile &
./exec $c8 < /local/classes/cs4431/trace/$currentFile > $n8$currentFile &

currentFile="126.gcc"

./exec $c1 < /local/classes/cs4431/trace/$currentFile > $n1$currentFile &
./exec $c2 < /local/classes/cs4431/trace/$currentFile > $n2$currentFile &
./exec $c3 < /local/classes/cs4431/trace/$currentFile > $n3$currentFile &
./exec $c4 < /local/classes/cs4431/trace/$currentFile > $n4$currentFile &

./exec $c5 < /local/classes/cs4431/trace/$currentFile > $n5$currentFile &
./exec $c6 < /local/classes/cs4431/trace/$currentFile > $n6$currentFile &
./exec $c7 < /local/classes/cs4431/trace/$currentFile > $n7$currentFile &
./exec $c8 < /local/classes/cs4431/trace/$currentFile > $n8$currentFile &

currentFile="129.compress"

./exec $c1 < /local/classes/cs4431/trace/$currentFile > $n1$currentFile &
./exec $c2 < /local/classes/cs4431/trace/$currentFile > $n2$currentFile &
./exec $c3 < /local/classes/cs4431/trace/$currentFile > $n3$currentFile &
./exec $c4 < /local/classes/cs4431/trace/$currentFile > $n4$currentFile &

./exec $c5 < /local/classes/cs4431/trace/$currentFile > $n5$currentFile &
./exec $c6 < /local/classes/cs4431/trace/$currentFile > $n6$currentFile &
./exec $c7 < /local/classes/cs4431/trace/$currentFile > $n7$currentFile &
./exec $c8 < /local/classes/cs4431/trace/$currentFile > $n8$currentFile &

currentFile="132.ijpeg"

./exec $c1 < /local/classes/cs4431/trace/$currentFile > $n1$currentFile &
./exec $c2 < /local/classes/cs4431/trace/$currentFile > $n2$currentFile &
./exec $c3 < /local/classes/cs4431/trace/$currentFile > $n3$currentFile &
./exec $c4 < /local/classes/cs4431/trace/$currentFile > $n4$currentFile &

./exec $c5 < /local/classes/cs4431/trace/$currentFile > $n5$currentFile &
./exec $c6 < /local/classes/cs4431/trace/$currentFile > $n6$currentFile &
./exec $c7 < /local/classes/cs4431/trace/$currentFile > $n7$currentFile &
./exec $c8 < /local/classes/cs4431/trace/$currentFile > $n8$currentFile &

currentFile="134.perl"

./exec $c1 < /local/classes/cs4431/trace/$currentFile > $n1$currentFile &
./exec $c2 < /local/classes/cs4431/trace/$currentFile > $n2$currentFile &
./exec $c3 < /local/classes/cs4431/trace/$currentFile > $n3$currentFile &
./exec $c4 < /local/classes/cs4431/trace/$currentFile > $n4$currentFile &

./exec $c5 < /local/classes/cs4431/trace/$currentFile > $n5$currentFile &
./exec $c6 < /local/classes/cs4431/trace/$currentFile > $n6$currentFile &
./exec $c7 < /local/classes/cs4431/trace/$currentFile > $n7$currentFile &
./exec $c8 < /local/classes/cs4431/trace/$currentFile > $n8$currentFile &