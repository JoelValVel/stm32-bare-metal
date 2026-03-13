#include "stm32f445xx_systick.h"

/**
 * @brief  Inicializa y configura el temporizador SysTick.
 *
 * @details
 * Configura la fuente de clock y el período de recarga del SysTick.
 * El contador se detiene durante la configuración para evitar
 * interrupciones o recargas inesperadas, y se limpia CVR para
 * garantizar que el primer conteo sea completo desde RVR hasta 0.
 *
 * Secuencia de inicialización:
 * 1. Deshabilita SysTick para configuración segura
 * 2. Configura la fuente de clock (HCLK o HCLK/8)
 * 3. Carga el valor de recarga en RVR
 * 4. Limpia el contador actual (CVR = 0)
 *
 * @note  Esta función no habilita SysTick ni su interrupción.
 *        Llamar a SYSTICK_Cmd(ENABLE) y SYSTICK_ITConfig(ENABLE)
 *        por separado después de esta función.
 *
 * @note  El período de interrupción se calcula como:
 * @code
 *   T = (SYSTICK_Period + 1) / f_clock
 *
 *   Ejemplo: SYSTICK_Period = 15999, f_clock = 16 MHz → T = 1 ms
 * @endcode
 *
 * @param[in]  SYSTICK_config  Puntero a la estructura de configuración
 *                             con los campos:
 *                             - SYSTICK_Clock_Source : HCLK o HCLK/8
 *                             - SYSTICK_Period       : valor de recarga (RVR)
 *
 * @pre   El clock del sistema debe estar configurado antes de llamar
 *        esta función, ya que SYSTICK_Period depende de f_clock.
 *
 * @see   SYSTICK_Cmd()
 * @see   SYSTICK_ITConfig()
 * @see   ARMv7-M Architecture Reference Manual — sección B3.3 (SysTick)
 */
void SYSTICK_Init(SYSTICK_Config_t *SYSTICK_config)
{
    /* Detiene el contador antes de modificar registros de configuración */
    SYSTICK_Cmd(DISABLE);

    /* Selecciona la fuente de clock: HCLK completo o HCLK dividido entre 8 */
    SYSTICK->CSR &= ~(0x01 << SYSTICK_CSR_CLKSOURCE);
    SYSTICK->CSR |= (SYSTICK_config->SYSTICK_Clock_Source << SYSTICK_CSR_CLKSOURCE);

    /* Carga el valor de recarga — SysTick contará desde este valor hasta 0 */
    SYSTICK->RVR = SYSTICK_config->SYSTICK_Period;

    /* Limpia el contador actual para que el primer período sea completo */
    SYSTICK->CVR = 0;
}


/**
 * @brief  Habilita o deshabilita el contador SysTick.
 *
 * @details
 * Controla el bit ENABLE del registro CSR. Cuando se deshabilita,
 * el contador se congela en su valor actual — no se reinicia.
 *
 * @param[in]  status  ENABLE  para iniciar el conteo.
 *                     DISABLE para detener el conteo.
 *
 * @see   SYSTICK_Init()
 * @see   SYSTICK_ITConfig()
 */
void SYSTICK_Cmd(uint8_t status)
{
    if(status == ENABLE)
    {
        SYSTICK->CSR |= (0x01 << SYSTICK_CSR_ENABLE);
    }else if(status == DISABLE)
    {
        SYSTICK->CSR &= ~(0x01 << SYSTICK_CSR_ENABLE);
    }
}


/**
 * @brief  Habilita o deshabilita la interrupción del SysTick.
 *
 * @details
 * Controla el bit TICKINT del registro CSR. Cuando está habilitada,
 * se genera una excepción SysTick cada vez que CVR llega a 0,
 * invocando automáticamente SysTick_Handler().
 *
 * @note  Habilitar la interrupción no inicia el contador.
 *        Llamar a SYSTICK_Cmd(ENABLE) para iniciar el conteo.
 *
 * @param[in]  status  ENABLE  para generar interrupción al llegar a 0.
 *                     DISABLE para ignorar el evento de recarga.
 *
 * @see   SYSTICK_Cmd()
 * @see   SysTick_Handler()
 */
void SYSTICK_ITConfig(uint8_t status)
{
    if(status == ENABLE)
    {
        SYSTICK->CSR |= (0x01 << SYSTICK_CSR_TICKINT);
    }else if(status == DISABLE)
    {
        SYSTICK->CSR &= ~(0x01 << SYSTICK_CSR_TICKINT);
    }
}


/**
 * @brief  Retorna el valor actual del contador SysTick (CVR).
 *
 * @details
 * CVR es descendente — cuenta desde RVR hasta 0. El valor retornado
 * representa cuántos ticks faltan para la próxima interrupción.
 *
 * @return  Valor actual del registro CVR (0 a RVR).
 *
 * @see   SYSTICK_SetPeriod()
 */
uint32_t SYSTICK_GetCounter(void)
{
    return SYSTICK->CVR;
}


/**
 * @brief  Actualiza el valor de recarga del SysTick (RVR).
 *
 * @details
 * El nuevo período toma efecto en el siguiente ciclo de recarga,
 * es decir, después de que CVR llegue a 0. El conteo actual
 * no se ve afectado inmediatamente.
 *
 * @note  El período de interrupción resultante será:
 * @code
 *   T = (value + 1) / f_clock
 * @endcode
 *
 * @param[in]  value  Nuevo valor de recarga. Rango válido: 0 a 0x00FFFFFF
 *                    (SysTick es de 24 bits en ARMv7-M).
 *
 * @see   SYSTICK_GetCounter()
 */
void SYSTICK_SetPeriod(uint32_t value)
{
    SYSTICK->RVR = value;
}


/**
 * @brief  Retorna el estado del flag COUNTFLAG del registro CSR.
 *
 * @details
 * COUNTFLAG se pone en 1 cuando CVR llega a 0, independientemente
 * de si la interrupción está habilitada. Se limpia automáticamente
 * al leer el registro CSR.
 *
 * Útil para polling sin necesidad de habilitar la interrupción:
 * @code
 *   while(!SYSTICK_GetCountFlag());  // espera un período completo
 * @endcode
 *
 * @return  1 si CVR llegó a 0 desde la última lectura, 0 en caso contrario.
 *
 * @see   SYSTICK_ITConfig()
 */
uint8_t SYSTICK_GetCountFlag(void)
{
    return ((SYSTICK->CSR & (1 << SYSTICK_CSR_COUNTFLAG)) != 0);
}


/**
 * @brief  Retorna el valor del registro de calibración del SysTick (CALIB).
 *
 * @details
 * El registro CALIB contiene el valor de recarga sugerido para generar
 * una interrupción cada 10 ms con el clock del procesador nominal.
 * Campos relevantes:
 * - TENMS[23:0] : valor de recarga para 10 ms (puede ser 0 si no disponible)
 * - SKEW  [30]  : 1 si TENMS no es exacto
 * - NOREF [31]  : 1 si no hay clock de referencia separado disponible
 *
 * @return  Valor completo del registro CALIB.
 *
 * @note  En el STM32F446RE el valor TENMS puede no estar implementado.
 *        Verificar el bit NOREF antes de usar este valor para calibración.
 *
 * @see   ARMv7-M Architecture Reference Manual — registro SYST_CALIB
 */
uint32_t SYSTICK_GetCalib(void)
{
    return SYSTICK->CALIB;
}
