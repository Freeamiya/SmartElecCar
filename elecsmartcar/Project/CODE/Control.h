//
// Created by Free on 2024/10/23.
//

#ifndef INC_1_ELECCAR_CONTROL_H
#define INC_1_ELECCAR_CONTROL_H

#define NORMAL_SPEED 280
extern float Exp_Speed;
extern float Exp_Speed_L,Exp_Speed_R;
extern short gx,gy,gz;
extern float Act_PwmL,Act_PwmR;
void Control_Speed(void);

#endif //INC_1_ELECCAR_CONTROL_H
