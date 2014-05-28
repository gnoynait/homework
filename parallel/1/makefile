all: rmpi rcpu val
rmpi: Reduction_mpi.cpp
	~/programs/mpich/bin/mpicxx Reduction_mpi.cpp -o rmpi
rcpu: Reduction.cpp
	g++ Reduction.cpp -o rcpu
val: Validation_mpi.cpp
	g++ Validation_mpi.cpp -o val
clean:
	rm rmpi rcpu val *.mat matrix
