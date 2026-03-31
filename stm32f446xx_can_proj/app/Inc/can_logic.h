/*
 * can_logic.h
 *
 *  Created on: 28 mar 2026
 *      Author: erjo_
 */

#ifndef APP_INC_CAN_LOGIC_H_
#define APP_INC_CAN_LOGIC_H_
#include <stdint.h>
#include <string.h>
typedef struct{
	float Preasure;
	float Temp;
	uint8_t Humidity;
}Telemetry_t;

void TelemetryDecode(uint8_t *raw_data,Telemetry_t *telemetry_data);
void TelemetryCode(float press, float temp, uint8_t humidity, uint8_t *raw_data);



#endif /* APP_INC_CAN_LOGIC_H_ */
