/*
 * Copyright 2009 Freescale Semiconductor, Inc. All Rights Reserved.
 */

/*
 * The code contained herein is licensed under the GNU General Public
 * License. You may obtain a copy of the GNU General Public License
 * Version 2 or later at the following locations:
 *
 * http://www.opensource.org/licenses/gpl-license.html
 * http://www.gnu.org/copyleft/gpl.html
 */

////////////////////////////////////////////////////////////////////////////////
// Includes and external references
////////////////////////////////////////////////////////////////////////////////
#include "types.h"
#include "error.h"

#include "hw/power/hw_power.h"
#include "registers/regspower.h"

////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//! See hw_power.h for details.
////////////////////////////////////////////////////////////////////////////////
bool hw_power_EnablePswitchInterrupt(bool bEnable) {
    bool bPrev = BF_RD(POWER_CTRL, ENIRQ_PSWITCH);

    if (bEnable) {
        BF_SET(POWER_CTRL, ENIRQ_PSWITCH);
    } else {
        BF_CLR(POWER_CTRL, ENIRQ_PSWITCH);
    }

    return bPrev;
}

////////////////////////////////////////////////////////////////////////////////
//! See hw_power.h for details.
////////////////////////////////////////////////////////////////////////////////
void hw_power_ClearPswitchInterrupt(void) { BF_CLR(POWER_CTRL, PSWITCH_IRQ); }

////////////////////////////////////////////////////////////////////////////////
//! See hw_power.h for details.
////////////////////////////////////////////////////////////////////////////////
void hw_power_SetPswitchInterruptSource(bool bSource) {
    if (bSource == HW_POWER_STS_PSWITCH_BIT_0) {
        BF_CLR(POWER_CTRL, PSWITCH_IRQ_SRC);
    } else // bSource == HW_POWER_STS_PSWITCH_BIT_1
    {
        BF_SET(POWER_CTRL, PSWITCH_IRQ_SRC);
    }
}

////////////////////////////////////////////////////////////////////////////////
//! See hw_power.h for details.
////////////////////////////////////////////////////////////////////////////////
void hw_power_SetPswitchInterruptPolarity(bool bPolarity) {
    if (bPolarity == HW_POWER_CHECK_PSWITCH_LOW) {
        BF_CLR(POWER_CTRL, POLARITY_PSWITCH);
    }

    // bPolarity == HW_POWER_CHECK_PSWITCH_HIGH
    else {
        BF_SET(POWER_CTRL, POLARITY_PSWITCH);
    }
}

////////////////////////////////////////////////////////////////////////////////
//! See hw_power.h for details.
////////////////////////////////////////////////////////////////////////////////
bool hw_power_GetPswitchInterruptPolarity(void) {
    // used to be hw_power_GetPswitchPolarityFlag
    return HW_POWER_CTRL.B.POLARITY_PSWITCH;
}

////////////////////////////////////////////////////////////////////////////////
//! See hw_power.h for details.
////////////////////////////////////////////////////////////////////////////////
void hw_power_EnableDcOkInterrupt(bool bEnable) {
    if (bEnable) {
        BF_SET(POWER_CTRL, ENIRQ_DC_OK);
    } else {
        BF_CLR(POWER_CTRL, ENIRQ_DC_OK);
    }
}

////////////////////////////////////////////////////////////////////////////////
//! See hw_power.h for details.
////////////////////////////////////////////////////////////////////////////////
void hw_power_ClearDcOkInterrupt(void) { BF_CLR(POWER_CTRL, DC_OK_IRQ); }

////////////////////////////////////////////////////////////////////////////////
//! See hw_power.h for details.
////////////////////////////////////////////////////////////////////////////////
bool hw_power_EnableBatteryBrownoutInterrupt(bool bEnable) {
    bool bPrev = BF_RD(POWER_CTRL, ENIRQBATT_BO);

    if (bEnable) {
        BF_SET(POWER_CTRL, ENIRQBATT_BO);
    } else {
        BF_CLR(POWER_CTRL, ENIRQBATT_BO);
    }

    return bPrev;
}

////////////////////////////////////////////////////////////////////////////////
//! See hw_power.h for details.
////////////////////////////////////////////////////////////////////////////////
void hw_power_ClearBatteryBrownoutInterrupt(void) {
    BF_CLR(POWER_CTRL, BATT_BO_IRQ);
}

////////////////////////////////////////////////////////////////////////////////
//! See hw_power.h for details.
////////////////////////////////////////////////////////////////////////////////
bool hw_power_EnableVddioBrownoutInterrupt(bool bEnable) {
    bool bPrev = BF_RD(POWER_CTRL, ENIRQ_VDDIO_BO);

    if (bEnable) {
        BF_SET(POWER_CTRL, ENIRQ_VDDIO_BO);
    } else {
        BF_CLR(POWER_CTRL, ENIRQ_VDDIO_BO);
    }

    return bPrev;
}

////////////////////////////////////////////////////////////////////////////////
//! See hw_power.h for details.
////////////////////////////////////////////////////////////////////////////////
void hw_power_ClearVddioBrownoutInterrupt(void) {
    BF_CLR(POWER_CTRL, VDDIO_BO_IRQ);
}

////////////////////////////////////////////////////////////////////////////////
//! See hw_power.h for details.
////////////////////////////////////////////////////////////////////////////////
bool hw_power_EnableVddaBrownoutInterrupt(bool bEnable) {
    bool bPrev = BF_RD(POWER_CTRL, ENIRQ_VDDA_BO);

    if (bEnable) {
        BF_SET(POWER_CTRL, ENIRQ_VDDA_BO);
    } else {
        BF_CLR(POWER_CTRL, ENIRQ_VDDA_BO);
    }

    return bPrev;
}

////////////////////////////////////////////////////////////////////////////////
//! See hw_power.h for details.
////////////////////////////////////////////////////////////////////////////////
void hw_power_ClearVddaBrownoutInterrupt(void) {
    BF_CLR(POWER_CTRL, VDDA_BO_IRQ);
}

////////////////////////////////////////////////////////////////////////////////
//! See hw_power.h for details.
////////////////////////////////////////////////////////////////////////////////
bool hw_power_EnableVdddBrownoutInterrupt(bool bEnable) {
    bool bPrev = BF_RD(POWER_CTRL, ENIRQ_VDDD_BO);

    if (bEnable) {
        BF_SET(POWER_CTRL, ENIRQ_VDDD_BO);
    } else {
        BF_CLR(POWER_CTRL, ENIRQ_VDDD_BO);
    }

    return bPrev;
}

////////////////////////////////////////////////////////////////////////////////
//! See hw_power.h for details.
////////////////////////////////////////////////////////////////////////////////
void hw_power_ClearVdddBrownoutInterrupt(void) {
    BF_CLR(POWER_CTRL, VDDD_BO_IRQ);
}

////////////////////////////////////////////////////////////////////////////////
//! See hw_power.h for details.
////////////////////////////////////////////////////////////////////////////////
bool hw_power_EnableVbusValidInterrupt(bool bEnable) {
    bool bPrev = BF_RD(POWER_CTRL, ENIRQ_VBUS_VALID);

    if (bEnable) {
        BF_SET(POWER_CTRL, ENIRQ_VBUS_VALID);
    } else {
        BF_CLR(POWER_CTRL, ENIRQ_VBUS_VALID);
    }

    return bPrev;
}

////////////////////////////////////////////////////////////////////////////////
//! See hw_power.h for details.
////////////////////////////////////////////////////////////////////////////////
void hw_power_ClearVbusValidInterrupt(void) {
    while (BF_RD(POWER_CTRL, VBUSVALID_IRQ) != 0) {
        BF_CLR(POWER_CTRL, VBUSVALID_IRQ);
    }
}

////////////////////////////////////////////////////////////////////////////////
//! See hw_power.h for details.
////////////////////////////////////////////////////////////////////////////////
bool hw_power_GetVbusValidInterruptPolarity(void) {
    return HW_POWER_CTRL.B.POLARITY_VBUSVALID;
}

////////////////////////////////////////////////////////////////////////////////
//! See hw_power.h for details.
////////////////////////////////////////////////////////////////////////////////
void hw_power_SetVbusValidInterruptPolarity(bool bPolarity) {
    if (bPolarity == HW_POWER_CHECK_5V_DISCONNECTED) {
        BF_CLR(POWER_CTRL, POLARITY_VBUSVALID);
    }

    // bPolarity == HW_POWER_CHECK_5V_CONNECTED
    else {
        BF_SET(POWER_CTRL, POLARITY_VBUSVALID);
    }
}

////////////////////////////////////////////////////////////////////////////////
//! See hw_power.h for details.
////////////////////////////////////////////////////////////////////////////////
bool hw_power_EnableVdd5vGtVddioInterrupt(bool bEnable) {
    bool bPrev = BF_RD(POWER_CTRL, ENIRQ_VDD5V_GT_VDDIO);

    if (bEnable) {
        BF_SET(POWER_CTRL, ENIRQ_VDD5V_GT_VDDIO);
    } else {
        BF_CLR(POWER_CTRL, ENIRQ_VDD5V_GT_VDDIO);
    }

    return bPrev;
}

////////////////////////////////////////////////////////////////////////////////
//! See hw_power.h for details.
////////////////////////////////////////////////////////////////////////////////
void hw_power_ClearVdd5vGtVddioInterrupt(void) {
    BF_CLR(POWER_CTRL, VDD5V_GT_VDDIO_IRQ);
}

////////////////////////////////////////////////////////////////////////////////
//! See hw_power.h for details.
////////////////////////////////////////////////////////////////////////////////
void hw_power_SetVdd5vGtVddioInterruptPolarity(bool bPolarity) {
    if (bPolarity == HW_POWER_CHECK_5V_DISCONNECTED) {
        BF_CLR(POWER_CTRL, POLARITY_VDD5V_GT_VDDIO);
    }

    // bPolarity == HW_POWER_CHECK_5V_CONNECTED
    else {
        BF_SET(POWER_CTRL, POLARITY_VDD5V_GT_VDDIO);
    }
}

////////////////////////////////////////////////////////////////////////////////
//! See hw_power.h for details.
////////////////////////////////////////////////////////////////////////////////
bool hw_power_GetVdd5vGtVddioInterruptPolarity(void) {
    return HW_POWER_CTRL.B.POLARITY_VDD5V_GT_VDDIO;
}

////////////////////////////////////////////////////////////////////////////////
//! See hw_power.h for details.
////////////////////////////////////////////////////////////////////////////////
bool hw_power_Enable4p2BrownoutInterrupt(bool bEnable) {
    bool bPrev = false;

    bPrev = BF_RD(POWER_CTRL, ENIRQ_DCDC4P2_BO);

    if (bEnable) {
        BF_SET(POWER_CTRL, ENIRQ_DCDC4P2_BO);
    } else {
        BF_CLR(POWER_CTRL, ENIRQ_DCDC4P2_BO);
    }

    return bPrev;
}

////////////////////////////////////////////////////////////////////////////////
//! See hw_power.h for details.
////////////////////////////////////////////////////////////////////////////////
void hw_power_Clear4p2BrownoutInterrupt(void) {

    BF_CLR(POWER_CTRL, DCDC4P2_BO_IRQ);
}

////////////////////////////////////////////////////////////////////////////////
//! See hw_power.h for details.
////////////////////////////////////////////////////////////////////////////////
bool hw_power_EnableVdd5vDroopInterrupt(bool bEnable) {
    bool bPrev = false;

    bPrev = BF_RD(POWER_CTRL, ENIRQ_VDD5V_DROOP);

    if (bEnable) {
        BF_SET(POWER_CTRL, ENIRQ_VDD5V_DROOP);
    } else {
        BF_CLR(POWER_CTRL, ENIRQ_VDD5V_DROOP);
    }

    return bPrev;
}

////////////////////////////////////////////////////////////////////////////////
//! See hw_power.h for details.
////////////////////////////////////////////////////////////////////////////////
void hw_power_ClearVdd5vDroopInterrupt(void) {

    while (BF_RD(POWER_CTRL, VDD5V_DROOP_IRQ) != 0) {
        BF_CLR(POWER_CTRL, VDD5V_DROOP_IRQ);
    }
}

////////////////////////////////////////////////////////////////////////////////
// End of file
////////////////////////////////////////////////////////////////////////////////
//! @}
