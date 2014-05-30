all: somp scpu val
somp: SVD_omp.cpp
	g++ -fopenmp SVD_omp.cpp -o somp
scpu: SVD.cpp
	g++ SVD.cpp -o scpu
val: Validation.cpp
	g++ Validation.cpp -o val

clean:
	rm somp scpu val *.mat matrix
