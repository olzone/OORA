FILES="mm1.c
mm2.c
mm3.c
mm4.c
mm5.c
mm5a.c
mm5b.c
mm6.c
mm7.c
mm8.c
mm9.c"

mkdir outs
cd sources/
for f in $FILES
do
	g++ -w -I/usr/local/include $f  /usr/local/lib/libpapi.a -o ../outs/$f''.out
done

cd ..
mkdir results
cd outs
for f in $FILES
do
	./$f''.out > ../results/$f''.txt
done

