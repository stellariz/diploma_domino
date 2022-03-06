#include "Field/Field.h"
#include "Field/FieldConfig.h"
#include <mpi/mpi.h>
#include <unistd.h>


void updateField(Field &field, const int dataVec, const int shiftVec) {
    int randomX = rand() % dataVec + shiftVec;
    int randomY = rand() % FieldConfig::WIDTH;
    field.applyFirstRule(field.getCell(randomX, randomY), shiftVec);
    std::cout << randomX << std::endl;
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
    Field field;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    dataVec = new int[size];
    shiftVec = new int[size];
    dataDistribution(dataVec, shiftVec, size);
    field.initProcField(dataVec[rank], shiftVec[rank]);

    for (int i = 0; i < 5000; ++i) {
        for (int j = 0; j < FieldConfig::LENGTH * FieldConfig::WIDTH; ++j) {
            updateField(field, dataVec[rank], shiftVec[rank]);
        }
        //MPI_Allgatherv(field.getProcField(), dataVec[rank], );
        if (rank == 0) {
            field.printMainField();
        }
    }
    /* if (rank == 3){
         for (int i = 0; i < 10; ++i){
             updateField(field, dataVec, shiftVec, rank, size);
         }
     }*/
    MPI_Finalize();
    delete[] dataVec;
    delete[] shiftVec;
    return 0;
}
