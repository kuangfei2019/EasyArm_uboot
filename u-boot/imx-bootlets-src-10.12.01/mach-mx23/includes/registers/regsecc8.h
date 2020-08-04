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

#ifndef _REGSECC8_H
#define _REGSECC8_H 1

#include "regs.h"

#ifndef REGS_ECC8_BASE
#define REGS_ECC8_BASE (REGS_BASE + 0x00008000)
#endif

////////////////////////////////////////////////////////////////////////////////
//// HW_ECC8_CTRL - Hardware ECC Accelerator Control Register
////////////////////////////////////////////////////////////////////////////////

#ifndef __LANGUAGE_ASM__
typedef union {
    reg32_t U;
    struct {
        unsigned COMPLETE_IRQ : 1;
        unsigned DEBUG_WRITE_IRQ : 1;
        unsigned DEBUG_STALL_IRQ : 1;
        unsigned BM_ERROR_IRQ : 1;
        unsigned RSRVD0 : 4;
        unsigned COMPLETE_IRQ_EN : 1;
        unsigned DEBUG_WRITE_IRQ_EN : 1;
        unsigned DEBUG_STALL_IRQ_EN : 1;
        unsigned RSRVD1 : 13;
        unsigned THROTTLE : 4;
        unsigned RSRVD2 : 1;
        unsigned AHBM_SFTRST : 1;
        unsigned CLKGATE : 1;
        unsigned SFTRST : 1;
    } B;
} hw_ecc8_ctrl_t;
#endif

//
// constants & macros for entire HW_ECC8_CTRL register
//

#define HW_ECC8_CTRL_ADDR (REGS_ECC8_BASE + 0x00000000)
#define HW_ECC8_CTRL_SET_ADDR (REGS_ECC8_BASE + 0x00000004)
#define HW_ECC8_CTRL_CLR_ADDR (REGS_ECC8_BASE + 0x00000008)
#define HW_ECC8_CTRL_TOG_ADDR (REGS_ECC8_BASE + 0x0000000C)

#ifndef __LANGUAGE_ASM__
#define HW_ECC8_CTRL (*(volatile hw_ecc8_ctrl_t *)HW_ECC8_CTRL_ADDR)
#define HW_ECC8_CTRL_RD() (HW_ECC8_CTRL.U)
#define HW_ECC8_CTRL_WR(v) (HW_ECC8_CTRL.U = (v))
#define HW_ECC8_CTRL_SET(v) ((*(volatile reg32_t *)HW_ECC8_CTRL_SET_ADDR) = (v))
#define HW_ECC8_CTRL_CLR(v) ((*(volatile reg32_t *)HW_ECC8_CTRL_CLR_ADDR) = (v))
#define HW_ECC8_CTRL_TOG(v) ((*(volatile reg32_t *)HW_ECC8_CTRL_TOG_ADDR) = (v))
#endif

//
// constants & macros for individual HW_ECC8_CTRL bitfields
//

//--- Register HW_ECC8_CTRL, field SFTRST

#define BP_ECC8_CTRL_SFTRST 31
#define BM_ECC8_CTRL_SFTRST 0x80000000

#ifndef __LANGUAGE_ASM__
#define BF_ECC8_CTRL_SFTRST(v) ((((reg32_t)v) << 31) & BM_ECC8_CTRL_SFTRST)
#else
#define BF_ECC8_CTRL_SFTRST(v) (((v) << 31) & BM_ECC8_CTRL_SFTRST)
#endif

#ifndef __LANGUAGE_ASM__
#define BW_ECC8_CTRL_SFTRST(v) BF_CS1(ECC8_CTRL, SFTRST, v)
#endif

#define BV_ECC8_CTRL_SFTRST__RUN 0x0
#define BV_ECC8_CTRL_SFTRST__RESET 0x1

//--- Register HW_ECC8_CTRL, field CLKGATE

#define BP_ECC8_CTRL_CLKGATE 30
#define BM_ECC8_CTRL_CLKGATE 0x40000000

#define BF_ECC8_CTRL_CLKGATE(v) (((v) << 30) & BM_ECC8_CTRL_CLKGATE)

#ifndef __LANGUAGE_ASM__
#define BW_ECC8_CTRL_CLKGATE(v) BF_CS1(ECC8_CTRL, CLKGATE, v)
#endif

#define BV_ECC8_CTRL_CLKGATE__RUN 0x0
#define BV_ECC8_CTRL_CLKGATE__NO_CLKS 0x1

//--- Register HW_ECC8_CTRL, field AHBM_SFTRST

#define BP_ECC8_CTRL_AHBM_SFTRST 29
#define BM_ECC8_CTRL_AHBM_SFTRST 0x20000000

#define BF_ECC8_CTRL_AHBM_SFTRST(v) (((v) << 29) & BM_ECC8_CTRL_AHBM_SFTRST)

#ifndef __LANGUAGE_ASM__
#define BW_ECC8_CTRL_AHBM_SFTRST(v) BF_CS1(ECC8_CTRL, AHBM_SFTRST, v)
#endif

#define BV_ECC8_CTRL_AHBM_SFTRST__RUN 0x0
#define BV_ECC8_CTRL_AHBM_SFTRST__RESET 0x1

//--- Register HW_ECC8_CTRL, field THROTTLE

#define BP_ECC8_CTRL_THROTTLE 24
#define BM_ECC8_CTRL_THROTTLE 0x0F000000

#define BF_ECC8_CTRL_THROTTLE(v) (((v) << 24) & BM_ECC8_CTRL_THROTTLE)

#ifndef __LANGUAGE_ASM__
#define BW_ECC8_CTRL_THROTTLE(v) BF_CS1(ECC8_CTRL, THROTTLE, v)
#endif

//--- Register HW_ECC8_CTRL, field DEBUG_STALL_IRQ_EN

#define BP_ECC8_CTRL_DEBUG_STALL_IRQ_EN 10
#define BM_ECC8_CTRL_DEBUG_STALL_IRQ_EN 0x00000400

#define BF_ECC8_CTRL_DEBUG_STALL_IRQ_EN(v)                                     \
    (((v) << 10) & BM_ECC8_CTRL_DEBUG_STALL_IRQ_EN)

#ifndef __LANGUAGE_ASM__
#define BW_ECC8_CTRL_DEBUG_STALL_IRQ_EN(v)                                     \
    BF_CS1(ECC8_CTRL, DEBUG_STALL_IRQ_EN, v)
#endif

//--- Register HW_ECC8_CTRL, field DEBUG_WRITE_IRQ_EN

#define BP_ECC8_CTRL_DEBUG_WRITE_IRQ_EN 9
#define BM_ECC8_CTRL_DEBUG_WRITE_IRQ_EN 0x00000200

#define BF_ECC8_CTRL_DEBUG_WRITE_IRQ_EN(v)                                     \
    (((v) << 9) & BM_ECC8_CTRL_DEBUG_WRITE_IRQ_EN)

#ifndef __LANGUAGE_ASM__
#define BW_ECC8_CTRL_DEBUG_WRITE_IRQ_EN(v)                                     \
    BF_CS1(ECC8_CTRL, DEBUG_WRITE_IRQ_EN, v)
#endif

//--- Register HW_ECC8_CTRL, field COMPLETE_IRQ_EN

#define BP_ECC8_CTRL_COMPLETE_IRQ_EN 8
#define BM_ECC8_CTRL_COMPLETE_IRQ_EN 0x00000100

#define BF_ECC8_CTRL_COMPLETE_IRQ_EN(v)                                        \
    (((v) << 8) & BM_ECC8_CTRL_COMPLETE_IRQ_EN)

#ifndef __LANGUAGE_ASM__
#define BW_ECC8_CTRL_COMPLETE_IRQ_EN(v) BF_CS1(ECC8_CTRL, COMPLETE_IRQ_EN, v)
#endif

//--- Register HW_ECC8_CTRL, field BM_ERROR_IRQ

#define BP_ECC8_CTRL_BM_ERROR_IRQ 3
#define BM_ECC8_CTRL_BM_ERROR_IRQ 0x00000008

#define BF_ECC8_CTRL_BM_ERROR_IRQ(v) (((v) << 3) & BM_ECC8_CTRL_BM_ERROR_IRQ)

#ifndef __LANGUAGE_ASM__
#define BW_ECC8_CTRL_BM_ERROR_IRQ(v) BF_CS1(ECC8_CTRL, BM_ERROR_IRQ, v)
#endif

//--- Register HW_ECC8_CTRL, field DEBUG_STALL_IRQ

#define BP_ECC8_CTRL_DEBUG_STALL_IRQ 2
#define BM_ECC8_CTRL_DEBUG_STALL_IRQ 0x00000004

#define BF_ECC8_CTRL_DEBUG_STALL_IRQ(v)                                        \
    (((v) << 2) & BM_ECC8_CTRL_DEBUG_STALL_IRQ)

#ifndef __LANGUAGE_ASM__
#define BW_ECC8_CTRL_DEBUG_STALL_IRQ(v) BF_CS1(ECC8_CTRL, DEBUG_STALL_IRQ, v)
#endif

//--- Register HW_ECC8_CTRL, field DEBUG_WRITE_IRQ

#define BP_ECC8_CTRL_DEBUG_WRITE_IRQ 1
#define BM_ECC8_CTRL_DEBUG_WRITE_IRQ 0x00000002

#define BF_ECC8_CTRL_DEBUG_WRITE_IRQ(v)                                        \
    (((v) << 1) & BM_ECC8_CTRL_DEBUG_WRITE_IRQ)

#ifndef __LANGUAGE_ASM__
#define BW_ECC8_CTRL_DEBUG_WRITE_IRQ(v) BF_CS1(ECC8_CTRL, DEBUG_WRITE_IRQ, v)
#endif

//--- Register HW_ECC8_CTRL, field COMPLETE_IRQ

#define BP_ECC8_CTRL_COMPLETE_IRQ 0
#define BM_ECC8_CTRL_COMPLETE_IRQ 0x00000001

#define BF_ECC8_CTRL_COMPLETE_IRQ(v) (((v) << 0) & BM_ECC8_CTRL_COMPLETE_IRQ)

#ifndef __LANGUAGE_ASM__
#define BW_ECC8_CTRL_COMPLETE_IRQ(v) BF_CS1(ECC8_CTRL, COMPLETE_IRQ, v)
#endif

////////////////////////////////////////////////////////////////////////////////
//// HW_ECC8_STATUS0 - Hardware ECC Accelerator Status Register 0
////////////////////////////////////////////////////////////////////////////////

#ifndef __LANGUAGE_ASM__
typedef union {
    reg32_t U;
    struct {
        unsigned RSVD0 : 2;
        unsigned UNCORRECTABLE : 1;
        unsigned CORRECTED : 1;
        unsigned ALLONES : 1;
        unsigned RSVD1 : 3;
        unsigned STATUS_AUX : 4;
        unsigned RS4ECC_DEC_PRESENT : 1;
        unsigned RS4ECC_ENC_PRESENT : 1;
        unsigned RS8ECC_DEC_PRESENT : 1;
        unsigned RS8ECC_ENC_PRESENT : 1;
        unsigned COMPLETED_CE : 4;
        unsigned HANDLE : 12;
    } B;
} hw_ecc8_status0_t;
#endif

//
// constants & macros for entire HW_ECC8_STATUS0 register
//

#define HW_ECC8_STATUS0_ADDR (REGS_ECC8_BASE + 0x00000010)

#ifndef __LANGUAGE_ASM__
#define HW_ECC8_STATUS0 (*(volatile hw_ecc8_status0_t *)HW_ECC8_STATUS0_ADDR)
#define HW_ECC8_STATUS0_RD() (HW_ECC8_STATUS0.U)
#endif

//
// constants & macros for individual HW_ECC8_STATUS0 bitfields
//

//--- Register HW_ECC8_STATUS0, field HANDLE

#define BP_ECC8_STATUS0_HANDLE 20
#define BM_ECC8_STATUS0_HANDLE 0xFFF00000

#ifndef __LANGUAGE_ASM__
#define BF_ECC8_STATUS0_HANDLE(v)                                              \
    ((((reg32_t)v) << 20) & BM_ECC8_STATUS0_HANDLE)
#else
#define BF_ECC8_STATUS0_HANDLE(v) (((v) << 20) & BM_ECC8_STATUS0_HANDLE)
#endif

//--- Register HW_ECC8_STATUS0, field COMPLETED_CE

#define BP_ECC8_STATUS0_COMPLETED_CE 16
#define BM_ECC8_STATUS0_COMPLETED_CE 0x000F0000

#define BF_ECC8_STATUS0_COMPLETED_CE(v)                                        \
    (((v) << 16) & BM_ECC8_STATUS0_COMPLETED_CE)

//--- Register HW_ECC8_STATUS0, field RS8ECC_ENC_PRESENT

#define BP_ECC8_STATUS0_RS8ECC_ENC_PRESENT 15
#define BM_ECC8_STATUS0_RS8ECC_ENC_PRESENT 0x00008000

#define BF_ECC8_STATUS0_RS8ECC_ENC_PRESENT(v)                                  \
    (((v) << 15) & BM_ECC8_STATUS0_RS8ECC_ENC_PRESENT)

//--- Register HW_ECC8_STATUS0, field RS8ECC_DEC_PRESENT

#define BP_ECC8_STATUS0_RS8ECC_DEC_PRESENT 14
#define BM_ECC8_STATUS0_RS8ECC_DEC_PRESENT 0x00004000

#define BF_ECC8_STATUS0_RS8ECC_DEC_PRESENT(v)                                  \
    (((v) << 14) & BM_ECC8_STATUS0_RS8ECC_DEC_PRESENT)

//--- Register HW_ECC8_STATUS0, field RS4ECC_ENC_PRESENT

#define BP_ECC8_STATUS0_RS4ECC_ENC_PRESENT 13
#define BM_ECC8_STATUS0_RS4ECC_ENC_PRESENT 0x00002000

#define BF_ECC8_STATUS0_RS4ECC_ENC_PRESENT(v)                                  \
    (((v) << 13) & BM_ECC8_STATUS0_RS4ECC_ENC_PRESENT)

//--- Register HW_ECC8_STATUS0, field RS4ECC_DEC_PRESENT

#define BP_ECC8_STATUS0_RS4ECC_DEC_PRESENT 12
#define BM_ECC8_STATUS0_RS4ECC_DEC_PRESENT 0x00001000

#define BF_ECC8_STATUS0_RS4ECC_DEC_PRESENT(v)                                  \
    (((v) << 12) & BM_ECC8_STATUS0_RS4ECC_DEC_PRESENT)

//--- Register HW_ECC8_STATUS0, field STATUS_AUX

#define BP_ECC8_STATUS0_STATUS_AUX 8
#define BM_ECC8_STATUS0_STATUS_AUX 0x00000F00

#define BF_ECC8_STATUS0_STATUS_AUX(v) (((v) << 8) & BM_ECC8_STATUS0_STATUS_AUX)

#define BV_ECC8_STATUS0_STATUS_AUX__NO_ERRORS 0x0
#define BV_ECC8_STATUS0_STATUS_AUX__ONE_CORRECTABLE 0x1
#define BV_ECC8_STATUS0_STATUS_AUX__TWO_CORRECTABLE 0x2
#define BV_ECC8_STATUS0_STATUS_AUX__THREE_CORRECTABLE 0x3
#define BV_ECC8_STATUS0_STATUS_AUX__FOUR_CORRECTABLE 0x4
#define BV_ECC8_STATUS0_STATUS_AUX__NOT_CHECKED 0xC
#define BV_ECC8_STATUS0_STATUS_AUX__UNCORRECTABLE 0xE
#define BV_ECC8_STATUS0_STATUS_AUX__ALL_ONES 0xF

//--- Register HW_ECC8_STATUS0, field ALLONES

#define BP_ECC8_STATUS0_ALLONES 4
#define BM_ECC8_STATUS0_ALLONES 0x00000010

#define BF_ECC8_STATUS0_ALLONES(v) (((v) << 4) & BM_ECC8_STATUS0_ALLONES)

//--- Register HW_ECC8_STATUS0, field CORRECTED

#define BP_ECC8_STATUS0_CORRECTED 3
#define BM_ECC8_STATUS0_CORRECTED 0x00000008

#define BF_ECC8_STATUS0_CORRECTED(v) (((v) << 3) & BM_ECC8_STATUS0_CORRECTED)

//--- Register HW_ECC8_STATUS0, field UNCORRECTABLE

#define BP_ECC8_STATUS0_UNCORRECTABLE 2
#define BM_ECC8_STATUS0_UNCORRECTABLE 0x00000004

#define BF_ECC8_STATUS0_UNCORRECTABLE(v)                                       \
    (((v) << 2) & BM_ECC8_STATUS0_UNCORRECTABLE)

////////////////////////////////////////////////////////////////////////////////
//// HW_ECC8_STATUS1 - Hardware ECC Accelerator Status Register 1
////////////////////////////////////////////////////////////////////////////////

#ifndef __LANGUAGE_ASM__
typedef union {
    reg32_t U;
    struct {
        unsigned STATUS_PAYLOAD0 : 4;
        unsigned STATUS_PAYLOAD1 : 4;
        unsigned STATUS_PAYLOAD2 : 4;
        unsigned STATUS_PAYLOAD3 : 4;
        unsigned STATUS_PAYLOAD4 : 4;
        unsigned STATUS_PAYLOAD5 : 4;
        unsigned STATUS_PAYLOAD6 : 4;
        unsigned STATUS_PAYLOAD7 : 4;
    } B;
} hw_ecc8_status1_t;
#endif

//
// constants & macros for entire HW_ECC8_STATUS1 register
//

#define HW_ECC8_STATUS1_ADDR (REGS_ECC8_BASE + 0x00000020)

#ifndef __LANGUAGE_ASM__
#define HW_ECC8_STATUS1 (*(volatile hw_ecc8_status1_t *)HW_ECC8_STATUS1_ADDR)
#define HW_ECC8_STATUS1_RD() (HW_ECC8_STATUS1.U)
#endif

//
// constants & macros for individual HW_ECC8_STATUS1 bitfields
//

//--- Register HW_ECC8_STATUS1, field STATUS_PAYLOAD7

#define BP_ECC8_STATUS1_STATUS_PAYLOAD7 28
#define BM_ECC8_STATUS1_STATUS_PAYLOAD7 0xF0000000

#ifndef __LANGUAGE_ASM__
#define BF_ECC8_STATUS1_STATUS_PAYLOAD7(v)                                     \
    ((((reg32_t)v) << 28) & BM_ECC8_STATUS1_STATUS_PAYLOAD7)
#else
#define BF_ECC8_STATUS1_STATUS_PAYLOAD7(v)                                     \
    (((v) << 28) & BM_ECC8_STATUS1_STATUS_PAYLOAD7)
#endif

#define BV_ECC8_STATUS1_STATUS_PAYLOAD7__NO_ERRORS 0x0
#define BV_ECC8_STATUS1_STATUS_PAYLOAD7__ONE_CORRECTABLE 0x1
#define BV_ECC8_STATUS1_STATUS_PAYLOAD7__TWO_CORRECTABLE 0x2
#define BV_ECC8_STATUS1_STATUS_PAYLOAD7__THREE_CORRECTABLE 0x3
#define BV_ECC8_STATUS1_STATUS_PAYLOAD7__FOUR_CORRECTABLE 0x4
#define BV_ECC8_STATUS1_STATUS_PAYLOAD7__FIVE_CORRECTABLE 0x5
#define BV_ECC8_STATUS1_STATUS_PAYLOAD7__SIX_CORRECTABLE 0x6
#define BV_ECC8_STATUS1_STATUS_PAYLOAD7__SEVEN_CORRECTABLE 0x7
#define BV_ECC8_STATUS1_STATUS_PAYLOAD7__EIGHT_CORRECTABLE 0x8
#define BV_ECC8_STATUS1_STATUS_PAYLOAD7__NOT_CHECKED 0xC
#define BV_ECC8_STATUS1_STATUS_PAYLOAD7__UNCORRECTABLE 0xE
#define BV_ECC8_STATUS1_STATUS_PAYLOAD7__ALL_ONES 0xF

//--- Register HW_ECC8_STATUS1, field STATUS_PAYLOAD6

#define BP_ECC8_STATUS1_STATUS_PAYLOAD6 24
#define BM_ECC8_STATUS1_STATUS_PAYLOAD6 0x0F000000

#define BF_ECC8_STATUS1_STATUS_PAYLOAD6(v)                                     \
    (((v) << 24) & BM_ECC8_STATUS1_STATUS_PAYLOAD6)

#define BV_ECC8_STATUS1_STATUS_PAYLOAD6__NO_ERRORS 0x0
#define BV_ECC8_STATUS1_STATUS_PAYLOAD6__ONE_CORRECTABLE 0x1
#define BV_ECC8_STATUS1_STATUS_PAYLOAD6__TWO_CORRECTABLE 0x2
#define BV_ECC8_STATUS1_STATUS_PAYLOAD6__THREE_CORRECTABLE 0x3
#define BV_ECC8_STATUS1_STATUS_PAYLOAD6__FOUR_CORRECTABLE 0x4
#define BV_ECC8_STATUS1_STATUS_PAYLOAD6__FIVE_CORRECTABLE 0x5
#define BV_ECC8_STATUS1_STATUS_PAYLOAD6__SIX_CORRECTABLE 0x6
#define BV_ECC8_STATUS1_STATUS_PAYLOAD6__SEVEN_CORRECTABLE 0x7
#define BV_ECC8_STATUS1_STATUS_PAYLOAD6__EIGHT_CORRECTABLE 0x8
#define BV_ECC8_STATUS1_STATUS_PAYLOAD6__NOT_CHECKED 0xC
#define BV_ECC8_STATUS1_STATUS_PAYLOAD6__UNCORRECTABLE 0xE
#define BV_ECC8_STATUS1_STATUS_PAYLOAD6__ALL_ONES 0xF

//--- Register HW_ECC8_STATUS1, field STATUS_PAYLOAD5

#define BP_ECC8_STATUS1_STATUS_PAYLOAD5 20
#define BM_ECC8_STATUS1_STATUS_PAYLOAD5 0x00F00000

#define BF_ECC8_STATUS1_STATUS_PAYLOAD5(v)                                     \
    (((v) << 20) & BM_ECC8_STATUS1_STATUS_PAYLOAD5)

#define BV_ECC8_STATUS1_STATUS_PAYLOAD5__NO_ERRORS 0x0
#define BV_ECC8_STATUS1_STATUS_PAYLOAD5__ONE_CORRECTABLE 0x1
#define BV_ECC8_STATUS1_STATUS_PAYLOAD5__TWO_CORRECTABLE 0x2
#define BV_ECC8_STATUS1_STATUS_PAYLOAD5__THREE_CORRECTABLE 0x3
#define BV_ECC8_STATUS1_STATUS_PAYLOAD5__FOUR_CORRECTABLE 0x4
#define BV_ECC8_STATUS1_STATUS_PAYLOAD5__FIVE_CORRECTABLE 0x5
#define BV_ECC8_STATUS1_STATUS_PAYLOAD5__SIX_CORRECTABLE 0x6
#define BV_ECC8_STATUS1_STATUS_PAYLOAD5__SEVEN_CORRECTABLE 0x7
#define BV_ECC8_STATUS1_STATUS_PAYLOAD5__EIGHT_CORRECTABLE 0x8
#define BV_ECC8_STATUS1_STATUS_PAYLOAD5__NOT_CHECKED 0xC
#define BV_ECC8_STATUS1_STATUS_PAYLOAD5__UNCORRECTABLE 0xE
#define BV_ECC8_STATUS1_STATUS_PAYLOAD5__ALL_ONES 0xF

//--- Register HW_ECC8_STATUS1, field STATUS_PAYLOAD4

#define BP_ECC8_STATUS1_STATUS_PAYLOAD4 16
#define BM_ECC8_STATUS1_STATUS_PAYLOAD4 0x000F0000

#define BF_ECC8_STATUS1_STATUS_PAYLOAD4(v)                                     \
    (((v) << 16) & BM_ECC8_STATUS1_STATUS_PAYLOAD4)

#define BV_ECC8_STATUS1_STATUS_PAYLOAD4__NO_ERRORS 0x0
#define BV_ECC8_STATUS1_STATUS_PAYLOAD4__ONE_CORRECTABLE 0x1
#define BV_ECC8_STATUS1_STATUS_PAYLOAD4__TWO_CORRECTABLE 0x2
#define BV_ECC8_STATUS1_STATUS_PAYLOAD4__THREE_CORRECTABLE 0x3
#define BV_ECC8_STATUS1_STATUS_PAYLOAD4__FOUR_CORRECTABLE 0x4
#define BV_ECC8_STATUS1_STATUS_PAYLOAD4__FIVE_CORRECTABLE 0x5
#define BV_ECC8_STATUS1_STATUS_PAYLOAD4__SIX_CORRECTABLE 0x6
#define BV_ECC8_STATUS1_STATUS_PAYLOAD4__SEVEN_CORRECTABLE 0x7
#define BV_ECC8_STATUS1_STATUS_PAYLOAD4__EIGHT_CORRECTABLE 0x8
#define BV_ECC8_STATUS1_STATUS_PAYLOAD4__NOT_CHECKED 0xC
#define BV_ECC8_STATUS1_STATUS_PAYLOAD4__UNCORRECTABLE 0xE
#define BV_ECC8_STATUS1_STATUS_PAYLOAD4__ALL_ONES 0xF

//--- Register HW_ECC8_STATUS1, field STATUS_PAYLOAD3

#define BP_ECC8_STATUS1_STATUS_PAYLOAD3 12
#define BM_ECC8_STATUS1_STATUS_PAYLOAD3 0x0000F000

#define BF_ECC8_STATUS1_STATUS_PAYLOAD3(v)                                     \
    (((v) << 12) & BM_ECC8_STATUS1_STATUS_PAYLOAD3)

#define BV_ECC8_STATUS1_STATUS_PAYLOAD3__NO_ERRORS 0x0
#define BV_ECC8_STATUS1_STATUS_PAYLOAD3__ONE_CORRECTABLE 0x1
#define BV_ECC8_STATUS1_STATUS_PAYLOAD3__TWO_CORRECTABLE 0x2
#define BV_ECC8_STATUS1_STATUS_PAYLOAD3__THREE_CORRECTABLE 0x3
#define BV_ECC8_STATUS1_STATUS_PAYLOAD3__FOUR_CORRECTABLE 0x4
#define BV_ECC8_STATUS1_STATUS_PAYLOAD3__FIVE_CORRECTABLE 0x5
#define BV_ECC8_STATUS1_STATUS_PAYLOAD3__SIX_CORRECTABLE 0x6
#define BV_ECC8_STATUS1_STATUS_PAYLOAD3__SEVEN_CORRECTABLE 0x7
#define BV_ECC8_STATUS1_STATUS_PAYLOAD3__EIGHT_CORRECTABLE 0x8
#define BV_ECC8_STATUS1_STATUS_PAYLOAD3__NOT_CHECKED 0xC
#define BV_ECC8_STATUS1_STATUS_PAYLOAD3__UNCORRECTABLE 0xE
#define BV_ECC8_STATUS1_STATUS_PAYLOAD3__ALL_ONES 0xF

//--- Register HW_ECC8_STATUS1, field STATUS_PAYLOAD2

#define BP_ECC8_STATUS1_STATUS_PAYLOAD2 8
#define BM_ECC8_STATUS1_STATUS_PAYLOAD2 0x00000F00

#define BF_ECC8_STATUS1_STATUS_PAYLOAD2(v)                                     \
    (((v) << 8) & BM_ECC8_STATUS1_STATUS_PAYLOAD2)

#define BV_ECC8_STATUS1_STATUS_PAYLOAD2__NO_ERRORS 0x0
#define BV_ECC8_STATUS1_STATUS_PAYLOAD2__ONE_CORRECTABLE 0x1
#define BV_ECC8_STATUS1_STATUS_PAYLOAD2__TWO_CORRECTABLE 0x2
#define BV_ECC8_STATUS1_STATUS_PAYLOAD2__THREE_CORRECTABLE 0x3
#define BV_ECC8_STATUS1_STATUS_PAYLOAD2__FOUR_CORRECTABLE 0x4
#define BV_ECC8_STATUS1_STATUS_PAYLOAD2__FIVE_CORRECTABLE 0x5
#define BV_ECC8_STATUS1_STATUS_PAYLOAD2__SIX_CORRECTABLE 0x6
#define BV_ECC8_STATUS1_STATUS_PAYLOAD2__SEVEN_CORRECTABLE 0x7
#define BV_ECC8_STATUS1_STATUS_PAYLOAD2__EIGHT_CORRECTABLE 0x8
#define BV_ECC8_STATUS1_STATUS_PAYLOAD2__NOT_CHECKED 0xC
#define BV_ECC8_STATUS1_STATUS_PAYLOAD2__UNCORRECTABLE 0xE
#define BV_ECC8_STATUS1_STATUS_PAYLOAD2__ALL_ONES 0xF

//--- Register HW_ECC8_STATUS1, field STATUS_PAYLOAD1

#define BP_ECC8_STATUS1_STATUS_PAYLOAD1 4
#define BM_ECC8_STATUS1_STATUS_PAYLOAD1 0x000000F0

#define BF_ECC8_STATUS1_STATUS_PAYLOAD1(v)                                     \
    (((v) << 4) & BM_ECC8_STATUS1_STATUS_PAYLOAD1)

#define BV_ECC8_STATUS1_STATUS_PAYLOAD1__NO_ERRORS 0x0
#define BV_ECC8_STATUS1_STATUS_PAYLOAD1__ONE_CORRECTABLE 0x1
#define BV_ECC8_STATUS1_STATUS_PAYLOAD1__TWO_CORRECTABLE 0x2
#define BV_ECC8_STATUS1_STATUS_PAYLOAD1__THREE_CORRECTABLE 0x3
#define BV_ECC8_STATUS1_STATUS_PAYLOAD1__FOUR_CORRECTABLE 0x4
#define BV_ECC8_STATUS1_STATUS_PAYLOAD1__FIVE_CORRECTABLE 0x5
#define BV_ECC8_STATUS1_STATUS_PAYLOAD1__SIX_CORRECTABLE 0x6
#define BV_ECC8_STATUS1_STATUS_PAYLOAD1__SEVEN_CORRECTABLE 0x7
#define BV_ECC8_STATUS1_STATUS_PAYLOAD1__EIGHT_CORRECTABLE 0x8
#define BV_ECC8_STATUS1_STATUS_PAYLOAD1__NOT_CHECKED 0xC
#define BV_ECC8_STATUS1_STATUS_PAYLOAD1__UNCORRECTABLE 0xE
#define BV_ECC8_STATUS1_STATUS_PAYLOAD1__ALL_ONES 0xF

//--- Register HW_ECC8_STATUS1, field STATUS_PAYLOAD0

#define BP_ECC8_STATUS1_STATUS_PAYLOAD0 0
#define BM_ECC8_STATUS1_STATUS_PAYLOAD0 0x0000000F

#define BF_ECC8_STATUS1_STATUS_PAYLOAD0(v)                                     \
    (((v) << 0) & BM_ECC8_STATUS1_STATUS_PAYLOAD0)

#define BV_ECC8_STATUS1_STATUS_PAYLOAD0__NO_ERRORS 0x0
#define BV_ECC8_STATUS1_STATUS_PAYLOAD0__ONE_CORRECTABLE 0x1
#define BV_ECC8_STATUS1_STATUS_PAYLOAD0__TWO_CORRECTABLE 0x2
#define BV_ECC8_STATUS1_STATUS_PAYLOAD0__THREE_CORRECTABLE 0x3
#define BV_ECC8_STATUS1_STATUS_PAYLOAD0__FOUR_CORRECTABLE 0x4
#define BV_ECC8_STATUS1_STATUS_PAYLOAD0__FIVE_CORRECTABLE 0x5
#define BV_ECC8_STATUS1_STATUS_PAYLOAD0__SIX_CORRECTABLE 0x6
#define BV_ECC8_STATUS1_STATUS_PAYLOAD0__SEVEN_CORRECTABLE 0x7
#define BV_ECC8_STATUS1_STATUS_PAYLOAD0__EIGHT_CORRECTABLE 0x8
#define BV_ECC8_STATUS1_STATUS_PAYLOAD0__NOT_CHECKED 0xC
#define BV_ECC8_STATUS1_STATUS_PAYLOAD0__UNCORRECTABLE 0xE
#define BV_ECC8_STATUS1_STATUS_PAYLOAD0__ALL_ONES 0xF

////////////////////////////////////////////////////////////////////////////////
//// HW_ECC8_DEBUG0 - Hardware ECC Accelerator Debug Register 0
////////////////////////////////////////////////////////////////////////////////

#ifndef __LANGUAGE_ASM__
typedef union {
    reg32_t U;
    struct {
        unsigned DEBUG_REG_SELECT : 6;
        unsigned RSRVD0 : 2;
        unsigned BM_KES_TEST_BYPASS : 1;
        unsigned KES_DEBUG_STALL : 1;
        unsigned KES_DEBUG_STEP : 1;
        unsigned KES_STANDALONE : 1;
        unsigned KES_DEBUG_KICK : 1;
        unsigned KES_DEBUG_MODE4K : 1;
        unsigned KES_DEBUG_PAYLOAD_FLAG : 1;
        unsigned KES_DEBUG_SHIFT_SYND : 1;
        unsigned KES_DEBUG_SYNDROME_SYMBOL : 9;
        unsigned RSRVD1 : 7;
    } B;
} hw_ecc8_debug0_t;
#endif

//
// constants & macros for entire HW_ECC8_DEBUG0 register
//

#define HW_ECC8_DEBUG0_ADDR (REGS_ECC8_BASE + 0x00000030)
#define HW_ECC8_DEBUG0_SET_ADDR (REGS_ECC8_BASE + 0x00000034)
#define HW_ECC8_DEBUG0_CLR_ADDR (REGS_ECC8_BASE + 0x00000038)
#define HW_ECC8_DEBUG0_TOG_ADDR (REGS_ECC8_BASE + 0x0000003C)

#ifndef __LANGUAGE_ASM__
#define HW_ECC8_DEBUG0 (*(volatile hw_ecc8_debug0_t *)HW_ECC8_DEBUG0_ADDR)
#define HW_ECC8_DEBUG0_RD() (HW_ECC8_DEBUG0.U)
#define HW_ECC8_DEBUG0_WR(v) (HW_ECC8_DEBUG0.U = (v))
#define HW_ECC8_DEBUG0_SET(v)                                                  \
    ((*(volatile reg32_t *)HW_ECC8_DEBUG0_SET_ADDR) = (v))
#define HW_ECC8_DEBUG0_CLR(v)                                                  \
    ((*(volatile reg32_t *)HW_ECC8_DEBUG0_CLR_ADDR) = (v))
#define HW_ECC8_DEBUG0_TOG(v)                                                  \
    ((*(volatile reg32_t *)HW_ECC8_DEBUG0_TOG_ADDR) = (v))
#endif

//
// constants & macros for individual HW_ECC8_DEBUG0 bitfields
//

//--- Register HW_ECC8_DEBUG0, field KES_DEBUG_SYNDROME_SYMBOL

#define BP_ECC8_DEBUG0_KES_DEBUG_SYNDROME_SYMBOL 16
#define BM_ECC8_DEBUG0_KES_DEBUG_SYNDROME_SYMBOL 0x01FF0000

#define BF_ECC8_DEBUG0_KES_DEBUG_SYNDROME_SYMBOL(v)                            \
    (((v) << 16) & BM_ECC8_DEBUG0_KES_DEBUG_SYNDROME_SYMBOL)

#ifndef __LANGUAGE_ASM__
#define BW_ECC8_DEBUG0_KES_DEBUG_SYNDROME_SYMBOL(v)                            \
    BF_CS1(ECC8_DEBUG0, KES_DEBUG_SYNDROME_SYMBOL, v)
#endif

#define BV_ECC8_DEBUG0_KES_DEBUG_SYNDROME_SYMBOL__NORMAL 0x0
#define BV_ECC8_DEBUG0_KES_DEBUG_SYNDROME_SYMBOL__TEST_MODE 0x1

//--- Register HW_ECC8_DEBUG0, field KES_DEBUG_SHIFT_SYND

#define BP_ECC8_DEBUG0_KES_DEBUG_SHIFT_SYND 15
#define BM_ECC8_DEBUG0_KES_DEBUG_SHIFT_SYND 0x00008000

#define BF_ECC8_DEBUG0_KES_DEBUG_SHIFT_SYND(v)                                 \
    (((v) << 15) & BM_ECC8_DEBUG0_KES_DEBUG_SHIFT_SYND)

#ifndef __LANGUAGE_ASM__
#define BW_ECC8_DEBUG0_KES_DEBUG_SHIFT_SYND(v)                                 \
    BF_CS1(ECC8_DEBUG0, KES_DEBUG_SHIFT_SYND, v)
#endif

//--- Register HW_ECC8_DEBUG0, field KES_DEBUG_PAYLOAD_FLAG

#define BP_ECC8_DEBUG0_KES_DEBUG_PAYLOAD_FLAG 14
#define BM_ECC8_DEBUG0_KES_DEBUG_PAYLOAD_FLAG 0x00004000

#define BF_ECC8_DEBUG0_KES_DEBUG_PAYLOAD_FLAG(v)                               \
    (((v) << 14) & BM_ECC8_DEBUG0_KES_DEBUG_PAYLOAD_FLAG)

#ifndef __LANGUAGE_ASM__
#define BW_ECC8_DEBUG0_KES_DEBUG_PAYLOAD_FLAG(v)                               \
    BF_CS1(ECC8_DEBUG0, KES_DEBUG_PAYLOAD_FLAG, v)
#endif

#define BV_ECC8_DEBUG0_KES_DEBUG_PAYLOAD_FLAG__DATA 0x1
#define BV_ECC8_DEBUG0_KES_DEBUG_PAYLOAD_FLAG__AUX 0x1

//--- Register HW_ECC8_DEBUG0, field KES_DEBUG_MODE4K

#define BP_ECC8_DEBUG0_KES_DEBUG_MODE4K 13
#define BM_ECC8_DEBUG0_KES_DEBUG_MODE4K 0x00002000

#define BF_ECC8_DEBUG0_KES_DEBUG_MODE4K(v)                                     \
    (((v) << 13) & BM_ECC8_DEBUG0_KES_DEBUG_MODE4K)

#ifndef __LANGUAGE_ASM__
#define BW_ECC8_DEBUG0_KES_DEBUG_MODE4K(v)                                     \
    BF_CS1(ECC8_DEBUG0, KES_DEBUG_MODE4K, v)
#endif

#define BV_ECC8_DEBUG0_KES_DEBUG_MODE4K__4k 0x1
#define BV_ECC8_DEBUG0_KES_DEBUG_MODE4K__2k 0x1

//--- Register HW_ECC8_DEBUG0, field KES_DEBUG_KICK

#define BP_ECC8_DEBUG0_KES_DEBUG_KICK 12
#define BM_ECC8_DEBUG0_KES_DEBUG_KICK 0x00001000

#define BF_ECC8_DEBUG0_KES_DEBUG_KICK(v)                                       \
    (((v) << 12) & BM_ECC8_DEBUG0_KES_DEBUG_KICK)

#ifndef __LANGUAGE_ASM__
#define BW_ECC8_DEBUG0_KES_DEBUG_KICK(v) BF_CS1(ECC8_DEBUG0, KES_DEBUG_KICK, v)
#endif

//--- Register HW_ECC8_DEBUG0, field KES_STANDALONE

#define BP_ECC8_DEBUG0_KES_STANDALONE 11
#define BM_ECC8_DEBUG0_KES_STANDALONE 0x00000800

#define BF_ECC8_DEBUG0_KES_STANDALONE(v)                                       \
    (((v) << 11) & BM_ECC8_DEBUG0_KES_STANDALONE)

#ifndef __LANGUAGE_ASM__
#define BW_ECC8_DEBUG0_KES_STANDALONE(v) BF_CS1(ECC8_DEBUG0, KES_STANDALONE, v)
#endif

#define BV_ECC8_DEBUG0_KES_STANDALONE__NORMAL 0x0
#define BV_ECC8_DEBUG0_KES_STANDALONE__TEST_MODE 0x1

//--- Register HW_ECC8_DEBUG0, field KES_DEBUG_STEP

#define BP_ECC8_DEBUG0_KES_DEBUG_STEP 10
#define BM_ECC8_DEBUG0_KES_DEBUG_STEP 0x00000400

#define BF_ECC8_DEBUG0_KES_DEBUG_STEP(v)                                       \
    (((v) << 10) & BM_ECC8_DEBUG0_KES_DEBUG_STEP)

#ifndef __LANGUAGE_ASM__
#define BW_ECC8_DEBUG0_KES_DEBUG_STEP(v) BF_CS1(ECC8_DEBUG0, KES_DEBUG_STEP, v)
#endif

//--- Register HW_ECC8_DEBUG0, field KES_DEBUG_STALL

#define BP_ECC8_DEBUG0_KES_DEBUG_STALL 9
#define BM_ECC8_DEBUG0_KES_DEBUG_STALL 0x00000200

#define BF_ECC8_DEBUG0_KES_DEBUG_STALL(v)                                      \
    (((v) << 9) & BM_ECC8_DEBUG0_KES_DEBUG_STALL)

#ifndef __LANGUAGE_ASM__
#define BW_ECC8_DEBUG0_KES_DEBUG_STALL(v)                                      \
    BF_CS1(ECC8_DEBUG0, KES_DEBUG_STALL, v)
#endif

#define BV_ECC8_DEBUG0_KES_DEBUG_STALL__NORMAL 0x0
#define BV_ECC8_DEBUG0_KES_DEBUG_STALL__WAIT 0x1

//--- Register HW_ECC8_DEBUG0, field BM_KES_TEST_BYPASS

#define BP_ECC8_DEBUG0_BM_KES_TEST_BYPASS 8
#define BM_ECC8_DEBUG0_BM_KES_TEST_BYPASS 0x00000100

#define BF_ECC8_DEBUG0_BM_KES_TEST_BYPASS(v)                                   \
    (((v) << 8) & BM_ECC8_DEBUG0_BM_KES_TEST_BYPASS)

#ifndef __LANGUAGE_ASM__
#define BW_ECC8_DEBUG0_BM_KES_TEST_BYPASS(v)                                   \
    BF_CS1(ECC8_DEBUG0, BM_KES_TEST_BYPASS, v)
#endif

#define BV_ECC8_DEBUG0_BM_KES_TEST_BYPASS__NORMAL 0x0
#define BV_ECC8_DEBUG0_BM_KES_TEST_BYPASS__TEST_MODE 0x1

//--- Register HW_ECC8_DEBUG0, field DEBUG_REG_SELECT

#define BP_ECC8_DEBUG0_DEBUG_REG_SELECT 0
#define BM_ECC8_DEBUG0_DEBUG_REG_SELECT 0x0000003F

#define BF_ECC8_DEBUG0_DEBUG_REG_SELECT(v)                                     \
    (((v) << 0) & BM_ECC8_DEBUG0_DEBUG_REG_SELECT)

#ifndef __LANGUAGE_ASM__
#define BW_ECC8_DEBUG0_DEBUG_REG_SELECT(v)                                     \
    BF_CS1(ECC8_DEBUG0, DEBUG_REG_SELECT, v)
#endif

////////////////////////////////////////////////////////////////////////////////
//// HW_ECC8_DBGKESREAD - KES Debug Read Register
////////////////////////////////////////////////////////////////////////////////

#ifndef __LANGUAGE_ASM__
typedef union {
    reg32_t U;
    struct {
        reg32_t VALUES;
    } B;
} hw_ecc8_dbgkesread_t;
#endif

//
// constants & macros for entire HW_ECC8_DBGKESREAD register
//

#define HW_ECC8_DBGKESREAD_ADDR (REGS_ECC8_BASE + 0x00000040)

#ifndef __LANGUAGE_ASM__
#define HW_ECC8_DBGKESREAD                                                     \
    (*(volatile hw_ecc8_dbgkesread_t *)HW_ECC8_DBGKESREAD_ADDR)
#define HW_ECC8_DBGKESREAD_RD() (HW_ECC8_DBGKESREAD.U)
#endif

//
// constants & macros for individual HW_ECC8_DBGKESREAD bitfields
//

//--- Register HW_ECC8_DBGKESREAD, field VALUES

#define BP_ECC8_DBGKESREAD_VALUES 0
#define BM_ECC8_DBGKESREAD_VALUES 0xFFFFFFFF

#ifndef __LANGUAGE_ASM__
#define BF_ECC8_DBGKESREAD_VALUES(v) ((reg32_t)v)
#else
#define BF_ECC8_DBGKESREAD_VALUES(v) (v)
#endif

////////////////////////////////////////////////////////////////////////////////
//// HW_ECC8_DBGCSFEREAD - Chien Search Forney Evaluator Debug Read Register
////////////////////////////////////////////////////////////////////////////////

#ifndef __LANGUAGE_ASM__
typedef union {
    reg32_t U;
    struct {
        reg32_t VALUES;
    } B;
} hw_ecc8_dbgcsferead_t;
#endif

//
// constants & macros for entire HW_ECC8_DBGCSFEREAD register
//

#define HW_ECC8_DBGCSFEREAD_ADDR (REGS_ECC8_BASE + 0x00000050)

#ifndef __LANGUAGE_ASM__
#define HW_ECC8_DBGCSFEREAD                                                    \
    (*(volatile hw_ecc8_dbgcsferead_t *)HW_ECC8_DBGCSFEREAD_ADDR)
#define HW_ECC8_DBGCSFEREAD_RD() (HW_ECC8_DBGCSFEREAD.U)
#endif

//
// constants & macros for individual HW_ECC8_DBGCSFEREAD bitfields
//

//--- Register HW_ECC8_DBGCSFEREAD, field VALUES

#define BP_ECC8_DBGCSFEREAD_VALUES 0
#define BM_ECC8_DBGCSFEREAD_VALUES 0xFFFFFFFF

#ifndef __LANGUAGE_ASM__
#define BF_ECC8_DBGCSFEREAD_VALUES(v) ((reg32_t)v)
#else
#define BF_ECC8_DBGCSFEREAD_VALUES(v) (v)
#endif

////////////////////////////////////////////////////////////////////////////////
//// HW_ECC8_DBGSYNDGENREAD - Syndrome Generator Debug Read Register
////////////////////////////////////////////////////////////////////////////////

#ifndef __LANGUAGE_ASM__
typedef union {
    reg32_t U;
    struct {
        reg32_t VALUES;
    } B;
} hw_ecc8_dbgsyndgenread_t;
#endif

//
// constants & macros for entire HW_ECC8_DBGSYNDGENREAD register
//

#define HW_ECC8_DBGSYNDGENREAD_ADDR (REGS_ECC8_BASE + 0x00000060)

#ifndef __LANGUAGE_ASM__
#define HW_ECC8_DBGSYNDGENREAD                                                 \
    (*(volatile hw_ecc8_dbgsyndgenread_t *)HW_ECC8_DBGSYNDGENREAD_ADDR)
#define HW_ECC8_DBGSYNDGENREAD_RD() (HW_ECC8_DBGSYNDGENREAD.U)
#endif

//
// constants & macros for individual HW_ECC8_DBGSYNDGENREAD bitfields
//

//--- Register HW_ECC8_DBGSYNDGENREAD, field VALUES

#define BP_ECC8_DBGSYNDGENREAD_VALUES 0
#define BM_ECC8_DBGSYNDGENREAD_VALUES 0xFFFFFFFF

#ifndef __LANGUAGE_ASM__
#define BF_ECC8_DBGSYNDGENREAD_VALUES(v) ((reg32_t)v)
#else
#define BF_ECC8_DBGSYNDGENREAD_VALUES(v) (v)
#endif

////////////////////////////////////////////////////////////////////////////////
//// HW_ECC8_DBGAHBMREAD - AHB Master and ECC8 Controller Debug Read Register
////////////////////////////////////////////////////////////////////////////////

#ifndef __LANGUAGE_ASM__
typedef union {
    reg32_t U;
    struct {
        reg32_t VALUES;
    } B;
} hw_ecc8_dbgahbmread_t;
#endif

//
// constants & macros for entire HW_ECC8_DBGAHBMREAD register
//

#define HW_ECC8_DBGAHBMREAD_ADDR (REGS_ECC8_BASE + 0x00000070)

#ifndef __LANGUAGE_ASM__
#define HW_ECC8_DBGAHBMREAD                                                    \
    (*(volatile hw_ecc8_dbgahbmread_t *)HW_ECC8_DBGAHBMREAD_ADDR)
#define HW_ECC8_DBGAHBMREAD_RD() (HW_ECC8_DBGAHBMREAD.U)
#endif

//
// constants & macros for individual HW_ECC8_DBGAHBMREAD bitfields
//

//--- Register HW_ECC8_DBGAHBMREAD, field VALUES

#define BP_ECC8_DBGAHBMREAD_VALUES 0
#define BM_ECC8_DBGAHBMREAD_VALUES 0xFFFFFFFF

#ifndef __LANGUAGE_ASM__
#define BF_ECC8_DBGAHBMREAD_VALUES(v) ((reg32_t)v)
#else
#define BF_ECC8_DBGAHBMREAD_VALUES(v) (v)
#endif

////////////////////////////////////////////////////////////////////////////////
//// HW_ECC8_BLOCKNAME - ECC8 Block Name Register
////////////////////////////////////////////////////////////////////////////////

#ifndef __LANGUAGE_ASM__
typedef union {
    reg32_t U;
    struct {
        reg32_t NAME;
    } B;
} hw_ecc8_blockname_t;
#endif

//
// constants & macros for entire HW_ECC8_BLOCKNAME register
//

#define HW_ECC8_BLOCKNAME_ADDR (REGS_ECC8_BASE + 0x00000080)

#ifndef __LANGUAGE_ASM__
#define HW_ECC8_BLOCKNAME                                                      \
    (*(volatile hw_ecc8_blockname_t *)HW_ECC8_BLOCKNAME_ADDR)
#define HW_ECC8_BLOCKNAME_RD() (HW_ECC8_BLOCKNAME.U)
#endif

//
// constants & macros for individual HW_ECC8_BLOCKNAME bitfields
//

//--- Register HW_ECC8_BLOCKNAME, field NAME

#define BP_ECC8_BLOCKNAME_NAME 0
#define BM_ECC8_BLOCKNAME_NAME 0xFFFFFFFF

#ifndef __LANGUAGE_ASM__
#define BF_ECC8_BLOCKNAME_NAME(v) ((reg32_t)v)
#else
#define BF_ECC8_BLOCKNAME_NAME(v) (v)
#endif

////////////////////////////////////////////////////////////////////////////////
//// HW_ECC8_VERSION - ECC8 Version Register
////////////////////////////////////////////////////////////////////////////////

#ifndef __LANGUAGE_ASM__
typedef union {
    reg32_t U;
    struct {
        reg16_t STEP;
        reg8_t MINOR;
        reg8_t MAJOR;
    } B;
} hw_ecc8_version_t;
#endif

//
// constants & macros for entire HW_ECC8_VERSION register
//

#define HW_ECC8_VERSION_ADDR (REGS_ECC8_BASE + 0x000000A0)

#ifndef __LANGUAGE_ASM__
#define HW_ECC8_VERSION (*(volatile hw_ecc8_version_t *)HW_ECC8_VERSION_ADDR)
#define HW_ECC8_VERSION_RD() (HW_ECC8_VERSION.U)
#endif

//
// constants & macros for individual HW_ECC8_VERSION bitfields
//

//--- Register HW_ECC8_VERSION, field MAJOR

#define BP_ECC8_VERSION_MAJOR 24
#define BM_ECC8_VERSION_MAJOR 0xFF000000

#ifndef __LANGUAGE_ASM__
#define BF_ECC8_VERSION_MAJOR(v) ((((reg32_t)v) << 24) & BM_ECC8_VERSION_MAJOR)
#else
#define BF_ECC8_VERSION_MAJOR(v) (((v) << 24) & BM_ECC8_VERSION_MAJOR)
#endif

//--- Register HW_ECC8_VERSION, field MINOR

#define BP_ECC8_VERSION_MINOR 16
#define BM_ECC8_VERSION_MINOR 0x00FF0000

#define BF_ECC8_VERSION_MINOR(v) (((v) << 16) & BM_ECC8_VERSION_MINOR)

//--- Register HW_ECC8_VERSION, field STEP

#define BP_ECC8_VERSION_STEP 0
#define BM_ECC8_VERSION_STEP 0x0000FFFF

#define BF_ECC8_VERSION_STEP(v) (((v) << 0) & BM_ECC8_VERSION_STEP)

#endif // _REGSECC8_H

////////////////////////////////////////////////////////////////////////////////
