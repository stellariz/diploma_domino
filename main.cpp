#include "Field/Field.h"
#include "Field/FieldConfig.h"
#include <mpi/mpi.h>
#include <unistd.h>


void updateField(Field &field) {
    int randomX = rand() % FieldConfig::LENGTH + 1;
    int randomY = rand() % FieldConfig::WIDTH + 1;
    field.applyTemplates(field.getCell(randomX, randomY));
}


//void waitEndOfCommunication(MPI_Request *reqr, MPI_Request *reqs, const int rank, const int size) {
//    if (rank != 0) {
//        MPI_Wait(&reqs[0], MPI_STATUS_IGNORE);
//        MPI_Wait(&reqr[1], MPI_STATUS_IGNORE);
//    }
//    if (rank != size - 1) {
//        MPI_Wait(&reqs[1], MPI_STATUS_IGNORE);
//        MPI_Wait(&reqr[0], MPI_STATUS_IGNORE);
//    }
//}


//void sendBoundaries(Field &field, MPI_Datatype cellType, const int sizePerProc, MPI_Request *reqs, MPI_Request *reqr,
//                    const int rank, const int size) {
//    if (rank != 0) {
//        MPI_Isend(field.getLowerBound(rank), 3 * FieldConfig::LENGTH, cellType, rank - 1, 123,
//                  MPI_COMM_WORLD, &reqs[0]);
//        MPI_Irecv(field.getLowerBound(rank) - 3 * FieldConfig::LENGTH, 3 * FieldConfig::LENGTH, cellType, rank - 1, 345,
//                  MPI_COMM_WORLD, &reqr[1]);
//    }
//    if (rank != size - 1) {
//        MPI_Isend(field.getUpperBound(rank, sizePerProc) - 3 * FieldConfig::LENGTH, 3 * FieldConfig::LENGTH, cellType,
//                  rank + 1, 345, MPI_COMM_WORLD, &reqs[1]);
//        MPI_Irecv(field.getUpperBound(rank, sizePerProc), 3 * FieldConfig::LENGTH, cellType, rank + 1, 123,
//                  MPI_COMM_WORLD,
//                  &reqr[0]);
//    }
//}
//
//
//void dataDistribution(int *dataVec, int *shiftVec, const int numProcs) {
//    dataVec[0] = (FieldConfig::WIDTH / numProcs) * FieldConfig::LENGTH;
//    shiftVec[0] = 0;
//    int restRows = FieldConfig::WIDTH;
//    for (int i = 1; i < numProcs; ++i) {
//        restRows -= dataVec[i - 1] / FieldConfig::LENGTH;
//        dataVec[i] = (restRows / (numProcs - i)) * FieldConfig::LENGTH;
//        shiftVec[i] = (shiftVec[i - 1] + dataVec[i - 1]);
//    }
//}
//
//MPI_Datatype createCellType() {
//    MPI_Datatype cellType;
//    Cell cell;
//    int lengths[6] = {1, 1, 1, 1, 1, 1};
//    MPI_Datatype types[6] = {MPI_INT, MPI_INT, MPI_INT, MPI_INT, MPI_INT, MPI_INT};
//    MPI_Aint disp[6];
//    MPI_Aint base_address;
//    MPI_Get_address(&cell, &base_address);
//    MPI_Get_address(&cell.posX, &disp[0]);
//    MPI_Get_address(&cell.posY, &disp[1]);
//    MPI_Get_address(&cell.curValue, &disp[2]);
//    MPI_Get_address(&cell.matchZeroRefval, &disp[3]);
//    MPI_Get_address(&cell.matchOneRefVal, &disp[4]);
//    MPI_Get_address(&cell.hitValue, &disp[5]);
//    disp[0] = MPI_Aint_diff(disp[0], base_address);
//    disp[1] = MPI_Aint_diff(disp[1], base_address);
//    disp[2] = MPI_Aint_diff(disp[2], base_address);
//    disp[3] = MPI_Aint_diff(disp[3], base_address);
//    disp[4] = MPI_Aint_diff(disp[4], base_address);
//    disp[5] = MPI_Aint_diff(disp[5], base_address);
//    MPI_Type_create_struct(6, lengths, disp, types, &cellType);
//    MPI_Type_commit(&cellType);
//    return cellType;
//}


int main(int argc, char **argv) {
    int dominoes[] = {0, 0, 0, 0, 0, 0};
    for (int k = 0; k < 1000; ++k) {
        Field field;
        for (int i = 0; i < 200; ++i) {
            for (int j = 0; j < FieldConfig::LENGTH * FieldConfig::WIDTH; ++j) {
                updateField(field);
            }
            int numOfDominoes = field.validateField();
            if (numOfDominoes) {
                dominoes[numOfDominoes-5]++;
                break;
            }
        }
    }
    for (int domino : dominoes) {
        std::cout << domino << " ";
    }
    return 0;
}
