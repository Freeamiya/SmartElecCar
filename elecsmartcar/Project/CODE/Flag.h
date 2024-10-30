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
void Flags_Init(Flag_t *flags,uint8 Flag_Out_L,uint8 Flag_Out_R,uint8 Flag_Stop);

typedef struct {
    float A;
    float B;
    float C;
} Parameter_t;

extern Parameter_t Params;
void Param_Init(Parameter_t *params,float a,float b,float c);
#endif //INC_1_ELECCAR_FLAG_H
