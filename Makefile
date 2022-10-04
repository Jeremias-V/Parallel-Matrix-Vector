PROGRAMS = sequential omp-directives mpi-collective mpi-omp

all: $(PROGRAMS)

sequential: matrix-vector.c
	gcc -o sequential matrix-vector.c

omp-directives: omp-mat-vec.c
	gcc -fopenmp -o omp-directives omp-mat-vec.c 

mpi-collective: mpi-mat-vec.c
	mpicc -o mpi-collective mpi-mat-vec.c

mpi-omp: mpi-omp-mat-vec.c
	mpicc -fopenmp -o mpi-omp mpi-omp-mat-vec.c

clean:
	rm -f $(PROGRAMS)
