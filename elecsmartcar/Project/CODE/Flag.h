//
// Created by Free on 2024/10/23.
//

#ifndef INC_1_ELECCAR_FLAG_H
#define INC_1_ELECCAR_FLAG_H

#include"common.h"

typedef struct {
    uint8 Flag_Out_L;
    uint8 Flag_Out_R;
    uint8 Flag_Stop;
} Flag_t;

extern Flag_t Flags;

void Flags_Init(void);
#endif //INC_1_ELECCAR_FLAG_H
