#include "Field/Field.h"
#include "Field/FieldConfig.h"
#include <mpi/mpi.h>
#include <unistd.h>


void updateField(Field &field, int rank, int size) {
    int randomX = rand() % FieldConfig::LENGTH;
    int randomY = rand() % FieldConfig::WIDTH;
    field.applyFirstRule(field.getCell(randomX, randomY));
}


void dataDistribution(int *dataVec, int *shiftVec, const int numProcs) {
    dataVec[0] = FieldConfig::WIDTH / numProcs;
    shiftVec[0] = 0;
    int restRows = FieldConfig::WIDTH;
    for (int i = 1; i < numProcs; ++i) {
        restRows -= dataVec[i - 1];
        dataVec[i] = restRows / (numProcs - i);
        shiftVec[i] = shiftVec[i - 1] + dataVec[i - 1];
    }
}


int main(int argc, char **argv) {
    int *dataVec, *shiftVec;
    int size, rank;
    MPI_Init(&argc, &argv);
    int a[3] =  {1,2,3};
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    dataVec = new int[size];
    shiftVec = new int[size];
    /*for (int i = 0; i < 5000; ++i) {
        for (int j = 0; j < FieldConfig::LENGTH * FieldConfig::WIDTH; ++j) {
            updateField(field, rank, size);
        }
        //  if (rank == 0) {
        field.printField();
        // }
    }*/
    //dataDistribution(dataVec, shiftVec, size);
    if (rank == 0){
        a[0] = 2;
    } else {
        sleep(3);
    }
    if (rank != 0){
        std::cout << a[1];
    }
    //Field field(rank, dataVec[rank]);
    MPI_Finalize();
    delete[] dataVec;
    delete[] shiftVec;
    return 0;
}
