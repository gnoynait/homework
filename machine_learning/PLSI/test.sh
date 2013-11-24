#!/bin/sh
for nz in 10 20 50 100 200 500; do
	echo nz = $nz
	./plsi $nz | tee likelihood_$nz.txt
done
