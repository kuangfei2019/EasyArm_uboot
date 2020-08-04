/*
 * iMX28 Boot Prep
 *
 * Copyright 2008-2010 Freescale Semiconductor
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
 */

#include <debug.h>
#include "regsclkctrl.h"
#include "regsemi.h"
#include "regsdram.h"
#include "regspower.h"
#include "regsuartdbg.h"
#include "regspinctrl.h"
#include "regsdigctl.h"
#include "regsocotp.h"
#include <stdarg.h>

#define PIN_DRIVE_12mA 2
#define EMI_PIN_DRIVE_20mA 2
#define EMI_PIN_DRIVE_ADDRESS EMI_PIN_DRIVE_20mA
#define EMI_PIN_DRIVE_CONTROL EMI_PIN_DRIVE_20mA
#define EMI_PIN_DRIVE_DUALPAD EMI_PIN_DRIVE_20mA
#define EMI_PIN_DRIVE_DATA_SLICE_3 EMI_PIN_DRIVE_20mA
#define EMI_PIN_DRIVE_DATA_SLICE_2 EMI_PIN_DRIVE_20mA
#define EMI_PIN_DRIVE_DATA_SLICE_1 EMI_PIN_DRIVE_20mA
#define EMI_PIN_DRIVE_DATA_SLICE_0 EMI_PIN_DRIVE_20mA

// for ddr2 bsp
#define EMI_MAX_BANK_COUNT 8
#define EMI_DDR2_PHY_BASE 0x40000000
#define EMI_EACH_BANK_SIZE (16 * 1024 * 1024) // 16M
#define EMI_EACH_BANK_OFFSET(n) (EMI_EACH_BANK_SIZE * n + EMI_DDR2_PHY_BASE)
#define EMI_MAX_FILL_COUNT (3 * 1024)
#define EMI_MAX_MEM_BK (0x0000F100)
#define EMI_MAX_MEM_BK_ANOTHER (0x0000F400)

#define printf(fmt, args...) // disable debug print

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;

struct ddr2_information {
    unsigned char header;
    unsigned char length;
    char ddr2_info[9];
};
struct ddr2_information ddr2_array[] = {
    {.header = 0xFE, .length = 5, .ddr2_info = "128M"},
    {.header = 0xFE, .length = 4, .ddr2_info = "64M"}};

//#define EMI_96M
/* Debug uart have been init by boot rom. */
void putc(char ch) {
    int loop = 0;
    while (HW_UARTDBGFR_RD() & BM_UARTDBGFR_TXFF) {
        loop++;
        if (loop > 10000)
            break;
    };

    /* if(!(HW_UARTDBGFR_RD() &BM_UARTDBGFR_TXFF)) */
    HW_UARTDBGDR_WR(ch);
}

#if 0
#define DEBUGE_PRINT()                                                         \
    do {                                                                       \
        printf("\r\n");                                                        \
        printf(__func__);                                                      \
        printf(":line=%d \r\n", __LINE__);                                     \
    } while (0)

#else
#define DEBUGE_PRINT()
#endif

void delay(unsigned int us) {
    unsigned int start, cur;
    start = cur = HW_DIGCTL_MICROSECONDS_RD();

    while (cur < start + us) {

        cur = HW_DIGCTL_MICROSECONDS_RD();
        /*printf("0x%x\r\n",cur);*/
    }
}

void mmu_disable_dcache() {
    register int i;

    /* read control register */
    __asm__ __volatile__("mrc p15, 0, %0, c1, c0, 0" : "=r"(i));

    i &= ~(1 << 2);

    /* write back to control register */
    __asm__ __volatile__("mcr p15, 0, %0, c1, c0, 0" : : "r"(i));
}

void mmu_disable_icache() {
    register int i;

    /* read control register */
    __asm__ __volatile__("mrc p15, 0, %0, c1, c0, 0" : "=r"(i));

    i &= ~(1 << 12);

    /* write back to control register */
    __asm__ __volatile__("mcr p15, 0, %0, c1, c0, 0" : : "r"(i));
}

void mmu_disable() {
    register int i;

    /* read control register */
    __asm__ __volatile__("mrc p15, 0, %0, c1, c0, 0" : "=r"(i));

    i &= ~0x1;

    /* write back to control register */
    __asm__ __volatile__("mcr p15, 0, %0, c1, c0, 0" : : "r"(i));
}

void mmu_invalidate_tlb() {
    __asm__ __volatile__("mcr p15, 0, %0, c8, c7, 0" : : "r"(0));
}

void Init_ddr2_ede1116_4_133MHz(void) {

    volatile unsigned int *DRAM_REG =
        (volatile unsigned int *)HW_DRAM_CTL00_ADDR;

    DRAM_REG[0] =
        0x00000000; // 00000000000000000000000000000000 user_def_reg_0(RW)
    DRAM_REG[1] =
        0x00000000; // 00000000000000000000000000000000 user_def_reg_1(RW)
    DRAM_REG[2] =
        0x00000000; // 00000000000000000000000000000000 user_def_reg_2(RW)
    DRAM_REG[3] =
        0x00000000; // 00000000000000000000000000000000 user_def_reg_3(RW)
    DRAM_REG[4] =
        0x00000000; // 00000000000000000000000000000000 user_def_reg_4(RW)
    DRAM_REG[5] =
        0x00000000; // 00000000000000000000000000000000 user_def_reg_5(RW)
    DRAM_REG[6] =
        0x00000000; // 00000000000000000000000000000000 user_def_reg_6(RW)
    DRAM_REG[7] =
        0x00000000; // 00000000000000000000000000000000 user_def_reg_7(RW)
    DRAM_REG[8] =
        0x00000000; // 00000000000000000000000000000000 user_def_reg_ro_0(RD)
    DRAM_REG[9] =
        0x00000000; // 00000000000000000000000000000000 user_def_reg_ro_1(RD)
    DRAM_REG[10] =
        0x00000000; // 00000000000000000000000000000000 user_def_reg_ro_2(RD)
    DRAM_REG[11] =
        0x00000000; // 00000000000000000000000000000000 user_def_reg_ro_3(RD)
    DRAM_REG[12] =
        0x00000000; // 00000000000000000000000000000000 user_def_reg_ro_4(RD)
    DRAM_REG[13] =
        0x00000000; // 00000000000000000000000000000000 user_def_reg_ro_5(RD)
    DRAM_REG[14] =
        0x00000000; // 00000000000000000000000000000000 user_def_reg_ro_6(RD)
    DRAM_REG[15] =
        0x00000000; // 00000000000000000000000000000000 user_def_reg_ro_7(RD)
    DRAM_REG[16] = 0x00000000; // 0000000_0 write_modereg(WR) 0000000_0
                               // power_down(RW) 000000000000000_0 start(RW)
    DRAM_REG[17] =
        0x00000100; // 0000000_0 auto_refresh_mode(RW) 0000000_0 arefresh(WR)
                    // 0000000_1 enable_quick_srefresh(RW) 0000000_0
                    // srefresh(RW+)
    DRAM_REG[18] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[19] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[20] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[21] =
        0x00000000; // 00000_000 cke_delay(RW) 00000000 dll_lock(RD) 0000000_0
                    // dlllockreg(RD) 0000000_0 dll_bypass_mode(RW)
    DRAM_REG[22] =
        0x00000000; // 000000000000_0000 lowpower_refresh_enable(RW) 000_00000
                    // lowpower_control(RW) 000_00000 lowpower_auto_enable(RW)
    DRAM_REG[23] = 0x00000000; // 0000000000000000 lowpower_internal_cnt(RW)
                               // 0000000000000000 lowpower_external_cnt(RW)
    DRAM_REG[24] = 0x00000000; // 0000000000000000 lowpower_self_refresh_cnt(RW)
                               // 0000000000000000 lowpower_refresh_hold(RW)
    DRAM_REG[25] = 0x00000000; // 00000000000000000000000000000000
                               // lowpower_power_down_cnt(RW)
    DRAM_REG[26] = 0x00010101; // 000000000000000_1 priority_en(RW) 0000000_1
                               // addr_cmp_en(RW) 0000000_1 placement_en(RW)
    DRAM_REG[27] =
        0x01010101; // 0000000_1 swap_port_rw_same_en(RW) 0000000_1 swap_en(RW)
                    // 0000000_1 bank_split_en(RW) 0000000_1 rw_same_en(RW)
    DRAM_REG[28] = 0x000f0f01; // 00000_000 q_fullness(RW) 0000_1111
                               // age_count(RW) 0000_1111 command_age_count(RW)
                               // 0000000_1 active_aging(RW)
    DRAM_REG[29] = 0x0f02020a; // 0000_1111 cs_map(RW) 00000_010 column_size(RW)
                               // 00000_010 addr_pins(RW) 0000_1010 aprebit(RW)
    DRAM_REG[30] = 0x00000000; // 0000000000000_000 max_cs_reg(RD) 0000_0000
                               // max_row_reg(RD) 0000_0000 max_col_reg(RD)
    DRAM_REG[31] =
        0x00010101; // 000000000000000_1 eight_bank_mode(RW) 0000000_1
                    // drive_dq_dqs(RW) 0000000_1 dqs_n_en(RW)
    DRAM_REG[32] = 0x00000100; // 00000000000000000000000_1 reduc(RW) 0000000_0
                               // reg_dimm_enable(RW)
    DRAM_REG[33] = 0x00000100; // 00000000000000000000000_1 concurrentap(RW)
                               // 0000000_0 ap(RW)
    DRAM_REG[34] =
        0x00000000; // 0000000_0 writeinterp(RW) 0000000_0 intrptwritea(RW)
                    // 0000000_0 intrptreada(RW) 0000000_0 intrptapburst(RW)
    DRAM_REG[35] =
        0x00000002; // 000000000000000_0 pwrup_srefresh_exit(RW)
                    // 0000000_0 no_cmd_init(RW) 0000_0010 initaref(RW)
    DRAM_REG[36] =
        0x01010000; // 0000000_1 tref_enable(RW) 0000000_1
                    // tras_lockout(RW) 000000000000000_0 fast_write(RW)
    DRAM_REG[37] =
        0x07080403; // 0000_0111 caslat_lin_gate(RW) 0000_1000 caslat_lin(RW)
                    // 00000_100 caslat(RW) 0000_0011 wrlat(RW)
    DRAM_REG[38] = 0x04003603; // 000_00100 tdal(RW) 0000000000110110 tcpd(RW)
                               // 00000_011 tcke(RW)
    DRAM_REG[39] =
        0x070000c8; // 00_000111 tfaw(RW) 000000000000000011001000 tdll(RW)
    DRAM_REG[40] =
        0x0200682b; // 000_00010 tmrd(RW) 000000000110100000101011 tinit(RW)
    DRAM_REG[41] = 0x00020208; // 0000000000000010 tpdex(RW) 00000010
                               // trcd_int(RW) 00_001000 trc(RW)
    DRAM_REG[42] = 0x00246c06; // 000000000010010001101100 tras_max(RW) 00000110
                               // tras_min(RW)
    DRAM_REG[43] = 0x02110409; // 0000_0010 trp(RW) 00010001 trfc(RW)
                               // 00_00010000001001 tref(RW)
    DRAM_REG[44] = 0x01020202; // 0000_0001 twtr(RW) 000_00010 twr_int(RW)
                               // 00000_010 trtp(RW) 00000_010 trrd(RW)
    DRAM_REG[45] =
        0x00c80013; // 0000000011001000 txsr(RW) 0000000000010011 txsnr(RW)
    DRAM_REG[46] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[47] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[48] = 0x00012100; // 0_0000000 axi0_current_bdw(RD) 0000000_1
                               // axi0_bdw_ovflow(RW) 0_0100001 axi0_bdw(RW)
                               // 000000_00 axi0_fifo_type_reg(RW)
    DRAM_REG[49] =
        0xffff0303; // 0101010101010101 axi0_en_size_lt_width_instr(RW)
                    // 00000_011 axi0_w_priority(RW) 00000_011
                    // axi0_r_priority(RW)
    DRAM_REG[50] = 0x00012100; // 0_0000000 axi1_current_bdw(RD) 0000000_1
                               // axi1_bdw_ovflow(RW) 0_0100001 axi1_bdw(RW)
                               // 000000_00 axi1_fifo_type_reg(RW)
    DRAM_REG[51] =
        0xffff0303; // 1111111100000000 axi1_en_size_lt_width_instr(RW)
                    // 00000_011 axi1_w_priority(RW) 00000_011
                    // axi1_r_priority(RW)
    DRAM_REG[52] = 0x00012100; // 0_0000000 axi2_current_bdw(RD) 0000000_1
                               // axi2_bdw_ovflow(RW) 0_0100001 axi2_bdw(RW)
                               // 000000_00 axi2_fifo_type_reg(RW)
    DRAM_REG[53] =
        0xffff0303; // 0000000000000001 axi2_en_size_lt_width_instr(RW)
                    // 00000_011 axi2_w_priority(RW) 00000_011
                    // axi2_r_priority(RW)
    DRAM_REG[54] = 0x00012100; // 0_0000000 axi3_current_bdw(RD) 0000000_1
                               // axi3_bdw_ovflow(RW) 0_0100001 axi3_bdw(RW)
                               // 000000_00 axi3_fifo_type_reg(RW)
    DRAM_REG[55] =
        0xffff0303; // 0000000000000001 axi3_en_size_lt_width_instr(RW)
                    // 00000_011 axi3_w_priority(RW) 00000_011
                    // axi3_r_priority(RW)
    DRAM_REG[56] =
        0x00000003; // 00000000000000000000000000000_011 arb_cmd_q_threshold(RW)
    DRAM_REG[57] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[58] = 0x00000000; // 00000_00000000000 int_status(RD)
                               // 00000_00000000000 int_mask(RW)
    DRAM_REG[59] =
        0x00000000; // 00000000000000000000000000000000 out_of_range_addr(RD)
    DRAM_REG[60] = 0x00000000; // 000000000000000000000000000000_00
    DRAM_REG[61] = 0x00000000; // 00_000000 out_of_range_type(RD) 0_0000000
                               // out_of_range_length(RD) 000_0000000000000
                               // out_of_range_source_id(RD)
    DRAM_REG[62] =
        0x00000000; // 00000000000000000000000000000000 port_cmd_error_addr(RD)
    DRAM_REG[63] = 0x00000000; // 000000000000000000000000000000_00
    DRAM_REG[64] =
        0x00000000; // 00000000000_0000000000000 port_cmd_error_id(RD)
                    // 0000_0000 port_cmd_error_type(RD)
    DRAM_REG[65] =
        0x00000000; // 00000000000_0000000000000 port_data_error_id(RD)
                    // 00000_000 port_data_error_type(RD)
    DRAM_REG[66] = 0x00000409; // 000000000000_0000 tdfi_ctrlupd_min(RD)
                               // 00_00010000001001 tdfi_ctrlupd_max(RW)
    DRAM_REG[67] =
        0x01000f02; // 0000_0001 tdfi_dram_clk_enable(RW) 00000_000
                    // tdfi_dram_clk_disable(RW) 0000_0000 dram_clk_disable(RW)
                    // 0000_0010 tdfi_ctrl_delay(RW)
    DRAM_REG[68] = 0x04090409; // 00_00010000001001 tdfi_phyupd_type0(RW)
                               // 00_00010000001001 tdfi_phyupd_resp(RW)
    DRAM_REG[69] =
        0x00000200; // 00000000000000000000_0010 tdfi_phy_wrlat_base(RW)
                    // 0000_0000 tdfi_phy_wrlat(RD)
    DRAM_REG[70] =
        0x00020006; // 000000000000_0010 tdfi_rddata_en_base(RW) 0000_0000
                    // tdfi_rddata_en(RD) 0000_0110 tdfi_phy_rdlat(RW)
    // DRAM_REG[71] =  0xf3014b27  ;  //11110011000000010100101100100111
    // phy_ctrl_reg_0_0(RW) DRAM_REG[72] =  0xf3014b27  ;
    // //11110011000000010100101100100111 phy_ctrl_reg_0_1(RW) DRAM_REG[73] =
    // 0xf3014b27  ;  //11110011000000010100101100100111 phy_ctrl_reg_0_2(RW)
    // DRAM_REG[74] =  0xf3014b27  ;  //11110011000000010100101100100111
    // phy_ctrl_reg_0_3(RW)

    ////////////////////
    DRAM_REG[71] = 0xf4004a27;
    DRAM_REG[72] = 0xf4004a27;
    DRAM_REG[73] = 0xf4004a27;
    DRAM_REG[74] = 0xf4004a27;

    DRAM_REG[75] =
        0x07400300; // 00000111010000000000001100000000 phy_ctrl_reg_1_0(RW)
    DRAM_REG[76] =
        0x07400300; // 00000111010000000000001100000000 phy_ctrl_reg_1_1(RW)
    DRAM_REG[77] =
        0x07400300; // 00000111010000000000001100000000 phy_ctrl_reg_1_2(RW)
    DRAM_REG[78] =
        0x07400300; // 00000111010000000000001100000000 phy_ctrl_reg_1_3(RW)

    ////////////////////
    // DRAM_REG[79] =  0x00000004  ;  //00000000000000000000000000000100
    // phy_ctrl_reg_2(RW)
    DRAM_REG[79] = 0x00000005;

    DRAM_REG[80] = 0x00000000; // 00000000000000000000000000000000
                               // dft_ctrl_reg(RW)
    DRAM_REG[81] =
        0x00000000; // 0000000000000000000_00000 ocd_adjust_pup_cs_0(RW)
                    // 000_00000 ocd_adjust_pdn_cs_0(RW)
    DRAM_REG[82] = 0x01000000; // 0000000_1 odt_alt_en(RW)
                               // 000000000000000000000000
    DRAM_REG[83] =
        0x01020408; // 0000_0001 odt_rd_map_cs3(RW) 0000_0010 odt_rd_map_cs2(RW)
                    // 0000_0100 odt_rd_map_cs1(RW) 0000_1000 odt_rd_map_cs0(RW)
    DRAM_REG[84] =
        0x08040201; // 0000_1000 odt_wr_map_cs3(RW) 0000_0100 odt_wr_map_cs2(RW)
                    // 0000_0010 odt_wr_map_cs1(RW) 0000_0001 odt_wr_map_cs0(RW)
    DRAM_REG[85] =
        0x000f1133; // 00000000000011110001000100110011 pad_ctrl_reg_0(RW)
    DRAM_REG[86] = 0x00000000; // 00000000000000000000000000000000 version(RD)
    /* DRAM_REG[87] =  0x00091e36  ;  //00000000000010010001111000110110
     dll_ctrl_reg_0_0(RW) DRAM_REG[88] =  0x00091e36  ;
     //00000000000010010001111000110110 dll_ctrl_reg_0_1(RW) DRAM_REG[89] =
     0x00091e36  ;  //00000000000010010001111000110110 dll_ctrl_reg_0_2(RW)
     DRAM_REG[90] =  0x00091e36  ;  //00000000000010010001111000110110
     dll_ctrl_reg_0_3(RW) DRAM_REG[91] =  0x00091f0f  ;
     //00000000000010010001111100001111 dll_ctrl_reg_1_0(RW) DRAM_REG[92] =
     0x00091f0f  ;  //00000000000010010001111100001111 dll_ctrl_reg_1_1(RW)
     DRAM_REG[93] =  0x00091f0f  ;  //00000000000010010001111100001111
     dll_ctrl_reg_1_2(RW) DRAM_REG[94] =  0x00091f0f  ;
     //00000000000010010001111100001111 dll_ctrl_reg_1_3(RW)
    */

    DRAM_REG[87] = 0x00001f04;
    DRAM_REG[88] = 0x00001f04;
    DRAM_REG[89] = 0x00001f04;
    DRAM_REG[90] = 0x00001f04;
    DRAM_REG[91] = 0x00001f04;
    DRAM_REG[92] = 0x00001f04;
    DRAM_REG[93] = 0x00001f04;
    DRAM_REG[94] = 0x00001f04;

    DRAM_REG[95] =
        0x00000000; // 00000000000000000000000000000000 dll_obs_reg_0_0(RD)
    DRAM_REG[96] =
        0x00000000; // 00000000000000000000000000000000 dll_obs_reg_0_1(RD)
    DRAM_REG[97] =
        0x00000000; // 00000000000000000000000000000000 dll_obs_reg_0_2(RD)
    DRAM_REG[98] =
        0x00000000; // 00000000000000000000000000000000 dll_obs_reg_0_3(RD)
    DRAM_REG[99] =
        0x00000000; // 00000000000000000000000000000000 phy_obs_reg_0_0(RD)
    DRAM_REG[100] =
        0x00000000; // 00000000000000000000000000000000 phy_obs_reg_0_1(RD)
    DRAM_REG[101] =
        0x00000000; // 00000000000000000000000000000000 phy_obs_reg_0_2(RD)
    DRAM_REG[102] =
        0x00000000; // 00000000000000000000000000000000 phy_obs_reg_0_3(RD)
    DRAM_REG[103] =
        0x00000000; // 00000000000000000000000000000000 dll_obs_reg_1_0(RD)
    DRAM_REG[104] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[105] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[106] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[107] = 0x00000000; // 00000000000000000000000_000000000
    DRAM_REG[108] =
        0x00000000; // 00000000000000000000000000000000 dll_obs_reg_1_1(RD)
    DRAM_REG[109] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[110] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[111] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[112] = 0x00000000; // 00000000000000000000000_000000000
    DRAM_REG[113] =
        0x00000000; // 00000000000000000000000000000000 dll_obs_reg_1_2(RD)
    DRAM_REG[114] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[115] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[116] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[117] = 0x00000000; // 00000000000000000000000_000000000
    DRAM_REG[118] =
        0x00000000; // 00000000000000000000000000000000 dll_obs_reg_1_3(RD)
    DRAM_REG[119] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[120] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[121] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[122] = 0x00000000; // 00000000000000000000000_000000000
    DRAM_REG[123] =
        0x00000000; // 00000000000000000000000000000000 dll_obs_reg_2_0(RD)
    DRAM_REG[124] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[125] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[126] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[127] = 0x00000000; // 00000000000000000000000_000000000
    DRAM_REG[128] =
        0x00000000; // 00000000000000000000000000000000 dll_obs_reg_2_1(RD)
    DRAM_REG[129] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[130] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[131] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[132] = 0x00000000; // 00000000000000000000000_000000000
    DRAM_REG[133] =
        0x00000000; // 00000000000000000000000000000000 dll_obs_reg_2_2(RD)
    DRAM_REG[134] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[135] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[136] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[137] = 0x00000000; // 00000000000000000000000_000000000
    DRAM_REG[138] =
        0x00000000; // 00000000000000000000000000000000 dll_obs_reg_2_3(RD)
    DRAM_REG[139] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[140] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[141] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[142] = 0x00000000; // 00000000000000000000000_000000000
    DRAM_REG[143] =
        0x00000000; // 00000000000000000000000000000000 dll_obs_reg_3_0(RD)
    DRAM_REG[144] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[145] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[146] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[147] = 0x00000000; // 00000000000000000000000_000000000
    DRAM_REG[148] =
        0x00000000; // 00000000000000000000000000000000 dll_obs_reg_3_1(RD)
    DRAM_REG[149] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[150] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[151] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[152] = 0x00000000; // 00000000000000000000000_000000000
    DRAM_REG[153] =
        0x00000000; // 00000000000000000000000000000000 dll_obs_reg_3_2(RD)
    DRAM_REG[154] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[155] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[156] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[157] = 0x00000000; // 00000000000000000000000_000000000
    DRAM_REG[158] =
        0x00000000; // 00000000000000000000000000000000 dll_obs_reg_3_3(RD)
    DRAM_REG[159] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[160] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[161] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[162] = 0x00010000; // 00000_000 w2r_samecs_dly(RW) 00000_001
                                // w2r_diffcs_dly(RW) 0000000_000000000
    DRAM_REG[163] =
        0x00030404; // 00000000 dll_rst_adj_dly(RW) 0000_0011 wrlat_adj(RW)
                    // 0000_0100 rdlat_adj(RW) 0000_0100 dram_class(RW)
    DRAM_REG[164] =
        0x00000002; // 00000000000000_0000000000 int_ack(WR) 00000010 tmod(RW)
    DRAM_REG[165] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[166] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[167] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[168] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[169] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[170] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[171] =
        0x01010000; // 0000000_1 axi5_bdw_ovflow(RW) 0000000_1
                    // axi4_bdw_ovflow(RW) 0000000000000000 dll_rst_delay(RW)
    DRAM_REG[172] =
        0x01000000; // 0000000_1 resync_dll_per_aref_en(RW) 0000000_0
                    // resync_dll(WR) 0000000_0 concurrentap_wr_only(RW)
                    // 0000000_0 cke_status(RD)
    DRAM_REG[173] =
        0x03030000; // 00000_011 axi4_w_priority(RW) 00000_011
                    // axi4_r_priority(RW) 000000_00 axi5_fifo_type_reg(RW)
                    // 000000_00 axi4_fifo_type_reg(RW)
    DRAM_REG[174] =
        0x00010303; // 00000_000 r2r_samecs_dly(RW) 00000_001 r2r_diffcs_dly(RW)
                    // 00000_011 axi5_w_priority(RW) 00000_011
                    // axi5_r_priority(RW)
    DRAM_REG[175] =
        0x01020202; // 00000_001 w2w_diffcs_dly(RW) 00000_010
                    // tbst_int_interval(RW) 00000_010
                    // r2w_samecs_dly(RW) 00000_010 r2w_diffcs_dly(RW)
    DRAM_REG[176] = 0x00000000; // 0000_0000 add_odt_clk_sametype_diffcs(RW)
                                // 0000_0000 add_odt_clk_difftype_samecs(RW)
                                // 0000_0000 add_odt_clk_difftype_diffcs(RW)
                                // 00000_000 w2w_samecs_dly(RW)
    DRAM_REG[177] = 0x02030303; // 000_00010 tccd(RW) 0000_0011 trp_ab(RW)
                                // 0000_0011 cksrx(RW) 0000_0011 cksre(RW)
    DRAM_REG[178] =
        0x21002103; // 0_0100001 axi5_bdw(RW) 0_0000000 axi4_current_bdw(RD)
                    // 0_0100001 axi4_bdw(RW) 000_00011 tckesr(RW)
    DRAM_REG[179] =
        0x00040900; // 0000000000_00010000001001 tdfi_phyupd_type1(RW)
                    // 0_0000000 axi5_current_bdw(RD)
    DRAM_REG[180] = 0x04090409; // 00_00010000001001 tdfi_phyupd_type3(RW)
                                // 00_00010000001001 tdfi_phyupd_type2(RW)
    DRAM_REG[181] = 0x02420242; // 0_000001001000010 mr0_data_1(RW)
                                // 0_000001001000010 mr0_data_0(RW)
    DRAM_REG[182] = 0x02420242; // 0_000001001000010 mr0_data_3(RW)
                                // 0_000001001000010 mr0_data_2(RW)
    DRAM_REG[183] = 0x00040004; // 0_000000000000100 mr1_data_1(RW)
                                // 0_000000000000100 mr1_data_0(RW)
    DRAM_REG[184] = 0x00040004; // 0_000000000000100 mr1_data_3(RW)
                                // 0_000000000000100 mr1_data_2(RW)
    DRAM_REG[185] = 0x00000000; // 0_000000000000000 mr2_data_1(RW)
                                // 0_000000000000000 mr2_data_0(RW)
    DRAM_REG[186] = 0x00000000; // 0_000000000000000 mr2_data_3(RW)
                                // 0_000000000000000 mr2_data_2(RW)
    DRAM_REG[187] = 0x00000000; // 0_000000000000000 mr3_data_1(RW)
                                // 0_000000000000000 mr3_data_0(RW)
    DRAM_REG[188] = 0x00000000; // 0_000000000000000 mr3_data_3(RW)
                                // 0_000000000000000 mr3_data_2(RW)
    DRAM_REG[189] =
        0xffffffff; // 0000000000000001 axi5_en_size_lt_width_instr(RW)
                    // 0000000000000001 axi4_en_size_lt_width_instr(RW)
}

void Init_ddr2_ede1116_4_150MHz(void) {

    volatile unsigned int *DRAM_REG =
        (volatile unsigned int *)HW_DRAM_CTL00_ADDR;

    DRAM_REG[0] =
        0x00000000; // 00000000000000000000000000000000 user_def_reg_0(RW)
    DRAM_REG[1] =
        0x00000000; // 00000000000000000000000000000000 user_def_reg_1(RW)
    DRAM_REG[2] =
        0x00000000; // 00000000000000000000000000000000 user_def_reg_2(RW)
    DRAM_REG[3] =
        0x00000000; // 00000000000000000000000000000000 user_def_reg_3(RW)
    DRAM_REG[4] =
        0x00000000; // 00000000000000000000000000000000 user_def_reg_4(RW)
    DRAM_REG[5] =
        0x00000000; // 00000000000000000000000000000000 user_def_reg_5(RW)
    DRAM_REG[6] =
        0x00000000; // 00000000000000000000000000000000 user_def_reg_6(RW)
    DRAM_REG[7] =
        0x00000000; // 00000000000000000000000000000000 user_def_reg_7(RW)
    DRAM_REG[8] =
        0x00000000; // 00000000000000000000000000000000 user_def_reg_ro_0(RD)
    DRAM_REG[9] =
        0x00000000; // 00000000000000000000000000000000 user_def_reg_ro_1(RD)
    DRAM_REG[10] =
        0x00000000; // 00000000000000000000000000000000 user_def_reg_ro_2(RD)
    DRAM_REG[11] =
        0x00000000; // 00000000000000000000000000000000 user_def_reg_ro_3(RD)
    DRAM_REG[12] =
        0x00000000; // 00000000000000000000000000000000 user_def_reg_ro_4(RD)
    DRAM_REG[13] =
        0x00000000; // 00000000000000000000000000000000 user_def_reg_ro_5(RD)
    DRAM_REG[14] =
        0x00000000; // 00000000000000000000000000000000 user_def_reg_ro_6(RD)
    DRAM_REG[15] =
        0x00000000; // 00000000000000000000000000000000 user_def_reg_ro_7(RD)
    DRAM_REG[16] = 0x00000000; // 0000000_0 write_modereg(WR) 0000000_0
                               // power_down(RW) 000000000000000_0 start(RW)
    DRAM_REG[17] =
        0x00000100; // 0000000_0 auto_refresh_mode(RW) 0000000_0 arefresh(WR)
                    // 0000000_1 enable_quick_srefresh(RW) 0000000_0
                    // srefresh(RW+)
    DRAM_REG[18] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[19] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[20] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[21] =
        0x00000000; // 00000_000 cke_delay(RW) 00000000 dll_lock(RD) 0000000_0
                    // dlllockreg(RD) 0000000_0 dll_bypass_mode(RW)
    DRAM_REG[22] =
        0x00000000; // 000000000000_0000 lowpower_refresh_enable(RW) 000_00000
                    // lowpower_control(RW) 000_00000 lowpower_auto_enable(RW)
    DRAM_REG[23] = 0x00000000; // 0000000000000000 lowpower_internal_cnt(RW)
                               // 0000000000000000 lowpower_external_cnt(RW)
    DRAM_REG[24] = 0x00000000; // 0000000000000000 lowpower_self_refresh_cnt(RW)
                               // 0000000000000000 lowpower_refresh_hold(RW)
    DRAM_REG[25] = 0x00000000; // 00000000000000000000000000000000
                               // lowpower_power_down_cnt(RW)
    DRAM_REG[26] = 0x00010101; // 000000000000000_1 priority_en(RW) 0000000_1
                               // addr_cmp_en(RW) 0000000_1 placement_en(RW)
    DRAM_REG[27] =
        0x01010101; // 0000000_1 swap_port_rw_same_en(RW) 0000000_1 swap_en(RW)
                    // 0000000_1 bank_split_en(RW) 0000000_1 rw_same_en(RW)
    DRAM_REG[28] = 0x000f0f01; // 00000_000 q_fullness(RW) 0000_1111
                               // age_count(RW) 0000_1111 command_age_count(RW)
                               // 0000000_1 active_aging(RW)
    DRAM_REG[29] = 0x0302020A; // 0000_1111 cs_map(RW) 00000_010 column_size(RW)
                               // 00000_010 addr_pins(RW) 0000_1010 aprebit(RW)
    DRAM_REG[30] = 0x00000000; // 0000000000000_000 max_cs_reg(RD) 0000_0000
                               // max_row_reg(RD) 0000_0000 max_col_reg(RD)
    DRAM_REG[31] =
        0x00010101; // 000000000000000_1 eight_bank_mode(RW) 0000000_1
                    // drive_dq_dqs(RW) 0000000_1 dqs_n_en(RW)
    DRAM_REG[32] = 0x00000100; // 00000000000000000000000_1 reduc(RW) 0000000_0
                               // reg_dimm_enable(RW)
    DRAM_REG[33] = 0x00000100; // 00000000000000000000000_1 concurrentap(RW)
                               // 0000000_0 ap(RW)
    DRAM_REG[34] =
        0x00000000; // 0000000_0 writeinterp(RW) 0000000_0 intrptwritea(RW)
                    // 0000000_0 intrptreada(RW) 0000000_0 intrptapburst(RW)
    DRAM_REG[35] =
        0x00000002; // 000000000000000_0 pwrup_srefresh_exit(RW)
                    // 0000000_0 no_cmd_init(RW) 0000_0010 initaref(RW)
    DRAM_REG[36] =
        0x01010000; // 0000000_1 tref_enable(RW) 0000000_1
                    // tras_lockout(RW) 000000000000000_0 fast_write(RW)
    DRAM_REG[37] =
        0x07080403; // 0000_0111 caslat_lin_gate(RW) 0000_1000 caslat_lin(RW)
                    // 00000_100 caslat(RW) 0000_0011 wrlat(RW)
    DRAM_REG[38] = 0x06003c03; // 000_00100 tdal(RW) 0000000000110110 tcpd(RW)
                               // 00000_011 tcke(RW)
    DRAM_REG[39] =
        0x080000c8; // 00_000111 tfaw(RW) 000000000000000011001000 tdll(RW)
    DRAM_REG[40] =
        0x02009C40; // 000_00010 tmrd(RW) 000000000110100000101011 tinit(RW)
    DRAM_REG[41] = 0x00020309; // 0000000000000010 tpdex(RW) 00000010
                               // trcd_int(RW) 00_001000 trc(RW)
    DRAM_REG[42] = 0x0028f507; // 000000000010010001101100 tras_max(RW) 00000110
                               // tras_min(RW)
    DRAM_REG[43] = 0x0314048b; // 0000_0010 trp(RW) 00010001 trfc(RW)
                               // 00_00010000001001 tref(RW)
    DRAM_REG[44] = 0x02040202; // 0000_0001 twtr(RW) 000_00010 twr_int(RW)
                               // 00000_010 trtp(RW) 00000_010 trrd(RW)
    DRAM_REG[45] =
        0x00c80015; // 0000000011001000 txsr(RW) 0000000000010011 txsnr(RW)
    DRAM_REG[46] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[47] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[48] = 0x00011900; // 0_0000000 axi0_current_bdw(RD) 0000000_1
                               // axi0_bdw_ovflow(RW) 0_0100001 axi0_bdw(RW)
                               // 000000_00 axi0_fifo_type_reg(RW)
    DRAM_REG[49] =
        0xffff0303; // 0101010101010101 axi0_en_size_lt_width_instr(RW)
                    // 00000_011 axi0_w_priority(RW) 00000_011
                    // axi0_r_priority(RW)
    DRAM_REG[50] = 0x00012100; // 0_0000000 axi1_current_bdw(RD) 0000000_1
                               // axi1_bdw_ovflow(RW) 0_0100001 axi1_bdw(RW)
                               // 000000_00 axi1_fifo_type_reg(RW)
    DRAM_REG[51] =
        0xffff0303; // 1111111100000000 axi1_en_size_lt_width_instr(RW)
                    // 00000_011 axi1_w_priority(RW) 00000_011
                    // axi1_r_priority(RW)
    DRAM_REG[52] = 0x00011900; // 0_0000000 axi2_current_bdw(RD) 0000000_1
                               // axi2_bdw_ovflow(RW) 0_0100001 axi2_bdw(RW)
                               // 000000_00 axi2_fifo_type_reg(RW)
    DRAM_REG[53] =
        0xffff0303; // 0000000000000001 axi2_en_size_lt_width_instr(RW)
                    // 00000_011 axi2_w_priority(RW) 00000_011
                    // axi2_r_priority(RW)
    DRAM_REG[54] = 0x00011900; // 0_0000000 axi3_current_bdw(RD) 0000000_1
                               // axi3_bdw_ovflow(RW) 0_0100001 axi3_bdw(RW)
                               // 000000_00 axi3_fifo_type_reg(RW)
    DRAM_REG[55] =
        0xffff0303; // 0000000000000001 axi3_en_size_lt_width_instr(RW)
                    // 00000_011 axi3_w_priority(RW) 00000_011
                    // axi3_r_priority(RW)
    DRAM_REG[56] =
        0x00000003; // 00000000000000000000000000000_011 arb_cmd_q_threshold(RW)
    DRAM_REG[57] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[58] = 0x00000000; // 00000_00000000000 int_status(RD)
                               // 00000_00000000000 int_mask(RW)
    DRAM_REG[59] =
        0x00000000; // 00000000000000000000000000000000 out_of_range_addr(RD)
    DRAM_REG[60] = 0x00000000; // 000000000000000000000000000000_00
    DRAM_REG[61] = 0x00000000; // 00_000000 out_of_range_type(RD) 0_0000000
                               // out_of_range_length(RD) 000_0000000000000
                               // out_of_range_source_id(RD)
    DRAM_REG[62] =
        0x00000000; // 00000000000000000000000000000000 port_cmd_error_addr(RD)
    DRAM_REG[63] = 0x00000000; // 000000000000000000000000000000_00
    DRAM_REG[64] =
        0x00000000; // 00000000000_0000000000000 port_cmd_error_id(RD)
                    // 0000_0000 port_cmd_error_type(RD)
    DRAM_REG[65] =
        0x00000000; // 00000000000_0000000000000 port_data_error_id(RD)
                    // 00000_000 port_data_error_type(RD)
    DRAM_REG[66] = 0x0000048b; // 000000000000_0000 tdfi_ctrlupd_min(RD)
                               // 00_00010000001001 tdfi_ctrlupd_max(RW)
    DRAM_REG[67] =
        0x01000f02; // 0000_0001 tdfi_dram_clk_enable(RW) 00000_000
                    // tdfi_dram_clk_disable(RW) 0000_0000 dram_clk_disable(RW)
                    // 0000_0010 tdfi_ctrl_delay(RW)
    DRAM_REG[68] = 0x04090409; // 00_00010000001001 tdfi_phyupd_type0(RW)
                               // 00_00010000001001 tdfi_phyupd_resp(RW)
    DRAM_REG[69] =
        0x00000200; // 00000000000000000000_0010 tdfi_phy_wrlat_base(RW)
                    // 0000_0000 tdfi_phy_wrlat(RD)
    DRAM_REG[70] =
        0x00020007; // 000000000000_0010 tdfi_rddata_en_base(RW) 0000_0000
                    // tdfi_rddata_en(RD) 0000_0110 tdfi_phy_rdlat(RW)
    // DRAM_REG[71] =  0xf3014b27  ;  //11110011000000010100101100100111
    // phy_ctrl_reg_0_0(RW) DRAM_REG[72] =  0xf3014b27  ;
    // //11110011000000010100101100100111 phy_ctrl_reg_0_1(RW) DRAM_REG[73] =
    // 0xf3014b27  ;  //11110011000000010100101100100111 phy_ctrl_reg_0_2(RW)
    // DRAM_REG[74] =  0xf3014b27  ;  //11110011000000010100101100100111
    // phy_ctrl_reg_0_3(RW)

    ////////////////////
    DRAM_REG[71] = 0xf4004a27;
    DRAM_REG[72] = 0xf4004a27;
    DRAM_REG[73] = 0xf4004a27;
    DRAM_REG[74] = 0xf4004a27;

    DRAM_REG[75] =
        0x07400300; // 00000111010000000000001100000000 phy_ctrl_reg_1_0(RW)
    DRAM_REG[76] =
        0x07400300; // 00000111010000000000001100000000 phy_ctrl_reg_1_1(RW)
    DRAM_REG[77] =
        0x07400300; // 00000111010000000000001100000000 phy_ctrl_reg_1_2(RW)
    DRAM_REG[78] =
        0x07400300; // 00000111010000000000001100000000 phy_ctrl_reg_1_3(RW)

    ////////////////////
    // DRAM_REG[79] =  0x00000004  ;  //00000000000000000000000000000100
    // phy_ctrl_reg_2(RW)
    DRAM_REG[79] = 0x00000005;

    DRAM_REG[80] = 0x00000000; // 00000000000000000000000000000000
                               // dft_ctrl_reg(RW)
    DRAM_REG[81] =
        0x00000000; // 0000000000000000000_00000 ocd_adjust_pup_cs_0(RW)
                    // 000_00000 ocd_adjust_pdn_cs_0(RW)
    DRAM_REG[82] = 0x01000000; // 0000000_1 odt_alt_en(RW)
                               // 000000000000000000000000
    DRAM_REG[83] =
        0x01020408; // 0000_0001 odt_rd_map_cs3(RW) 0000_0010 odt_rd_map_cs2(RW)
                    // 0000_0100 odt_rd_map_cs1(RW) 0000_1000 odt_rd_map_cs0(RW)
    DRAM_REG[84] =
        0x08040201; // 0000_1000 odt_wr_map_cs3(RW) 0000_0100 odt_wr_map_cs2(RW)
                    // 0000_0010 odt_wr_map_cs1(RW) 0000_0001 odt_wr_map_cs0(RW)
    DRAM_REG[85] =
        0x000f1133; // 00000000000011110001000100110011 pad_ctrl_reg_0(RW)
    DRAM_REG[86] = 0x00000000; // 00000000000000000000000000000000 version(RD)
    /* DRAM_REG[87] =  0x00091e36  ;  //00000000000010010001111000110110
     dll_ctrl_reg_0_0(RW) DRAM_REG[88] =  0x00091e36  ;
     //00000000000010010001111000110110 dll_ctrl_reg_0_1(RW) DRAM_REG[89] =
     0x00091e36  ;  //00000000000010010001111000110110 dll_ctrl_reg_0_2(RW)
     DRAM_REG[90] =  0x00091e36  ;  //00000000000010010001111000110110
     dll_ctrl_reg_0_3(RW) DRAM_REG[91] =  0x00091f0f  ;
     //00000000000010010001111100001111 dll_ctrl_reg_1_0(RW) DRAM_REG[92] =
     0x00091f0f  ;  //00000000000010010001111100001111 dll_ctrl_reg_1_1(RW)
     DRAM_REG[93] =  0x00091f0f  ;  //00000000000010010001111100001111
     dll_ctrl_reg_1_2(RW) DRAM_REG[94] =  0x00091f0f  ;
     //00000000000010010001111100001111 dll_ctrl_reg_1_3(RW)
    */

    DRAM_REG[87] = 0x00001f04;
    DRAM_REG[88] = 0x00001f04;
    DRAM_REG[89] = 0x00001f04;
    DRAM_REG[90] = 0x00001f04;
    DRAM_REG[91] = 0x00001f04;
    DRAM_REG[92] = 0x00001f04;
    DRAM_REG[93] = 0x00001f04;
    DRAM_REG[94] = 0x00001f04;

    DRAM_REG[95] =
        0x00000000; // 00000000000000000000000000000000 dll_obs_reg_0_0(RD)
    DRAM_REG[96] =
        0x00000000; // 00000000000000000000000000000000 dll_obs_reg_0_1(RD)
    DRAM_REG[97] =
        0x00000000; // 00000000000000000000000000000000 dll_obs_reg_0_2(RD)
    DRAM_REG[98] =
        0x00000000; // 00000000000000000000000000000000 dll_obs_reg_0_3(RD)
    DRAM_REG[99] =
        0x00000000; // 00000000000000000000000000000000 phy_obs_reg_0_0(RD)
    DRAM_REG[100] =
        0x00000000; // 00000000000000000000000000000000 phy_obs_reg_0_1(RD)
    DRAM_REG[101] =
        0x00000000; // 00000000000000000000000000000000 phy_obs_reg_0_2(RD)
    DRAM_REG[102] =
        0x00000000; // 00000000000000000000000000000000 phy_obs_reg_0_3(RD)
    DRAM_REG[103] =
        0x00000000; // 00000000000000000000000000000000 dll_obs_reg_1_0(RD)
    DRAM_REG[104] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[105] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[106] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[107] = 0x00000000; // 00000000000000000000000_000000000
    DRAM_REG[108] =
        0x00000000; // 00000000000000000000000000000000 dll_obs_reg_1_1(RD)
    DRAM_REG[109] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[110] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[111] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[112] = 0x00000000; // 00000000000000000000000_000000000
    DRAM_REG[113] =
        0x00000000; // 00000000000000000000000000000000 dll_obs_reg_1_2(RD)
    DRAM_REG[114] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[115] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[116] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[117] = 0x00000000; // 00000000000000000000000_000000000
    DRAM_REG[118] =
        0x00000000; // 00000000000000000000000000000000 dll_obs_reg_1_3(RD)
    DRAM_REG[119] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[120] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[121] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[122] = 0x00000000; // 00000000000000000000000_000000000
    DRAM_REG[123] =
        0x00000000; // 00000000000000000000000000000000 dll_obs_reg_2_0(RD)
    DRAM_REG[124] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[125] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[126] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[127] = 0x00000000; // 00000000000000000000000_000000000
    DRAM_REG[128] =
        0x00000000; // 00000000000000000000000000000000 dll_obs_reg_2_1(RD)
    DRAM_REG[129] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[130] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[131] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[132] = 0x00000000; // 00000000000000000000000_000000000
    DRAM_REG[133] =
        0x00000000; // 00000000000000000000000000000000 dll_obs_reg_2_2(RD)
    DRAM_REG[134] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[135] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[136] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[137] = 0x00000000; // 00000000000000000000000_000000000
    DRAM_REG[138] =
        0x00000000; // 00000000000000000000000000000000 dll_obs_reg_2_3(RD)
    DRAM_REG[139] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[140] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[141] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[142] = 0x00000000; // 00000000000000000000000_000000000
    DRAM_REG[143] =
        0x00000000; // 00000000000000000000000000000000 dll_obs_reg_3_0(RD)
    DRAM_REG[144] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[145] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[146] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[147] = 0x00000000; // 00000000000000000000000_000000000
    DRAM_REG[148] =
        0x00000000; // 00000000000000000000000000000000 dll_obs_reg_3_1(RD)
    DRAM_REG[149] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[150] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[151] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[152] = 0x00000000; // 00000000000000000000000_000000000
    DRAM_REG[153] =
        0x00000000; // 00000000000000000000000000000000 dll_obs_reg_3_2(RD)
    DRAM_REG[154] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[155] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[156] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[157] = 0x00000000; // 00000000000000000000000_000000000
    DRAM_REG[158] =
        0x00000000; // 00000000000000000000000000000000 dll_obs_reg_3_3(RD)
    DRAM_REG[159] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[160] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[161] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[162] = 0x00010000; // 00000_000 w2r_samecs_dly(RW) 00000_001
                                // w2r_diffcs_dly(RW) 0000000_000000000
    DRAM_REG[163] =
        0x00030404; // 00000000 dll_rst_adj_dly(RW) 0000_0011 wrlat_adj(RW)
                    // 0000_0100 rdlat_adj(RW) 0000_0100 dram_class(RW)
    DRAM_REG[164] =
        0x00000002; // 00000000000000_0000000000 int_ack(WR) 00000010 tmod(RW)
    DRAM_REG[165] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[166] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[167] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[168] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[169] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[170] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[171] =
        0x01010000; // 0000000_1 axi5_bdw_ovflow(RW) 0000000_1
                    // axi4_bdw_ovflow(RW) 0000000000000000 dll_rst_delay(RW)
    DRAM_REG[172] =
        0x01000000; // 0000000_1 resync_dll_per_aref_en(RW) 0000000_0
                    // resync_dll(WR) 0000000_0 concurrentap_wr_only(RW)
                    // 0000000_0 cke_status(RD)
    DRAM_REG[173] =
        0x03030000; // 00000_011 axi4_w_priority(RW) 00000_011
                    // axi4_r_priority(RW) 000000_00 axi5_fifo_type_reg(RW)
                    // 000000_00 axi4_fifo_type_reg(RW)
    DRAM_REG[174] =
        0x00010303; // 00000_000 r2r_samecs_dly(RW) 00000_001 r2r_diffcs_dly(RW)
                    // 00000_011 axi5_w_priority(RW) 00000_011
                    // axi5_r_priority(RW)
    DRAM_REG[175] =
        0x01020202; // 00000_001 w2w_diffcs_dly(RW) 00000_010
                    // tbst_int_interval(RW) 00000_010
                    // r2w_samecs_dly(RW) 00000_010 r2w_diffcs_dly(RW)
    DRAM_REG[176] = 0x00000000; // 0000_0000 add_odt_clk_sametype_diffcs(RW)
                                // 0000_0000 add_odt_clk_difftype_samecs(RW)
                                // 0000_0000 add_odt_clk_difftype_diffcs(RW)
                                // 00000_000 w2w_samecs_dly(RW)
    DRAM_REG[177] = 0x02040303; // 000_00010 tccd(RW) 0000_0011 trp_ab(RW)
                                // 0000_0011 cksrx(RW) 0000_0011 cksre(RW)
    DRAM_REG[178] =
        0x21002103; // 0_0100001 axi5_bdw(RW) 0_0000000 axi4_current_bdw(RD)
                    // 0_0100001 axi4_bdw(RW) 000_00011 tckesr(RW)
    DRAM_REG[179] =
        0x00048b00; // 0000000000_00010000001001 tdfi_phyupd_type1(RW)
                    // 0_0000000 axi5_current_bdw(RD)
    DRAM_REG[180] = 0x048b048b; // 00_00010000001001 tdfi_phyupd_type3(RW)
                                // 00_00010000001001 tdfi_phyupd_type2(RW)
    DRAM_REG[181] = 0x04420442; // 0_000001001000010 mr0_data_1(RW)
                                // 0_000001001000010 mr0_data_0(RW)
    DRAM_REG[182] = 0x04420442; // 0_000001001000010 mr0_data_3(RW)
                                // 0_000001001000010 mr0_data_2(RW)
    DRAM_REG[183] = 0x00040004; // 0_000000000000100 mr1_data_1(RW)
                                // 0_000000000000100 mr1_data_0(RW)
    DRAM_REG[184] = 0x00040004; // 0_000000000000100 mr1_data_3(RW)
                                // 0_000000000000100 mr1_data_2(RW)
    DRAM_REG[185] = 0x00000000; // 0_000000000000000 mr2_data_1(RW)
                                // 0_000000000000000 mr2_data_0(RW)
    DRAM_REG[186] = 0x00000000; // 0_000000000000000 mr2_data_3(RW)
                                // 0_000000000000000 mr2_data_2(RW)
    DRAM_REG[187] = 0x00000000; // 0_000000000000000 mr3_data_1(RW)
                                // 0_000000000000000 mr3_data_0(RW)
    DRAM_REG[188] = 0x00000000; // 0_000000000000000 mr3_data_3(RW)
                                // 0_000000000000000 mr3_data_2(RW)
    DRAM_REG[189] =
        0xffffffff; // 0000000000000001 axi5_en_size_lt_width_instr(RW)
                    // 0000000000000001 axi4_en_size_lt_width_instr(RW)
}
void Init_ddr2_ede1116_4_166MHz() {

    volatile unsigned int *DRAM_REG =
        (volatile unsigned int *)HW_DRAM_CTL00_ADDR;
    DRAM_REG[0] =
        0x00000000; // 00000000000000000000000000000000 user_def_reg_0(RW)
    DRAM_REG[1] =
        0x00000000; // 00000000000000000000000000000000 user_def_reg_1(RW)
    DRAM_REG[2] =
        0x00000000; // 00000000000000000000000000000000 user_def_reg_2(RW)
    DRAM_REG[3] =
        0x00000000; // 00000000000000000000000000000000 user_def_reg_3(RW)
    DRAM_REG[4] =
        0x00000000; // 00000000000000000000000000000000 user_def_reg_4(RW)
    DRAM_REG[5] =
        0x00000000; // 00000000000000000000000000000000 user_def_reg_5(RW)
    DRAM_REG[6] =
        0x00000000; // 00000000000000000000000000000000 user_def_reg_6(RW)
    DRAM_REG[7] =
        0x00000000; // 00000000000000000000000000000000 user_def_reg_7(RW)
    DRAM_REG[8] =
        0x00000000; // 00000000000000000000000000000000 user_def_reg_ro_0(D)
    DRAM_REG[9] =
        0x00000000; // 00000000000000000000000000000000 user_def_reg_ro_1(RD)
    DRAM_REG[10] =
        0x00000000; // 00000000000000000000000000000000 user_def_reg_ro_2(RD)
    DRAM_REG[11] =
        0x00000000; // 00000000000000000000000000000000 user_def_reg_ro_3(RD)
    DRAM_REG[12] =
        0x00000000; // 00000000000000000000000000000000 user_def_reg_ro_4(RD)
    DRAM_REG[13] =
        0x00000000; // 00000000000000000000000000000000 user_def_reg_ro_5(RD)
    DRAM_REG[14] =
        0x00000000; // 00000000000000000000000000000000 user_def_reg_ro_6(RD)
    DRAM_REG[15] =
        0x00000000; // 00000000000000000000000000000000 user_def_reg_ro_7(RD)
    DRAM_REG[16] = 0x00000000; // 0000000_0 write_modereg(WR) 0000000_0
                               // power_down(RW) 000000000000000_0 start(RW)
    DRAM_REG[17] =
        0x00000100; // 0000000_0 auto_refresh_mode(RW) 0000000_0 arefresh(WR)
                    // 0000000_1 enable_quick_srefresh(RW) 0000000_0
                    // srefresh(RW+)
    DRAM_REG[18] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[19] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[20] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[21] =
        0x00000000; // 00000_000 cke_delay(RW) 00000000 dll_lock(RD) 0000000_0
                    // dlllockreg(RD) 0000000_0 dll_bypass_mode(RW)
    DRAM_REG[22] =
        0x00000000; // 000000000000_0000 lowpower_refresh_enable(RW) 000_00000
                    // lowpower_control(RW) 000_00000 lowpower_auto_enable(RW)
    DRAM_REG[23] = 0x00000000; // 0000000000000000 lowpower_internal_cnt(RW)
                               // 0000000000000000 lowpower_external_cnt(RW)
    DRAM_REG[24] = 0x00000000; // 0000000000000000 lowpower_self_refresh_cnt(RW)
                               // 0000000000000000 lowpower_refresh_hold(RW)
    DRAM_REG[25] = 0x00000000; // 00000000000000000000000000000000
                               // lowpower_power_down_cnt(RW)
    DRAM_REG[26] = 0x00010101; // 000000000000000_1 priority_en(RW) 0000000_1
                               // addr_cmp_en(RW) 0000000_1 placement_en(RW)
    DRAM_REG[27] =
        0x01010101; // 0000000_1 swap_port_rw_same_en(RW) 0000000_1 swap_en(RW)
                    // 0000000_1 bank_split_en(RW) 0000000_1 rw_same_en(RW)
    DRAM_REG[28] = 0x000f0f01; // 00000_000 q_fullness(RW) 0000_1111
                               // age_count(RW) 0000_1111 command_age_count(RW)
                               // 0000000_1 active_aging(RW)
    DRAM_REG[29] = 0x0f02020a; // 0000_1111 cs_map(RW) 00000_010 column_size(RW)
                               // 00000_010 addr_pins(RW) 0000_1010 aprebit(RW)
    DRAM_REG[30] = 0x00000000; // 0000000000000_000 max_cs_reg(RD) 0000_0000
                               // max_row_reg(RD) 0000_0000 max_col_reg(RD)
    DRAM_REG[31] =
        0x00010101; // 000000000000000_1 eight_bank_mode(RW) 0000000_1
                    // drive_dq_dqs(RW) 0000000_1 dqs_n_en(RW)
    DRAM_REG[32] = 0x00000100; // 00000000000000000000000_1 reduc(RW) 0000000_0
                               // reg_dimm_enable(RW)
    DRAM_REG[33] = 0x00000100; // 00000000000000000000000_1 concurrentap(RW)
                               // 0000000_0 ap(RW)
    DRAM_REG[34] =
        0x00000000; // 0000000_0 writeinterp(RW) 0000000_0 intrptwritea(RW)
                    // 0000000_0 intrptreada(RW) 0000000_0 intrptapburst(RW)
    DRAM_REG[35] =
        0x00000002; // 000000000000000_0 pwrup_srefresh_exit(RW)
                    // 0000000_0 no_cmd_init(RW) 0000_0010 initaref(RW)
    DRAM_REG[36] =
        0x01010000; // 0000000_1 tref_enable(RW) 0000000_1
                    // tras_lockout(RW) 000000000000000_0 fast_write(RW)
    DRAM_REG[37] =
        0x07080403; // 0000_0111 caslat_lin_gate(RW) 0000_1000 caslat_lin(RW)
                    // 00000_100 caslat(RW) 0000_0011 wrlat(RW)
    DRAM_REG[38] = 0x06004303; // 000_00110 tdal(RW) 0000000001000011 tcpd(RW)
                               // 00000_011 tcke(RW)
    DRAM_REG[39] =
        0x090000c8; // 00_001001 tfaw(RW) 000000000000000011001000 tdll(RW)
    DRAM_REG[40] =
        0x02008236; // 000_00010 tmrd(RW) 000000001000001000110110 tinit(RW)
    DRAM_REG[41] = 0x0002030a; // 0000000000000010 tpdex(RW) 00000011
                               // trcd_int(RW) 00_001010 trc(RW)
    DRAM_REG[42] = 0x002d8908; // 000000000010110110001001 tras_max(RW) 00001000
                               // tras_min(RW)
    DRAM_REG[43] = 0x0316050e; // 0000_0011 trp(RW) 00010110 trfc(RW)
                               // 00_00010100001110 tref(RW)
    DRAM_REG[44] = 0x02030202; // 0000_0010 twtr(RW) 000_00011 twr_int(RW)
                               // 00000_010 trtp(RW) 00000_010 trrd(RW)
    DRAM_REG[45] =
        0x00c80017; // 0000000011001000 txsr(RW) 0000000000010111 txsnr(RW)
    DRAM_REG[46] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[47] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[48] = 0x00012100; // 0_0000000 axi0_current_bdw(RD) 0000000_1
                               // axi0_bdw_ovflow(RW) 0_0100001 axi0_bdw(RW)
                               // 000000_00 axi0_fifo_type_reg(RW)
    DRAM_REG[49] =
        0xffff0303; // 0101010101010101 axi0_en_size_lt_width_instr(RW)
                    // 00000_011 axi0_w_priority(RW) 00000_011
                    // axi0_r_priority(RW)
    DRAM_REG[50] = 0x00012100; // 0_0000000 axi1_current_bdw(RD) 0000000_1
                               // axi1_bdw_ovflow(RW) 0_0100001 axi1_bdw(RW)
                               // 000000_00 axi1_fifo_type_reg(RW)
    DRAM_REG[51] =
        0xff000303; // 1111111100000000 axi1_en_size_lt_width_instr(RW)
                    // 00000_011 axi1_w_priority(RW) 00000_011
                    // axi1_r_priority(RW)
    DRAM_REG[52] = 0x00012100; // 0_0000000 axi2_current_bdw(RD) 0000000_1
                               // axi2_bdw_ovflow(RW) 0_0100001 axi2_bdw(RW)
                               // 000000_00 axi2_fifo_type_reg(RW)
    DRAM_REG[53] =
        0xffff0303; // 0000000000000001 axi2_en_size_lt_width_instr(RW)
                    // 00000_011 axi2_w_priority(RW) 00000_011
                    // axi2_r_priority(RW)
    DRAM_REG[54] = 0x00012100; // 0_0000000 axi3_current_bdw(RD) 0000000_1
                               // axi3_bdw_ovflow(RW) 0_0100001 axi3_bdw(RW)
                               // 000000_00 axi3_fifo_type_reg(RW)
    DRAM_REG[55] =
        0xffff0303; // 0000000000000001 axi3_en_size_lt_width_instr(RW)
                    // 00000_011 axi3_w_priority(RW) 00000_011
                    // axi3_r_priority(RW)
    DRAM_REG[56] =
        0x00000003; // 00000000000000000000000000000_011 arb_cmd_q_threshold(RW)
    DRAM_REG[57] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[58] = 0x00000000; // 00000_00000000000 int_status(RD)
                               // 00000_00000000000 int_mask(RW)
    DRAM_REG[59] =
        0x00000000; // 00000000000000000000000000000000 out_of_range_addr(RD)
    DRAM_REG[60] = 0x00000000; // 000000000000000000000000000000_00
    DRAM_REG[61] = 0x00000000; // 00_000000 out_of_range_type(RD) 0_0000000
                               // out_of_range_length(RD) 000_0000000000000
                               // out_of_range_source_id(RD)
    DRAM_REG[62] =
        0x00000000; // 00000000000000000000000000000000 port_cmd_error_addr(RD)
    DRAM_REG[63] = 0x00000000; // 000000000000000000000000000000_00
    DRAM_REG[64] =
        0x00000000; // 00000000000_0000000000000 port_cmd_error_id(RD)
                    // 0000_0000 port_cmd_error_type(RD)
    DRAM_REG[65] =
        0x00000000; // 00000000000_0000000000000 port_data_error_id(RD)
                    // 00000_000 port_data_error_type(RD)
    DRAM_REG[66] = 0x0000050e; // 000000000000_0000 tdfi_ctrlupd_min(RD)
                               // 00_00010100001110 tdfi_ctrlupd_max(RW)
    DRAM_REG[67] =
        0x01000f02; // 0000_0001 tdfi_dram_clk_enable(RW) 00000_000
                    // tdfi_dram_clk_disable(RW) 0000_0000 dram_clk_disable(RW)
                    // 0000_0010 tdfi_ctrl_delay(RW)
    DRAM_REG[68] = 0x050e050e; // 00_00010100001110 tdfi_phyupd_type0(RW)
                               // 00_00010100001110 tdfi_phyupd_resp(RW)
    DRAM_REG[69] =
        0x00000200; // 00000000000000000000_0010 tdfi_phy_wrlat_base(RW)
                    // 0000_0000 tdfi_phy_wrlat(RD)
    DRAM_REG[70] =
        0x00020007; // 000000000000_0010 tdfi_rddata_en_base(RW) 0000_0000
                    // tdfi_rddata_en(RD) 0000_0111 tdfi_phy_rdlat(RW)
    /*
        DRAM_REG[71] =  0xf4014a27 ; //11110100000000010100101000100111
       phy_ctrl_reg_0_0(RW) DRAM_REG[72] =  0xf4014a27 ;
       //11110100000000010100101000100111 phy_ctrl_reg_0_1(RW) DRAM_REG[73] =
       0xf4014a27 ; //11110100000000010100101000100111 phy_ctrl_reg_0_2(RW)
        DRAM_REG[74] =  0xf4014a27 ; //11110100000000010100101000100111
       phy_ctrl_reg_0_3(RW)
    */
    DRAM_REG[71] = 0xf5004a27;
    DRAM_REG[72] = 0xf5004a27;
    DRAM_REG[73] = 0xf5004a27;
    DRAM_REG[74] = 0xf5004a27;
    DRAM_REG[75] =
        0x07400300; // 00000111010000000000001100000000 phy_ctrl_reg_1_0(RW)
    DRAM_REG[76] =
        0x07400300; // 00000111010000000000001100000000 phy_ctrl_reg_1_1(RW)
    DRAM_REG[77] =
        0x07400300; // 00000111010000000000001100000000 phy_ctrl_reg_1_2(RW)
    DRAM_REG[78] =
        0x07400300; // 00000111010000000000001100000000 phy_ctrl_reg_1_3(RW)
    // DRAM_REG[79] =  0x00000005 ; //00000000000000000000000000000101
    // phy_ctrl_reg_2(RW)
    DRAM_REG[79] = 0x00000006;
    DRAM_REG[80] = 0x00000000; // 00000000000000000000000000000000
                               // dft_ctrl_reg(RW)
    DRAM_REG[81] =
        0x00000000; // 0000000000000000000_00000 ocd_adjust_pup_cs_0(RW)
                    // 000_00000 ocd_adjust_pdn_cs_0(RW)
    DRAM_REG[82] = 0x01000000; // 0000000_1 odt_alt_en(RW)
                               // 000000000000000000000000
    DRAM_REG[83] =
        0x01020408; // 0000_0001 odt_rd_map_cs3(RW) 0000_0010 odt_rd_map_cs2(RW)
                    // 0000_0100 odt_rd_map_cs1(RW) 0000_1000 odt_rd_map_cs0(RW)
    DRAM_REG[84] =
        0x08040201; // 0000_1000 odt_wr_map_cs3(RW) 0000_0100 odt_wr_map_cs2(RW)
                    // 0000_0010 odt_wr_map_cs1(RW) 0000_0001 odt_wr_map_cs0(RW)
    DRAM_REG[85] =
        0x000f1133; // 00000000000011110001000100110011 pad_ctrl_reg_0(RW)
    DRAM_REG[86] = 0x00000000; // 00000000000000000000000000000000 version(RD)
    /*
        DRAM_REG[87] =  0x00079e2d ; //00000000000001111001111000101101
       dll_ctrl_reg_0_0(RW) DRAM_REG[88] =  0x00079e2d ;
       //00000000000001111001111000101101 dll_ctrl_reg_0_1(RW) DRAM_REG[89] =
       0x00079e2d ; //00000000000001111001111000101101 dll_ctrl_reg_0_2(RW)
        DRAM_REG[90] =  0x00079e2d ; //00000000000001111001111000101101
       dll_ctrl_reg_0_3(RW) DRAM_REG[91] =  0x00079f0c ;
       //00000000000001111001111100001100 dll_ctrl_reg_1_0(RW) DRAM_REG[92] =
       0x00079f0c ; //00000000000001111001111100001100 dll_ctrl_reg_1_1(RW)
        DRAM_REG[93] =  0x00079f0c ; //00000000000001111001111100001100
       dll_ctrl_reg_1_2(RW) DRAM_REG[94] =  0x00079f0c ;
       //00000000000001111001111100001100 dll_ctrl_reg_1_3(RW)
    */
    DRAM_REG[87] = 0x00001f04;
    DRAM_REG[88] = 0x00001f04;
    DRAM_REG[89] = 0x00001f04;
    DRAM_REG[90] = 0x00001f04;
    DRAM_REG[91] = 0x00001f04;
    DRAM_REG[92] = 0x00001f04;
    DRAM_REG[93] = 0x00001f04;
    DRAM_REG[94] = 0x00001f04;
    DRAM_REG[95] =
        0x00000000; // 00000000000000000000000000000000 dll_obs_reg_0_0(RD)
    DRAM_REG[96] =
        0x00000000; // 00000000000000000000000000000000 dll_obs_reg_0_1(RD)
    DRAM_REG[97] =
        0x00000000; // 00000000000000000000000000000000 dll_obs_reg_0_2(RD)
    DRAM_REG[98] =
        0x00000000; // 00000000000000000000000000000000 dll_obs_reg_0_3(RD)
    DRAM_REG[99] =
        0x00000000; // 00000000000000000000000000000000 phy_obs_reg_0_0(RD)
    DRAM_REG[100] =
        0x00000000; // 00000000000000000000000000000000 phy_obs_reg_0_1(RD)
    DRAM_REG[101] =
        0x00000000; // 00000000000000000000000000000000 phy_obs_reg_0_2(RD)
    DRAM_REG[102] =
        0x00000000; // 00000000000000000000000000000000 phy_obs_reg_0_3(RD)
    DRAM_REG[103] =
        0x00000000; // 00000000000000000000000000000000 dll_obs_reg_1_0(RD)
    DRAM_REG[104] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[105] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[106] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[107] = 0x00000000; // 00000000000000000000000_000000000
    DRAM_REG[108] =
        0x00000000; // 00000000000000000000000000000000 dll_obs_reg_1_1(RD)
    DRAM_REG[109] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[110] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[111] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[112] = 0x00000000; // 00000000000000000000000_000000000
    DRAM_REG[113] =
        0x00000000; // 00000000000000000000000000000000 dll_obs_reg_1_2(RD)
    DRAM_REG[114] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[115] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[116] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[117] = 0x00000000; // 00000000000000000000000_000000000
    DRAM_REG[118] =
        0x00000000; // 00000000000000000000000000000000 dll_obs_reg_1_3(RD)
    DRAM_REG[119] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[120] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[121] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[122] = 0x00000000; // 00000000000000000000000_000000000
    DRAM_REG[123] =
        0x00000000; // 00000000000000000000000000000000 dll_obs_reg_2_0(RD)
    DRAM_REG[124] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[125] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[126] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[127] = 0x00000000; // 00000000000000000000000_000000000
    DRAM_REG[128] =
        0x00000000; // 00000000000000000000000000000000 dll_obs_reg_2_1(RD)
    DRAM_REG[129] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[130] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[131] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[132] = 0x00000000; // 00000000000000000000000_000000000
    DRAM_REG[133] =
        0x00000000; // 00000000000000000000000000000000 dll_obs_reg_2_2(RD)
    DRAM_REG[134] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[135] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[136] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[137] = 0x00000000; // 00000000000000000000000_000000000
    DRAM_REG[138] =
        0x00000000; // 00000000000000000000000000000000 dll_obs_reg_2_3(RD)
    DRAM_REG[139] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[140] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[141] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[142] = 0x00000000; // 00000000000000000000000_000000000
    DRAM_REG[143] =
        0x00000000; // 00000000000000000000000000000000 dll_obs_reg_3_0(RD)
    DRAM_REG[144] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[145] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[146] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[147] = 0x00000000; // 00000000000000000000000_000000000
    DRAM_REG[148] =
        0x00000000; // 00000000000000000000000000000000 dll_obs_reg_3_1(RD)
    DRAM_REG[149] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[150] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[151] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[152] = 0x00000000; // 00000000000000000000000_000000000
    DRAM_REG[153] =
        0x00000000; // 00000000000000000000000000000000 dll_obs_reg_3_2(RD)
    DRAM_REG[154] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[155] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[156] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[157] = 0x00000000; // 00000000000000000000000_000000000
    DRAM_REG[158] =
        0x00000000; // 00000000000000000000000000000000 dll_obs_reg_3_3(RD)
    DRAM_REG[159] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[160] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[161] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[162] = 0x00010000; // 00000_000 w2r_samecs_dly(RW) 00000_001
                                // w2r_diffcs_dly(RW) 0000000_000000000
    DRAM_REG[163] =
        0x00030404; // 00000000 dll_rst_adj_dly(RW) 0000_0011 wrlat_adj(RW)
                    // 0000_0100 rdlat_adj(RW) 0000_0100 dram_class(RW)
    DRAM_REG[164] =
        0x00000002; // 00000000000000_0000000000 int_ack(WR) 00000010 tmod(RW)
    DRAM_REG[165] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[166] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[167] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[168] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[169] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[170] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[171] =
        0x01010000; // 0000000_1 axi5_bdw_ovflow(RW) 0000000_1
                    // axi4_bdw_ovflow(RW) 0000000000000000 dll_rst_delay(RW)
    DRAM_REG[172] =
        0x01000000; // 0000000_1 resync_dll_per_aref_en(RW) 0000000_0
                    // resync_dll(WR) 0000000_0 concurrentap_wr_only(RW)
                    // 0000000_0 cke_status(RD)
    DRAM_REG[173] =
        0x03030000; // 00000_011 axi4_w_priority(RW) 00000_011
                    // axi4_r_priority(RW) 000000_00 axi5_fifo_type_reg(RW)
                    // 000000_00 axi4_fifo_type_reg(RW)
    DRAM_REG[174] =
        0x00010303; // 00000_000 r2r_samecs_dly(RW) 00000_001 r2r_diffcs_dly(RW)
                    // 00000_011 axi5_w_priority(RW) 00000_011
                    // axi5_r_priority(RW)
    DRAM_REG[175] =
        0x01020202; // 00000_001 w2w_diffcs_dly(RW) 00000_010
                    // tbst_int_interval(RW) 00000_010
                    // r2w_samecs_dly(RW) 00000_010 r2w_diffcs_dly(RW)
    DRAM_REG[176] = 0x00000000; // 0000_0000 add_odt_clk_sametype_diffcs(RW)
                                // 0000_0000 add_odt_clk_difftype_samecs(RW)
                                // 0000_0000 add_odt_clk_difftype_diffcs(RW)
                                // 00000_000 w2w_samecs_dly(RW)
    DRAM_REG[177] = 0x02040303; // 000_00010 tccd(RW) 0000_0100 trp_ab(RW)
                                // 0000_0011 cksrx(RW) 0000_0011 cksre(RW)
    DRAM_REG[178] =
        0x21002103; // 0_0100001 axi5_bdw(RW) 0_0000000 axi4_current_bdw(RD)
                    // 0_0100001 axi4_bdw(RW) 000_00011 tckesr(RW)
    DRAM_REG[179] =
        0x00050e00; // 0000000000_00010100001110 tdfi_phyupd_type1(RW)
                    // 0_0000000 axi5_current_bdw(RD)
    DRAM_REG[180] = 0x050e050e; // 00_00010100001110 tdfi_phyupd_type3(RW)
                                // 00_00010100001110 tdfi_phyupd_type2(RW)
    DRAM_REG[181] = 0x04420442; // 0_000010001000010 mr0_data_1(RW)
                                // 0_000010001000010 mr0_data_0(RW)
    DRAM_REG[182] = 0x04420442; // 0_000010001000010 mr0_data_3(RW)
                                // 0_000010001000010 mr0_data_2(RW)
    DRAM_REG[183] = 0x00040004; // 0_000000000000100 mr1_data_1(RW)
                                // 0_000000000000100 mr1_data_0(RW)
    DRAM_REG[184] = 0x00040004; // 0_000000000000100 mr1_data_3(RW)
                                // 0_000000000000100 mr1_data_2(RW)
    DRAM_REG[185] = 0x00000000; // 0_000000000000000 mr2_data_1(RW)
                                // 0_000000000000000 mr2_data_0(RW)
    DRAM_REG[186] = 0x00000000; // 0_000000000000000 mr2_data_3(RW)
                                // 0_000000000000000 mr2_data_2(RW)
    DRAM_REG[187] = 0x00000000; // 0_000000000000000 mr3_data_1(RW)
                                // 0_000000000000000 mr3_data_0(RW)
    DRAM_REG[188] = 0x00000000; // 0_000000000000000 mr3_data_3(RW)
                                // 0_000000000000000 mr3_data_2(RW)
    DRAM_REG[189] =
        0xffffffff; // 0000000000000001 axi5_en_size_lt_width_instr(RW)
                    // 0000000000000001 axi4_en_size_lt_width_instr(RW)
}

//#define H5PS2562GFR  0
//#define BSP_64DDR 0
void DDR2EmiController_EDE1116_200MHz(int i) {
    volatile unsigned int *DRAM_REG =
        (volatile unsigned int *)HW_DRAM_CTL00_ADDR;
    DRAM_REG[0] =
        0x00000000; // 00000000000000000000000000000000 user_def_reg_0(RW)
    DRAM_REG[1] =
        0x00000000; // 00000000000000000000000000000000 user_def_reg_1(RW)
    DRAM_REG[2] =
        0x00000000; // 00000000000000000000000000000000 user_def_reg_2(RW)
    DRAM_REG[3] =
        0x00000000; // 00000000000000000000000000000000 user_def_reg_3(RW)
    DRAM_REG[4] =
        0x00000000; // 00000000000000000000000000000000 user_def_reg_4(RW)
    DRAM_REG[5] =
        0x00000000; // 00000000000000000000000000000000 user_def_reg_5(RW)
    DRAM_REG[6] =
        0x00000000; // 00000000000000000000000000000000 user_def_reg_6(RW)
    DRAM_REG[7] =
        0x00000000; // 00000000000000000000000000000000 user_def_reg_7(RW)
    DRAM_REG[8] =
        0x00000000; // 00000000000000000000000000000000 user_def_reg_ro_0(RD)
    DRAM_REG[9] =
        0x00000000; // 00000000000000000000000000000000 user_def_reg_ro_1(RD)
    DRAM_REG[10] =
        0x00000000; // 00000000000000000000000000000000 user_def_reg_ro_2(RD)
    DRAM_REG[11] =
        0x00000000; // 00000000000000000000000000000000 user_def_reg_ro_3(RD)
    DRAM_REG[12] =
        0x00000000; // 00000000000000000000000000000000 user_def_reg_ro_4(RD)
    DRAM_REG[13] =
        0x00000000; // 00000000000000000000000000000000 user_def_reg_ro_5(RD)
    DRAM_REG[14] =
        0x00000000; // 00000000000000000000000000000000 user_def_reg_ro_6(RD)
    DRAM_REG[15] =
        0x00000000; // 00000000000000000000000000000000 user_def_reg_ro_7(RD)
    DRAM_REG[16] = 0x00000000; // 0000000_0 write_modereg(WR) 0000000_0
                               // power_down(RW) 000000000000000_0 start(RW)
    DRAM_REG[17] =
        0x00000100; // 0000000_0 auto_refresh_mode(RW) 0000000_0 arefresh(WR)
                    // 0000000_1 enable_quick_srefresh(RW) 0000000_0
                    // srefresh(RW+)
    DRAM_REG[18] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[19] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[20] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[21] =
        0x00000000; // 00000_000 cke_delay(RW) 00000000 dll_lock(RD) 0000000_0
                    // dlllockreg(RD) 0000000_0 dll_bypass_mode(RW)
    DRAM_REG[22] =
        0x00000000; // 000000000000_0000 lowpower_refresh_enable(RW) 000_00000
                    // lowpower_control(RW) 000_00000 lowpower_auto_enable(RW)
    DRAM_REG[23] = 0x00000000; // 0000000000000000 lowpower_internal_cnt(RW)
                               // 0000000000000000 lowpower_external_cnt(RW)
    DRAM_REG[24] = 0x00000000; // 0000000000000000 lowpower_self_refresh_cnt(RW)
                               // 0000000000000000 lowpower_refresh_hold(RW)
    DRAM_REG[25] = 0x00000000; // 00000000000000000000000000000000
                               // lowpower_power_down_cnt(RW)
    DRAM_REG[26] = 0x00010101; // 000000000000000_1 priority_en(RW) 0000000_1
                               // addr_cmp_en(RW) 0000000_1 placement_en(RW)
    DRAM_REG[27] =
        0x01010101; // 0000000_1 swap_port_rw_same_en(RW) 0000000_1 swap_en(RW)
                    // 0000000_1 bank_split_en(RW) 0000000_1 rw_same_en(RW)
    DRAM_REG[28] = 0x000f0f01; // 00000_000 q_fullness(RW) 0000_1111
                               // age_count(RW) 0000_1111 command_age_count(RW)
                               // 0000000_1 active_aging(RW)
    DRAM_REG[29] = 0x0f02020a; // 0000_1111 cs_map(RW) 00000_010 column_size(RW)
                               // 00000_010 addr_pins(RW) 0000_1010 aprebit(RW)
    DRAM_REG[30] = 0x00000000; // 0000000000000_000 max_cs_reg(RD) 0000_0000
                               // max_row_reg(RD) 0000_0000 max_col_reg(RD)
    /* modiby by wangzeqiong@zlg.cn */
    //#ifndef BSP_64DDR
    if (1 == i)
        DRAM_REG[31] =
            0x00010101; // 000000000000000_1 eight_bank_mode(RW) 0000000_1
                        // drive_dq_dqs(RW) 0000000_1 dqs_n_en(RW)
    //#else
    else
        DRAM_REG[31] =
            0x00000101; // 000000000000000_1 eight_bank_mode(RW) 0000000_1
                        // drive_dq_dqs(RW) 0000000_1 dqs_n_en(RW)
    //#endif
    DRAM_REG[32] = 0x00000100; // 00000000000000000000000_1 reduc(RW) 0000000_0
                               // reg_dimm_enable(RW)
    DRAM_REG[33] = 0x00000100; // 00000000000000000000000_1 concurrentap(RW)
                               // 0000000_0 ap(RW)
    DRAM_REG[34] =
        0x00000000; // 0000000_0 writeinterp(RW) 0000000_0 intrptwritea(RW)
                    // 0000000_0 intrptreada(RW) 0000000_0 intrptapburst(RW)
    DRAM_REG[35] =
        0x00000002; // 000000000000000_0 pwrup_srefresh_exit(RW)
                    // 0000000_0 no_cmd_init(RW) 0000_0010 initaref(RW)
    DRAM_REG[36] =
        0x01010000; // 0000000_1 tref_enable(RW) 0000000_1
                    // tras_lockout(RW) 000000000000000_0 fast_write(RW)
    DRAM_REG[37] =
        0x07080403; // 0000_0111 caslat_lin_gate(RW) 0000_1000 caslat_lin(RW)
                    // 00000_100 caslat(RW) 0000_0011 wrlat(RW)
    DRAM_REG[38] = 0x06005003; // 000_00110 tdal(RW) 0000000001010000 tcpd(RW)
                               // 00000_011 tcke(RW)
    DRAM_REG[39] =
        0x0a0000c8; // 00_001010 tfaw(RW) 000000000000000011001000 tdll(RW)
    DRAM_REG[40] =
        0x02009c40; // 000_00010 tmrd(RW) 000000000111010100100010 tinit(RW)
    DRAM_REG[41] = 0x0002030c; // 0000000000000010 tpdex(RW) 00000011
                               // trcd_int(RW) 00_001100 trc(RW)
    DRAM_REG[42] = 0x0036a609; // 000000000011011010100110 tras_max(RW) 00001001
                               // tras_min(RW)
    DRAM_REG[43] = 0x031a0612; // 0000_0011 trp(RW) 00011010 trfc(RW)
                               // 00_00011000010010 tref(RW)
    DRAM_REG[44] = 0x02030202; // 0000_0010 twtr(RW) 000_00011 twr_int(RW)
                               // 00000_010 trtp(RW) 00000_010 trrd(RW)
    DRAM_REG[45] =
        0x00c8001c; // 0000000011001000 txsr(RW) 0000000000011100 txsnr(RW)
    DRAM_REG[46] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[47] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[48] = 0x00012100; // 0_0000000 axi0_current_bdw(RD) 0000000_1
                               // axi0_bdw_ovflow(RW) 0_0100001 axi0_bdw(RW)
                               // 000000_00 axi0_fifo_type_reg(RW)
    // DRAM_REG[49] = 0x55550303 ; //0101010101010101
    // axi0_en_size_lt_width_instr(RW) 00000_011 axi0_w_priority(RW) 00000_011
    // axi0_r_priority(RW)
    DRAM_REG[49] =
        0xffff0303; // 0101010101010101 axi0_en_size_lt_width_instr(RW)
                    // 00000_011 axi0_w_priority(RW) 00000_011
                    // axi0_r_priority(RW)
    DRAM_REG[50] = 0x00012100; // 0_0000000 axi1_current_bdw(RD) 0000000_1
                               // axi1_bdw_ovflow(RW) 0_0100001 axi1_bdw(RW)
                               // 000000_00 axi1_fifo_type_reg(RW)
    DRAM_REG[51] =
        0xffff0303; // 1111111100000000 axi1_en_size_lt_width_instr(RW)
                    // 00000_011 axi1_w_priority(RW) 00000_011
                    // axi1_r_priority(RW)
    DRAM_REG[52] = 0x00012100; // 0_0000000 axi2_current_bdw(RD) 0000000_1
                               // axi2_bdw_ovflow(RW) 0_0100001 axi2_bdw(RW)
                               // 000000_00 axi2_fifo_type_reg(RW)
    DRAM_REG[53] =
        0xffff0303; // 0000000000000001 axi2_en_size_lt_width_instr(RW)
                    // 00000_011 axi2_w_priority(RW) 00000_011
                    // axi2_r_priority(RW)
    DRAM_REG[54] = 0x00012100; // 0_0000000 axi3_current_bdw(RD) 0000000_1
                               // axi3_bdw_ovflow(RW) 0_0100001 axi3_bdw(RW)
                               // 000000_00 axi3_fifo_type_reg(RW)
    DRAM_REG[55] =
        0xffff0303; // 0000000000000001 axi3_en_size_lt_width_instr(RW)
                    // 00000_011 axi3_w_priority(RW) 00000_011
                    // axi3_r_priority(RW)
    DRAM_REG[56] =
        0x00000003; // 00000000000000000000000000000_011 arb_cmd_q_threshold(RW)
    DRAM_REG[57] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[58] = 0x00000000; // 00000_00000000000 int_status(RD)
                               // 00000_00000000000 int_mask(RW)
    DRAM_REG[59] =
        0x00000000; // 00000000000000000000000000000000 out_of_range_addr(RD)
    DRAM_REG[60] = 0x00000000; // 000000000000000000000000000000_00
    DRAM_REG[61] = 0x00000000; // 00_000000 out_of_range_type(RD) 0_0000000
                               // out_of_range_length(RD) 000_0000000000000
                               // out_of_range_source_id(RD)
    DRAM_REG[62] =
        0x00000000; // 00000000000000000000000000000000 port_cmd_error_addr(RD)
    DRAM_REG[63] = 0x00000000; // 000000000000000000000000000000_00
    DRAM_REG[64] =
        0x00000000; // 00000000000_0000000000000 port_cmd_error_id(RD)
                    // 0000_0000 port_cmd_error_type(RD)
    DRAM_REG[65] =
        0x00000000; // 00000000000_0000000000000 port_data_error_id(RD)
                    // 00000_000 port_data_error_type(RD)
    DRAM_REG[66] = 0x00000612; // 000000000000_0000 tdfi_ctrlupd_min(RD)
                               // 00_00011000010010 tdfi_ctrlupd_max(RW)
    // DRAM_REG[67] = 0x01000002 ; //0000_0001 tdfi_dram_clk_enable(RW)
    // 00000_000 tdfi_dram_clk_disable(RW) 0000_0000 dram_clk_disable(RW)
    // 0000_0010 tdfi_ctrl_delay(RW)
    DRAM_REG[67] =
        0x01000f02; // 0000_0001 tdfi_dram_clk_enable(RW) 00000_000
                    // tdfi_dram_clk_disable(RW) 0000_0000 dram_clk_disable(RW)
                    // 0000_0010 tdfi_ctrl_delay(RW)
    DRAM_REG[68] = 0x06120612; // 00_00011000010010 tdfi_phyupd_type0(RW)
                               // 00_00011000010010 tdfi_phyupd_resp(RW)
    DRAM_REG[69] =
        0x00000200; // 00000000000000000000_0010 tdfi_phy_wrlat_base(RW)
                    // 0000_0000 tdfi_phy_wrlat(RD)
    DRAM_REG[70] =
        0x00020007; // 000000000000_0010 tdfi_rddata_en_base(RW) 0000_0000
                    // tdfi_rddata_en(RD) 0000_0111 tdfi_phy_rdlat(RW)
    DRAM_REG[71] = 0xf4004a27;
    DRAM_REG[72] = 0xf4004a27;
    DRAM_REG[73] = 0xf4004a27;
    DRAM_REG[74] = 0xf4004a27;
    DRAM_REG[75] =
        0x07000300; // 00000111000000000000001100000000 phy_ctrl_reg_1_0(RW)
    DRAM_REG[76] =
        0x07000300; // 00000111000000000000001100000000 phy_ctrl_reg_1_1(RW)
    DRAM_REG[77] =
        0x07400300; // 00000111010000000000001100000000 phy_ctrl_reg_1_2(RW)
    DRAM_REG[78] =
        0x07400300; // 00000111010000000000001100000000 phy_ctrl_reg_1_3(RW)
    DRAM_REG[79] =
        0x00000005; // 00000000000000000000000000000101 phy_ctrl_reg_2(RW)
    DRAM_REG[80] = 0x00000000; // 00000000000000000000000000000000
                               // dft_ctrl_reg(RW)
    DRAM_REG[81] =
        0x00000000; // 0000000000000000000_00000 ocd_adjust_pup_cs_0(RW)
                    // 000_00000 ocd_adjust_pdn_cs_0(RW)
    DRAM_REG[82] = 0x01000000; // 0000000_1 odt_alt_en(RW)
                               // 000000000000000000000000
    DRAM_REG[83] =
        0x01020408; // 0000_0001 odt_rd_map_cs3(RW) 0000_0010 odt_rd_map_cs2(RW)
                    // 0000_0100 odt_rd_map_cs1(RW) 0000_1000 odt_rd_map_cs0(RW)
    DRAM_REG[84] =
        0x08040201; // 0000_1000 odt_wr_map_cs3(RW) 0000_0100 odt_wr_map_cs2(RW)
                    // 0000_0010 odt_wr_map_cs1(RW) 0000_0001 odt_wr_map_cs0(RW)
    DRAM_REG[85] =
        0x000f1133; // 00000000000011110001000100110011 pad_ctrl_reg_0(RW)
    DRAM_REG[86] = 0x00000000; // 00000000000000000000000000000000 version(RD)
    DRAM_REG[87] = 0x00001f04;
    DRAM_REG[88] = 0x00001f04;
    DRAM_REG[89] = 0x00001f04;
    DRAM_REG[90] = 0x00001f04;
    DRAM_REG[91] = 0x00001f04;
    DRAM_REG[92] = 0x00001f04;
    DRAM_REG[93] = 0x00001f04;
    DRAM_REG[94] = 0x00001f04;
    DRAM_REG[95] =
        0x00000000; // 00000000000000000000000000000000 dll_obs_reg_0_0(RD)
    DRAM_REG[96] =
        0x00000000; // 00000000000000000000000000000000 dll_obs_reg_0_1(RD)
    DRAM_REG[97] =
        0x00000000; // 00000000000000000000000000000000 dll_obs_reg_0_2(RD)
    DRAM_REG[98] =
        0x00000000; // 00000000000000000000000000000000 dll_obs_reg_0_3(RD)
    DRAM_REG[99] =
        0x00000000; // 00000000000000000000000000000000 phy_obs_reg_0_0(RD)
    DRAM_REG[100] =
        0x00000000; // 00000000000000000000000000000000 phy_obs_reg_0_1(RD)
    DRAM_REG[101] =
        0x00000000; // 00000000000000000000000000000000 phy_obs_reg_0_2(RD)
    DRAM_REG[102] =
        0x00000000; // 00000000000000000000000000000000 phy_obs_reg_0_3(RD)
    DRAM_REG[103] =
        0x00000000; // 00000000000000000000000000000000 dll_obs_reg_1_0(RD)
    DRAM_REG[104] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[105] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[106] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[107] = 0x00000000; // 00000000000000000000000_000000000
    DRAM_REG[108] =
        0x00000000; // 00000000000000000000000000000000 dll_obs_reg_1_1(RD)
    DRAM_REG[109] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[110] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[111] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[112] = 0x00000000; // 00000000000000000000000_000000000
    DRAM_REG[113] =
        0x00000000; // 00000000000000000000000000000000 dll_obs_reg_1_2(RD)
    DRAM_REG[114] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[115] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[116] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[117] = 0x00000000; // 00000000000000000000000_000000000
    DRAM_REG[118] =
        0x00000000; // 00000000000000000000000000000000 dll_obs_reg_1_3(RD)
    DRAM_REG[119] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[120] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[121] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[122] = 0x00000000; // 00000000000000000000000_000000000
    DRAM_REG[123] =
        0x00000000; // 00000000000000000000000000000000 dll_obs_reg_2_0(RD)
    DRAM_REG[124] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[125] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[126] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[127] = 0x00000000; // 00000000000000000000000_000000000
    DRAM_REG[128] =
        0x00000000; // 00000000000000000000000000000000 dll_obs_reg_2_1(RD)
    DRAM_REG[129] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[130] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[131] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[132] = 0x00000000; // 00000000000000000000000_000000000
    DRAM_REG[133] =
        0x00000000; // 00000000000000000000000000000000 dll_obs_reg_2_2(RD)
    DRAM_REG[134] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[135] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[136] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[137] = 0x00000000; // 00000000000000000000000_000000000
    DRAM_REG[138] =
        0x00000000; // 00000000000000000000000000000000 dll_obs_reg_2_3(RD)
    DRAM_REG[139] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[140] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[141] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[142] = 0x00000000; // 00000000000000000000000_000000000
    DRAM_REG[143] =
        0x00000000; // 00000000000000000000000000000000 dll_obs_reg_3_0(RD)
    DRAM_REG[144] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[145] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[146] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[147] = 0x00000000; // 00000000000000000000000_000000000
    DRAM_REG[148] =
        0x00000000; // 00000000000000000000000000000000 dll_obs_reg_3_1(RD)
    DRAM_REG[149] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[150] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[151] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[152] = 0x00000000; // 00000000000000000000000_000000000
    DRAM_REG[153] =
        0x00000000; // 00000000000000000000000000000000 dll_obs_reg_3_2(RD)
    DRAM_REG[154] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[155] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[156] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[157] = 0x00000000; // 00000000000000000000000_000000000
    DRAM_REG[158] =
        0x00000000; // 00000000000000000000000000000000 dll_obs_reg_3_3(RD)
    DRAM_REG[159] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[160] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[161] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[162] = 0x00010000; // 00000_000 w2r_samecs_dly(RW) 00000_001
                                // w2r_diffcs_dly(RW) 0000000_000000000
    DRAM_REG[163] =
        0x00030404; // 00000000 dll_rst_adj_dly(RW) 0000_0011 wrlat_adj(RW)
                    // 0000_0100 rdlat_adj(RW) 0000_0100 dram_class(RW)
    DRAM_REG[164] =
        0x00000003; // 00000000000000_0000000000 int_ack(WR) 00000011 tmod(RW)
    DRAM_REG[165] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[166] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[167] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[168] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[169] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[170] = 0x00000000; // 00000000000000000000000000000000
    DRAM_REG[171] =
        0x01010000; // 0000000_1 axi5_bdw_ovflow(RW) 0000000_1
                    // axi4_bdw_ovflow(RW) 0000000000000000 dll_rst_delay(RW)
    DRAM_REG[172] =
        0x01000000; // 0000000_1 resync_dll_per_aref_en(RW) 0000000_0
                    // resync_dll(WR) 0000000_0 concurrentap_wr_only(RW)
                    // 0000000_0 cke_status(RD)
    DRAM_REG[173] =
        0x03030000; // 00000_011 axi4_w_priority(RW) 00000_011
                    // axi4_r_priority(RW) 000000_00 axi5_fifo_type_reg(RW)
                    // 000000_00 axi4_fifo_type_reg(RW)
    DRAM_REG[174] =
        0x00010303; // 00000_000 r2r_samecs_dly(RW) 00000_001 r2r_diffcs_dly(RW)
                    // 00000_011 axi5_w_priority(RW) 00000_011
                    // axi5_r_priority(RW)
    DRAM_REG[175] =
        0x01020202; // 00000_001 w2w_diffcs_dly(RW) 00000_010
                    // tbst_int_interval(RW) 00000_010
                    // r2w_samecs_dly(RW) 00000_010 r2w_diffcs_dly(RW)
    DRAM_REG[176] = 0x00000000; // 0000_0000 add_odt_clk_sametype_diffcs(RW)
                                // 0000_0000 add_odt_clk_difftype_samecs(RW)
                                // 0000_0000 add_odt_clk_difftype_diffcs(RW)
                                // 00000_000 w2w_samecs_dly(RW)
    DRAM_REG[177] = 0x02040303; // 000_00010 tccd(RW) 0000_0100 trp_ab(RW)
                                // 0000_0011 cksrx(RW) 0000_0011 cksre(RW)
    DRAM_REG[178] =
        0x21002103; // 0_0100001 axi5_bdw(RW) 0_0000000 axi4_current_bdw(RD)
                    // 0_0100001 axi4_bdw(RW) 000_00011 tckesr(RW)
    DRAM_REG[179] =
        0x00061200; // 0000000000_00011000010010 tdfi_phyupd_type1(RW)
                    // 0_0000000 axi5_current_bdw(RD)
    DRAM_REG[180] = 0x06120612; // 00_00011000010010 tdfi_phyupd_type3(RW)
                                // 00_00011000010010 tdfi_phyupd_type2(RW)
    DRAM_REG[181] = 0x04420442; // 0_000010001000010 mr0_data_1(RW)
                                // 0_000010001000010 mr0_data_0(RW)
    DRAM_REG[182] = 0x04420442; // 0_000010001000010 mr0_data_3(RW)
                                // 0_000010001000010 mr0_data_2(RW)
    DRAM_REG[183] = 0x00040004; // 0_000000000000100 mr1_data_1(RW)
                                // 0_000000000000100 mr1_data_0(RW)
    DRAM_REG[184] = 0x00040004; // 0_000000000000100 mr1_data_3(RW)
                                // 0_000000000000100 mr1_data_2(RW)
    DRAM_REG[185] = 0x00000000; // 0_000000000000000 mr2_data_1(RW)
                                // 0_000000000000000 mr2_data_0(RW)
    DRAM_REG[186] = 0x00000000; // 0_000000000000000 mr2_data_3(RW)
                                // 0_000000000000000 mr2_data_2(RW)
    DRAM_REG[187] = 0x00000000; // 0_000000000000000 mr3_data_1(RW)
                                // 0_000000000000000 mr3_data_0(RW)
    DRAM_REG[188] = 0x00000000; // 0_000000000000000 mr3_data_3(RW)
                                // 0_000000000000000 mr3_data_2(RW)
    DRAM_REG[189] =
        0xffffffff; // 0000000000000001 axi5_en_size_lt_width_instr(RW)
                    // 0000000000000001 axi4_en_size_lt_width_instr(RW)

#if 0
	DRAM_REG[0] = 0x00000000;
	DRAM_REG[1] = 0x00000000;
	DRAM_REG[2] = 0x00000000;
	DRAM_REG[3] = 0x00000000;
	DRAM_REG[4] = 0x00000000;
	DRAM_REG[5] = 0x00000000;
	DRAM_REG[6] = 0x00000000;
	DRAM_REG[7] = 0x00000000;  
	DRAM_REG[8] = 0x00000000;
	DRAM_REG[9] = 0x00000000;
	DRAM_REG[10] = 0x00000000;
	DRAM_REG[11] = 0x00000000;
	DRAM_REG[12] = 0x00000000;
	DRAM_REG[13] = 0x00000000;
	DRAM_REG[14] = 0x00000000;
	DRAM_REG[15] = 0x00000000;
	DRAM_REG[16] = 0x00000000;//
	DRAM_REG[17] = 0x00000100;
	DRAM_REG[18] = 0x00000000;
	DRAM_REG[19] = 0x00000000;
	DRAM_REG[20] = 0x00000000;
	DRAM_REG[21] = 0x00000000;
	DRAM_REG[22] = 0x00000000;
	DRAM_REG[23] = 0x00000000;
	DRAM_REG[24] = 0x00000000;
	DRAM_REG[25] = 0x00000000;
	DRAM_REG[26] = 0x00010101;
	DRAM_REG[27] = 0x01010101;
	DRAM_REG[28] = 0x000f0f01;
#if H5PS2562GFR == 0
	DRAM_REG[29] = 0x0f02020a;//
#else
	DRAM_REG[29] = 0x0103020a;
#endif
	DRAM_REG[30] = 0x00000000;
	DRAM_REG[31] = 0x00010101;//
	DRAM_REG[32] = 0x00000100;
	DRAM_REG[33] = 0x00000100;
	DRAM_REG[34] = 0x00000000;
	DRAM_REG[35] = 0x00000002;//
	DRAM_REG[36] = 0x01010000;
	DRAM_REG[37] = 0x07080403;//
	DRAM_REG[38] = 0x06005003;//
	DRAM_REG[39] = 0x0a0000c8;//
	DRAM_REG[40] = 0x02009c40;//
	DRAM_REG[41] = 0x0002030c;//
#if H5PS2562GFR == 0
	DRAM_REG[42] = 0x0036a609;//
#else
	DRAM_REG[42] = 0x0036b009;
#endif
	DRAM_REG[43] = 0x031a0612;
	DRAM_REG[44] = 0x02030202;
	DRAM_REG[45] = 0x00c8001c;
	DRAM_REG[46] = 0x00000000;
	DRAM_REG[47] = 0x00000000;
	DRAM_REG[48] = 0x00012100;
	DRAM_REG[49] = 0xffff0303;
	DRAM_REG[50] = 0x00012100;
	DRAM_REG[51] = 0xffff0303;
	DRAM_REG[52] = 0x00012100;
	DRAM_REG[53] = 0xffff0303;
	DRAM_REG[54] = 0x00012100;
	DRAM_REG[55] = 0xffff0303;
	DRAM_REG[56] = 0x00000003;
	DRAM_REG[57] = 0x00000000;
	DRAM_REG[58] = 0x00000000;
	DRAM_REG[59] = 0x00000000;
	DRAM_REG[60] = 0x00000000;
	DRAM_REG[61] = 0x00000000;
	DRAM_REG[62] = 0x00000000;
	DRAM_REG[63] = 0x00000000;
	DRAM_REG[64] = 0x00000000;
	DRAM_REG[65] = 0x00000000;
	DRAM_REG[66] = 0x00000612;
	DRAM_REG[67] = 0x01000f02;
	DRAM_REG[68] = 0x06120612;
	DRAM_REG[69] = 0x00000200;
	DRAM_REG[70] = 0x00020007;
	DRAM_REG[71] = 0xf4004a27;
	DRAM_REG[72] = 0xf4004a27;
	DRAM_REG[73] = 0xf4004a27;
	DRAM_REG[74] = 0xf4004a27;
	DRAM_REG[75] = 0x07000300;
	DRAM_REG[76] = 0x07000300;
	DRAM_REG[77] = 0x07400300;
	DRAM_REG[78] = 0x07400300;
	DRAM_REG[79] = 0x00000005;
	DRAM_REG[80] = 0x00000000;
	DRAM_REG[81] = 0x00000000;
	DRAM_REG[82] = 0x01000000;
	DRAM_REG[83] = 0x01020408;
	DRAM_REG[84] = 0x08040201;
	DRAM_REG[85] = 0x000f1133;
	DRAM_REG[86] = 0x00000000;
	DRAM_REG[87] = 0x00001f04;
	DRAM_REG[88] = 0x00001f04;
	DRAM_REG[89] = 0x00001f04;
	DRAM_REG[90] = 0x00001f04;
	DRAM_REG[91] = 0x00001f04;
	DRAM_REG[92] = 0x00001f04;
	DRAM_REG[93] = 0x00001f04;
	DRAM_REG[94] = 0x00001f04;
	DRAM_REG[95] = 0x00000000;
	DRAM_REG[96] = 0x00000000;
	DRAM_REG[97] = 0x00000000;
	DRAM_REG[98] = 0x00000000;
	DRAM_REG[99] = 0x00000000;
	DRAM_REG[100] = 0x00000000;
	DRAM_REG[101] = 0x00000000;
	DRAM_REG[102] = 0x00000000;
	DRAM_REG[103] = 0x00000000;
	DRAM_REG[104] = 0x00000000;
	DRAM_REG[105] = 0x00000000;
	DRAM_REG[106] = 0x00000000;
	DRAM_REG[107] = 0x00000000;
	DRAM_REG[108] = 0x00000000;
	DRAM_REG[109] = 0x00000000;
	DRAM_REG[110] = 0x00000000;
	DRAM_REG[111] = 0x00000000;
	DRAM_REG[112] = 0x00000000;
	DRAM_REG[113] = 0x00000000;
	DRAM_REG[114] = 0x00000000;
	DRAM_REG[115] = 0x00000000;
	DRAM_REG[116] = 0x00000000;
	DRAM_REG[117] = 0x00000000;
	DRAM_REG[118] = 0x00000000;
	DRAM_REG[119] = 0x00000000;
	DRAM_REG[120] = 0x00000000;
	DRAM_REG[121] = 0x00000000;
	DRAM_REG[122] = 0x00000000;
	DRAM_REG[123] = 0x00000000;
	DRAM_REG[124] = 0x00000000;
	DRAM_REG[125] = 0x00000000;
	DRAM_REG[126] = 0x00000000;
	DRAM_REG[127] = 0x00000000;
	DRAM_REG[128] = 0x00000000;
	DRAM_REG[129] = 0x00000000;
	DRAM_REG[130] = 0x00000000;
	DRAM_REG[131] = 0x00000000;
	DRAM_REG[132] = 0x00000000;
	DRAM_REG[133] = 0x00000000;
	DRAM_REG[134] = 0x00000000;
	DRAM_REG[135] = 0x00000000;
	DRAM_REG[136] = 0x00000000;
	DRAM_REG[137] = 0x00000000;
	DRAM_REG[138] = 0x00000000;
	DRAM_REG[139] = 0x00000000;
	DRAM_REG[140] = 0x00000000;
	DRAM_REG[141] = 0x00000000;
	DRAM_REG[142] = 0x00000000;
	DRAM_REG[143] = 0x00000000;
	DRAM_REG[144] = 0x00000000;
	DRAM_REG[145] = 0x00000000;
	DRAM_REG[146] = 0x00000000;
	DRAM_REG[147] = 0x00000000;
	DRAM_REG[148] = 0x00000000;
	DRAM_REG[149] = 0x00000000;
	DRAM_REG[150] = 0x00000000;
	DRAM_REG[151] = 0x00000000;
	DRAM_REG[152] = 0x00000000;
	DRAM_REG[153] = 0x00000000;
	DRAM_REG[154] = 0x00000000;
	DRAM_REG[155] = 0x00000000;
	DRAM_REG[156] = 0x00000000;
	DRAM_REG[157] = 0x00000000;
	DRAM_REG[158] = 0x00000000;
	DRAM_REG[159] = 0x00000000;
	DRAM_REG[160] = 0x00000000;
	DRAM_REG[161] = 0x00000000;
	DRAM_REG[162] = 0x00010000;
	DRAM_REG[163] = 0x00030404;
	DRAM_REG[164] = 0x00000003;
	DRAM_REG[165] = 0x00000000;
	DRAM_REG[166] = 0x00000000;
	DRAM_REG[167] = 0x00000000;
	DRAM_REG[168] = 0x00000000;
	DRAM_REG[169] = 0x00000000;
	DRAM_REG[170] = 0x00000000;
	DRAM_REG[171] = 0x01010000;
	DRAM_REG[172] = 0x01000000;
	DRAM_REG[173] = 0x03030000;
	DRAM_REG[174] = 0x00010303;
	DRAM_REG[175] = 0x01020202;
	DRAM_REG[176] = 0x00000000;
#if H5PS2562GFR == 0
	DRAM_REG[177] = 0x02040303;
#else
	DRAM_REG[177] = 0x02030303;
#endif
	DRAM_REG[178] = 0x21002103;
	DRAM_REG[179] = 0x00061200;
	DRAM_REG[180] = 0x06120612;
	DRAM_REG[181] = 0x04420442;
	DRAM_REG[182] = 0x04420442;
	DRAM_REG[183] = 0x00040004;
//	DRAM_REG[184] = 0x00040004;
	DRAM_REG[184] = 0x00000000;
	DRAM_REG[185] = 0x00000000;
	DRAM_REG[186] = 0x00000000;
	DRAM_REG[187] = 0x00000000;
	DRAM_REG[188] = 0x00000000;
	DRAM_REG[189] = 0xffffffff;
#endif
}
void Init_mddr_200MHz() {
    volatile unsigned int *DRAM_REG =
        (volatile unsigned int *)HW_DRAM_CTL00_ADDR;
    DRAM_REG[0] = 0x00000000;
    DRAM_REG[16] = 0x00000000;
    DRAM_REG[21] = 0x00000000;
    DRAM_REG[22] = 0x00000000;
    DRAM_REG[23] = 0x00000000;
    DRAM_REG[24] = 0x00000000;
    DRAM_REG[25] = 0x00000000;
    DRAM_REG[26] = 0x00010101;
    DRAM_REG[27] = 0x01010101;
    DRAM_REG[28] = 0x000f0f01;
    DRAM_REG[29] = 0x0f02010a;
    DRAM_REG[31] = 0x00000101;
    DRAM_REG[32] = 0x00000100;
    DRAM_REG[33] = 0x00000100;
    DRAM_REG[34] = 0x01000000;
    DRAM_REG[35] = 0x00000002;
    DRAM_REG[36] = 0x01010000;
    DRAM_REG[37] = 0x08060301;
    DRAM_REG[38] = 0x06000001;
    DRAM_REG[39] = 0x0a000000;
    DRAM_REG[40] = 0x02009c40;
    DRAM_REG[41] = 0x0002030b;
    DRAM_REG[42] = 0x0036a608;
    DRAM_REG[43] = 0x03160305;
    DRAM_REG[44] = 0x03030002;
    DRAM_REG[45] = 0x001f001c;
    DRAM_REG[48] = 0x00012100;
    DRAM_REG[49] = 0xffff0303;
    DRAM_REG[50] = 0x00012100;
    DRAM_REG[51] = 0xffff0303;
    DRAM_REG[52] = 0x00012100;
    DRAM_REG[53] = 0xffff0303;
    DRAM_REG[54] = 0x00012100;
    DRAM_REG[55] = 0xffff0303;
    DRAM_REG[56] = 0x00000003;
    DRAM_REG[58] = 0x00000000;
    DRAM_REG[66] = 0x00000305;
    DRAM_REG[67] = 0x01000f02;
    DRAM_REG[69] = 0x00000200;
    DRAM_REG[70] = 0x00020007;
    DRAM_REG[71] = 0xf3004a27;
    DRAM_REG[72] = 0xf3004a27;
    DRAM_REG[75] = 0x07000310;
    DRAM_REG[76] = 0x07000310;
    DRAM_REG[79] = 0x00800004;
    DRAM_REG[80] = 0x00000000;
    DRAM_REG[81] = 0x00000000;
    DRAM_REG[82] = 0x01000000;
    DRAM_REG[83] = 0x01020408;
    DRAM_REG[84] = 0x08040201;
    DRAM_REG[85] = 0x000f1133;
    DRAM_REG[87] = 0x00001f08;
    DRAM_REG[88] = 0x00001f08;
    DRAM_REG[91] = 0x00001f01;
    DRAM_REG[92] = 0x00001f01;
    DRAM_REG[162] = 0x00000000;
    DRAM_REG[163] = 0x00010301;
    DRAM_REG[164] = 0x00000002;
    DRAM_REG[171] = 0x01010000;
    DRAM_REG[172] = 0x01000100;
    DRAM_REG[173] = 0x03030000;
    DRAM_REG[174] = 0x00020303;
    DRAM_REG[175] = 0x01010202;
    DRAM_REG[176] = 0x00000000;
    DRAM_REG[177] = 0x01030101;
    DRAM_REG[178] = 0x21002101;
    DRAM_REG[179] = 0x00030500;
    DRAM_REG[180] = 0x03050305;
    DRAM_REG[181] = 0x00320032;
    DRAM_REG[182] = 0x00320032;
    DRAM_REG[183] = 0x00000000;
    DRAM_REG[184] = 0x00000000;
    DRAM_REG[185] = 0x00000000;
    DRAM_REG[186] = 0x00000000;
    DRAM_REG[187] = 0x00000000;
    DRAM_REG[188] = 0x00000000;
    DRAM_REG[189] = 0xffffffff;
}

void poweron_pll() { HW_CLKCTRL_PLL0CTRL0_SET(BM_CLKCTRL_PLL0CTRL0_POWER); }
void turnon_mem_rail(int mv) {
    unsigned int value;
    //	HW_POWER_CTRL_CLR(BM_POWER_CTRL_CLKGATE);

    value = BM_POWER_VDDMEMCTRL_ENABLE_ILIMIT |
            BM_POWER_VDDMEMCTRL_ENABLE_LINREG |
            BM_POWER_VDDMEMCTRL_PULLDOWN_ACTIVE | (mv - 1700) / 50;

    HW_POWER_VDDMEMCTRL_WR(value);
    delay(20000);
    value &= ~(BM_POWER_VDDMEMCTRL_ENABLE_ILIMIT |
               BM_POWER_VDDMEMCTRL_PULLDOWN_ACTIVE);
    HW_POWER_VDDMEMCTRL_WR(value);
}
void set_emi_frac(unsigned int div) {
    HW_CLKCTRL_FRAC0_SET(BM_CLKCTRL_FRAC0_EMIFRAC);
    div = (~div);
    HW_CLKCTRL_FRAC0_CLR(BF_CLKCTRL_FRAC0_EMIFRAC(div));
}
void init_clock() {
    HW_CLKCTRL_FRAC0_SET(BM_CLKCTRL_FRAC0_CLKGATEEMI);

    set_emi_frac(21);

    HW_CLKCTRL_FRAC0_CLR(BM_CLKCTRL_FRAC0_CLKGATEEMI);
    delay(11000);

    HW_CLKCTRL_EMI_WR(BF_CLKCTRL_EMI_DIV_XTAL(1) | BF_CLKCTRL_EMI_DIV_EMI(2));

    /*choose ref_emi*/
    HW_CLKCTRL_CLKSEQ_CLR(BM_CLKCTRL_CLKSEQ_BYPASS_EMI);

    printf("FRAC 0x%x\r\n", HW_CLKCTRL_FRAC0_RD());
}

void disable_emi_padkeepers(void) {
#if 0
    HW_PINCTRL_CTRL_CLR(BM_PINCTRL_CTRL_SFTRST | BM_PINCTRL_CTRL_CLKGATE);

    HW_PINCTRL_PULL3_SET(
    BM_PINCTRL_PULL3_BANK3_PIN17 |
    BM_PINCTRL_PULL3_BANK3_PIN16 |
    BM_PINCTRL_PULL3_BANK3_PIN15 |
    BM_PINCTRL_PULL3_BANK3_PIN14 |
    BM_PINCTRL_PULL3_BANK3_PIN13 |
    BM_PINCTRL_PULL3_BANK3_PIN12 |
    BM_PINCTRL_PULL3_BANK3_PIN11 |
    BM_PINCTRL_PULL3_BANK3_PIN10 |
    BM_PINCTRL_PULL3_BANK3_PIN09 |
    BM_PINCTRL_PULL3_BANK3_PIN08 |
    BM_PINCTRL_PULL3_BANK3_PIN07 |
    BM_PINCTRL_PULL3_BANK3_PIN06 |
    BM_PINCTRL_PULL3_BANK3_PIN05 |
    BM_PINCTRL_PULL3_BANK3_PIN04 |
    BM_PINCTRL_PULL3_BANK3_PIN03 |
    BM_PINCTRL_PULL3_BANK3_PIN02 |
    BM_PINCTRL_PULL3_BANK3_PIN01 |
    BM_PINCTRL_PULL3_BANK3_PIN00);
#endif
}

#define PIN_VOL(pin, v) ((v) ? (pin) : 0)
void init_emi_pin(int pin_voltage, int pin_drive) {
#ifdef MEM_MDDR
    disable_emi_padkeepers();
    HW_PINCTRL_EMI_DS_CTRL_WR(
        BF_PINCTRL_EMI_DS_CTRL_ADDRESS_MA(EMI_PIN_DRIVE_ADDRESS) |
        BF_PINCTRL_EMI_DS_CTRL_CONTROL_MA(EMI_PIN_DRIVE_CONTROL) |
        BF_PINCTRL_EMI_DS_CTRL_DUALPAD_MA(EMI_PIN_DRIVE_DUALPAD) |
        BF_PINCTRL_EMI_DS_CTRL_SLICE3_MA(EMI_PIN_DRIVE_DATA_SLICE_3) |
        BF_PINCTRL_EMI_DS_CTRL_SLICE2_MA(EMI_PIN_DRIVE_DATA_SLICE_2) |
        BF_PINCTRL_EMI_DS_CTRL_SLICE1_MA(EMI_PIN_DRIVE_DATA_SLICE_1) |
        BF_PINCTRL_EMI_DS_CTRL_SLICE0_MA(EMI_PIN_DRIVE_DATA_SLICE_0));

    /* Configure Bank-3 Pins 0-15 as EMI pins*/
    HW_PINCTRL_MUXSEL10_CLR(
        BM_PINCTRL_MUXSEL10_BANK5_PIN00 | BM_PINCTRL_MUXSEL10_BANK5_PIN01 |
        BM_PINCTRL_MUXSEL10_BANK5_PIN02 | BM_PINCTRL_MUXSEL10_BANK5_PIN03 |
        BM_PINCTRL_MUXSEL10_BANK5_PIN04 | BM_PINCTRL_MUXSEL10_BANK5_PIN05 |
        BM_PINCTRL_MUXSEL10_BANK5_PIN06 | BM_PINCTRL_MUXSEL10_BANK5_PIN07 |
        BM_PINCTRL_MUXSEL10_BANK5_PIN08 | BM_PINCTRL_MUXSEL10_BANK5_PIN09 |
        BM_PINCTRL_MUXSEL10_BANK5_PIN10 | BM_PINCTRL_MUXSEL10_BANK5_PIN11 |
        BM_PINCTRL_MUXSEL10_BANK5_PIN12 | BM_PINCTRL_MUXSEL10_BANK5_PIN13 |
        BM_PINCTRL_MUXSEL10_BANK5_PIN14 | BM_PINCTRL_MUXSEL10_BANK5_PIN15);

    HW_PINCTRL_MUXSEL11_CLR(
        BM_PINCTRL_MUXSEL11_BANK5_PIN16 | BM_PINCTRL_MUXSEL11_BANK5_PIN17 |
        BM_PINCTRL_MUXSEL11_BANK5_PIN18 | BM_PINCTRL_MUXSEL11_BANK5_PIN19 |
        BM_PINCTRL_MUXSEL11_BANK5_PIN20 | BM_PINCTRL_MUXSEL11_BANK5_PIN21 |
        BM_PINCTRL_MUXSEL11_BANK5_PIN22 | BM_PINCTRL_MUXSEL11_BANK5_PIN23 |
        BM_PINCTRL_MUXSEL11_BANK5_PIN26);

    HW_PINCTRL_MUXSEL12_CLR(
        BM_PINCTRL_MUXSEL12_BANK6_PIN00 | BM_PINCTRL_MUXSEL12_BANK6_PIN01 |
        BM_PINCTRL_MUXSEL12_BANK6_PIN02 | BM_PINCTRL_MUXSEL12_BANK6_PIN03 |
        BM_PINCTRL_MUXSEL12_BANK6_PIN04 | BM_PINCTRL_MUXSEL12_BANK6_PIN05 |
        BM_PINCTRL_MUXSEL12_BANK6_PIN06 | BM_PINCTRL_MUXSEL12_BANK6_PIN07 |
        BM_PINCTRL_MUXSEL12_BANK6_PIN08 | BM_PINCTRL_MUXSEL12_BANK6_PIN09 |
        BM_PINCTRL_MUXSEL12_BANK6_PIN10 | BM_PINCTRL_MUXSEL12_BANK6_PIN11 |
        BM_PINCTRL_MUXSEL12_BANK6_PIN12 | BM_PINCTRL_MUXSEL12_BANK6_PIN13 |
        BM_PINCTRL_MUXSEL12_BANK6_PIN14);

    HW_PINCTRL_MUXSEL13_CLR(
        BM_PINCTRL_MUXSEL13_BANK6_PIN16 | BM_PINCTRL_MUXSEL13_BANK6_PIN17 |
        BM_PINCTRL_MUXSEL13_BANK6_PIN18 | BM_PINCTRL_MUXSEL13_BANK6_PIN19 |
        BM_PINCTRL_MUXSEL13_BANK6_PIN20 | BM_PINCTRL_MUXSEL13_BANK6_PIN21 |
        BM_PINCTRL_MUXSEL13_BANK6_PIN22 | BM_PINCTRL_MUXSEL13_BANK6_PIN23 |
        BM_PINCTRL_MUXSEL13_BANK6_PIN24);
#else
    /* Configure Bank-3 Pins 0-15 as EMI pins*/
    HW_PINCTRL_MUXSEL10_CLR(
        BM_PINCTRL_MUXSEL10_BANK5_PIN00 | BM_PINCTRL_MUXSEL10_BANK5_PIN01 |
        BM_PINCTRL_MUXSEL10_BANK5_PIN02 | BM_PINCTRL_MUXSEL10_BANK5_PIN03 |
        BM_PINCTRL_MUXSEL10_BANK5_PIN04 | BM_PINCTRL_MUXSEL10_BANK5_PIN05 |
        BM_PINCTRL_MUXSEL10_BANK5_PIN06 | BM_PINCTRL_MUXSEL10_BANK5_PIN07 |
        BM_PINCTRL_MUXSEL10_BANK5_PIN08 | BM_PINCTRL_MUXSEL10_BANK5_PIN09 |
        BM_PINCTRL_MUXSEL10_BANK5_PIN10 | BM_PINCTRL_MUXSEL10_BANK5_PIN11 |
        BM_PINCTRL_MUXSEL10_BANK5_PIN12 | BM_PINCTRL_MUXSEL10_BANK5_PIN13 |
        BM_PINCTRL_MUXSEL10_BANK5_PIN14 | BM_PINCTRL_MUXSEL10_BANK5_PIN15);

    HW_PINCTRL_MUXSEL11_CLR(
        BM_PINCTRL_MUXSEL11_BANK5_PIN16 | BM_PINCTRL_MUXSEL11_BANK5_PIN17 |
        BM_PINCTRL_MUXSEL11_BANK5_PIN18 | BM_PINCTRL_MUXSEL11_BANK5_PIN19 |
        BM_PINCTRL_MUXSEL11_BANK5_PIN20 | BM_PINCTRL_MUXSEL11_BANK5_PIN21 |
        BM_PINCTRL_MUXSEL11_BANK5_PIN22 | BM_PINCTRL_MUXSEL11_BANK5_PIN23 |
        BM_PINCTRL_MUXSEL11_BANK5_PIN26);

    HW_PINCTRL_MUXSEL12_CLR(
        BM_PINCTRL_MUXSEL12_BANK6_PIN00 | BM_PINCTRL_MUXSEL12_BANK6_PIN01 |
        BM_PINCTRL_MUXSEL12_BANK6_PIN02 | BM_PINCTRL_MUXSEL12_BANK6_PIN03 |
        BM_PINCTRL_MUXSEL12_BANK6_PIN04 | BM_PINCTRL_MUXSEL12_BANK6_PIN05 |
        BM_PINCTRL_MUXSEL12_BANK6_PIN06 | BM_PINCTRL_MUXSEL12_BANK6_PIN07 |
        BM_PINCTRL_MUXSEL12_BANK6_PIN08 | BM_PINCTRL_MUXSEL12_BANK6_PIN09 |
        BM_PINCTRL_MUXSEL12_BANK6_PIN10 | BM_PINCTRL_MUXSEL12_BANK6_PIN11 |
        BM_PINCTRL_MUXSEL12_BANK6_PIN12 | BM_PINCTRL_MUXSEL12_BANK6_PIN13 |
        BM_PINCTRL_MUXSEL12_BANK6_PIN14);

    HW_PINCTRL_MUXSEL13_CLR(
        BM_PINCTRL_MUXSEL13_BANK6_PIN16 | BM_PINCTRL_MUXSEL13_BANK6_PIN17 |
        BM_PINCTRL_MUXSEL13_BANK6_PIN18 | BM_PINCTRL_MUXSEL13_BANK6_PIN19 |
        BM_PINCTRL_MUXSEL13_BANK6_PIN20 | BM_PINCTRL_MUXSEL13_BANK6_PIN21 |
        BM_PINCTRL_MUXSEL13_BANK6_PIN22 | BM_PINCTRL_MUXSEL13_BANK6_PIN23 |
        BM_PINCTRL_MUXSEL13_BANK6_PIN24);
#endif
}
void exit_selfrefresh() {
#if 0
	unsigned int start;
	unsigned int value;
	value = HW_DRAM_CTL16_RD();
	value &= ~(1<<17);
	HW_DRAM_CTL16_WR(value);

	start = HW_DIGCTL_MICROSECONDS_RD();

	while ((HW_EMI_STAT_RD()&BM_EMI_STAT_DRAM_HALTED)) {

		if (HW_DIGCTL_MICROSECONDS_RD() > (start + 1000000)) {

			printf("exit self refresh timeout\r\n");
			return;
		}
	}
#endif
}

void set_port_priority() {
    // unsigned int value;
#if 0
	HW_EMI_CTRL_CLR(BM_EMI_CTRL_PORT_PRIORITY_ORDER);
	HW_EMI_CTRL_SET(BF_EMI_CTRL_PORT_PRIORITY_ORDER(
				BV_EMI_CTRL_PORT_PRIORITY_ORDER__PORT1230)
		       );

	HW_EMI_CTRL_CLR(BM_EMI_CTRL_PORT_PRIORITY_ORDER);
	HW_EMI_CTRL_SET(BF_EMI_CTRL_PORT_PRIORITY_ORDER(0x2));
#endif
}
void entry_auto_clock_gate() {
    unsigned int value;
    value = HW_DRAM_CTL16_RD();
    value |= 1 << 19;
    HW_DRAM_CTL16_WR(value);

    value = HW_DRAM_CTL16_RD();
    value |= 1 << 11;
    HW_DRAM_CTL16_WR(value);
}
void change_cpu_freq() {
    int value = HW_POWER_VDDDCTRL_RD();

    printf("power 0x%x\r\n", value);
    value &= ~BM_POWER_VDDDCTRL_TRG;
    value |= BF_POWER_VDDDCTRL_TRG(28);
    value &= ~BM_POWER_VDDDCTRL_BO_OFFSET;
    value |= BF_POWER_VDDDCTRL_BO_OFFSET(7);
    value &= ~BM_POWER_VDDDCTRL_LINREG_OFFSET;
    value |= BF_POWER_VDDDCTRL_LINREG_OFFSET(2);
    // value |= BM_POWER_VDDDCTRL_ENABLE_LINREG;
    // value |= BM_POWER_VDDDCTRL_DISABLE_STEPPING;

    HW_POWER_VDDDCTRL_WR(value); /*change to 1.50v*/

    delay(10000);

    printf("Frac 0x%x\r\n", HW_CLKCTRL_FRAC0_RD());

    value = HW_CLKCTRL_FRAC0_RD();
    value &= ~BM_CLKCTRL_FRAC0_CPUFRAC;
    value |= BF_CLKCTRL_FRAC0_CPUFRAC(19);
    value &= ~BM_CLKCTRL_FRAC0_CLKGATECPU;

    HW_CLKCTRL_FRAC0_WR(value); /*Change cpu to 360Mhz*/

    HW_CLKCTRL_CLKSEQ_SET(BM_CLKCTRL_CLKSEQ_BYPASS_CPU);

    HW_CLKCTRL_HBUS_SET(BM_CLKCTRL_HBUS_DIV);
    HW_CLKCTRL_HBUS_CLR(((~3) & BM_CLKCTRL_HBUS_DIV));

    delay(10000);
    printf("start change cpu freq\r\n");

    value = HW_CLKCTRL_CPU_RD();
    value &= ~BM_CLKCTRL_CPU_DIV_CPU;
    value |= 1;
    HW_CLKCTRL_CPU_WR(value);

    HW_CLKCTRL_CLKSEQ_CLR(BM_CLKCTRL_CLKSEQ_BYPASS_CPU);

    printf("hbus 0x%x\r\n", HW_CLKCTRL_HBUS_RD());
    printf("cpu 0x%x\r\n", HW_CLKCTRL_CPU_RD());
}
void poweron_vdda() {
    int value = HW_POWER_VDDACTRL_RD();
    value &= ~BM_POWER_VDDACTRL_TRG;
    value |= BF_POWER_VDDACTRL_TRG(0xC);
    value &= ~BM_POWER_VDDACTRL_BO_OFFSET;
    value |= BF_POWER_VDDACTRL_BO_OFFSET(6);
    value &= ~BM_POWER_VDDACTRL_LINREG_OFFSET;
    value |= BF_POWER_VDDACTRL_LINREG_OFFSET(2);

    HW_POWER_VDDACTRL_WR(value);
}

typedef int (*pfun)(int);
int testDDRcode(int i) {
    //	printf("I am run in DDR2\r\n");
    //	printf("myaddr=0x%x\r\n",testDDRcode);
    return i;
}

void DDR2_Setup(int i) {
    unsigned int value;

    value = HW_DRAM_CTL16_RD();
    value &= ~BM_DRAM_CTL16_START;
    HW_DRAM_CTL16_WR(value);
#if 0
#ifdef MEM_MDDR
	Init_mddr_200MHz();
	printf("memory type is mDDR\n");
#else
//	DEBUGE_PRINT();
#if EasyARM 
	DDR2EmiController_EDE1116_200MHz();
#else
	intDDR2((unsigned int*) HW_DRAM_CTL00_ADDR);
#endif
	printf("memory type is DDR2\n");
#endif
#endif
    DDR2EmiController_EDE1116_200MHz(i); // 64M DDRAM

    value = HW_DRAM_CTL17_RD();
    value &= ~BM_DRAM_CTL17_SREFRESH;
    HW_DRAM_CTL17_WR(value);

    value = HW_DRAM_CTL16_RD();
    value |= BM_DRAM_CTL16_START;
    HW_DRAM_CTL16_WR(value);

    // Wait for DDR ready
    printf("Wait for ddr ready 1");
    while (!(HW_DRAM_CTL58_RD() & 0x100000))
        ;
}

// modified by luozhizhuo for DDR2 BSP

static void *memcpy(void *s1, const void *s2, int n) {
    char *dst = s1;
    const char *src = s2;

    while (n-- > 0)
        *dst++ = *src++;

    return s1;
}

uint16_t UpdateCRC16(uint16_t crcIn, uint8_t byte) {
    uint32_t crc = crcIn;
    uint32_t in = byte | 0x100;
    do {
        crc <<= 1;
        in <<= 1;
        if (in & 0x100)
            ++crc;
        if (crc & 0x10000)
            crc ^= 0x1021;
    } while (!(in & 0x10000));
    return crc & 0xffffu;
}

uint16_t Cal_CRC16(const char *data, int size) {
    int crc = 0;
    const char *dataEnd = data + size;
    while (data < dataEnd)
        crc = UpdateCRC16(crc, *data++);

    crc = UpdateCRC16(crc, 0);
    crc = UpdateCRC16(crc, 0);
    return crc & 0xffffu;
}

void saveddr2information(int index) {
    char *pMemlocation = (char *)EMI_MAX_MEM_BK;
    int i;
    uint16_t crc;

    for (i = 0; i < 2; i++) {
        memcpy(pMemlocation, &ddr2_array[index], ddr2_array[index].length + 2);
        crc = Cal_CRC16(pMemlocation, ddr2_array[index].length + 2);
        pMemlocation += ddr2_array[index].length + 2;
        *pMemlocation++ = crc >> 8;
        *pMemlocation++ = crc & 0xff;
        pMemlocation = (char *)EMI_MAX_MEM_BK_ANOTHER;
    }
    // printf("crc value:%d\r\n",crc);
}
void DDR2Enumeration(void) {
    volatile int *pTest;
    int count, testdata;
    int i, index;
    int checkfail = 0;

    testdata = 0;
    //每个Bank写入20字节数据来测试 DDR2
    pTest = (volatile int *)EMI_EACH_BANK_OFFSET(7);
    for (i = 0; i < EMI_MAX_FILL_COUNT; i++)
        *pTest++ = i;

    checkfail = 0;
    pTest = (volatile int *)EMI_EACH_BANK_OFFSET(7);
    for (i = 0; i < EMI_MAX_FILL_COUNT; i++) {
        if (*pTest != i) {
            checkfail = 1;
            break;
        }
        pTest++;
    }
    if (0 == checkfail) {
        printf("bank count is 8\r\n");
        /*
         *pMemlocation++  = '1';
         *pMemlocation++  = '2';
         *pMemlocation++  = '8';
         *pMemlocation++  = 'M';
         *pMemlocation++  = '\0';*/

    } else {
        DDR2_Setup(0);
        printf("bank count is 4\r\n");
        /*
         *pMemlocation++  = '6';
         *pMemlocation++  = '4';
         *pMemlocation++  = 'M';
         *pMemlocation++  = '\0';*/
    }
    saveddr2information(checkfail);
}

extern void intDDR2(unsigned int *);
#define EasyARM 0
int _start(int arg) {
    unsigned int value;
    volatile int *pTest = 0x40000000;
    unsigned int i, j;

    // boot rom wrong use debug uart port.
    // If fuse burned, the below two line can be removed.
#if 0
	HW_PINCTRL_MUXSEL7_CLR(0xF);
	HW_PINCTRL_MUXSEL7_SET(0xA);
#endif
    HW_PINCTRL_MUXSEL6_CLR(0xF0);
    HW_PINCTRL_MUXSEL6_SET(0xA0);

    // printf("start bootlets\r\n");
    // printf("_start addr =%x\r\n",(unsigned int)_start);
    /* Boot ROM set BANK3_PIN24 as debug uart rx.
     * which cause uboot can't input
     */
    HW_PINCTRL_MUXSEL7_SET(0x30000);

#if 0
	/* disable I/D cache */
	mmu_disable_dcache();
	mmu_disable_icache();
	mmu_disable();
	mmu_invalidate_tlb();
#endif

#ifdef MEM_MDDR
    /* set to mddr mode*/
    HW_PINCTRL_EMI_DS_CTRL_CLR(BW_PINCTRL_EMI_DS_CTRL_DDR_MODE(0x3));
#else
    /* set to ddr2 mode*/
    HW_PINCTRL_EMI_DS_CTRL_SET(BW_PINCTRL_EMI_DS_CTRL_DDR_MODE(0x3));
#endif
    printf(__DATE__ __TIME__);
    printf("\r\n");
    /*printf("Fuse 0x%x\r\n",HW_OCOTP_CUSTCAP_RD());*/

    poweron_pll();
    delay(11000);

    init_emi_pin(0, PIN_DRIVE_12mA);

    init_clock();

    delay(10000);

    poweron_vdda();

#if 0 // modified by luozhizhuo for ddr bsp
	value = HW_DRAM_CTL16_RD();
	value &= ~BM_DRAM_CTL16_START;
	HW_DRAM_CTL16_WR(value);
#if 0
#ifdef MEM_MDDR
	Init_mddr_200MHz();
	printf("memory type is mDDR\n");
#else
//	DEBUGE_PRINT();
#if EasyARM 
	DDR2EmiController_EDE1116_200MHz();
#else
	intDDR2((unsigned int*) HW_DRAM_CTL00_ADDR);
#endif
	printf("memory type is DDR2\n");
#endif
#endif
	DDR2EmiController_EDE1116_200MHz();	//64M DDRAM

	value = HW_DRAM_CTL17_RD();
	value &= ~BM_DRAM_CTL17_SREFRESH;
	HW_DRAM_CTL17_WR(value);

	value = HW_DRAM_CTL16_RD();
	value |= BM_DRAM_CTL16_START;
	HW_DRAM_CTL16_WR(value);

	//Wait for DDR ready
	printf("Wait for ddr ready 1");
	while(!(HW_DRAM_CTL58_RD()&0x100000));
#else
    DDR2_Setup(1);
    DDR2Enumeration(); // modified by luozhizhuo for DDR2 BSP
#endif // end modify
#if 0
	exit_selfrefresh();

	set_port_priority();

	entry_auto_clock_gate();
#endif

    change_cpu_freq();

#if 0
	for (i = 0; i <= 40; i++) {
		printf("mem %x - 0x%x\r\n",
			i, *(volatile int*)(0x800E0000 + i * 4));
	}
#endif
#define DDRTESTADDR 0x40ffff00 // 0x42000000
    unsigned int flag = 0, testdata = 0x0, testsize = 0x100;
    char *pdata0 = (char *)testDDRcode;
    char *pdata1 = pdata0;
    pTest = (volatile int *)DDRTESTADDR;
    /*Test Memory;*/
    printf("start test memory accress\r\n");
    printf("ddr2 0x%x\r\n", pTest);
    for (i = testdata; i < testdata + testsize; i++) {
        //              printf("0x%x;\r\n", pTest);
        *pTest++ = *pdata0++;
    }

    pTest = (volatile int *)DDRTESTADDR;

    for (i = testdata; i < testdata + testsize; i++) {
        if (*pTest != (*pdata1)) {
            flag = 1;
            printf("0x%x error value 0x%x\r\n", *pdata1, *pTest);
        }
        pdata1++;
        pTest++;
    }
    printf("finish simple test\r\n");

    if (flag) {
        printf("&&&&&&&ddr2 read write failed\r\n");
    } else {
        printf("******ddr2 read write success!\r\n");
    }
    printf("finish simple test\r\n");

#define DEBUG_BOOTLETS 0
#if DEBUG_BOOTLETS
    i = 10;
    while (i--) {
        printf("test %x\r\n", i--);
        delay(500000);
    }
#endif
    printf("finish boot prep,start to run ...\r\n");

    /* modefy by zhuguojun 283 287 的蜂鸣器 */
    HW_PINCTRL_MUXSEL3_SET(3 << 10);
    HW_PINCTRL_DOE1_SET(1 << 21);

    for (i = 0; i < 100; i++) {
        HW_PINCTRL_DOUT1_SET(1 << 21);
        delay(500);
        HW_PINCTRL_DOUT1_CLR(1 << 21);
        delay(50);
    }

    /* modefy by zhuguojun 在280是用了GPIO2_6用蜂鸣器 */
    HW_PINCTRL_MUXSEL3_SET(3 << 12);
    HW_PINCTRL_DOE2_SET(1 << 6);
    for (i = 0; i < 100; i++) {
        HW_PINCTRL_DOUT2_SET(1 << 6);
        delay(500);
        HW_PINCTRL_DOUT2_CLR(1 << 6);
        delay(50);
    }

    //	printf("testDDRcode=%d\r\n",testDDRcode(1));

    return 0;
}

/* kiss gcc's ass to make it happy */
void __aeabi_unwind_cpp_pr0() {}
void __aeabi_unwind_cpp_pr1() {}
