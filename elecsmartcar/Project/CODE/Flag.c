//
// Created by Free on 2024/10/23.
//

#include "Flag.h"
#include "headfile.h"
Flag_t Flags;
Parameter_t Params;
void Flags_Init(Flag_t *flags,uint8 Flag_Out_L,uint8 Flag_Out_R,uint8 Flag_Stop)
{
    flags->Flag_Out_L = Flag_Out_L;
    flags->Flag_Out_R = Flag_Out_R;
    flags->Flag_Stop = Flag_Stop;
}
void Param_Init(Parameter_t *params,float a,float b,float c)
{
    params->A = a;
    params->B = b;
    params->C = c;
}
