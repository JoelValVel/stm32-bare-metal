#include <unity.h>

#include "can_logic.h"

void setUp(void)
{

}

void test_telemetry_decode(void)
{
	Telemetry_t telm;
	uint8_t raw_data[] = {0x00, 0x50, 0x7D, 0x44, 0x5A, 0x0A, 0x2D};
	TelemetryDecode(raw_data, &telm);

	TEST_ASSERT_EQUAL_FLOAT(1013.25f, telm.Preasure);
	TEST_ASSERT_EQUAL_FLOAT(26.50f, telm.Temp);
	TEST_ASSERT_EQUAL_UINT8(45, telm.Humidity);
}

void test_telemetry_code(void)
{
	uint8_t data_coded[8];
	TelemetryCode(1013.25, 26.5, 45, data_coded);

	// Presión (IEEE 754: 0x447D5000)
	TEST_ASSERT_EQUAL_HEX8(0x00, data_coded[0]);
	TEST_ASSERT_EQUAL_HEX8(0x50, data_coded[1]);
	TEST_ASSERT_EQUAL_HEX8(0x7D, data_coded[2]);
	TEST_ASSERT_EQUAL_HEX8(0x44, data_coded[3]);

	// Temperatura (2650 -> 0x0A5A)
	TEST_ASSERT_EQUAL_HEX8(0x5A, data_coded[4]);
	TEST_ASSERT_EQUAL_HEX8(0x0A, data_coded[5]);

	// Humedad (45 -> 0x2D)
	TEST_ASSERT_EQUAL_HEX8(0x2D, data_coded[6]);
}
