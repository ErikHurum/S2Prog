#ifndef __FLASH_ASM_DE_FH__
#define __FLASH_ASM_DE_FH__

extern void do_spm (unsigned int adr, unsigned char function);
extern void write_lock_bits (unsigned char val);
extern unsigned int read_program_memory (unsigned int,unsigned char);
extern void fill_temp_buffer (unsigned int data,unsigned int adr);
extern void re_enable_RWW(void);
extern void CSEG_Write(void);

#endif /* !__FLASH_ASM_DE_FH__ */

