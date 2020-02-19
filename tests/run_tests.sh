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

run_nm()
{
	echo "==================================="
	echo "nm $lft"
	echo "==================================="
	/usr/bin/nm $lft
	echo "==================================="
	echo "nm $lft | egrep --color 'T _(malloc|free|realloc|show_alloc_mem)$'"
	echo "==================================="
	/usr/bin/nm $lft | egrep --color 'T _(malloc|free|realloc|show_alloc_mem)$'
}

run_base()
{
	echo "==================================="
	echo "/usr/bin/time -l $out/test0"
	echo "==================================="
	/usr/bin/time -l $out/test0
	echo "==================================="
	echo "/usr/bin/time -l $out/test1"
	echo "==================================="
	/usr/bin/time -l $out/test1
}

run_test1()
{
	echo "==================================="
	echo "./run.sh /usr/bin/time -l $out/test1"
	echo "==================================="
	./run.sh /usr/bin/time -l $out/test1
}

run_test2()
{
	echo "==================================="
	echo "./run.sh /usr/bin/time -l $out/test2"
	echo "==================================="
	./run.sh /usr/bin/time -l $out/test2
}

run_test3()
{
	echo "==================================="
	echo "./run.sh /usr/bin/time -l $out/test3"
	echo "==================================="
	./run.sh $out/test3
}

run_test3b()
{
	echo "==================================="
	echo "./run.sh /usr/bin/time -l $out/test3b"
	echo "==================================="
	./run.sh $out/test3b
}

run_test4()
{
	echo "==================================="
	echo "./run.sh /usr/bin/time -l $out/test4"
	echo "==================================="
	./run.sh $out/test4
}

run_test5()
{
	echo "==================================="
	echo "export DYLD_LIBRARY_PATH=../"
	echo "./run.sh /usr/bin/time -l $out/test5"
	echo "==================================="
	export DYLD_LIBRARY_PATH=../
	./$out/test5
}

run_all()
{
	run_nm
	run_base
	run_base_test1
	run_test1
	run_test2
	run_test3
	run_test3b
	run_test4
	run_test5
}

case $1 in
	nm) run_nm;;
	base) run_base;;
	1) run_test1;;
	2) run_test2;;
	3) run_test3;;
	3b) run_test3b;;
	4) run_test4;;
	5) run_test5;;
	*) run_all;;
esac
