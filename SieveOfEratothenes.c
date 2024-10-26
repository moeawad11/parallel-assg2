#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    int n, rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        printf("Enter the value of n: ");
        fflush(stdout);
        scanf("%d", &n);

        double start_time = MPI_Wtime();

        for (int i = 2; i <= n; i++) {
            MPI_Send(&i, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
        }
        int terminator = -1;
        MPI_Send(&terminator, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);

        double end_time = MPI_Wtime();

        printf("Execution Time: %f seconds\n", end_time - start_time);
    } else {
        int prime;
        MPI_Recv(&prime, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        
        while (1) {
            int number;
            MPI_Recv(&number, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            if (number == -1) {
                if (rank < size - 1)
                    MPI_Send(&number, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
                break;
            }
            if (number % prime != 0) {
                if (rank < size - 1)
                    MPI_Send(&number, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
            }
        }
    }

    MPI_Finalize();
    return 0;
}
