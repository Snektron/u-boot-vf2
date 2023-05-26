// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (C) 2021 Shanghai StarFive Technology Co., Ltd.
 * YanHong  Wang <yanhong.wang@starfivetech.com>
 */


#ifndef _STARFIVE_VISIONFIVE2_H
#define _STARFIVE_VISIONFIVE2_H

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
#define CONFIG_ARP_TIMEOUT	500
#define CONFIG_NETMASK		255.255.255.0
#define CONFIG_IPADDR		192.168.120.230
#define CONFIG_IP_DEFRAG
#ifndef CONFIG_NET_MAXDEFRAG
#define CONFIG_NET_MAXDEFRAG	16384
#endif
#endif

/* HACK these should have '#if defined (stuff) around them like zynqp*/
#define BOOT_TARGET_DEVICES(func) \
    func(MMC, mmc, 1) \
    func(MMC, mmc, 0) \
    func(DHCP, dhcp, na)

#include <config_distro_bootcmd.h>


#include <environment/distro/sf.h>

#define CONFIG_EXTRA_ENV_SETTINGS		\
	"fdt_high=0xffffffffffffffff\0"		\
	"initrd_high=0xffffffffffffffff\0"	\
	"kernel_addr_r=0x40200000\0"		\
	"fdt_addr_r=0x46000000\0"			\
	"scriptaddr=0x43900000\0"			\
	"script_offset_f=0x1fff000\0"		\
	"script_size_f=0x1000\0"			\
	"pxefile_addr_r=0x45900000\0"		\
	"ramdisk_addr_r=0x46100000\0"		\
	BOOTENV								\

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

