// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (C) 2021 Shanghai StarFive Technology Co., Ltd.
 * YanHong  Wang <yanhong.wang@starfivetech.com>
 */


#ifndef _STARFIVE_EVB_H
#define _STARFIVE_EVB_H

#include <version.h>
#include <linux/sizes.h>

#ifdef CONFIG_SPL

#define CONFIG_SPL_MAX_SIZE		0x00040000
#define CONFIG_SPL_BSS_START_ADDR	0x08040000
#define CONFIG_SPL_BSS_MAX_SIZE		0x00010000
#define CONFIG_SYS_SPL_MALLOC_START	(0x80000000)
#define CONFIG_SYS_SPL_MALLOC_SIZE	0x00800000

#define CONFIG_SPL_STACK	(0x08000000 + 0x00180000 -	\
				 GENERATED_GBL_DATA_SIZE)

#define STARFIVE_SPL_BOOT_LOAD_ADDR 0xa0000000
#endif


#define CONFIG_SYS_CACHELINE_SIZE 64

/*
 * Miscellaneous configurable options
 */
#define CONFIG_SYS_CBSIZE	1024	/* Console I/O Buffer Size */
#define CONFIG_SYS_BOOTM_LEN (32 << 20) /* 32MB */

/*
 * Print Buffer Size
 */
#define CONFIG_SYS_PBSIZE					\
	(CONFIG_SYS_CBSIZE + sizeof(CONFIG_SYS_PROMPT) + 16)

/*
 * max number of command args
 */
#define CONFIG_SYS_MAXARGS	16

/*
 * Boot Argument Buffer Size
 */
#define CONFIG_SYS_BARGSIZE	CONFIG_SYS_CBSIZE

/*
 * Size of malloc() pool
 * 512kB is suggested, (CONFIG_ENV_SIZE + 128 * 1024) was not enough
 */
#define CONFIG_SYS_MALLOC_LEN		SZ_8M

#define CONFIG_NR_DRAM_BANKS	1

#define PHYS_SDRAM_0		0x40000000	/* SDRAM Bank #1 */
#define PHYS_SDRAM_0_SIZE	0x100000000	/* 8 GB */

#define CONFIG_SYS_SDRAM_BASE	(PHYS_SDRAM_0)


/* Init Stack Pointer */
#define CONFIG_SYS_INIT_SP_ADDR		(CONFIG_SYS_SDRAM_BASE + SZ_2M)

#define CONFIG_SYS_LOAD_ADDR		(CONFIG_SYS_SDRAM_BASE + SZ_16M)
#define CONFIG_STANDALONE_LOAD_ADDR	0x41000000

#define CONFIG_SYS_PCI_64BIT		/* enable 64-bit PCI resources */

/*
 * Ethernet
 */
#ifdef CONFIG_CMD_NET
#define CONFIG_DW_ALTDESCRIPTOR
#define DWC_NET_PHYADDR		0
#define CONFIG_ARP_TIMEOUT	500
#define PHY_ANEG_TIMEOUT	8000 /* PHY needs longer aneg time */
#define CONFIG_NETMASK		255.255.255.0
#define CONFIG_IPADDR		192.168.120.230
#define CONFIG_IP_DEFRAG
#ifndef CONFIG_NET_MAXDEFRAG
#define CONFIG_NET_MAXDEFRAG	16384
#endif
#endif

/* HACK these should have '#if defined (stuff) around them like zynqp*/
#define BOOT_TARGET_DEVICES(func) func(DHCP, dhcp, na)	func(MMC, mmc, 0)

#include <config_distro_bootcmd.h>


#include <environment/distro/sf.h>

#define TYPE_GUID_LOADER1	"5B193300-FC78-40CD-8002-E86C45580B47"
#define TYPE_GUID_LOADER2	"2E54B353-1271-4842-806F-E436D6AF6985"
#define TYPE_GUID_SYSTEM	"0FC63DAF-8483-4772-8E79-3D69D8477DE4"

#define CPU_VOL_1020_SET \
	"cpu_vol_1020_set=" 			\
	"fdt set /opp-table-0/opp-1500000000 opp-microvolt <1020000>;\0"

#define CPU_VOL_1040_SET \
	"cpu_vol_1040_set="			\
	"fdt set /opp-table-0/opp-1500000000 opp-microvolt <1040000>;\0"

#define CPU_VOL_1060_SET \
	"cpu_vol_1060_set="			\
	"fdt set /opp-table-0/opp-1500000000 opp-microvolt <1060000>;\0"

#define CPU_VOL_1080_SET \
	"cpu_vol_1080_set="			\
	"fdt set /opp-table-0/opp-1500000000 opp-microvolt <1080000>;\0"

#define CPU_VOL_1100_SET \
	"cpu_vol_1100_set=" 			\
	"fdt set /opp-table-0/opp-1500000000 opp-microvolt <1100000>;\0"

#define CPU_VOL_SET	\
	"cpu_vol_set="				\
	"if test ${cpu_max_vol} = 1100000; then "	\
		"run cpu_vol_1100_set;"			\
	"elif test ${cpu_max_vol} = 1080000; then "	\
		"run cpu_vol_1080_set;"			\
	"elif test ${cpu_max_vol} = 1060000; then "	\
		"run cpu_vol_1060_set;"			\
	"elif test ${cpu_max_vol} = 1020000; then "	\
		"run cpu_vol_1020_set;"			\
	"else "						\
		"run cpu_vol_1040_set;"			\
	"fi; \0"

#define CHIPA_GMAC_SET \
	"chipa_gmac_set="	\
	"fdt set /soc/ethernet@16030000/ethernet-phy@0 tx_inverted_10 <0x1>;"	\
	"fdt set /soc/ethernet@16030000/ethernet-phy@0 tx_inverted_100 <0x1>;"	\
	"fdt set /soc/ethernet@16030000/ethernet-phy@0 tx_inverted_1000 <0x1>;\0"

#define CHIPA_SET	\
	"chipa_set="				\
	"if test ${chip_vision} = B; then "	\
		"run chipa_gmac_set;"		\
	"fi; \0"				\
	"chipa_set_uboot="			\
	"fdt addr ${fdtcontroladdr};"		\
	"run chipa_set;\0"			\
	"chipa_set_linux="			\
	"fdt addr ${fdt_addr_r};"		\
	"run chipa_set;\0"

#define PARTS_DEFAULT							\
	"name=loader1,start=17K,size=1M,type=${type_guid_gpt_loader1};" \
	"name=loader2,size=4MB,type=${type_guid_gpt_loader2};"		\
	"name=system,size=-,bootable,type=${type_guid_gpt_system};"

#define CONFIG_EXTRA_ENV_SETTINGS			\
	"fdt_high=0xffffffffffffffff\0"			\
	"initrd_high=0xffffffffffffffff\0"		\
	"kernel_addr_r=0x40200000\0"			\
	"fdt_addr_r=0x46000000\0"			\
	"scriptaddr=0x43900000\0"			\
	"script_offset_f=0x1fff000\0"			\
	"script_size_f=0x1000\0"			\
	"pxefile_addr_r=0x45900000\0"			\
	"ramdisk_addr_r=0x46100000\0"			\
	CHIPA_GMAC_SET					\
	CHIPA_SET					\
	CPU_VOL_1020_SET				\
	CPU_VOL_1040_SET				\
	CPU_VOL_1060_SET				\
	CPU_VOL_1080_SET				\
	CPU_VOL_1100_SET				\
	CPU_VOL_SET					\
	"type_guid_gpt_loader1=" TYPE_GUID_LOADER1 "\0" \
	"type_guid_gpt_loader2=" TYPE_GUID_LOADER2 "\0" \
	"type_guid_gpt_system=" TYPE_GUID_SYSTEM "\0"	\
	"partitions=" PARTS_DEFAULT "\0"		\
	BOOTENV						\
	BOOTENV_SF

/*
 * memtest works on 1.9 MB in DRAM
 */
#define CONFIG_SYS_MEMTEST_START	PHYS_SDRAM_0
#define CONFIG_SYS_MEMTEST_END		(PHYS_SDRAM_0 + PHYS_SDRAM_0_SIZE)

#define CONFIG_SYS_BAUDRATE_TABLE {9600, 19200, 38400, 57600, 115200, 230400, 460800, 921600}
#define CONFIG_SYS_LOADS_BAUD_CHANGE 1		/* allow baudrate change */

/* 6.25MHz RTC clock, StarFive JH7110*/
#define CONFIG_SYS_HZ_CLOCK	4000000

#define __io

#define memset_io(c, v, l)	memset((c), (v), (l))
#define memcpy_fromio(a, c, l)	memcpy((a), (c), (l))
#define memcpy_toio(c, a, l)	memcpy((c), (a), (l))

#define CONFIG_VIDEO_BMP_LOGO
#define CONFIG_VIDEO_LOGO
#define CONFIG_BMP_16BPP
#define CONFIG_BMP_24BPP
#define CONFIG_BMP_32BPP

#endif /* _STARFIVE_EVB_H */

