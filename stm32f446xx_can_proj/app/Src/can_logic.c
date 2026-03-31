
#include "can_logic.h"


void TelemetryDecode(uint8_t *raw_data,Telemetry_t *telemetry_data)
{
	uint16_t raw_temp;
	memcpy(&telemetry_data->Preasure, raw_data,4);

	raw_temp = (uint16_t)(raw_data[5] <<8 | raw_data[4]);
	telemetry_data->Temp = (float)(raw_temp / 100.0);

	telemetry_data->Humidity = raw_data[6];

}
void TelemetryCode(float press, float temp, uint8_t humidity, uint8_t *raw_data)
{
	uint16_t raw_temp;

	memcpy(raw_data,&press,4);

	raw_temp = (uint16_t)(temp*100);
	raw_data[4] = (uint8_t)(raw_temp & 0xFF);
	raw_data[5] = (uint8_t)((raw_temp>>8) & 0xFF);

	raw_data[6] = humidity;
}
