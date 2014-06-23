python gendata.py $1
echo single thread version time:
time ./cg $1 > result.dat
echo openMP version time:
time ./cg_omp $1 >> result.dat
