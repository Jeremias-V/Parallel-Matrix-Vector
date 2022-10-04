# Parallel-Matrix-Vector
A matrix-vector multiplication approach for the parallel computing course using MPI collective operations and OMP.

## Running

To run this programs you must first use `make` to compile the binaries.

Then run the non-mpi binaries with `./run.sh <target_binary> <test_number>` where `<target binary>` is the compiled program from running `make` that you want to run and `<test_number>` the test you want to run (from 1 to 9).

To run the mpi binaries use `./run-mpi <target_binary> <n_processes> <test_number>` where `<target binary>` is the compiled program from running `make` that you want to run, `<n_processes>` the number of processes you want to simulate and and `<test_number>` the test you want to run (from 1 to 9). Be sure `<n_processes>` is not greater than the input matrix row size and that is a power of two.

The result of running any program with the bash scripts is located in `Tests/output.txt`.
