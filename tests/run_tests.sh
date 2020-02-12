#!/bin/sh
#!/bin/sh
dir=.
src=srcs
out=outs
lft=../libft_malloc.so

mkdir $out
gcc -o $dir/$out/test0 	$dir/$src/test0.c;
gcc -o $dir/$out/test1 	$dir/$src/test1.c;
gcc -o $dir/$out/test2 	$dir/$src/test2.c;
gcc -o $dir/$out/test3 	$dir/$src/test3.c;
gcc -o $dir/$out/test3b $dir/$src/test3b.c;
gcc -o $dir/$out/test4 	$dir/$src/test4.c;
gcc -o $dir/$out/test5 	$dir/$src/test5.c -I ../incs/ -L../ -lft_malloc;

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
echo "./run.sh /usr/bin/time -l $out/test3b"
echo "==================================="
./run.sh $out/test3b

echo "==================================="
echo "./run.sh /usr/bin/time -l $out/test4"
echo "==================================="
./run.sh $out/test4

echo "==================================="
echo "export DYLD_LIBRARY_PATH=../"
echo "./run.sh /usr/bin/time -l $out/test5"
echo "==================================="
export DYLD_LIBRARY_PATH=../
./$out/test5
