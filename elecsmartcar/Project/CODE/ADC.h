#ifndef __ADC_H
#define __ADC_H

#define EDGE_PROTECT 	12

extern float ADC_proc[];
extern float Ratio;
extern float Last_Ratio;


void ADC_InitAll(void);
void ADC_GetValue(void);
void Get_Ratio(void);
float Voltage_Detect(void);
#endif
