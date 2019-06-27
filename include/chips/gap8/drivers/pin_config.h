#ifndef __PMSIS_PIN_CONFIG_H__
#define __PMSIS_PIN_CONFIG_H__

#include "pmsis.h"

/*! @brief Pin mux selection */
typedef enum _port_mux
{
    PORT_MUX_ALT0 = 0U,           /*!< Default */
    PORT_MUX_ALT1 = 1U,           /*!< Corresponding pin is configured as GPIO. */
    PORT_MUX_GPIO = PORT_MUX_ALT1,/*!< Corresponding pin is configured as GPIO. */
    PORT_MUX_ALT2 = 2U,           /*!< Chip-specific */
    PORT_MUX_ALT3 = 3U,           /*!< Chip-specific */
} port_mux_t;

static inline void port_set_pin_mux(PORT_Type *base, uint32_t pin, port_mux_t mux)
{
    int reg_num = (pin >> 4) & 0x3;
    /* Positon in the target register */
    int pos = pin & 0xF;
    int val = base->PADFUN[reg_num];
    val &= ~(PORT_PADFUN_MUX_MASK << (pos << 1));
    base->PADFUN[reg_num] = val | (uint32_t)(mux << (pos << 1));
}

void pin_function(pin_mode_e pin, int function);

void pin_mode(pin_name_e pin, pin_mode_e mode);

#endif
