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
//
// WARNING!  THIS FILE IS AUTOMATICALLY GENERATED FROM XML.
//                DO NOT MODIFY THIS FILE DIRECTLY.
//
////////////////////////////////////////////////////////////////////////////////
//
// The following naming conventions are followed in this file.
//      XX_<module>_<regname>_<field>
//
// XX specifies the define / macro class
//      HW pertains to a register
//      BM indicates a Bit Mask
//      BF indicates a Bit Field macro
//
// <module> is the hardware module name which can be any of the following...
//      USB20 (Note when there is more than one copy of a given module, the
//      module name includes a number starting from 0 for the first instance
//      of that module)
//
// <regname> is the specific register within that module
//
// <field> is the specific bitfield within that <module>_<register>
//
// We also define the following...
//      hw_<module>_<regname>_t is typedef of anonymous union
//
////////////////////////////////////////////////////////////////////////////////

#ifndef _REGSSIMSSPSEL_H
#define _REGSSIMSSPSEL_H 1

#include "regs.h"

////////////////////////////////////////////////////////////////////////////////
//// HW_SIMSSPSEL_CTRL - Simulation External Memory Selection Control Register
////////////////////////////////////////////////////////////////////////////////

#ifndef __LANGUAGE_ASM__
typedef union {
    reg32_t U;
    struct {
        unsigned PRI_SEL : 5;
        unsigned RSVRD : 3;
        unsigned ALT_SEL : 5;
        unsigned RSVRD : 3;
        reg16_t RSVRD;
    } B;
} hw_simsspsel_ctrl_t;
#endif

//
// constants & macros for entire HW_SIMSSPSEL_CTRL register
//

#define HW_SIMSSPSEL_CTRL_ADDR (REGS_BASE + 0x0003C0A0)
#define HW_SIMSSPSEL_CTRL_SET_ADDR (REGS_BASE + 0x0003C0A4)
#define HW_SIMSSPSEL_CTRL_CLR_ADDR (REGS_BASE + 0x0003C0A8)
#define HW_SIMSSPSEL_CTRL_TOG_ADDR (REGS_BASE + 0x0003C0AC)

#ifndef __LANGUAGE_ASM__
#define HW_SIMSSPSEL_CTRL                                                      \
    (*(volatile hw_simsspsel_ctrl_t *)HW_SIMSSPSEL_CTRL_ADDR)
#define HW_SIMSSPSEL_CTRL_RD() (HW_SIMSSPSEL_CTRL.U)
#define HW_SIMSSPSEL_CTRL_WR(v) (HW_SIMSSPSEL_CTRL.U = (v))
#define HW_SIMSSPSEL_CTRL_SET(v)                                               \
    ((*(volatile reg32_t *)HW_SIMSSPSEL_CTRL_SET_ADDR) = (v))
#define HW_SIMSSPSEL_CTRL_CLR(v)                                               \
    ((*(volatile reg32_t *)HW_SIMSSPSEL_CTRL_CLR_ADDR) = (v))
#define HW_SIMSSPSEL_CTRL_TOG(v)                                               \
    ((*(volatile reg32_t *)HW_SIMSSPSEL_CTRL_TOG_ADDR) = (v))
#endif

//
// constants & macros for individual HW_SIMSSPSEL_CTRL bitfields
//

#define BP_SIMSSPSEL_CTRL_ALT_SEL 8
#define BM_SIMSSPSEL_CTRL_ALT_SEL 0x00001F00

#define BF_SIMSSPSEL_CTRL_ALT_SEL(v) (((v) << 8) & BM_SIMSSPSEL_CTRL_ALT_SEL)

#ifndef __LANGUAGE_ASM__
#define BW_SIMSSPSEL_CTRL_ALT_SEL(v) BF_CS1(SIMSSPSEL_CTRL, ALT_SEL, v)
#endif

//---

#define BP_SIMSSPSEL_CTRL_PRI_SEL 0
#define BM_SIMSSPSEL_CTRL_PRI_SEL 0x0000001F

#define BF_SIMSSPSEL_CTRL_PRI_SEL(v) (((v) << 0) & BM_SIMSSPSEL_CTRL_PRI_SEL)

#ifndef __LANGUAGE_ASM__
#define BW_SIMSSPSEL_CTRL_PRI_SEL(v) BF_CS1(SIMSSPSEL_CTRL, PRI_SEL, v)
#endif

#endif // _REGSSIMSSPSEL_H

////////////////////////////////////////////////////////////////////////////////
