#include "Field/Field.h"
#include "Field/FieldConfig.h"


int main() {
    const int total_iter = 1000;
    const int T_max = 200;
    Field field;
    for (int m = 0; m < total_iter; ++m) {
        int dominoes[] = {0, 0, 0, 0, 0, 0};
        double total_step = 0;
        for (int k = 0; k < total_iter; ++k) {
            field.initField();
            for (int i = 0; i < T_max; ++i) {
                for (int posY = 1; posY <= FieldConfig::WIDTH; ++posY) {
                    for (int posX = 1; posX <= FieldConfig::LENGTH; ++posX) {
                        field.applyTemplates(field.getCell(posX, posY));
                    }
                }
                field.updateEvolveState();
                int numOfDominoes = field.validateField();
                if (numOfDominoes >= 5) {
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
        std::cout << "t_avg = " << total_step / total_iter << std::endl;
    }
    return 0;
}
