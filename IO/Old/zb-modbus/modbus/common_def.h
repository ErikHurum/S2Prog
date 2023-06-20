#ifndef COMMON_DEF_H__
#define COMMON_DEF_H__

#ifndef TRUE
#define TRUE  1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef HIGH
#define HIGH  1
#endif

#ifndef LOW
#define LOW   0
#endif

//
// IAR is one of the worst compiler!!!
//
typedef signed char int8_t;
typedef unsigned char uint8_t;
typedef signed int int16_t;
typedef unsigned int uint16_t;
typedef signed long int int32_t;
typedef unsigned long int uint32_t;
typedef signed long long int int64_t;
typedef unsigned long long int uint64_t;

#define COMMON_TYPES_DEFINED      1

#define _BV(bit)          (1 << (bit))

#endif /* !COMMON_DEF_H__ */
