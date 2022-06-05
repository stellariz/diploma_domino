#include "Field/Field.h"
#include "Field/FieldConfig.h"


int main() {
    int dominoes[] = {0, 0, 0, 0, 0, 0};
    const int gaps_number = 0;
    const int total_iter = 1000;
    const int T_max = 200;
    double total_step = 0;
    Field field;
    for (int k = 0; k < total_iter; ++k) {
        field.initField();
        for (int i = 0; i < T_max; ++i) {
            for (int posY = 1; posY <= FieldConfig::WIDTH; ++posY){
                for (int posX = 1; posX <= FieldConfig::LENGTH; ++posX){
                    field.applyTemplates(field.getCell(posX, posY));
                }
            }
            // 25
            int changedCells = field.updateEvolveState();
            int numOfDominoes = field.validateField();
            if (changedCells <= gaps_number && numOfDominoes >= 5) {
                dominoes[numOfDominoes - 5]++;
                total_step += i;
                break;
            }
        }
    }
    for (const int domino: dominoes) {
        std::cout << domino << " ";
    }
    std::cout << std::endl;
    std::cout << "total_step = " << total_step / total_iter;
    return 0;
}
