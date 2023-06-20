#ifndef __FLASH_DEF_H__
#define __FLASH_DEF_H__

#define FLASH_APP_END         0x1e000

#define EEPROM_BOOT_FLAG_ADDR 0xfff

extern void flash_erase(unsigned long addr);
extern char flash_program(unsigned long addr, char* buf, unsigned len);
extern void flash_read(unsigned long addr, char* buf, unsigned len);

#endif /* !__FLASH_DEF_H__ */
