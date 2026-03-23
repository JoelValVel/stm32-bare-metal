/*
 * BSP_WWDG.h
 *
 *  Created on: 12 mar 2026
 *      Author: erjo_
 */

#ifndef INC_BSP_WWDG_H_
#define INC_BSP_WWDG_H_

#include "stm32f446xx_wwdg.h"
void WWDG_Setup(void);

extern WWDG_Config_t	WWDG_config;

#endif /* INC_BSP_WWDG_H_ */
