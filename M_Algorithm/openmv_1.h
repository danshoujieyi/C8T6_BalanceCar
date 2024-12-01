//
// Created by Áõ¼Î¿¡ on 24-9-22.
//

#ifndef C8T6_BALANCE_OPENMV_1_H
#define C8T6_BALANCE_OPENMV_1_H

#include "stm32f1xx.h"


void openmv_receive_data(int16_t com_data);

void coordinate_transformation(uint8_t center_x_temp, uint8_t center_y_temp);

#endif //C8T6_BALANCE_OPENMV_1_H
