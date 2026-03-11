#include "BSP_TIM_ICOC.h"

TIM_Handle_t h_tim2 = {0};
TIM_Handle_t h_tim5 = {0};

/**
 * @brief  Configura el TIM2 en modo Input Capture para el canal 2
 * @note   Utiliza el HSI de 16 MHz sin prescalers en AHB y APBx
 * @note   Periodo maximo de 0xFFFFFFFF aprovechando los 32 bits del TIM2
 * @note   Prescaler de 1 para una resolucion de captura de 125 ns por tick
 * @note   Configurado para capturar en flanco de subida sin filtro ni prescaler
 * @param  none
 * @retval none
 */
void TIM2_IC_Setup(void)
{
    h_tim2.pTIMx = TIM2;
    // periodo maximo para capturar señales de baja frecuencia sin desbordamiento
    h_tim2.TIM_TimeBase.TIM_Period = 0xffffffff;
    // prescaler de 1, el timer corre a 8 MHz (16 MHz / 2)
    h_tim2.TIM_TimeBase.TIM_Prescaler = 1;
    h_tim2.TIM_TimeBase.TIM_CounterMode = TIM_CouterMode_UP;
    // canal 2 en modo directo, flanco de subida, sin filtro ni prescaler
    h_tim2.TIM_InputCapture.TIM_Channel = TIM_CH2;
    h_tim2.TIM_InputCapture.TIM_ICFilter = TIM_ICFilter_NONE;
    h_tim2.TIM_InputCapture.TIM_ICPolarity = TIM_ICPolarity_RE;
    h_tim2.TIM_InputCapture.TIM_ICPrescaler = TIM_ICPrescaler_NONE;
    h_tim2.TIM_InputCapture.TIM_ICSelection = TIM_ICSelection_Direct;

    TIM_ICInit(&h_tim2);
}

/**
 * @brief  Configura el TIM2 en modo Output Compare Toggle para el canal 1
 * @note   Utiliza el HSI de 16 MHz sin prescalers en AHB y APBx
 * @note   Prescaler de 16000 genera un tick de 1 ms
 * @note   Periodo de 1000 ticks genera un periodo de 1 segundo
 * @note   El pin toglea cada vez que CNT alcanza el valor de TIM_Pulse
 * @param  none
 * @retval none
 */
void TIM2_OC_TOGGLE_Setup(void)
{
    h_tim2.pTIMx = TIM2;
    // periodo de 1 segundo con tick de 1 ms
    h_tim2.TIM_TimeBase.TIM_Period = 1000 - 1;
    // prescaler para obtener un tick de 1 ms con HSI de 16 MHz
    h_tim2.TIM_TimeBase.TIM_Prescaler = 16000 - 1;
    h_tim2.TIM_TimeBase.TIM_CounterMode = TIM_CouterMode_UP;
    // canal 1 en modo toggle con polaridad activa alta
    h_tim2.TIM_OutputCompare.TIM_Channel = TIM_CH1;
    h_tim2.TIM_OutputCompare.TIM_OCMode = TIM_OCMode_Toggle;
    h_tim2.TIM_OutputCompare.TIM_OCPolarity = TIM_OCPolarity_Active_HIGH;
    // el toggle ocurre cuando CNT alcanza 1000
    h_tim2.TIM_OutputCompare.TIM_Pulse = 1000;

    TIM_OC_Init(&h_tim2);
}

/**
 * @brief  Configura el TIM2 en modo Output Compare Toggle para los 4 canales
 * @note   Utiliza el HSI de 16 MHz sin prescalers en AHB y APBx
 * @note   Prescaler de 16000 genera un tick de 1 ms
 * @note   Periodo de 1000 ticks genera un periodo de 1 segundo
 * @note   Los 4 canales tienen diferentes valores de comparacion generando
 *         señales desfasadas entre si:
 *         - CH1: toggle en 250 ms
 *         - CH2: toggle en 500 ms
 *         - CH3: toggle en 750 ms
 *         - CH4: toggle en 1000 ms
 * @param  none
 * @retval none
 */
void TIM2_OC_TOGGLE_4Channels_Setup(void)
{
    h_tim2.pTIMx = TIM2;
    // periodo de 1 segundo con tick de 1 ms
    h_tim2.TIM_TimeBase.TIM_Period = 1000 - 1;
    // prescaler para obtener un tick de 1 ms con HSI de 16 MHz
    h_tim2.TIM_TimeBase.TIM_Prescaler = 16000 - 1;
    h_tim2.TIM_TimeBase.TIM_CounterMode = TIM_CouterMode_UP;

    // canal 1 — toggle en 250 ms
    h_tim2.TIM_OutputCompare.TIM_Channel = TIM_CH1;
    h_tim2.TIM_OutputCompare.TIM_OCMode = TIM_OCMode_Toggle;
    h_tim2.TIM_OutputCompare.TIM_OCPolarity = TIM_OCPolarity_Active_HIGH;
    h_tim2.TIM_OutputCompare.TIM_Pulse = 250 - 1;
    TIM_OC_Init(&h_tim2);

    // canal 2 — toggle en 500 ms, hereda modo y polaridad del CH1
    h_tim2.TIM_OutputCompare.TIM_Channel = TIM_CH2;
    h_tim2.TIM_OutputCompare.TIM_Pulse = 500 - 1;
    TIM_OC_Init(&h_tim2);

    // canal 3 — toggle en 750 ms, hereda modo y polaridad del CH1
    h_tim2.TIM_OutputCompare.TIM_Channel = TIM_CH3;
    h_tim2.TIM_OutputCompare.TIM_Pulse = 750 - 1;
    TIM_OC_Init(&h_tim2);

    // canal 4 — toggle en 1000 ms, hereda modo y polaridad del CH1
    h_tim2.TIM_OutputCompare.TIM_Channel = TIM_CH4;
    h_tim2.TIM_OutputCompare.TIM_Pulse = 1000 - 1;
    TIM_OC_Init(&h_tim2);
}


/**
 * @brief  Configura el Timer 2 (TIM2) en modo PWM para el STM32F446RE.
 *
 * @details
 * Esta función inicializa TIM2 con las siguientes características:
 *
 * - **Clock fuente**: HSI interno a 16 MHz
 * - **Prescaler**: 9 → el timer recibe 16 MHz / (9+1) = **1.6 MHz**
 * - **Periodo (ARR)**: 1500 → frecuencia PWM = 1.6 MHz / 1500 ≈ **1.067 kHz**
 * - **Tick efectivo**: 1 / 1.6 MHz ≈ **625 ns por tick**
 * - **Canal**: CH1 en modo PWM1 con polaridad activa alta
 * - **Duty cycle inicial**: 0% (TIM_Pulse = 0)
 *
 * @note
 * Para modificar el duty cycle en tiempo de ejecución, actualizar el registro
 * CCR1 directamente:
 * @code
 *   TIM2->CCR1 = <nuevo_valor>;  // Rango: 0 a TIM_Period (0% a 100%)
 * @endcode
 *
 * @pre  El clock del sistema debe estar configurado con HSI a 16 MHz.
 * @pre  El pin correspondiente al canal CH1 de TIM2 debe configurarse
 *       en modo Alternate Function (AF1) antes de llamar esta función.
 *
 * @see  TIM_OC_Init()
 * @see  STM32F446RE Reference Manual — sección 18 (General-purpose timers)
 */
void TIM2_PWM_Setup(void)
{
    h_tim2.pTIMx = TIM2;

    // Período del PWM: 1500 ticks × 625 ns/tick ≈ 937.5 µs (~1.067 kHz)

    h_tim2.TIM_TimeBase.TIM_Period = 1500;

    // Prescaler = 9 → f_CK_CNT = 16 MHz / (9+1) = 1.6 MHz (tick ≈ 625 ns)
    h_tim2.TIM_TimeBase.TIM_Prescaler = 9;

    /* Modo de conteo ascendente: CNT incrementa de 0 hasta TIM_Period */
    h_tim2.TIM_TimeBase.TIM_CounterMode = TIM_CouterMode_UP;

    /* Canal 1 configurado en modo PWM con polaridad activa alta:
     * La salida es HIGH mientras CNT < CCR1, y LOW cuando CNT >= CCR1 */
    h_tim2.TIM_OutputCompare.TIM_Channel    = TIM_CH1;
    h_tim2.TIM_OutputCompare.TIM_OCMode     = TIM_OCMode_PWM1;
    h_tim2.TIM_OutputCompare.TIM_OCPolarity = TIM_OCPolarity_Active_HIGH;

    /* Duty cycle inicial = 0%: la salida permanece en LOW hasta que
     * se actualice CCR1 con un valor mayor que 0. */
    h_tim2.TIM_OutputCompare.TIM_Pulse = 0;

    TIM_OC_Init(&h_tim2);
}

/**
 * @brief  Configura TIM5 en modo PWM Input para medir frecuencia y duty cycle.
 *
 * @details
 * Implementa el modo "PWM Input" usando dos canales sobre una misma señal física:
 *
 * - **CH1 (Direct,   flanco de subida)**: captura el período completo de la señal.
 *   El valor de CNT en cada subida queda guardado en CCR1.
 * - **CH2 (Indirect, flanco de bajada)**: captura el tiempo en alto (pulso).
 *   El valor de CNT en la bajada queda guardado en CCR2.
 *
 * Con ambos valores se puede calcular:
 * @code
 *   Periodo    = CCR1  (gracias al reset por slave mode)
 *   Pulso alto = CCR2
 *   Duty cycle = (CCR2 / CCR1) * 100  [%]
 *   Frecuencia = f_CK_CNT / CCR1
 * @endcode
 *
 * El Slave Reset Mode reinicia CNT en cada flanco de subida de TI1,
 * por lo que CCR1 siempre representa exactamente un período completo.
 *
 * Parámetros del timer:
 * - **Clock fuente** : HSI 16 MHz
 * - **Prescaler**    : 1  → f_CK_CNT = 16 MHz / (1+1) = **8 MHz** (tick = 125 ns)
 * - **Period (ARR)** : 0xFFFFFFFF → desbordamiento cada ~537 segundos,
 *                      permitiendo medir señales de muy baja frecuencia
 * - **Rango medible**: desde ~0.002 Hz hasta 4 MHz (la señal debe tener
 *                      al menos 2 ticks de período para ser distinguible)
 *
 * @note  Solo se requiere conexión física en el pin de CH1 (TI1).
 *        CH2 recibe la misma señal internamente vía IC Selection Indirect.
 *
 * @note  TIM5 es el único timer de 32 bits en el STM32F446RE, lo que lo hace
 *        ideal para captura de señales de baja frecuencia sin riesgo de
 *        desbordamiento prematuro.
 *
 * @pre   El pin asignado a TI1 (CH1 de TIM5) debe configurarse en modo
 *        Alternate Function antes de llamar esta función.
 * @pre   El clock de TIM5 debe estar habilitado en RCC.
 *
 * @see   TIM_ICInit()
 * @see   TIM_InputTrigger()
 * @see   TIM_SlaveMode()
 * @see   STM32F446RE Reference Manual — sección 18.3.6 (PWM input mode)
 */
void TIM5_PWM_M_Setup(void)
{
    h_tim5.pTIMx = TIM5;

    /* Prescaler = 1 → f_CK_CNT = 8 MHz (tick = 125 ns).
     * Equilibrio entre resolución temporal y rango de frecuencias medibles */
    h_tim5.TIM_TimeBase.TIM_Prescaler = 1;

    /* ARR al máximo de 32 bits: evita desbordamiento en señales de baja frecuencia
     * y aprovecha que TIM5 es el único timer de 32 bits del STM32F446RE */
    h_tim5.TIM_TimeBase.TIM_Period = 0xffffffff;

    h_tim5.TIM_TimeBase.TIM_CounterMode = TIM_CouterMode_UP;

    /* CH1 Direct en flanco de subida: captura CNT al inicio de cada período.
     * Con el Slave Reset Mode activo, CCR1 = duración de un período completo */
    h_tim5.TIM_InputCapture.TIM_Channel    = TIM_CH1;
    h_tim5.TIM_InputCapture.TIM_ICPolarity = TIM_ICPolarity_RE;
    h_tim5.TIM_InputCapture.TIM_ICSelection = TIM_ICSelection_Direct;
    TIM_ICInit(&h_tim5);

    /* CH2 Indirect en flanco de bajada: recibe TI1 internamente (sin pin físico).
     * CCR2 = tiempo en alto → permite calcular duty cycle como CCR2/CCR1 */
    h_tim5.TIM_InputCapture.TIM_Channel    = TIM_CH2;
    h_tim5.TIM_InputCapture.TIM_ICPolarity = TIM_ICPolarity_FE;
    h_tim5.TIM_InputCapture.TIM_ICSelection = TIM_ICSelection_Indirect;
    TIM_ICInit(&h_tim5);

    /* TI1 filtrada como trigger: sincroniza el timer esclavo con la señal de entrada */
    TIM_InputTrigger(h_tim5.pTIMx, TIM_Trigger_Filtered_Timer_Input_1);

    /* Reset Mode: CNT se reinicia a 0 en cada flanco de subida de TI1,
     * garantizando que CCR1 represente exactamente un período por ciclo */
    TIM_SlaveMode(h_tim5.pTIMx, TIM_Slave_Reset_Mode);
}

/**
 * @brief  Configura TIM5 en modo Encoder para lectura de encoder rotatorio.
 *
 * @details
 * Implementa el modo Encoder tipo 2 (TIM_Slave_Encoder_Mode_2), en el cual
 * el timer cuenta los flancos de la señal TI2 (CH2) únicamente, usando TI1 (CH1)
 * para determinar la dirección de conteo:
 *
 * - **CH1 (Direct, flanco de subida)**: señal A del encoder — indica dirección
 * - **CH2 (Direct, flanco de subida)**: señal B del encoder — genera los pulsos de conteo
 *
 * El valor de CNT refleja la posición actual del encoder:
 * - CNT incrementa cuando el encoder gira en sentido horario
 * - CNT decrementa cuando el encoder gira en sentido antihorario
 *
 * Parámetros del timer:
 * - **Prescaler** : 0 → el clock del bus no es la fuente de conteo en modo encoder,
 *                   TI1/TI2 reemplazan al clock, por lo que el prescaler es irrelevante
 * - **Period (ARR)**: 0xFFFFFFFF → aprovecha los 32 bits de TIM5 para maximizar
 *                     el rango de conteo sin desbordamiento prematuro
 *
 * @note  TIM5 es el único timer de 32 bits del STM32F446RE, lo que permite
 *        un rango de conteo de 0 a 4,294,967,295 pasos sin desbordamiento.
 *
 * @note  En modo encoder el prescaler no tiene efecto útil ya que el clock
 *        del bus es ignorado — la fuente de conteo son los flancos de TI1/TI2.
 *
 * @pre   Los pines de CH1 y CH2 de TIM5 deben configurarse en modo
 *        Alternate Function antes de llamar esta función.
 * @pre   El clock de TIM5 debe estar habilitado en RCC.
 *
 * @see   TIM_ICInit()
 * @see   TIM_SlaveMode()
 * @see   STM32F446RE Reference Manual — sección 18.3.12 (Encoder interface mode)
 */
void TIM5_Encoder_Setup(void)
{
	h_tim5.pTIMx = TIM5;

	    /* En modo encoder el clock del bus no es la fuente de conteo (la fuente
	     * son TI1/TI2), por lo que el prescaler no tiene efecto útil */
	    h_tim5.TIM_TimeBase.TIM_Prescaler = 0;

	    /* ARR al máximo de 32 bits: aprovecha que TIM5 es el único timer de 32 bits
	     * del STM32F446RE, maximizando el rango de posición sin desbordamiento */
	    h_tim5.TIM_TimeBase.TIM_Period = 0xffffffff;

	    h_tim5.TIM_TimeBase.TIM_CounterMode = TIM_CouterMode_UP;

	    /* CH1 Direct en flanco de subida: señal A del encoder.
	     * En Encoder Mode 2 esta señal determina la dirección de conteo */
	    h_tim5.TIM_InputCapture.TIM_Channel     = TIM_CH1;
	    h_tim5.TIM_InputCapture.TIM_ICPolarity  = TIM_ICPolarity_RE;
	    h_tim5.TIM_InputCapture.TIM_ICSelection = TIM_ICSelection_Direct;
	    TIM_ICInit(&h_tim5);

	    /* CH2 Direct en flanco de subida: señal B del encoder.
	     * En Encoder Mode 2 esta señal genera los pulsos que incrementan o
	     * decrementan CNT según la dirección indicada por CH1 */
	    h_tim5.TIM_InputCapture.TIM_Channel     = TIM_CH2;
	    h_tim5.TIM_InputCapture.TIM_ICPolarity  = TIM_ICPolarity_RE;
	    h_tim5.TIM_InputCapture.TIM_ICSelection = TIM_ICSelection_Direct;
	    TIM_ICInit(&h_tim5);

	    /* Encoder Mode 2: CNT cuenta los flancos de TI2 usando TI1 para
	     * determinar dirección — CNT++ horario, CNT-- antihorario */
	    TIM_SlaveMode(h_tim5.pTIMx, TIM_Slave_Encoder_Mode_2);
}



void TIM2_IT_ICOC_Setup(void)
{
	// habilitamos la interupcion en el periferico TIMER
	TIM_ITConfig(h_tim2.pTIMx, TIM_SR_CC2IF, ENABLE);
	// habilitamos el IRQ del ISER del nvic
	NVIC_IRQ_Enable(IRQ_TIM2);
}

void TIM2_IRQHandler(void)
{
	TIM_IRQHandler(&h_tim2);
}
