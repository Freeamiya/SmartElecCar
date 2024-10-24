//
// Created by Free on 2024/10/23.
//

#include "Flag.h"
#include "headfile.h"

Flag_t Flags;

void Flags_Init(void)
{
    Flags.Flag_Out_L = 0;
    Flags.Flag_Out_R = 0;
    Flags.Flag_Stop = 0;
}