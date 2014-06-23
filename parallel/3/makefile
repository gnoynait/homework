all: cg cg_omp
cg:CG.cpp
	g++ -o cg CG.cpp
cg_omp:CG_omp.cpp
	g++ -o cg_omp -fopenmp CG_omp.cpp
clean:
	rm *.dat cg cg_omp
