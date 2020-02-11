#!/bin/sh

lft=../../libft_malloc.so
out=./out

echo "==================================="
echo "nm $lft"
echo "==================================="
/usr/bin/nm $lft

echo "==================================="
echo "nm $lft | egrep --color 'T _(malloc|free|realloc|show_alloc_mem)$'" 
echo "==================================="
/usr/bin/nm $lft | egrep --color 'T _(malloc|free|realloc|show_alloc_mem)$'

echo "==================================="
echo "/usr/bin/time -l $out/test0"
echo "==================================="
/usr/bin/time -l $out/test0

echo "==================================="
echo "/usr/bin/time -l $out/test1"
echo "==================================="
/usr/bin/time -l $out/test1

echo "==================================="
echo "./run.sh /usr/bin/time -l $out/test1"
echo "==================================="
./run.sh /usr/bin/time -l $out/test1

echo "==================================="
echo "./run.sh /usr/bin/time -l $out/test2"
echo "==================================="
./run.sh /usr/bin/time -l $out/test2

echo "==================================="
echo "./run.sh /usr/bin/time -l $out/test3"
echo "==================================="
./run.sh $out/test3

echo "==================================="
echo "./run.sh /usr/bin/time -l $out/test3bis"
echo "==================================="
./run.sh $out/test3bis

echo "==================================="
echo "./run.sh /usr/bin/time -l $out/test4"
echo "==================================="
./run.sh $out/test4

echo "==================================="
echo "./run.sh /usr/bin/time -l $out/test5"
echo "==================================="
./$out/test5
