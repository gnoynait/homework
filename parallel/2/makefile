all: mcpu momp
mcpu: mandelbrot.c
	g++ -o mcpu mandelbrot.c
momp: mandelbrot_omp.c
	gcc -o momp -fopenmp mandelbrot_omp.c
clean:
	rm mcpu momp *.dat
