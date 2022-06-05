#include "Field/Field.h"
#include "Field/FieldConfig.h"


int main() {
    int dominoes[] = {0, 0, 0, 0, 0, 0};
    const int nonGapState = 0;
    const int T_max = 200;
    double t_avg = 0;
    Field field;
    for (int k = 0; k < 1000; ++k) {
        std::cout << k << std::endl;
        field.initField();
        for (int i = 0; i < T_max; ++i) {
            for (int posY = 1; posY <= FieldConfig::WIDTH; ++posY){
                for (int posX = 1; posX <= FieldConfig::LENGTH; ++posX){
                    field.applyTemplates(field.getCell(posX, posY));
                }
            }
            int changedCells = field.updateEvolveState();
            int numOfDominoes = field.validateField();
            if (changedCells <= nonGapState && numOfDominoes >= 5) {
                dominoes[numOfDominoes - 5]++;
                field.printMainField();
                t_avg += i;
                break;
            }
        }
    }
    for (int domino: dominoes) {
        std::cout << domino << " ";
    }
    std::cout << std::endl;
    std::cout << "t_avg = " << t_avg / 1000;
    return 0;
}
