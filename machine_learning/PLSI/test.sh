#!/bin/sh
if [ -e likelihood.txt ]; then
	rm likelihood.txt
fi
if [ -e time.txt ]; then
	rm time.txt
fi
for nz in 10 30  50  70 90 110 130 150; do
	echo nz = $nz
	/usr/bin/time -f "$nz %E" -o time.txt -a ./plsi $nz | tee likelihood_$nz.txt
	tail -n 1 likelihood_$nz.txt >> likelihood.txt
done

python plot.py likelihood.txt
