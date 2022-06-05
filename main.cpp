#include "Field/Field.h"
#include "Field/FieldConfig.h"

void updateField(Field &field) {
    int randomX = rand() % FieldConfig::LENGTH + 1;
    int randomY = rand() % FieldConfig::WIDTH + 1;
    field.applyTemplates(field.getCell(randomX, randomY));
}


int main() {
    int dominoes[] = {0, 0, 0, 0, 0, 0};
    const int nonGapState = 0;
    const int total_iter = 1000;
    const int T_max = 200;
    double total_step = 0;
    Field field;
    for (int k = 0; k < total_iter; ++k) {
        field.initField();
        for (int i = 0; i < T_max; ++i) {
            for (int j = 0; j < FieldConfig::LENGTH * FieldConfig::WIDTH; ++j) {
                updateField(field);
            }
            int numOfDominoes = field.validateField();
            if (numOfDominoes >= 5) {
                dominoes[numOfDominoes - 5]++;
                total_step += i;
                break;
            }
        }
    }
    for (int domino: dominoes) {
        std::cout << domino << " ";
    }
    std::cout << std::endl;
    std::cout << "t_avg= " << total_step / total_iter;
    return 0;
}
