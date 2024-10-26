#ifndef __ADC_H
#define __ADC_H

#define EDGE_PROTECT 	12

extern float ADC_proc[];
extern float Ratio;


void ADC_InitAll(void);
void ADC_GetValue(void);
void Get_Ratio(void);

float sqrtf_custom(float x);
#endif
