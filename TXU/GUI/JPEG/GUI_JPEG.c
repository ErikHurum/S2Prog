/*********************************************************************
*                SEGGER MICROCONTROLLER SYSTEME GmbH                 *
*        Solutions for real time microcontroller applications        *
**********************************************************************
*                                                                    *
*        (c) 1996 - 2007  SEGGER Microcontroller Systeme GmbH        *
*                                                                    *
*        Internet: www.segger.com    Support:  support@segger.com    *
*                                                                    *
**********************************************************************

** emWin V4.14 - Graphical user interface for embedded applications **
emWin is protected by international copyright laws.   Knowledge of the
source code may not be used to write a similar product.  This file may
only be used in accordance with a license and should not be re-
distributed in any way. We appreciate your understanding and fairness.
----------------------------------------------------------------------
File        : GUI_JPEG.c
Purpose     : Implementation of GUI_JPEG... functions
---------------------------END-OF-HEADER------------------------------
*/

#include <stdlib.h>
#include <string.h>

#include "GUI_Private.h"
#include "GUI_JPEG_Private.h"

#if (GUI_SELECT_JPEG == 0)

/*********************************************************************
*
*       Configuration
*
**********************************************************************
*/
#ifndef   USE_LIMIT_TABLE
  #define USE_LIMIT_TABLE 1
#endif
#ifndef   TEST_BANDING
  #define TEST_BANDING 0
#endif

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#define MIN(a, b) (((a) < (b)) ? (a) : (b))

/* Buffer size of input buffer */
#define INPUT_BUF_SIZE 4096

/* Dequantization of a DPCM (Differential Pulse Code Modulation) value */
#define DEQUANT_DCPM(x, s) ((x) < _aExtendTest[s] ? (x) + _aExtendOffset[s] : (x))

/* Constants for IDCT */
#define CONST_BITS 13
#define PASS1_BITS  2

#define FIX_0_298631336 ((I32) 2446)
#define FIX_0_390180644 ((I32) 3196)
#define FIX_0_541196100 ((I32) 4433)
#define FIX_0_765366865 ((I32) 6270)
#define FIX_0_899976223 ((I32) 7373)
#define FIX_1_175875602 ((I32) 9633)
#define FIX_1_501321110 ((I32)12299)
#define FIX_1_847759065 ((I32)15137)
#define FIX_1_961570560 ((I32)16069)
#define FIX_2_053119869 ((I32)16819)
#define FIX_2_562915447 ((I32)20995)
#define FIX_3_072711026 ((I32)25172)

/* Macros for IDCT */
#define DESCALE(x, n)  (((x) + (((I32)1) << ((n) - 1))) >> (n))
#define MULTIPLY(v, c) ((v) * (c))

/* Macros for color conversion */
#if USE_LIMIT_TABLE
  #define LIMIT(x) _aLimit[x + 0x100] /* Limiting a value per table works much faster than calculating value by value */
#else
  #define LIMIT(v)    \
    if (v > 255) {    \
      v = 255;        \
    }                 \
    if (v & 0xFF00) { \
      v = 0;          \
    }
#endif

/*********************************************************************
*
*       Static (const) data
*
**********************************************************************
*/
#if USE_LIMIT_TABLE
/* Array for limiting color convertion values */
static const U8 _aLimit[] = {
/* Values in the range of 0xffffffff - 0xffffff00 */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* Values in the range of 0x00 - 0xff */
0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f,
0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f,
0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3a, 0x3b, 0x3c, 0x3d, 0x3e, 0x3f,
0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4a, 0x4b, 0x4c, 0x4d, 0x4e, 0x4f,
0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5a, 0x5b, 0x5c, 0x5d, 0x5e, 0x5f,
0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6a, 0x6b, 0x6c, 0x6d, 0x6e, 0x6f,
0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7a, 0x7b, 0x7c, 0x7d, 0x7e, 0x7f,
0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f,
0x90, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98, 0x99, 0x9a, 0x9b, 0x9c, 0x9d, 0x9e, 0x9f,
0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf,
0xb0, 0xb1, 0xb2, 0xb3, 0xb4, 0xb5, 0xb6, 0xb7, 0xb8, 0xb9, 0xba, 0xbb, 0xbc, 0xbd, 0xbe, 0xbf,
0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf,
0xd0, 0xd1, 0xd2, 0xd3, 0xd4, 0xd5, 0xd6, 0xd7, 0xd8, 0xd9, 0xda, 0xdb, 0xdc, 0xdd, 0xde, 0xdf,
0xe0, 0xe1, 0xe2, 0xe3, 0xe4, 0xe5, 0xe6, 0xe7, 0xe8, 0xe9, 0xea, 0xeb, 0xec, 0xed, 0xee, 0xef,
0xf0, 0xf1, 0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xf7, 0xf8, 0xf9, 0xfa, 0xfb, 0xfc, 0xfd, 0xfe, 0xff,
/* Values in the range of 0x100 - 0x1ff */
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
};
#endif

/* Decompression context */
GUI_JPEG_DCONTEXT GUI_JPEG__DContext;

/* Array contains the storage order of coefficients in input data stream */
static const U8 _aCoeffOrder[] = {
   0,  1,  8, 16,  9,  2,  3, 10,
  17, 24, 32, 25, 18, 11,  4,  5,
  12, 19, 26, 33, 40, 48, 41, 34,
  27, 20, 13,  6,  7, 14, 21, 28,
  35, 42, 49, 56, 57, 50, 43, 36,
  29, 22, 15, 23, 30, 37, 44, 51,
  58, 59, 52, 45, 38, 31, 39, 46,
  53, 60, 61, 54, 47, 55, 62, 63,
  63, 63, 63, 63, 63, 63, 63, 63,
  63, 63, 63, 63, 63, 63, 63, 63
};

/* Tables used for extending differential pulse code modulation (DPCM) values */
static const int _aExtendTest[16] = {
  0x0000, 0x0001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040,
  0x0080, 0x0100, 0x0200, 0x0400, 0x0800, 0x1000, 0x2000, 0x4000
};

static const int _aExtendOffset[16] = {
  0               , ((-1) <<  1) + 1, ((-1) <<  2) + 1, ((-1) <<  3) + 1,
  ((-1) <<  4) + 1, ((-1) <<  5) + 1, ((-1) <<  6) + 1, ((-1) <<  7) + 1,
  ((-1) <<  8) + 1, ((-1) <<  9) + 1, ((-1) << 10) + 1, ((-1) << 11) + 1,
  ((-1) << 12) + 1, ((-1) << 13) + 1, ((-1) << 14) + 1, ((-1) << 15) + 1
};

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
/*********************************************************************
*
*       _FillInputBuffer
*
* Purpuse:
*   Calls the 'GetData' function to fill the input buffer with new data.
*/
static int _FillInputBuffer(GUI_JPEG_DCONTEXT * pContext) {
  const U8 * pBuffer;
  int NumBytes;
  NumBytes = pContext->pfGetData(pContext->pParam, /* Void parameter passed to function */
                                 INPUT_BUF_SIZE,        /* Nummer of requested bytes */
                                 &pBuffer,              /* Pointer to data pointer. To be set by the function */
                                 pContext->StartOfFile);   /* Start flag */
  if (!NumBytes) {
    return 1;
  }
  pContext->NumBytesInBuffer = NumBytes;
  pContext->pBuffer          = pBuffer;
  pContext->StartOfFile      = 0;
  return 0;
}

/*********************************************************************
*
*       _GetU8
*
* Purpose:
*   Reads one byte from the input buffer or if stuffed bytes exist
*   from the stuff buffer. If the input buffer is empty, _FillInputBuffer
*   is called to fill up the buffer.
*/
static int _GetU8(GUI_JPEG_DCONTEXT * pContext, U8 * pByte) {/**/
  if (pContext->NumBytesInBuffer == 0) {
    _FillInputBuffer(pContext);
    if (pContext->NumBytesInBuffer == 0) {
      return 1;
    }
  }
  *pByte = *pContext->pBuffer++;
  pContext->NumBytesInBuffer--;
  return 0;
}

/*********************************************************************
*
*       _GetStuff
*
* Purpose:
*   Returns bytes that have been stuffed back into the input buffer.
*   After the last 'stuff'-byte has been returned, the function pointer
*   pContext->pfGetU8() will be set to _GetU8()
*/
static int _GetStuff(GUI_JPEG_DCONTEXT * pContext, U8 * pByte) {
  *pByte = pContext->aStuff[--pContext->NumBytesStuffed];
  if (pContext->NumBytesStuffed == 0) {
    pContext->pfGetU8 = _GetU8;
  }
  return 0;
}

/*********************************************************************
*
*       _StoreU8
*
* Purpose:
*   In some cases it is required to crop the already read data back into
*   the input buffer, which is done by this function. The function pointer
*   pContext->pfGetU8() will be set to _GetStuff()
*/
static int _StoreU8(GUI_JPEG_DCONTEXT * pContext, U8 Byte) {
  if (pContext->NumBytesStuffed == sizeof(pContext->aStuff)) {
    return 1;
  }
  pContext->aStuff[pContext->NumBytesStuffed++] = Byte;
  pContext->pfGetU8 = _GetStuff;
  return 0;
}

/*********************************************************************
*
*       _GetU16
*
* Purpose:
*   Reads 2 bytes from the input buffer and returns them as U16 value.
*/
static int _GetU16(GUI_JPEG_DCONTEXT * pContext, U16 * pValue) {
  U8 c0, c1;
  if (pContext->pfGetU8(pContext, &c0)) {
    return 1;
  }
  if (pContext->pfGetU8(pContext, &c1)) {
    return 1;
  }
  *pValue = (c0 << 8) | c1;
  return 0;
}

/*********************************************************************
*
*       _GetInt
*
* Purpose:
*   Reads 2 bytes from the input buffer and returns them as integer value.
*/
static int _GetInt(GUI_JPEG_DCONTEXT * pContext, int * pValue) {
  U8 c0, c1;
  if (pContext->pfGetU8(pContext, &c0)) {
    return 1;
  }
  if (pContext->pfGetU8(pContext, &c1)) {
    return 1;
  }
  *pValue = (c0 << 8) | c1;
  return 0;
}

/*********************************************************************
*
*       _GetU8_NoMarker
*
* Purpose:
*   Reads a byte from the input stream. In case of a marker has been
*   read, it returns 0xff.
*
*/
static int _GetU8_NoMarker(GUI_JPEG_DCONTEXT * pContext, U8 * pData) {
  U8 c;
  if (pContext->pfGetU8(pContext, &c)) {
    return 1;
  }
  if (c == 0xFF) {
    if (pContext->pfGetU8(pContext, &c)) {
      return 1;
    }
    if (c == 0x00) {
      *pData = 0xff;
      return 0;
    } else {
      _StoreU8(pContext, c);
      _StoreU8(pContext, 0xff);
      *pData = 0xff;
      return 0;
    }
  }
  *pData = c;
  return 0;
}

/*********************************************************************
*
*       _GetBitsNoMarker
*
* Purpose:
*   Returns the given number of bits from the bitbuffer. If the bitbuffer
*   does not contain enough bits it will be filled up.
*/
static unsigned _GetBitsNoMarker(GUI_JPEG_DCONTEXT * pContext, int NumBits) {
  unsigned Value;
  /* Take the upper bits from the lower word */
  Value = (pContext->BitBuffer >> (16 - NumBits)) & ((1 << NumBits) - 1);
  /* Fill up the buffer if it is empty */
  if ((pContext->NumBitsLeft -= NumBits) <= 0) {
    U8 c0, c1;
    /* Read 2 bytes */
    if (_GetU8_NoMarker(pContext, &c0)) {
      return 0xff;
    }
    if (_GetU8_NoMarker(pContext, &c1)) {
      return 0xff;
    }
    /* Add the remaining number of bits */
    NumBits += pContext->NumBitsLeft;
    /* Empty the buffer */
    pContext->BitBuffer = ((pContext->BitBuffer << NumBits) | (pContext->BitBuffer >> (32 - NumBits)));
    /* Store the new bytes into the upper 16 bits of the buffer */
    pContext->BitBuffer = (pContext->BitBuffer & 0xFFFF) | (((U32)c0) << 24) | (((U32)c1) << 16);
    /* Adjust bitbuffer, so that next access reads the remaining bits */
    pContext->BitBuffer = ((pContext->BitBuffer << -(pContext->NumBitsLeft)) | (pContext->BitBuffer >> (32 + pContext->NumBitsLeft)));
    /* Increment number of bits */
    pContext->NumBitsLeft += 16;
  } else {
    /* Shift the upper bits into the lower bits of the bitbuffer */
    pContext->BitBuffer = ((pContext->BitBuffer << NumBits) | (pContext->BitBuffer >> (32 - NumBits)));
  }
  return Value;
}

/*********************************************************************
*
*       _InitBitBuffer
*/
static void _InitBitBuffer(GUI_JPEG_DCONTEXT * pContext) {
  pContext->NumBitsLeft = 16;
  _GetBitsNoMarker(pContext, 16);
  _GetBitsNoMarker(pContext, 16);
}

/*********************************************************************
*
*       _ReadFirstMarker
*
* Porpose:
*   Reads the first marker of the data stream. First marker has to be
*   a Start Of Image (SOI) marker
*/
static int _ReadFirstMarker(GUI_JPEG_DCONTEXT * pContext, U8 * pMarker) {
  U8 c0, c1;
  if (pContext->pfGetU8(pContext, &c0)) return 1;
  if (pContext->pfGetU8(pContext, &c1)) return 1;
  if ((c0 != 0xff) || (c1 != M_SOI)) return 1;
  *pMarker = c1;
  return 0;
}

/*********************************************************************
*
*       _ReadNextMarker
*
* Purpose:
*   Reads a marker whith respect of padding bytes
*/
static int _ReadNextMarker(GUI_JPEG_DCONTEXT * pContext, U8 * pMarker) {
  U8 c;
  while (1) {
    if (pContext->pfGetU8(pContext, &c)) return 1;
    /* Skip any non-FF bytes */
    while (c != 0xff) {
      if (pContext->pfGetU8(pContext, &c)) return 1;
    }
    /* This loop swallows any duplicate FF bytes. Extra FFs are legal. */
    do {
      if (pContext->pfGetU8(pContext, &c)) return 1;
    } while (c == 0xFF);
    if (c != 0) {
      break;	/* Found a valid marker, exit loop */
    }
  }
  *pMarker = c;
  return 0;
}

/*********************************************************************
*
*       _SkipInputData
*
* Purpose:
*   Skips the given number of bytes in the input buffer.
*/
static void _SkipInputData(GUI_JPEG_DCONTEXT * pContext, I32 Length) {
  if (Length > 0) {
    while (Length > (I32)pContext->NumBytesInBuffer) {
      Length -= pContext->NumBytesInBuffer;
      _FillInputBuffer(pContext);
    }
    pContext->pBuffer          += Length;
    pContext->NumBytesInBuffer -= Length;
  }
}

/*********************************************************************
*
*       _SkipVariable
*
* Purpose:
*   Skips a complete variable block which is preceeded by the number of
*   bytes in the block.
*/
static int _SkipVariable(GUI_JPEG_DCONTEXT * pContext) {
  int Length;
  if (_GetInt(pContext, &Length)) return 1;
  Length -= 2;
  _SkipInputData(pContext, Length);
  return 0;
}

/*********************************************************************
*
*       _GetDQT
*
* Purpose:
*   Reads the definition of a quantization table.
*/
static int _GetDQT(GUI_JPEG_DCONTEXT * pContext) {
  int Length;
  U8 n, Precision;
  U16 * pData;
  int i;
  if (_GetInt(pContext, &Length)) return 1;
  Length -= 2;
  while (Length > 0) {
    if (pContext->pfGetU8(pContext, &n)) return 1;
    Precision = n >> 4;
    n &= 0xf;
    /* Number of tables is limited to 4 */
    if (n >= GUI_COUNTOF(pContext->aaQuantTbl)) {
      return 1;
    }
    pData = &pContext->aaQuantTbl[n][0];
    pContext->apQuantTbl[n] = pData;
    for (i = 0; i < 64; i++) {
      U8  Byte;
      U16 Word;
      if (Precision) {
        if (_GetU16(pContext, &Word)) return 1;
        *(pData + _aCoeffOrder[i]) = Word;
      } else {
        if (pContext->pfGetU8(pContext, &Byte)) return 1;
        *(pData + i) = Byte;
      }
    }
    if (Precision) {
      Length -= 1 + (64 << 1);
    } else {
      Length -= 1 + 64;
    }
  }
  if (Length != 0) {
    return 1;
  }
  return 0;
}

/*********************************************************************
*
*       _GetSOF
*
* Purpose:
*   Read the start of frame (SOF) marker.
*/
static int _GetSOF(GUI_JPEG_DCONTEXT * pContext) {
  int Length, i;
  U8 Prec;
  if (_GetInt(pContext, &Length)) return 1;
  if (pContext->pfGetU8 (pContext, &Prec)) return 1;
  if (_GetU16(pContext, &pContext->ySize)) return 1;
  if (_GetU16(pContext, &pContext->xSize)) return 1;
  if (pContext->pfGetU8 (pContext, &pContext->NumCompsPerFrame)) return 1;
  Length -= 8;
  if ((pContext->ySize == 0) || (pContext->xSize == 0)) {
    return 1; /* Error: Empty image */
  }
  if (pContext->NumCompsPerFrame > MAX_COMPONENTS) {
    return 1; /* Error: Unsupported number of components */
  }
  if (Length != pContext->NumCompsPerFrame * 3) {
    return 1; /* Error: Bad length */
  }
  for (i = 0; i < pContext->NumCompsPerFrame; i++) {
    U8 c;
    if (pContext->pfGetU8 (pContext, &pContext->aCompId[i])) return 1;
    if (pContext->pfGetU8 (pContext, &c)) return 1;
    pContext->aCompHSamp[i] = c >> 4;
    pContext->aCompVSamp[i] = c & 0xf;
    if (pContext->pfGetU8 (pContext, &pContext->aCompQuant[i])) return 1;
  }
  return 0;
}

/*********************************************************************
*
*       _GetDHT
*
* Purpose:
*   Read the definition of a Huffman code table.
*/
static int _GetDHT(GUI_JPEG_DCONTEXT * pContext) {
  int Length, Cnt;
  if (_GetInt(pContext, &Length)) return 1;
  Length -= 2;
  while (Length > 16) {
    int i;
    U8 Index;
    U8 * pData;
    if (pContext->pfGetU8(pContext, &Index)) return 1;
    Index = (Index & 0x0f) + ((Index & 0x10) >> 4) * (MAX_HUFFTABLES >> 1);
    if (Index > MAX_HUFFTABLES) {
      return 1;
    }
    /* Read number of Huffman codes per bit size */
    pContext->aHuffNumTableAvail[Index] = 1;
    pData    = &pContext->aaHuffNum[Index][0];
    Cnt      = 0;
    *pData++ = 0;
    for (i = 1; i <= 16; i++) {
      U8 c;
      if (pContext->pfGetU8(pContext, &c)) return 1;
      *pData++ = c;
      Cnt += c;
    }
    Length -= 16 + 1; /* 16 numbers + index */
    if ((Cnt > 255) || (Cnt > Length)) {
      return 1;
    }
    /* Read Huffman codes */
    pData = &pContext->aaHuffVal[Index][0];
    for (i = 0; i < Cnt; i++) {
      if (pContext->pfGetU8(pContext, pData++)) return 1;
    }
    Length -= Cnt;
  }
  return 0;
}

/*********************************************************************
*
*       _GetSOS
*
* Purpose:
*   Reads a Start Of Scan (SOS) marker.
*/
static int _GetSOS(GUI_JPEG_DCONTEXT * pContext) {
  int Length, i;
  U8 n, c, SpectralStart, SpectralEnd;
  if (_GetInt(pContext, &Length)) return 1;
  if (pContext->pfGetU8(pContext, &n)) return 1;
  if ((Length != (n * 2 + 6)) || (n > MAX_COMPSINSCAN)) {
    return 1; /* Error: Bad length */
  }
  Length -= 3;
  pContext->NumCompsPerScan = n;
  for (i = 0; i < n; i++) {
    int j;
    U8 Id, Found;
    if (pContext->pfGetU8(pContext, &Id)) return 1;
    if (pContext->pfGetU8(pContext, &c))  return 1;
    Length -= 2;
    for (j = 0, Found = 0; j < pContext->NumCompsPerFrame; j++) {
      if (Id == pContext->aCompId[j]) {
        Found = 1;
        break;
      }
    }
    if (!Found) {
      return 1;
    }
    pContext->aCompList[i]  = j;
    pContext->aCompDC_Tab[j] = (c >> 4) & 0xf;
    pContext->aCompAC_Tab[j] = (c & 0xf) + (MAX_HUFFTABLES >> 1);
  }
  if (pContext->pfGetU8(pContext, &SpectralStart)) return 1;
  if (pContext->pfGetU8(pContext, &SpectralEnd)) return 1;
  if (pContext->pfGetU8(pContext, &c)) return 1;
  pContext->SuccessiveHigh = c >> 4;
  pContext->SuccessiveLow  = c & 0xf;
  if (pContext->IsProgressive) {
    pContext->SpectralStart = SpectralStart;
    pContext->SpectralEnd   = SpectralEnd;
  } else {
    pContext->SpectralStart = 0;
    pContext->SpectralEnd   = 63;
  }
  Length -= 3;
  _SkipInputData(pContext, Length);
  return 0;
}

/*********************************************************************
*
*       _GetDRI
*
* Purpose:
*   Reads a Define Restart Interval (DRI) marker.
*/
static int _GetDRI(GUI_JPEG_DCONTEXT * pContext) {
  int Length;
  if (_GetInt(pContext, &Length)) return 1;
  if (Length != 4) return 1; /* Error: Bad DRI length */
  if (_GetInt(pContext, &pContext->RestartInterval)) return 1;
  return 0;
}

/*********************************************************************
*
*       _ReadMarkers
*
* Purpose:
*   Read markers. Return if SOFx, EOI or SOS marker has been found.
*
* Parameter:
*   pContext - obvios
*   pMarker  - Pointer for returning the last marker.
*/
static int _ReadMarkers(GUI_JPEG_DCONTEXT * pContext, U8 * pMarker) {
  while (1) {
    /* Read marker to be processed */
    if (_ReadNextMarker(pContext, pMarker)) {
      return 1;
    }
    /* Process marker */
    switch (*pMarker) {
    case M_SOF0:
    case M_SOF1:
    case M_SOF2:
    case M_SOF3:
    case M_SOF5:
    case M_SOF6:
    case M_SOF7:
    case M_SOF9:
    case M_SOF10:
    case M_SOF11:
    case M_SOF13:
    case M_SOF14:
    case M_SOF15:
    case M_SOI:
    case M_EOI:
    case M_SOS:
      return 0; /* Return without error. Marker needs to be processed by the calling function */
    case M_DHT:
      /* Huffman table */
      if (_GetDHT(pContext)) {
        return 1;
      }
      break;
    case M_DAC:
      /* Arithmetic Coding Table */
      return 1; /* No arithmetic support */
    case M_DQT:
      /* Quantisation Table */
      if (_GetDQT(pContext)) {
        return 1;
      }
      break;
    case M_DRI:
      /* Restart Interval */
      if (_GetDRI(pContext)) {
        return 1;
      }
      break;
    case M_JPG:
    case M_RST0:
    case M_RST1:
    case M_RST2:
    case M_RST3:
    case M_RST4:
    case M_RST5:
    case M_RST6:
    case M_RST7:
    case M_TEM:
      return 1; /* Unexpected marker */
    default:    /* DNL, DHP, EXP, APPn, JPGn, COM, or RESn or APP0 */
      _SkipVariable(pContext);
    }
  }
}

/*********************************************************************
*
*       _HuffDecode
*
* Purpose:
*   Decodes a Huffman encoded symbol
*/
static int _HuffDecode(GUI_JPEG_DCONTEXT * pContext, HUFF_TABLE * pTable) {
  int Symbol;
  /* Check first 8-bits: do we have a complete symbol? */
  if ((Symbol = pTable->aLookUp[(pContext->BitBuffer >> 8) & 0xFF]) < 0) {
    /* Decode more bits, use a tree traversal to find symbol */
    _GetBitsNoMarker(pContext, 8);
    do {
      Symbol = pTable->aTree[~Symbol + (1 - _GetBitsNoMarker(pContext, 1))];
    } while (Symbol < 0);
  } else {
    _GetBitsNoMarker(pContext, pTable->aCodeSize[Symbol]);
  }
  return Symbol;
}

/*********************************************************************
*
*       _CalcMCUBlockOrder
*/
static void _CalcMCUBlockOrder(GUI_JPEG_DCONTEXT * pContext) {
  int ComponentNum, ComponentId, MaxHSamp, MaxVSamp;
  int aCompHBlocks[MAX_COMPONENTS];
  int aCompVBlocks[MAX_COMPONENTS];
  MaxHSamp = 0;
  MaxVSamp = 0;
  for (ComponentId = 0; ComponentId < pContext->NumCompsPerFrame; ComponentId++) {
    if (pContext->aCompHSamp[ComponentId] > MaxHSamp) {
      MaxHSamp = pContext->aCompHSamp[ComponentId];
    }
    if (pContext->aCompVSamp[ComponentId] > MaxVSamp) {
      MaxVSamp = pContext->aCompVSamp[ComponentId];
    }
  }
  for (ComponentId = 0; ComponentId < pContext->NumCompsPerFrame; ComponentId++) {
    aCompHBlocks[ComponentId] = ((((pContext->xSize * pContext->aCompHSamp[ComponentId]) + (MaxHSamp - 1)) / MaxHSamp) + 7) / 8;
    aCompVBlocks[ComponentId] = ((((pContext->ySize * pContext->aCompVSamp[ComponentId]) + (MaxVSamp - 1)) / MaxVSamp) + 7) / 8;
  }
  if (pContext->NumCompsPerScan == 1) {
    pContext->MCUsPerRow = aCompHBlocks[pContext->aCompList[0]];
    pContext->MCUsPerCol = aCompVBlocks[pContext->aCompList[0]];
  } else {
    pContext->MCUsPerRow = (((pContext->xSize + 7) / 8) + (MaxHSamp - 1)) / MaxHSamp;
    pContext->MCUsPerCol = (((pContext->ySize + 7) / 8) + (MaxVSamp - 1)) / MaxVSamp;
  }
  if (pContext->NumCompsPerScan == 1) {
    pContext->aMCU_Org[0] = pContext->aCompList[0];
    pContext->NumBlocksPerMCU = 1;
  } else {
    pContext->NumBlocksPerMCU = 0;
    for (ComponentNum = 0; ComponentNum < pContext->NumCompsPerScan; ComponentNum++) {
      int NumBlocks;
      ComponentId = pContext->aCompList[ComponentNum];
      NumBlocks = pContext->aCompHSamp[ComponentId] * pContext->aCompVSamp[ComponentId];
      while (NumBlocks--) {
        pContext->aMCU_Org[pContext->NumBlocksPerMCU++] = ComponentId;
      }
    }
  }
}

/*********************************************************************
*
*       _ProcessRestart
*
* Purpose:
*   Processes a restart marker
*/
static int _ProcessRestart(GUI_JPEG_DCONTEXT * pContext) {
  int i;
  U8 Byte;
  for (i = 2000; i; i--) {
    if (pContext->pfGetU8(pContext, &Byte)) return 1;
    if (Byte == 0xff) {
      break;
    }
  }
  if (i == 0) {
    return 1; /* Error: Marker not found */
  }
  for ( ; i > 0; i--) {
    if (pContext->pfGetU8(pContext, &Byte)) return 1;
    if (Byte != 0xff) {
      break;
    }
  }
  if (i == 0) {
    return 1; /* Error: Marker not found */
  }
  if (Byte != (pContext->NextRestartNum + M_RST0)) {
    return 1; /* Error: Unexpected marker */
  }
  GUI_MEMSET((U8 *)pContext->aLastDC_Val, 0, pContext->NumCompsPerFrame * sizeof(unsigned));
  pContext->EOB_Run = 0;
  pContext->RestartsLeft = pContext->RestartInterval;
  pContext->NextRestartNum = (pContext->NextRestartNum + 1) & 7;
  _InitBitBuffer(pContext);
  return 0;
}

/*********************************************************************
*
*       _CoeffBufferAlloc
*
* Purpose:
*   Allocates coefficient buffer for one complete frame of a progressive scan
*/
static int _CoeffBufferAlloc(GUI_JPEG_DCONTEXT * pContext, COEFF_BUFFER * pBuffer, int BufferIndex, int LenBlock) {
  pBuffer->NumBlocksX = pContext->MaxMCUsPerRow * pContext->aCompHSamp[BufferIndex];
  pBuffer->NumBlocksY = pContext->MaxMCUsPerCol * pContext->aCompVSamp[BufferIndex];
  pBuffer->BlockSize  = LenBlock * LenBlock * sizeof(I16);
  pBuffer->hData = GUI_ALLOC_AllocZero(pBuffer->BlockSize * pBuffer->NumBlocksX * pBuffer->NumBlocksY);
  if (pBuffer->hData == 0) {
    return 1;
  }
  return 0;
}

/*********************************************************************
*
*       _CoeffBufferAllocBanding
*
* Purpose:
*   Allocates coefficient buffer for one band of a progressive scan
*/
static int _CoeffBufferAllocBanding(GUI_JPEG_DCONTEXT * pContext, COEFF_BUFFER * pBuffer, int BufferIndex, int LenBlock) {
  pBuffer->NumBlocksX = pContext->MaxMCUsPerRow * pContext->aCompHSamp[BufferIndex];
  pBuffer->NumBlocksY = pContext->NumBlocksPerBand;
  pBuffer->BlockSize  = LenBlock * LenBlock * sizeof(I16);
  pBuffer->hData = GUI_ALLOC_AllocZero(pBuffer->BlockSize * pBuffer->NumBlocksX * pBuffer->NumBlocksY);
  if (pBuffer->hData == 0) {
    return 1;
  }
  return 0;
}

/*********************************************************************
*
*       _CoeffBufferGetP
*
* Purpose:
*   Returns the requested pointer of a coefficient buffer. Used for progressive scans only.
*/
static I16 * _CoeffBufferGetP(GUI_JPEG_DCONTEXT * pContext, int ComponentId, COEFF_BUFFER * pBuffer, int BlockX, int BlockY) {
  U8 * p;
  unsigned BlockSize;
  if (pContext->BandingRequired == 0) {
    if (pBuffer->NumBlocksX <= BlockX) {
      return NULL; /* Error */
    }
    if (pBuffer->NumBlocksY <= BlockY) {
      return NULL; /* Error */
    }
    BlockSize = pBuffer->BlockSize;
    p = (U8 *)GUI_ALLOC_h2p(pBuffer->hData);
    p += BlockX * BlockSize + BlockY * BlockSize * pBuffer->NumBlocksX;
    return (I16 *)p;
  } else {
    int FirstBlockOfBand;
    FirstBlockOfBand = pContext->aFirstBlockOfBand[ComponentId];
    if ((BlockY >= FirstBlockOfBand) && (BlockY <= (FirstBlockOfBand + pContext->NumBlocksPerBand - 1))) {
      BlockSize = pBuffer->BlockSize;
      p = (U8 *)GUI_ALLOC_h2p(pBuffer->hData);
      p += BlockX * BlockSize + (BlockY - FirstBlockOfBand) * BlockSize * pBuffer->NumBlocksX;
      return (I16 *)p;
    } else {
      return NULL;
    }
  }
}

/*********************************************************************
*
*       _DecodeBlockDC_First
*
* Purpose:
*   DC decoding in a progressive scan.
*/
static int _DecodeBlockDC_First(GUI_JPEG_DCONTEXT * pContext, int ComponentId, int BlockX, int BlockY) {
  int s;
  int r;
  I16 * p;
  p = _CoeffBufferGetP(pContext, ComponentId, &pContext->aDC_Coeffs[ComponentId], BlockX, BlockY);
  if (p == NULL) {
    return 1; /* Error */
  }
  s = _HuffDecode(pContext, &pContext->aHuffTable[pContext->aCompDC_Tab[ComponentId]]);
  if (s != 0) {
    r = _GetBitsNoMarker(pContext, s);
    s = DEQUANT_DCPM(r, s);
  }
  s += pContext->aLastDC_Val[ComponentId];
  pContext->aLastDC_Val[ComponentId] = s;
  *p = s << pContext->SuccessiveLow;
  return 0;
}

/*********************************************************************
*
*       _DecodeBlockDC_Refine
*
* Purpose:
*   DC refinement in a progressive scan.
*/
static int _DecodeBlockDC_Refine(GUI_JPEG_DCONTEXT * pContext, int ComponentId, int BlockX, int BlockY) {
  I16 * p;
  if (_GetBitsNoMarker(pContext, 1)) {
    p = _CoeffBufferGetP(pContext, ComponentId, &pContext->aDC_Coeffs[ComponentId], BlockX, BlockY);
    if (p == NULL) {
      return 1;
    }
    *p |= (1 << pContext->SuccessiveLow);
  }
  return 0;
}

/*********************************************************************
*
*       _DecodeBlockAC_First
*
* Purpose:
*   AC decoding in a progressive scan.
*/
static int _DecodeBlockAC_First(GUI_JPEG_DCONTEXT * pContext, int ComponentId, int BlockX, int BlockY) {
  int k;
  int s;
  int r;
  I16 * p;
  if (pContext->EOB_Run) {
    pContext->EOB_Run--;
    return 0;
  }
  p = _CoeffBufferGetP(pContext, ComponentId, &pContext->aAC_Coeffs[ComponentId], BlockX, BlockY);
  for (k = pContext->SpectralStart; k <= pContext->SpectralEnd; k++) {
    s = _HuffDecode(pContext, &pContext->aHuffTable[pContext->aCompAC_Tab[ComponentId]]);
    r = s >> 4;
    s &= 0xf;
    if (s) {
      if ((k += r) > 63) {
        return 1; /* Error */
      }
      r = _GetBitsNoMarker(pContext, s);
      s = DEQUANT_DCPM(r, s);
      *(p + _aCoeffOrder[k]) = s << pContext->SuccessiveLow;
    } else {
      if (r == 15) {
        if ((k += 15) > 63) {
          return 1; /* Error */
        }
      } else {
        pContext->EOB_Run = 1 << r;
        if (r) {
          pContext->EOB_Run += _GetBitsNoMarker(pContext, r);
        }
        pContext->EOB_Run--;
        break;
      }
    }
  }
  return 0;
}

/*********************************************************************
*
*       _DecodeBlockAC_Refine
*
* Purpose:
*   AC refinement in a progressive scan.
*/
static int _DecodeBlockAC_Refine(GUI_JPEG_DCONTEXT * pContext, int ComponentId, int BlockX, int BlockY) {
  int k;
  int s;
  int r;
  I16 * p;
  I16 * pCoeff;
  int p1;
  int m1;
  p1 = (+1) << pContext->SuccessiveLow;
  m1 = (-1) << pContext->SuccessiveLow;
  p = _CoeffBufferGetP(pContext, ComponentId, &pContext->aAC_Coeffs[ComponentId], BlockX, BlockY);
  k = pContext->SpectralStart;
  if (pContext->EOB_Run == 0) {
    for (; k < pContext->SpectralEnd; k++) {
      s = _HuffDecode(pContext, &pContext->aHuffTable[pContext->aCompAC_Tab[ComponentId]]);
      r = s >> 4;
      s &= 0xf;
      if (s) {
        if (s != 1) {
          return 1; /* Error */
        }
        if (_GetBitsNoMarker(pContext, 1)) {
          s = p1;
        } else {
          s = m1;
        }
      } else {
        if (r != 15) {
          pContext->EOB_Run = 1 << r;
          if (r) {
            pContext->EOB_Run += _GetBitsNoMarker(pContext, r);
          }
          break;
        }
      }
      do {
        pCoeff = p + _aCoeffOrder[k];
        if (*pCoeff) {
          if (_GetBitsNoMarker(pContext, 1)) {
            if ((*pCoeff & p1) == 0) {
              if (*pCoeff >= 0) {
                *pCoeff += p1;
              } else {
                *pCoeff += m1;
              }
            }
          }
        } else {
          if (--r) {
            break;
          }
        }
        k++;
      } while (k < pContext->SpectralEnd);
      if (s && (k < 64)) {
        *(p + _aCoeffOrder[k]) = s;
      }
    }
  }
  if (pContext->EOB_Run > 0) {
    for (; k < pContext->SpectralEnd; k++) {
      pCoeff = p + _aCoeffOrder[k];
      if (*pCoeff) {
        if (_GetBitsNoMarker(pContext, 1)) {
          if ((*pCoeff & p1) == 0) {
            if (*pCoeff >= 0) {
              *pCoeff += p1;
            } else {
              *pCoeff += m1;
            }
          }
        }
      }
    }
    pContext->EOB_Run--;
  }
  return 0;
}

/*********************************************************************
*
*       _DecodeBlockDC_FirstBanding
*
* Purpose:
*   DC decoding in a progressive scan.
*/
static int _DecodeBlockDC_FirstBanding(GUI_JPEG_DCONTEXT * pContext, int ComponentId, int BlockX, int BlockY) {
  int s;
  int r;
  I16 * p;
  p = _CoeffBufferGetP(pContext, ComponentId, &pContext->aDC_Coeffs[ComponentId], BlockX, BlockY);
  s = _HuffDecode(pContext, &pContext->aHuffTable[pContext->aCompDC_Tab[ComponentId]]);
  if (s != 0) {
    r = _GetBitsNoMarker(pContext, s);
    s = DEQUANT_DCPM(r, s);
  }
  s += pContext->aLastDC_Val[ComponentId];
  pContext->aLastDC_Val[ComponentId] = s;
  if (p) {
    *p = s << pContext->SuccessiveLow;
  }
  return 0;
}

/*********************************************************************
*
*       _DecodeBlockDC_RefineBanding
*
* Purpose:
*   DC refinement in a progressive scan.
*/
static int _DecodeBlockDC_RefineBanding(GUI_JPEG_DCONTEXT * pContext, int ComponentId, int BlockX, int BlockY) {
  I16 * p;
  if (_GetBitsNoMarker(pContext, 1)) {
    p = _CoeffBufferGetP(pContext, ComponentId, &pContext->aDC_Coeffs[ComponentId], BlockX, BlockY);
    if (p) {
      *p |= (1 << pContext->SuccessiveLow);
    }
  }
  return 0;
}

/*********************************************************************
*
*       _DecodeBlockAC_FirstBanding
*
* Purpose:
*   AC decoding in a progressive scan.
*/
static int _DecodeBlockAC_FirstBanding(GUI_JPEG_DCONTEXT * pContext, int ComponentId, int BlockX, int BlockY) {
  int k;
  int s;
  int r;
  I16 * p;
  if (pContext->EOB_Run) {
    pContext->EOB_Run--;
    return 0;
  }
  p = _CoeffBufferGetP(pContext, ComponentId, &pContext->aAC_Coeffs[ComponentId], BlockX, BlockY);
  for (k = pContext->SpectralStart; k <= pContext->SpectralEnd; k++) {
    s = _HuffDecode(pContext, &pContext->aHuffTable[pContext->aCompAC_Tab[ComponentId]]);
    r = s >> 4;
    s &= 0xf;
    if (s) {
      if ((k += r) > 63) {
        return 1; /* Error */
      }
      r = _GetBitsNoMarker(pContext, s);
      s = DEQUANT_DCPM(r, s);
      if (p) {
        *(p + _aCoeffOrder[k]) = s << pContext->SuccessiveLow;
      }
    } else {
      if (r == 15) {
        if ((k += 15) > 63) {
          return 1; /* Error */
        }
      } else {
        pContext->EOB_Run = 1 << r;
        if (r) {
          pContext->EOB_Run += _GetBitsNoMarker(pContext, r);
        }
        pContext->EOB_Run--;
        break;
      }
    }
  }
  return 0;
}

/*********************************************************************
*
*       _DecodeBlockAC_RefineBanding
*
* Purpose:
*   AC refinement in a progressive scan.
*/
static int _DecodeBlockAC_RefineBanding(GUI_JPEG_DCONTEXT * pContext, int ComponentId, int BlockX, int BlockY) {
  GUI_USE_PARA(pContext);
  GUI_USE_PARA(ComponentId);
  GUI_USE_PARA(BlockX);
  GUI_USE_PARA(BlockY);
  return 1; /* Does not work with banding... */
}

/*********************************************************************
*
*       _DecodeScanProg
*
* Purpose:
*   Does the complete coefficient decoding for one progressive scan.
*/
static int _DecodeScanProg(GUI_JPEG_DCONTEXT * pContext, int (* pfDecodeBlock)(GUI_JPEG_DCONTEXT * pContext, int ComponentId, int BlockX, int BlockY)) {
  int MCU_Row;
  int MCU_Col;
  int MCU_Block;
  int ComponentNumber;
  int ComponentId;
  int aBlockX_MCU[MAX_COMPONENTS];
  int aBlockY_MCU[MAX_COMPONENTS];
  int BlockX_MCU_Off;
  int BlockY_MCU_Off;
  int BlockX;
  int BlockY;
  GUI_MEMSET((U8 *)aBlockY_MCU, 0, sizeof(aBlockY_MCU));
  for (MCU_Col = 0; MCU_Col < pContext->MCUsPerCol; MCU_Col++) {
    GUI_MEMSET((U8 *)aBlockX_MCU, 0, sizeof(aBlockX_MCU));
    for (MCU_Row = 0; MCU_Row < pContext->MCUsPerRow; MCU_Row++) {
      BlockX_MCU_Off = BlockY_MCU_Off = 0;
      if ((pContext->RestartInterval) && (pContext->RestartsLeft == 0)) {
        _ProcessRestart(pContext);
      }
      for (MCU_Block = 0; MCU_Block < pContext->NumBlocksPerMCU; MCU_Block++) {
        ComponentId = pContext->aMCU_Org[MCU_Block];
        BlockX = aBlockX_MCU[ComponentId] + BlockX_MCU_Off;
        BlockY = aBlockY_MCU[ComponentId] + BlockY_MCU_Off;
        if (pfDecodeBlock(pContext, ComponentId, BlockX, BlockY)) {
          return 1;
        }
        if (pContext->NumCompsPerScan == 1) {
          aBlockX_MCU[ComponentId]++;
        } else {
          if (++BlockX_MCU_Off == pContext->aCompHSamp[ComponentId]) {
            BlockX_MCU_Off = 0;
            if (++BlockY_MCU_Off == pContext->aCompVSamp[ComponentId]) {
              BlockY_MCU_Off = 0;
              aBlockX_MCU[ComponentId] += pContext->aCompHSamp[ComponentId];
            }
          }
        }
      }
      pContext->RestartsLeft--;
    }
    if (pContext->NumCompsPerScan == 1) {
      aBlockY_MCU[pContext->aCompList[0]]++;
    } else {
      for (ComponentNumber = 0; ComponentNumber < pContext->NumCompsPerScan; ComponentNumber++) {
        ComponentId = pContext->aCompList[ComponentNumber];
        aBlockY_MCU[ComponentId] += pContext->aCompVSamp[ComponentId];
      }
    }
  }
  return 0;
}

/*********************************************************************
*
*       _CreateHuffmanTable
*
* Purpose:
*   Creates a huffmann table
*/
static void _CreateHuffmanTable(GUI_JPEG_DCONTEXT * pContext, int Index, HUFF_TABLE * pTable) {
  int p, i, l, Size;
  U8       aHuffSize[257];
  unsigned aHuffCode[257];
  unsigned Code;
  unsigned SubTree;
  int CodeSize;
  int Last_p;
  int NextFreeEntry;
  int CurrentEntry;
  p = 0;
  for (l = 1; l <= 16; l++) {
    for (i = 1; i <= pContext->aaHuffNum[Index][l]; i++) {
      aHuffSize[p++] = l;
    }
  }
  aHuffSize[p] = 0;
  Last_p       = p;
  Code         = 0;
  Size         = aHuffSize[0];
  p = 0;
  while (aHuffSize[p]) {
    while (aHuffSize[p] == Size) {
      aHuffCode[p++] = Code;
      Code++;
    }
    Code <<= 1;
    Size++;
  }
  GUI_MEMSET((U8 *)pTable->aLookUp,   0, sizeof(pTable->aLookUp));
  GUI_MEMSET((U8 *)pTable->aTree,     0, sizeof(pTable->aTree));
  GUI_MEMSET((U8 *)pTable->aCodeSize, 0, sizeof(pTable->aCodeSize));
  NextFreeEntry = -1;
  p = 0;
  while (p < Last_p) {
    i        = pContext->aaHuffVal[Index][p];
    Code     = aHuffCode[p];
    CodeSize = aHuffSize[p];
    pTable->aCodeSize[i] = CodeSize;
    if (CodeSize <= 8) {
      Code <<= (8 - CodeSize);
      for (l = 1 << (8 - CodeSize); l > 0; l--) {
        pTable->aLookUp[Code] = i;
        Code++;
      }
    } else {
      SubTree      = (Code >> (CodeSize - 8)) & 0xFF;
      CurrentEntry = pTable->aLookUp[SubTree];
      if (CurrentEntry == 0) {
        pTable->aLookUp[SubTree] = CurrentEntry = NextFreeEntry;
        NextFreeEntry -= 2;
      }
      Code <<= (16 - (CodeSize - 8));
      for (l = CodeSize; l > 9; l--) {
        if ((Code & 0x8000) == 0) {
          CurrentEntry--;
        }
        if (pTable->aTree[-CurrentEntry - 1] == 0) {
          pTable->aTree[-CurrentEntry - 1] = NextFreeEntry;
          CurrentEntry = NextFreeEntry;
          NextFreeEntry -= 2;
        } else {
          CurrentEntry = pTable->aTree[-CurrentEntry - 1];
        }
        Code <<= 1;
      }
      if ((Code & 0x8000) == 0) {
        CurrentEntry--;
      }
      pTable->aTree[-CurrentEntry - 1] = i;
    }
    p++;
  }
}

/*********************************************************************
*
*       _CheckHuffmanTables
*/
static int _CheckHuffmanTables(GUI_JPEG_DCONTEXT * pContext) {
  int i;
  for (i = 0; i < pContext->NumCompsPerScan; i++) {
    unsigned TableIndex;
    TableIndex = pContext->aCompList[i];
    if ((pContext->SpectralStart == 0) && (pContext->aHuffNumTableAvail[pContext->aCompDC_Tab[TableIndex]] == 0)) {
      return 1;
    }
    if ((pContext->SpectralEnd   >  0) && (pContext->aHuffNumTableAvail[pContext->aCompAC_Tab[TableIndex]] == 0)) {
      return 1;
    }
  }
  for (i = 0; i < MAX_HUFFTABLES; i++) {
    _CreateHuffmanTable(pContext, i, &pContext->aHuffTable[i]);
  }
  for (i = 0; i < pContext->NumBlocksPerMCU; i++) {
    int MCU_Org;
    U8  CompDC_Tab;
    MCU_Org    = pContext->aMCU_Org[i];
    CompDC_Tab = pContext->aCompDC_Tab[MCU_Org];
    pContext->apDC_Huff[i]   = &pContext->aHuffTable [MCU_Org];
    pContext->apAC_Huff[i]   = &pContext->aHuffTable [MCU_Org];
    pContext->apComponent[i] = &pContext->aLastDC_Val[CompDC_Tab];
  }
  return 0;
}

/*********************************************************************
*
*       _CheckQuantTables
*/
static int _CheckQuantTables(GUI_JPEG_DCONTEXT * pContext) {
  int i;
  for (i = 0; i < pContext->NumCompsPerScan; i++) {
    if (pContext->apQuantTbl[pContext->aCompQuant[pContext->aCompList[i]]] == NULL) {
      return 1;
    }
  }
  return 0;
}

/*********************************************************************
*
*       _InitScan
*/
static int _InitScan(GUI_JPEG_DCONTEXT * pContext) {
  U8 Marker;
  if (_ReadMarkers(pContext, &Marker)) {
    return 1;
  }
  if (Marker != M_SOS) {
    return 1;
  }
  if (_GetSOS(pContext)) {
    return 1;
  }
  _CalcMCUBlockOrder(pContext);
  if (_CheckHuffmanTables(pContext)) {
    return 1;
  }
  if (_CheckQuantTables(pContext)) {
    return 1;
  }
  GUI_MEMSET((U8 *)pContext->aLastDC_Val, 0, sizeof(pContext->aLastDC_Val));
  pContext->EOB_Run = 0;
  if (pContext->RestartInterval) {
    pContext->RestartsLeft   = pContext->RestartInterval;
    pContext->NextRestartNum = 0;
  }
  _InitBitBuffer(pContext);
  return 0;
}

/*********************************************************************
*
*       _CalcBanding
*
* Purpose:
*   Returns the number of required bands. If too less memory is available
*   for scanning the whole frame, the frame will be drawn band by band.
*   This routine calculates the number of required bands.
*/
static int _CalcBanding(GUI_JPEG_DCONTEXT * pContext) {
  int i;
  U32 MemSize;
  U32 RequiredBytes;

  RequiredBytes = 0;
  for (i = 0; i < pContext->NumCompsPerFrame; i++) {
    RequiredBytes += (64 + 1) * sizeof(I16) *
                     pContext->MaxMCUsPerRow * pContext->aCompHSamp[i] *
                     pContext->MaxMCUsPerCol * pContext->aCompVSamp[i];
  }
#if TEST_BANDING
  MemSize = RequiredBytes / 3;
#else
  MemSize = GUI_ALLOC_GetMaxSize();
#endif
  if (MemSize < RequiredBytes) {
    U32 RequiredBytes1;

    pContext->BandingRequired = 1;
    RequiredBytes1 = 0;
    for (i = 0; i < pContext->NumCompsPerFrame; i++) {
      RequiredBytes1 += (64 + 1) * sizeof(I16) * pContext->MaxMCUsPerRow * pContext->aCompHSamp[i];// * pContext->aCompVSamp[i];
    }
    pContext->NumBlocksPerBand = MemSize / RequiredBytes1;
    if (pContext->NumBlocksPerBand == 0) {
      return 1;
    }
    pContext->NumBands = (((pContext->ySize + 7) / 8) + pContext->NumBlocksPerBand - 1) / pContext->NumBlocksPerBand;
  }
  return 0;
}

/*********************************************************************
*
*       _DecodeProgressive
*
* Purpose:
*   Initializes a progressive scan. It also contains allocating of
*   the AC and DC coefficient buffers.
*/
static int _DecodeProgressive(GUI_JPEG_DCONTEXT * pContext) {
  int i;
  U8 NumCompsPerFrame;
  NumCompsPerFrame = pContext->NumCompsPerFrame;
  if (NumCompsPerFrame == 4) {
    return 1; /* Error: Unsupported color space */
  }
  for (i = 0; i < NumCompsPerFrame; i++) {
    if (_CoeffBufferAlloc(pContext, &pContext->aDC_Coeffs[i], i, 1)) {
      return 1;
    }
    if (_CoeffBufferAlloc(pContext, &pContext->aAC_Coeffs[i], i, 8)) {
      return 1;
    }
  }
  while (1) {
    int DC_OnlyScan;
    int RefinementScan;
    int (* pfDecodeBlock)(GUI_JPEG_DCONTEXT * pContext, int ComponentId, int BlockX, int BlockY);
    /* Initialize scan by reading the markers including the SOS marker */
    if (_InitScan(pContext)) {
      /* Break if there is nothing else to scan */
      break;
    }
    DC_OnlyScan    = (pContext->SpectralStart  ? 0 : 1);
    RefinementScan = (pContext->SuccessiveHigh ? 1 : 0);
    if (pContext->SpectralStart > pContext->SpectralEnd) {
      return 1; /* Error: Bad SOS spectral */
    }
    if (DC_OnlyScan) {
      if (pContext->SpectralEnd) {
        return 1; /* Error: Bad SOS spectral */
      }
    } else if (pContext->NumCompsPerScan != 1) {
      return 1; /* Error: Bad SOS spectral */
    }
    if (RefinementScan && (pContext->SuccessiveLow != pContext->SuccessiveHigh)) {
      return 1; /* Error: Bad SOS successive */
    }
    /* Set the right decoding routine */
    if (DC_OnlyScan) {
      if (RefinementScan) {
        pfDecodeBlock = _DecodeBlockDC_Refine;
      } else {
        pfDecodeBlock = _DecodeBlockDC_First;
      }
    } else {
      if (RefinementScan) {
        pfDecodeBlock = _DecodeBlockAC_Refine;
      } else {
        pfDecodeBlock = _DecodeBlockAC_First;
      }
    }
    /* Decode... */
    if (_DecodeScanProg(pContext, pfDecodeBlock)) {
      return 1;
    }
  }
  pContext->NumCompsPerScan = pContext->NumCompsPerFrame;
  for (i = 0; i < pContext->NumCompsPerScan; i++) {
    pContext->aCompList[i] = i;
  }
  _CalcMCUBlockOrder(pContext);
  return 0;
}

/*********************************************************************
*
*       _WritePixels
*
* Purpose:
*   Routine for drawing one line of decoded data.
*/
static void _WritePixels(int x0, int y0, GUI_JPEG_DCONTEXT * pContext, GUI_COLOR (* pfGetColor)(const U8 ** ppData, unsigned SkipCnt), tLCDDEV_Color2Index * pfColor2Index) {
  int xSize;
  const U8 * pData;
  
  GUI_USE_PARA(pfColor2Index);
  if (pContext->BufferIndex == 0) {
    pData = (U8 *)GUI_ALLOC_h2p(pContext->hScanLine0);
  } else {
    pData = (U8 *)GUI_ALLOC_h2p(pContext->hScanLine1);
  }
  xSize = pContext->xSize;
  while (xSize) {
    LCD_SetColor(pfGetColor(&pData, 1));
    LCD_DrawPixel(x0++, y0);
    xSize--;
  }
}

/*********************************************************************
*
*       _WritePixelsOptRGB
*
* Purpose:
*   Optimized routine for drawing one line of decoded RGB data.
*/
static void _WritePixelsOptRGB(int x0, int y0, GUI_JPEG_DCONTEXT * pContext, GUI_COLOR (* pfGetColor)(const U8 ** ppData, unsigned SkipCnt), tLCDDEV_Color2Index * pfColor2Index) {
  LCD_PIXELINDEX * p;
  LCD_PIXELINDEX * pSic;
  int xSize;
  LCD_COLOR * pColor;

  GUI_USE_PARA(pfGetColor);
  if (pContext->BufferIndex == 0) {
    pColor = (LCD_COLOR *)GUI_ALLOC_h2p(pContext->hScanLine0);
  } else {
    pColor = (LCD_COLOR *)GUI_ALLOC_h2p(pContext->hScanLine1);
  }
  xSize = pContext->xSize;
  if (pContext->hBmpLine) {
    p = (LCD_PIXELINDEX *)GUI_ALLOC_h2p(pContext->hBmpLine);
    pSic = p;
    do {
      LCD_COLOR Color;
      Color = *pColor++;
      *p++ = pfColor2Index(Color);
    } while (--xSize);
    LCD_DrawBitmap(x0, y0, pContext->xSize, 1, 1, 1, LCD_BITSPERPIXEL, pContext->xSize * sizeof(LCD_PIXELINDEX), (U8 *)pSic, NULL);
  }
}

/*********************************************************************
*
*       _InitFrame
*
* Purpose:
*   Initializes variables and does the memory allocation for decoding
*   a JPEG file.
*/
static int _InitFrame(GUI_JPEG_DCONTEXT * pContext) {
  int i, k;
  if (pContext->NumCompsPerFrame == 1) {
    pContext->ScanType        = GRAYSCALE;
    pContext->MaxBlocksPerMCU = 1;
    pContext->MaxMCU_xSize    = 8;
    pContext->MaxMCU_ySize    = 8;
  } else if (pContext->NumCompsPerFrame == 3) {
    if ((pContext->aCompHSamp[1] != 1) || (pContext->aCompVSamp[1] != 1) ||
        (pContext->aCompHSamp[2] != 1) || (pContext->aCompVSamp[2] != 1)) {
      return 1; /* Unsupported sampling factors */
    }
    if        ((pContext->aCompHSamp[0] == 1) && (pContext->aCompVSamp[0] == 1)) {
      pContext->ScanType        = YH1V1;
      pContext->MaxBlocksPerMCU = 3;
      pContext->MaxMCU_xSize    = 8;
      pContext->MaxMCU_ySize    = 8;
    } else if ((pContext->aCompHSamp[0] == 2) && (pContext->aCompVSamp[0] == 1)) {
      pContext->ScanType        = YH2V1;
      pContext->MaxBlocksPerMCU = 4;
      pContext->MaxMCU_xSize    = 16;
      pContext->MaxMCU_ySize    = 8;
    } else if ((pContext->aCompHSamp[0] == 1) && (pContext->aCompVSamp[0] == 2)) {
      pContext->ScanType        = YH1V2;
      pContext->MaxBlocksPerMCU = 4;
      pContext->MaxMCU_xSize    = 8;
      pContext->MaxMCU_ySize    = 16;
    } else if ((pContext->aCompHSamp[0] == 2) && (pContext->aCompVSamp[0] == 2)) {
      pContext->ScanType        = YH2V2;
      pContext->MaxBlocksPerMCU = 6;
      pContext->MaxMCU_xSize    = 16;
      pContext->MaxMCU_ySize    = 16;
    } else {
      return 1;
    }
  } else {
    return 1;
  }
  pContext->MaxMCUsPerRow  = (pContext->xSize + (pContext->MaxMCU_xSize - 1)) / pContext->MaxMCU_xSize;
  pContext->MaxMCUsPerCol  = (pContext->ySize + (pContext->MaxMCU_ySize - 1)) / pContext->MaxMCU_ySize;
  pContext->TotalLinesLeft = pContext->ySize;
  pContext->MCULinesLeft   = 0;
  /* Calculate number of destination bytes per pixel and scanline */
  if (pContext->ScanType == GRAYSCALE) {
    pContext->DestBytesPerPixel = 1;
  } else {
    pContext->DestBytesPerPixel = 4;
  }
  pContext->DestBytesPerScanline = ((pContext->xSize + 15) & 0xFFF0) * pContext->DestBytesPerPixel;
  /* Allocate scan line buffers */
  if ((pContext->hScanLine0 = GUI_ALLOC_AllocZero(pContext->DestBytesPerScanline)) == 0) return 1;
  if ((pContext->ScanType == YH1V2) || (pContext->ScanType == YH2V2)) {
    if ((pContext->hScanLine1 = GUI_ALLOC_AllocZero(pContext->DestBytesPerScanline)) == 0) return 1;
  }
  pContext->MaxBlocksPerRow = pContext->MaxMCUsPerRow * pContext->MaxBlocksPerMCU;
  if (pContext->MaxBlocksPerRow > MAX_BLOCKSPERROW) {
    return 1;
  }
  /* Allocate blocks for one row */
  for (i = 0; i < pContext->MaxBlocksPerRow; i++) {
    if ((pContext->ahBlocks[i] = GUI_ALLOC_AllocZero(64 * sizeof(U16) + 8)) == 0) return 1;
  }
  /* Allocate sample buffer */
  if ((pContext->hSampleBuf = GUI_ALLOC_AllocZero(pContext->MaxBlocksPerRow * 64 + 8)) == 0) return 1;
  /* Initialize YCbCr color conversion to RGB */
  for (i = 0; i <= 255; i++) {
		k = (i * 2) - 256;
    pContext->aCRR[i] = ( ((I32) ((1.40200 / 2) * (1L << 16) + 0.5))  * k + ((I32) 1 << (16 - 1))) >> 16;
    pContext->aCBB[i] = ( ((I32) ((1.77200 / 2) * (1L << 16) + 0.5))  * k + ((I32) 1 << (16 - 1))) >> 16;
    pContext->aCRG[i] = (-((I32) ((0.71414 / 2) * (1L << 16) + 0.5))) * k;
    pContext->aCBG[i] = (-((I32) ((0.34414 / 2) * (1L << 16) + 0.5))  * k + ((I32) 1 << (16 - 1))) >> 16;
  }
  for (i = 0; i < MAX_BLOCKSPERROW; i++) {
    pContext->aBlockMaxZagSet[i] = 64;
  }
  return 0;
}

/*********************************************************************
*
*       _IDCT
*
* Purpose:
*   Inverse Discrete Cosinus Transformation
*/
static void _IDCT(I16 * pSrc, U8 * pDst) {
  I32 tmp0,  tmp1,  tmp2,  tmp3;
  I32 tmp10, tmp11, tmp12, tmp13;
  I32 z1, z2, z3, z4, z5;
  I16 DC_Val;
  I16 * pData;
  int RowCtr;
  pData = pSrc;
  for (RowCtr = 8 - 1; RowCtr >= 0; RowCtr--) {
    if ((*(pData + 1) |
         *(pData + 2) |
         *(pData + 3) |
         *(pData + 4) |
         *(pData + 5) |
         *(pData + 6) |
         *(pData + 7)) == 0) {
      DC_Val = (I16)(*(pData + 0) << PASS1_BITS);
      *(pData + 0) = DC_Val;
      *(pData + 1) = DC_Val;
      *(pData + 2) = DC_Val;
      *(pData + 3) = DC_Val;
      *(pData + 4) = DC_Val;
      *(pData + 5) = DC_Val;
      *(pData + 6) = DC_Val;
      *(pData + 7) = DC_Val;
      pData += 8;       /* Move pointer to next row */
      continue;
    }
    z2 = (I32)*(pData + 2);
    z3 = (I32)*(pData + 6);
    z1 = MULTIPLY(z2 + z3, FIX_0_541196100);
    tmp2 = z1 + MULTIPLY(z3, - FIX_1_847759065);
    tmp3 = z1 + MULTIPLY(z2, FIX_0_765366865);
    z2 = (I32)*(pData + 0);
    z3 = (I32)*(pData + 4);
    tmp0 = (z2 + z3) << CONST_BITS;
    tmp1 = (z2 - z3) << CONST_BITS;
    tmp10 = tmp0 + tmp3;
    tmp13 = tmp0 - tmp3;
    tmp11 = tmp1 + tmp2;
    tmp12 = tmp1 - tmp2;
    tmp0 = (I32)*(pData + 7);
    tmp1 = (I32)*(pData + 5);
    tmp2 = (I32)*(pData + 3);
    tmp3 = (I32)*(pData + 1);
    z1 = tmp0 + tmp3;
    z2 = tmp1 + tmp2;
    z3 = tmp0 + tmp2;
    z4 = tmp1 + tmp3;
    z5 = MULTIPLY(z3 + z4, FIX_1_175875602);
    tmp0 = MULTIPLY(tmp0, FIX_0_298631336);
    tmp1 = MULTIPLY(tmp1, FIX_2_053119869);
    tmp2 = MULTIPLY(tmp2, FIX_3_072711026);
    tmp3 = MULTIPLY(tmp3, FIX_1_501321110);
    z1 = MULTIPLY(z1, - FIX_0_899976223);
    z2 = MULTIPLY(z2, - FIX_2_562915447);
    z3 = MULTIPLY(z3, - FIX_1_961570560);
    z4 = MULTIPLY(z4, - FIX_0_390180644);
    z3 += z5;
    z4 += z5;
    tmp0 += z1 + z3;
    tmp1 += z2 + z4;
    tmp2 += z2 + z3;
    tmp3 += z1 + z4;
    *(pData + 0) = (I16)DESCALE(tmp10 + tmp3, CONST_BITS - PASS1_BITS);
    *(pData + 7) = (I16)DESCALE(tmp10 - tmp3, CONST_BITS - PASS1_BITS);
    *(pData + 1) = (I16)DESCALE(tmp11 + tmp2, CONST_BITS - PASS1_BITS);
    *(pData + 6) = (I16)DESCALE(tmp11 - tmp2, CONST_BITS - PASS1_BITS);
    *(pData + 2) = (I16)DESCALE(tmp12 + tmp1, CONST_BITS - PASS1_BITS);
    *(pData + 5) = (I16)DESCALE(tmp12 - tmp1, CONST_BITS - PASS1_BITS);
    *(pData + 3) = (I16)DESCALE(tmp13 + tmp0, CONST_BITS - PASS1_BITS);
    *(pData + 4) = (I16)DESCALE(tmp13 - tmp0, CONST_BITS - PASS1_BITS);
    pData += 8;
  }
  pData = pSrc;
  for (RowCtr = 8 - 1; RowCtr >= 0; RowCtr--) {
    I16 i;
    if ((*(pData + 8 * 1) |
         *(pData + 8 * 2) |
         *(pData + 8 * 3) |
         *(pData + 8 * 4) |
         *(pData + 8 * 5) |
         *(pData + 8 * 6) |
         *(pData + 8 * 7)) == 0) {
      DC_Val = (I16)DESCALE((I32)*(pData + 0), PASS1_BITS + 3);
      if ((DC_Val += 128) < 0) {
        DC_Val = 0;
      } else if (DC_Val > 255) {
        DC_Val = 255;
      }
      *(pDst + 8 * 0) = (U8)DC_Val;
      *(pDst + 8 * 1) = (U8)DC_Val;
      *(pDst + 8 * 2) = (U8)DC_Val;
      *(pDst + 8 * 3) = (U8)DC_Val;
      *(pDst + 8 * 4) = (U8)DC_Val;
      *(pDst + 8 * 5) = (U8)DC_Val;
      *(pDst + 8 * 6) = (U8)DC_Val;
      *(pDst + 8 * 7) = (U8)DC_Val;
      pData++;
      pDst++;
      continue;
    }
    z2 = (I32)*(pData + 8 * 2);
    z3 = (I32)*(pData + 8 * 6);
    z1 = MULTIPLY(z2 + z3, FIX_0_541196100);
    tmp2 = z1 + MULTIPLY(z3, - FIX_1_847759065);
    tmp3 = z1 + MULTIPLY(z2, FIX_0_765366865);
    tmp0 = ((I32)*(pData + 8 * 0) + (I32)*(pData + 8 * 4)) << CONST_BITS;
    tmp1 = ((I32)*(pData + 8 * 0) - (I32)*(pData + 8 * 4)) << CONST_BITS;
    tmp10 = tmp0 + tmp3;
    tmp13 = tmp0 - tmp3;
    tmp11 = tmp1 + tmp2;
    tmp12 = tmp1 - tmp2;
    tmp0 = (I32)*(pData + 8 * 7);
    tmp1 = (I32)*(pData + 8 * 5);
    tmp2 = (I32)*(pData + 8 * 3);
    tmp3 = (I32)*(pData + 8 * 1);
    z1 = tmp0 + tmp3;
    z2 = tmp1 + tmp2;
    z3 = tmp0 + tmp2;
    z4 = tmp1 + tmp3;
    z5 = MULTIPLY(z3 + z4, FIX_1_175875602);
    tmp0 = MULTIPLY(tmp0, FIX_0_298631336);
    tmp1 = MULTIPLY(tmp1, FIX_2_053119869);
    tmp2 = MULTIPLY(tmp2, FIX_3_072711026);
    tmp3 = MULTIPLY(tmp3, FIX_1_501321110);
    z1 = MULTIPLY(z1, - FIX_0_899976223);
    z2 = MULTIPLY(z2, - FIX_2_562915447);
    z3 = MULTIPLY(z3, - FIX_1_961570560);
    z4 = MULTIPLY(z4, - FIX_0_390180644);
    z3 += z5;
    z4 += z5;
    tmp0 += z1 + z3;
    tmp1 += z2 + z4;
    tmp2 += z2 + z3;
    tmp3 += z1 + z4;
    i = (I16)DESCALE(tmp10 + tmp3, CONST_BITS + PASS1_BITS + 3) + 128;
    if (i & 0xFF00) {
      i = (((~i) >> 15) & 0xFF);
    }
    *(pDst + 8 * 0) = (U8)i;
    i = (I16)DESCALE(tmp10 - tmp3, CONST_BITS + PASS1_BITS + 3) + 128;
    if (i & 0xFF00) {
      i = (((~i) >> 15) & 0xFF);
    }
    *(pDst + 8 * 7) = (U8)i;
    i = (I16)DESCALE(tmp11 + tmp2, CONST_BITS + PASS1_BITS + 3) + 128;
    if (i & 0xFF00) {
      i = (((~i) >> 15) & 0xFF);
    }
    *(pDst + 8 * 1) = (U8)i;
    i = (I16)DESCALE(tmp11 - tmp2, CONST_BITS + PASS1_BITS + 3) + 128;
    if (i & 0xFF00) {
      i = (((~i) >> 15) & 0xFF);
    }
    *(pDst + 8 * 6) = (U8)i;
    i = (I16)DESCALE(tmp12 + tmp1, CONST_BITS + PASS1_BITS + 3) + 128;
    if (i & 0xFF00) {
      i = (((~i) >> 15) & 0xFF);
    }
    *(pDst + 8 * 2) = (U8)i;
    i = (I16)DESCALE(tmp12 - tmp1, CONST_BITS + PASS1_BITS + 3) + 128;
    if (i & 0xFF00) {
      i = (((~i) >> 15) & 0xFF);
    }
    *(pDst + 8 * 5) = (U8)i;
    i = (I16)DESCALE(tmp13 + tmp0, CONST_BITS + PASS1_BITS + 3) + 128;
    if (i & 0xFF00) {
      i = (((~i) >> 15) & 0xFF);
    }
    *(pDst + 8 * 3) = (U8)i;
    i = (I16)DESCALE(tmp13 - tmp0, CONST_BITS + PASS1_BITS + 3) + 128;
    if (i & 0xFF00) {
      i = (((~i) >> 15) & 0xFF);
    }
    *(pDst + 8 * 4) = (U8)i;
    pData++;
    pDst++;
  }
}

/*********************************************************************
*
*       _TransformRow
*
* Purpose:
*   Performs an IDCT over the entire row's coefficient buffer
*/
static int _TransformRow(GUI_JPEG_DCONTEXT * pContext) {
  int i;
  I16 aTemp[64];
  I16 * pSrc;
  U8  * pDest;
  pContext->pSampleBuf = (U8 *)GUI_ALLOC_h2p(pContext->hSampleBuf);
  pDest = pContext->pSampleBuf;
  for (i = 0; i < pContext->MaxBlocksPerRow; i++) {
    pSrc = (I16 *)GUI_ALLOC_h2p(pContext->ahBlocks[i]);
    if (!pSrc) {
      return 1;
    }
    GUI_MEMCPY(aTemp, pSrc, 64 * sizeof(I16));
    _IDCT(aTemp, pDest);
    pDest += 64;
  }
  return 0;
}

/*********************************************************************
*
*       _DecodeNextRow
*
* Purpose:
*   Decodes the next line of MCUs for baseline scans
*/
static int _DecodeNextRow(GUI_JPEG_DCONTEXT * pContext) {
  int MCU_Row;
  int RowBlock;
  RowBlock = 0;
  for (MCU_Row = 0; MCU_Row < pContext->MCUsPerRow; MCU_Row++) {
    int MCU_Block;
    if ((pContext->RestartInterval) && (pContext->RestartsLeft == 0)) {
      _ProcessRestart(pContext);
    }
    for (MCU_Block = 0; MCU_Block < pContext->NumBlocksPerMCU; MCU_Block++) {
      HUFF_TABLE * pTable;
      U16 * p;
      U16 * q;
      int ComponentId, r, s, PrevNumSet, k;
      ComponentId = pContext->aMCU_Org[MCU_Block];
      p = (U16 *)GUI_ALLOC_h2p(pContext->ahBlocks[RowBlock]);
      q = pContext->apQuantTbl[pContext->aCompQuant[ComponentId]];
      if ((s = _HuffDecode(pContext, &pContext->aHuffTable[pContext->aCompDC_Tab[ComponentId]])) != 0) {
        r = _GetBitsNoMarker(pContext, s);
        s = DEQUANT_DCPM(r, s);
      }
      s += pContext->aLastDC_Val[ComponentId];
      pContext->aLastDC_Val[ComponentId] = s;
      p[0] = s * q[0];
      PrevNumSet = pContext->aBlockMaxZagSet[RowBlock];
      pTable = &pContext->aHuffTable[pContext->aCompAC_Tab[ComponentId]];
      for (k = 1; k < 64; k++) {
        s = _HuffDecode(pContext, pTable);
        r = s >> 4;
        s &= 15;
        if (s) {
          if (r) {
            if ((k + r) > 63) {
              return 1;
            }
            if (k < PrevNumSet) {
              int n, kt;
              n = MIN(r, PrevNumSet - k);
              kt = k;
              while (n--) {
                p[_aCoeffOrder[kt++]] = 0;
              }
            }
            k += r;
          }
          r = _GetBitsNoMarker(pContext, s);
          s = DEQUANT_DCPM(r, s);
          p[_aCoeffOrder[k]] = s * q[k];
        } else {
          if (r == 15) {
            if ((k + 15) > 63) {
              return 1;
            }
            if (k < PrevNumSet) {
              int n, kt;
              n = MIN(16, PrevNumSet - k);
              kt = k;
              while (n--) {
                p[_aCoeffOrder[kt++]] = 0;
              }
            }
            k += 15;
          } else {
            break;
          }
        }
      }
      if (k < PrevNumSet) {
        int kt;
        kt = k;
        while (kt < PrevNumSet) {
          p[_aCoeffOrder[kt++]] = 0;
        }
      }
      pContext->aBlockMaxZagSet[RowBlock] = k;
      RowBlock++;
    }
    pContext->RestartsLeft--;
  }
  return 0;
}

/*********************************************************************
*
*       _LoadNextRow
*
* Purpose:
*   Loads the next row of already decoded MCUs for progressive scans
*/
static int _LoadNextRow(GUI_JPEG_DCONTEXT * pContext) {
  U16 * p;
  U16 * q;
  int MCU_Row;
  int MCU_Block;
  int RowBlock;
  int ComponentNumber;
  int ComponentId;
  int aBlockX_MCU[MAX_COMPONENTS];
  int BlockX_MCU_Off;
  int BlockY_MCU_Off;
  I16 * pDC;
  I16 * pAC;
  int i;
  int BlockX;
  int BlockY;
  RowBlock = 0;
  GUI_MEMSET((U8 *)aBlockX_MCU, 0, sizeof(aBlockX_MCU));
  for (MCU_Row = 0; MCU_Row < pContext->MCUsPerRow; MCU_Row++) {
    BlockX_MCU_Off = BlockY_MCU_Off = 0;
    for (MCU_Block = 0; MCU_Block < pContext->NumBlocksPerMCU; MCU_Block++) {
      ComponentId = pContext->aMCU_Org[MCU_Block];
      p = (U16 *)GUI_ALLOC_h2p(pContext->ahBlocks[RowBlock]);
      q = pContext->apQuantTbl[pContext->aCompQuant[ComponentId]];
      BlockX = aBlockX_MCU[ComponentId] + BlockX_MCU_Off;
      BlockY = pContext->aBlockY_MCU[ComponentId] + BlockY_MCU_Off;
      pDC = _CoeffBufferGetP(pContext, ComponentId, &pContext->aDC_Coeffs[ComponentId], BlockX, BlockY);
      pAC = _CoeffBufferGetP(pContext, ComponentId, &pContext->aAC_Coeffs[ComponentId], BlockX, BlockY);
      if (pDC) {
        *p = *pDC;
        GUI_MEMCPY((void *)(p + 1), (void *)(pAC + 1), 63 * sizeof(I16));
        for (i = 63; i > 0; i--) {
          if (*(p + _aCoeffOrder[i])) {
            break;
          }
        }
        for (; i >= 0; i--) {
          if (*(p + _aCoeffOrder[i])) {
            *(p + _aCoeffOrder[i]) *= *(q + i);
          }
        }
      }
      RowBlock++;
      if (pContext->NumCompsPerScan == 1) {
        aBlockX_MCU[ComponentId]++;
      } else {
        if (++BlockX_MCU_Off == pContext->aCompHSamp[ComponentId]) {
          BlockX_MCU_Off = 0;
          if (++BlockY_MCU_Off == pContext->aCompVSamp[ComponentId]) {
            BlockY_MCU_Off = 0;
            aBlockX_MCU[ComponentId] += pContext->aCompHSamp[ComponentId];
          }
        }
      }
    }
  }
  if (pContext->NumCompsPerScan == 1) {
    pContext->aBlockY_MCU[pContext->aCompList[0]]++;
  } else {
    for (ComponentNumber = 0; ComponentNumber < pContext->NumCompsPerScan; ComponentNumber++) {
      ComponentId = pContext->aCompList[ComponentNumber];
      pContext->aBlockY_MCU[ComponentId] += pContext->aCompVSamp[ComponentId];
    }
  }
  return 0;
}

/*********************************************************************
*
*       _ConvertH1V1
*
* Purpose:
*   YCbCr conversion to RGB.
*   Horizontal resolution 1 pixel, vertical resolution 1 pixel, 3 blocks per MCU
*/
static void _ConvertH1V1(GUI_JPEG_DCONTEXT * pContext) {
  int * pCRR;
  int * pCBB;
  I32 * pCRG;
  I32 * pCBG;
  int Row;
  int i;
  int j;
  U8 * pDst;
  U8 * pSrc;
  pCRR = pContext->aCRR;
  pCBB = pContext->aCBB;
  pCRG = pContext->aCRG;
  pCBG = pContext->aCBG;
  Row = pContext->MaxMCU_ySize - pContext->MCULinesLeft;
  pDst = (U8 *)GUI_ALLOC_h2p(pContext->hScanLine0);
  pSrc = pContext->pSampleBuf + Row * 8;
  for (i = pContext->MaxMCUsPerRow; i > 0; i--) {
    for (j = 0; j < 8; j ++) {
      int y;
      int cb;
      int cr;
#if (USE_LIMIT_TABLE == 0)
      int v;
#endif
      y =  *(pSrc + j);
      cb = *(pSrc + j + 64);
      cr = *(pSrc + j + 128);
#if USE_LIMIT_TABLE
      *(pDst + 0) = LIMIT(y + pCRR[cr]);
      *(pDst + 1) = LIMIT(y + ((pCRG[cr] + pCBG[cb]) >> 16));
      *(pDst + 2) = LIMIT(y + pCBB[cb]);
#else
      v = y + pCRR[cr];
      LIMIT(v);
      *(pDst + 0) = v;
      v = y + ((pCRG[cr] + pCBG[cb]) >> 16);
      LIMIT(v);
      *(pDst + 1) = v;
      v = y + pCBB[cb];
      LIMIT(v);
      *(pDst + 1) = v;
#endif
      pDst += 4;
    }
    pSrc += 64 * 3;
  }
}

/*********************************************************************
*
*       _ConvertH2V2
*
* Purpose:
*   YCbCr conversion to RGB.
*   Horizontal resolution 2 pixel, vertical resolution 2 pixel, 6 blocks per MCU
*/
static void _ConvertH2V2(GUI_JPEG_DCONTEXT * pContext) {
  int * pCRR;
  int * pCBB;
  I32 * pCRG;
  I32 * pCBG;
  int Row;
  int i;
  int l;
  int j;
  U8 * pDst_0;
  U8 * pDst_1;
  U8 * pY;
  U8 * pC;
  pCRR = pContext->aCRR;
  pCBB = pContext->aCBB;
  pCRG = pContext->aCRG;
  pCBG = pContext->aCBG;
  Row = pContext->MaxMCU_ySize - pContext->MCULinesLeft;
  pDst_0 = (U8 *)GUI_ALLOC_h2p(pContext->hScanLine0);
  pDst_1 = (U8 *)GUI_ALLOC_h2p(pContext->hScanLine1);
  if (Row < 8) {
    pY = pContext->pSampleBuf + Row * 8;
  } else {
    pY = pContext->pSampleBuf + 64 * 2 + (Row & 7) * 8;
  }
  pC = pContext->pSampleBuf + 64 * 4 + (Row >> 1) * 8;
  for (i = pContext->MaxMCUsPerRow; i > 0; i--) {
    for (l = 0; l < 2; l++) {
      for (j = 0; j < 8; j += 2) {
        int cb;
        int cr;
        int rc;
        int gc;
        int bc;
        int yy;
#if (USE_LIMIT_TABLE == 0)
        int v;
#endif
        cb = *(pC + 0);
        cr = *(pC + 64);
        rc = *(pCRR + cr);
        gc = (*(pCRG + cr) + *(pCBG + cb)) >> 16;
        bc = *(pCBB + cb);
        #ifdef _DEBUG
        if (gc > 511) {
          GUI_DEBUG_ERROROUT("GUI_JPEG: Illegal value!");
          return;
        }
        if (gc < -256) {
          GUI_DEBUG_ERROROUT("GUI_JPEG: Illegal value!");
          return;
        }
        #endif
#if USE_LIMIT_TABLE
        yy = *(pY + j);
        *(pDst_0 + 0) = LIMIT(yy + rc);
        *(pDst_0 + 1) = LIMIT(yy + gc);
        *(pDst_0 + 2) = LIMIT(yy + bc);
        yy = *(pY + j + 1);
        *(pDst_0 + 4) = LIMIT(yy + rc);
        *(pDst_0 + 5) = LIMIT(yy + gc);
        *(pDst_0 + 6) = LIMIT(yy + bc);
        yy = *(pY + j + 8);
        *(pDst_1 + 0) = LIMIT(yy + rc);
        *(pDst_1 + 1) = LIMIT(yy + gc);
        *(pDst_1 + 2) = LIMIT(yy + bc);
        yy = *(pY + j + 8 + 1);
        *(pDst_1 + 4) = LIMIT(yy + rc);
        *(pDst_1 + 5) = LIMIT(yy + gc);
        *(pDst_1 + 6) = LIMIT(yy + bc);
#else
        yy = *(pY + j);
        v = (yy + rc);
        LIMIT(v);
        *(pDst_0 + 0) = v;
        v = (yy + gc);
        LIMIT(v);
        *(pDst_0 + 1) = v;
        v = (yy + bc);
        LIMIT(v);
        *(pDst_0 + 2) = v;

        yy = *(pY + j + 1);
        v = (yy + rc);
        LIMIT(v);
        *(pDst_0 + 4) = v;
        v = (yy + gc);
        LIMIT(v);
        *(pDst_0 + 5) = v;
        v = (yy + bc);
        LIMIT(v);
        *(pDst_0 + 6) = v;

        yy = *(pY + j + 8);
        v = (yy + rc);
        LIMIT(v);
        *(pDst_1 + 0) = v;
        v = (yy + gc);
        LIMIT(v);
        *(pDst_1 + 1) = v;
        v = (yy + bc);
        LIMIT(v);
        *(pDst_1 + 2) = v;

        yy = *(pY + j + 8 + 1);
        v = (yy + rc);
        LIMIT(v);
        *(pDst_1 + 4) = v;
        v = (yy + gc);
        LIMIT(v);
        *(pDst_1 + 5) = v;
        v = (yy + bc);
        LIMIT(v);
        *(pDst_1 + 6) = v;
#endif
        pDst_0 += 8;
        pDst_1 += 8;
        pC++;
      }
      pY += 64;
    }
    pY += 64 * 6 - 64 * 2;
    pC += 64 * 6 - 8;
  }
}

/*********************************************************************
*
*       _ConvertH2V1
*
* Purpose:
*   YCbCr conversion to RGB.
*   Horizontal resolution 2 pixel, vertical resolution 1 pixel, 4 blocks per MCU
*/
static void _ConvertH2V1(GUI_JPEG_DCONTEXT * pContext) {
  int * pCRR;
  int * pCBB;
  I32 * pCRG;
  I32 * pCBG;
  int Row;
  int i;
  int l;
  int j;
  U8 * pDst;
  U8 * pY;
  U8 * pC;
  pCRR = pContext->aCRR;
  pCBB = pContext->aCBB;
  pCRG = pContext->aCRG;
  pCBG = pContext->aCBG;
  Row = pContext->MaxMCU_ySize - pContext->MCULinesLeft;
  pDst = (U8 *)GUI_ALLOC_h2p(pContext->hScanLine0);
  pY = pContext->pSampleBuf + Row * 8;
  pC = pContext->pSampleBuf + 64 * 2 + Row * 8;
  for (i = pContext->MaxMCUsPerRow; i > 0; i--) {
    for (l = 0; l < 2; l++) {
      for (j = 0; j < 4; j++) {
        int cb;
        int cr;
        int rc;
        int gc;
        int bc;
        int yy;
#if (USE_LIMIT_TABLE == 0)
        int v;
#endif
        cb = *(pC + 0);
        cr = *(pC + 64);
        rc = pCRR[cr];
        gc = ((pCRG[cr] + pCBG[cb]) >> 16);
        bc = pCBB[cb];
#if USE_LIMIT_TABLE
        yy = *(pY + (j << 1));
        *(pDst + 0) = LIMIT(yy + rc);
        *(pDst + 1) = LIMIT(yy + gc);
        *(pDst + 2) = LIMIT(yy + bc);
        yy = *(pY + (j << 1) + 1);
        *(pDst + 4) = LIMIT(yy + rc);
        *(pDst + 5) = LIMIT(yy + gc);
        *(pDst + 6) = LIMIT(yy + bc);
#else
        yy = *(pY + (j << 1));
        v = (yy + rc);
        LIMIT(v);
        *(pDst + 0) = v;
        v = (yy + gc);
        LIMIT(v);
        *(pDst + 1) = v;
        v = (yy + bc);
        LIMIT(v);
        *(pDst + 2) = v;

        yy = *(pY + (j << 1) + 1);
        v = (yy + rc);
        LIMIT(v);
        *(pDst + 4) = v;
        v = (yy + gc);
        LIMIT(v);
        *(pDst + 5) = v;
        v = (yy + bc);
        LIMIT(v);
        *(pDst + 6) = v;
#endif
        pDst += 8;
        pC++;
      }
      pY += 64;
    }
    pY += 64 * 4 - 64 * 2;
    pC += 64 * 4 - 8;
  }
}

/*********************************************************************
*
*       _ConvertH1V2
*
* Purpose:
*   YCbCr conversion to RGB.
*   Horizontal resolution 1 pixel, vertical resolution 2 pixel, 4 blocks per MCU
*/
static void _ConvertH1V2(GUI_JPEG_DCONTEXT * pContext) {
  int * pCRR;
  int * pCBB;
  I32 * pCRG;
  I32 * pCBG;
  int Row;
  int i;
  int j;
  U8 * pDst_0;
  U8 * pDst_1;
  U8 * pY;
  U8 * pC;
  pCRR = pContext->aCRR;
  pCBB = pContext->aCBB;
  pCRG = pContext->aCRG;
  pCBG = pContext->aCBG;
  Row = pContext->MaxMCU_ySize - pContext->MCULinesLeft;
  pDst_0 = (U8 *)GUI_ALLOC_h2p(pContext->hScanLine0);
  pDst_1 = (U8 *)GUI_ALLOC_h2p(pContext->hScanLine1);
  if (Row < 8) {
    pY = pContext->pSampleBuf + Row * 8;
  } else {
    pY = pContext->pSampleBuf + 64 * 1 + (Row & 7) * 8;
  }
  pC = pContext->pSampleBuf + 64 * 2 + (Row >> 1) * 8;
  for (i = pContext->MaxMCUsPerRow; i > 0; i--) {
    for (j = 0; j < 8; j++) {
      int cb;
      int cr;
      int rc;
      int gc;
      int bc;
      int yy;
#if (USE_LIMIT_TABLE == 0)
      int v;
#endif
      cb = *(pC +  0 + j);
      cr = *(pC + 64 + j);
      rc = pCRR[cr];
      gc = ((pCRG[cr] + pCBG[cb]) >> 16);
      bc = pCBB[cb];
#if USE_LIMIT_TABLE
      yy = *(pY + j);
      *(pDst_0 + 0) = LIMIT(yy + rc);
      *(pDst_0 + 1) = LIMIT(yy + gc);
      *(pDst_0 + 2) = LIMIT(yy + bc);
      yy = *(pY + 8 + j);
      *(pDst_1 + 0) = LIMIT(yy + rc);
      *(pDst_1 + 1) = LIMIT(yy + gc);
      *(pDst_1 + 2) = LIMIT(yy + bc);
#else
      yy = *(pY + j);
      v = (yy + rc);
      LIMIT(v);
      *(pDst_0 + 0) = v;
      v = (yy + gc);
      LIMIT(v);
      *(pDst_0 + 1) = v;
      v = (yy + bc);
      LIMIT(v);
      *(pDst_0 + 2) = v;

      yy = *(pY + 8 + j);
      v = (yy + rc);
      LIMIT(v);
      *(pDst_1 + 0) = v;
      v = (yy + gc);
      LIMIT(v);
      *(pDst_1 + 1) = v;
      v = (yy + bc);
      LIMIT(v);
      *(pDst_1 + 2) = v;
#endif
      pDst_0 += 4;
      pDst_1 += 4;
    }
    pY += 64 * 4;
    pC += 64 * 4;
  }
}

/*********************************************************************
*
*       _ConvertGray
*
* Purpose:
*   YCbCr conversion to RGB. 1 block per MCU.
*/
static void _ConvertGray(GUI_JPEG_DCONTEXT * pContext) {
  int Row;
  int i;
  U8 * pDst;
  U8 * pSrc;
  Row = pContext->MaxMCU_ySize - pContext->MCULinesLeft;
  pDst = (U8 *)GUI_ALLOC_h2p(pContext->hScanLine0);
  pSrc = pContext->pSampleBuf + Row * 8;
  for (i = pContext->MaxMCUsPerRow; i > 0; i--) {
    GUI_MEMCPY(pDst, pSrc, 8);
    pSrc += 64;
    pDst += 8;
  }
}

/*********************************************************************
*
*       _DrawBanding
*
* Purpose:
*   Draws one JPEG frame band by band. The file will be scanned multiple times.
*/
static int _DrawBanding(GUI_JPEG_DCONTEXT * pContext, int x0, int y0, GUI_COLOR (* pfGetColor)(const U8 ** ppData, unsigned SkipCnt), tLCDDEV_Color2Index * pfColor2Index) {
  unsigned Band;
  int r;
  int i;
  r = 0;
  /* Allocate coefficient buffer */
  if (GUI_JPEG__AllocBandingCoeffBuffer(pContext) != 0) {
    return 1;
  }
  for (Band = 0; Band < pContext->NumBands; Band++) {
    int BlockY;
    /* Start reading and process markers until SOF marker */
    if (Band) {
      GUI_JPEG__ReadUntilSOF(pContext);
    }
    /* Decode one band of data */
    GUI_JPEG__DecodeProgressiveBanding(pContext);
    /* Draw one band of data */
    for (i = 0; i < pContext->ySize; i++) {
      /* Load line */
      if (GUI_JPEG__DecodeLine(pContext)) {
        r = 1;
        break;
      }
      /* Calculate block */
      BlockY = i >> 3;
      /* Skip rest of file */
      if (BlockY > (pContext->FirstBlockOfBand + pContext->NumBlocksPerBand - 1)) {
        break;
      }
      /* Draw the line */
      if ((BlockY >= pContext->FirstBlockOfBand) && (BlockY <= (pContext->FirstBlockOfBand + pContext->NumBlocksPerBand - 1))) {
        pContext->pfWritePixels(x0, y0 + i, pContext, pfGetColor, pfColor2Index);
      }
    }
    /* Set parameters for next band */
    GUI_JPEG__SetNextBand(pContext);
  }
  return r;
}

/*********************************************************************
*
*       _DrawAtOnce
*
* Purpose:
*   Draws one JPEG frame at once, that means scanning of the file is required only one time.
*/
static int _DrawAtOnce(GUI_JPEG_DCONTEXT * pContext, int x0, int y0, GUI_COLOR (* pfGetColor)(const U8 ** ppData, unsigned SkipCnt), tLCDDEV_Color2Index * pfColor2Index) {
  int i, r;
  r = 0;
  /* Iterate over all lines */
  for (i = 0; i < pContext->ySize; i++) {
    /* Decode line */
    if (GUI_JPEG__DecodeLine(pContext)) {
      r = 1;
      break;
    }
    /* Draw the line */
    pContext->pfWritePixels(x0, y0 + i, pContext, pfGetColor, pfColor2Index);
  }
  return r;
}

/*********************************************************************
*
*       _Draw
*/
static int _Draw(GUI_JPEG_DCONTEXT * pContext, GUI_JPEG_GET_DATA_FUNC * pfGetData, void * p, int x0, int y0) {
  #if (GUI_WINSUPPORT)
    GUI_RECT Rect;
  #endif
  tLCDDEV_Color2Index * pfColor2Index;
  GUI_JPEG_INFO Info;
  GUI_COLOR (* pfGetColor)(const U8 ** ppData, unsigned SkipCnt);
  int r;
  int OldIndex;

  /* Remember old foreground color */
  OldIndex = LCD_GetColorIndex();
  /* Get size of image */
  if (GUI_JPEG_GetInfoEx(pfGetData, p, &Info)) {
    return 1;
  }
  /* Iterate over all windows */
  #if (GUI_WINSUPPORT)
    WM_ADDORG(x0,y0);
    Rect.x1 = (Rect.x0 = x0) + Info.XSize - 1;
    Rect.y1 = (Rect.y0 = y0) + Info.YSize - 1;
    WM_ITERATE_START(&Rect) {
  #endif
    GUI_MEMSET((U8 *)pContext, 0, sizeof(GUI_JPEG_DCONTEXT));
    pContext->pParam = p;
    pContext->pfGetData = pfGetData;
    /* Initialize drawing and allocate memory */
    r = GUI_JPEG__InitDraw(pContext);
    if (pContext->ScanType == GRAYSCALE) {
      pfGetColor = GUI_JPEG__GetColorGray;
    } else {
      pfGetColor = GUI_JPEG__GetColorRGB;
    }
    /* Calculate function pointer for drawing one line of data */
    if ((LCD_GetBitsPerPixelEx(GUI_Context.SelLayer) == (sizeof(LCD_PIXELINDEX) << 3)) && (pContext->ScanType != GRAYSCALE)) {
      pContext->pfWritePixels = _WritePixelsOptRGB;
      pContext->hBmpLine = GUI_ALLOC_AllocZero(pContext->xSize * sizeof(LCD_PIXELINDEX));
    } else {
      pContext->pfWritePixels = _WritePixels;
    }
    /* Get the right color conversion routine */
    #if GUI_SUPPORT_MEMDEV
    if (GUI_Context.hDevData) {
      GUI_MEMDEV * pDevData;
      pDevData = GUI_MEMDEV_H2P(GUI_Context.hDevData);
      pfColor2Index = pDevData->pfColor2Index;
    } else {
    #else
    {
    #endif
      /* If no memory device is selected, use the color conversion routine of the current layer */
      pfColor2Index = (tLCDDEV_Color2Index *)LCD_GetpfColor2IndexEx(GUI_Context.SelLayer);
    }
    if (r == 0) {
      if (pContext->BandingRequired == 0) {
        r = _DrawAtOnce(pContext, x0, y0, pfGetColor, pfColor2Index);
      } else {
        r = _DrawBanding(pContext, x0, y0, pfGetColor, pfColor2Index);
      }
    }
    /* Free allocated memory */
    GUI_JPEG__Free(pContext);
  #if (GUI_WINSUPPORT)
    } WM_ITERATE_END();
  #endif
  /* Restore foreground color */
  LCD_SetColor(LCD_Index2Color(OldIndex));
  return r;
}

/*********************************************************************
*
*       Private code
*
**********************************************************************
*/
/*********************************************************************
*
*       GUI_JPEG__GetData
*
* Purpose:
*   This routine is called by _FillInputBuffer when GUI_JPEG_Draw() is
*   executed. It is responsible for setting the data pointer to a valid
*   data location with at least one valid byte.
*
* Parameters:
*   p           - Pointer to application defined data.
*   NumBytesReq - Number of bytes requested.
*   ppData      - Pointer to data pointer. This pointer should be set to
*                 a valid location.
*   StartOfFile - If this flag is 1, the data pointer should be set to the
*                 beginning of the data stream.
*
* Return value:
*   Number of data bytes available.
*/
int GUI_JPEG__GetData(void * p, int NumBytesReq, const U8 ** ppData, unsigned StartOfFile) {
  int RemBytes, NumBytes;
  GUI_JPEG_PARAM * pParam;
  NumBytes = 0;
  pParam = (GUI_JPEG_PARAM *)p;
  if (StartOfFile) {
    pParam->Off = 0;
  }
  RemBytes = pParam->FileSize - pParam->Off;
  if (RemBytes > 0) {
    NumBytes = (RemBytes > NumBytesReq) ? NumBytesReq : RemBytes;
    *ppData  = pParam->pFileData + pParam->Off;
    pParam->Off += NumBytes;
  }
  return NumBytes;
}

/*********************************************************************
*
*       GUI_JPEG__ReadUntilSOF
*
* Purpose:
*   Process all markers until (and including) the SOFx marker to get basic file information.
*/
int GUI_JPEG__ReadUntilSOF(GUI_JPEG_DCONTEXT * pContext) {
  U8 Marker;
  pContext->StartOfFile = 1;
  pContext->pfGetU8 = _GetU8;
  if (_ReadFirstMarker(pContext, &Marker)) {
    return 1;
  }
  if (Marker != M_SOI) {
    return 1;
  }
  if (_ReadMarkers(pContext, &Marker)) {
    return 1;
  }
  switch (Marker) {
  case M_SOF2: /* Progressive, Huffman */
    pContext->IsProgressive = 1;
    /* No break here... */
  case M_SOF0: /* Baseline */
  case M_SOF1: /* Extended sequential, Huffman */
    if (_GetSOF(pContext)) {
      return 1;
    }
    break;
  }
  return 0;
}

/*********************************************************************
*
*       GUI_JPEG__DecodeProgressiveBanding
*
* Purpose:
*   Decodes the coefficients of one band of a progressive scan
*/
int GUI_JPEG__DecodeProgressiveBanding(GUI_JPEG_DCONTEXT * pContext) {
  int i;
  U8 NumCompsPerFrame;
  NumCompsPerFrame = pContext->NumCompsPerFrame;
  if (NumCompsPerFrame == 4) {
    return 1; /* Error: Unsupported color space */
  }
  while (1) {
    int DC_OnlyScan;
    int RefinementScan;
    int (* pfDecodeBlock)(GUI_JPEG_DCONTEXT * pContext, int ComponentId, int BlockX, int BlockY);
    /* Initialize scan by reading the markers including the SOS marker */
    if (_InitScan(pContext)) {
      /* Break if there is nothing else to scan */
      break;
    }
    DC_OnlyScan    = (pContext->SpectralStart  ? 0 : 1);
    RefinementScan = (pContext->SuccessiveHigh ? 1 : 0);
    if (pContext->SpectralStart > pContext->SpectralEnd) {
      return 1; /* Error: Bad SOS spectral */
    }
    if (DC_OnlyScan) {
      if (pContext->SpectralEnd) {
        return 1; /* Error: Bad SOS spectral */
      }
    } else if (pContext->NumCompsPerScan != 1) {
      return 1; /* Error: Bad SOS spectral */
    }
    if (RefinementScan && (pContext->SuccessiveLow != pContext->SuccessiveHigh)) {
      return 1; /* Error: Bad SOS successive */
    }
    /* Set the right decoding routine */
    if (DC_OnlyScan) {
      if (RefinementScan) {
        pfDecodeBlock = _DecodeBlockDC_RefineBanding;
      } else {
        pfDecodeBlock = _DecodeBlockDC_FirstBanding;
      }
    } else {
      if (RefinementScan) {
        pfDecodeBlock = _DecodeBlockAC_RefineBanding;
      } else {
        pfDecodeBlock = _DecodeBlockAC_FirstBanding;
      }
    }
    /* Decode... */
    if (_DecodeScanProg(pContext, pfDecodeBlock)) {
      return 1;
    }
  }
  pContext->NumCompsPerScan = pContext->NumCompsPerFrame;
  for (i = 0; i < pContext->NumCompsPerScan; i++) {
    pContext->aCompList[i] = i;
  }
  _CalcMCUBlockOrder(pContext);
  return 0;
}

/*********************************************************************
*
*       GUI_JPEG__Free
*
* Purpose:
*   Frees all allocated data of the given decoding context
*/
void GUI_JPEG__Free(GUI_JPEG_DCONTEXT * pContext) {
  int i;
  if (pContext->hScanLine0) {
    GUI_ALLOC_Free(pContext->hScanLine0);
  }
  if (pContext->hScanLine1) {
    GUI_ALLOC_Free(pContext->hScanLine1);
  }
  for (i = 0; i < pContext->MaxBlocksPerRow; i++) {
    if (pContext->ahBlocks[i]) {
      GUI_ALLOC_Free(pContext->ahBlocks[i]);
    }
  }
  if (pContext->hSampleBuf) {
    GUI_ALLOC_Free(pContext->hSampleBuf);
  }
  for (i = 0; i < pContext->NumCompsPerFrame; i++) {
    GUI_HMEM hMem;
    hMem = pContext->aAC_Coeffs[i].hData;
    if (hMem) {
      GUI_ALLOC_Free(hMem);
    }
    hMem = pContext->aDC_Coeffs[i].hData;
    if (hMem) {
      GUI_ALLOC_Free(hMem);
    }
  }
  if (pContext->hBmpLine) {
    GUI_ALLOC_Free(pContext->hBmpLine);
  }
}

/*********************************************************************
*
*       GUI_JPEG__SkipLine
*
* Purpose:
*   Decodes a line on demand and does the YCbCr->RGB conversion. After
*   calling this routine the output buffer contains one line of RGB data.
*/
int GUI_JPEG__SkipLine(GUI_JPEG_DCONTEXT * pContext) {
  if (pContext->MCULinesLeft == 0) {
    if (pContext->IsProgressive) {
      if (_LoadNextRow(pContext)) {
        return 1;
      }
    } else {
      if (_DecodeNextRow(pContext)) {
        return 1;
      }
      if (pContext->TotalLinesLeft <= pContext->MaxMCU_ySize) {
        U8 Marker;
        if (_ReadMarkers(pContext, &Marker)) {
          return 1;
        }
        if (Marker != M_EOI) {
          return 1;
        }
      }
      pContext->TransformationRequired = 1;
    }
    pContext->MCULinesLeft = pContext->MaxMCU_ySize;
  }
  pContext->MCULinesLeft--;
  pContext->TotalLinesLeft--;
  return 0;
}

/*********************************************************************
*
*       GUI_JPEG__DecodeLine
*
* Purpose:
*   Decodes a line on demand and does the DPCM and the YCbCr->RGB conversion.
*   After calling this routine the output buffer contains one line of
*   valid RGB data.
*/
int GUI_JPEG__DecodeLine(GUI_JPEG_DCONTEXT * pContext) {
  /* Decode a new line if buffer is empty */
  if (pContext->MCULinesLeft == 0) {
    if (pContext->IsProgressive) {
      if (_LoadNextRow(pContext)) {
        return 1;
      }
    } else {
      if (_DecodeNextRow(pContext)) {
        return 1;
      }
      if (pContext->TotalLinesLeft <= pContext->MaxMCU_ySize) {
        U8 Marker;
        if (_ReadMarkers(pContext, &Marker)) {
          return 1;
        }
        if (Marker != M_EOI) {
          return 1;
        }
      }
    }
    pContext->TransformationRequired = 1;
    pContext->MCULinesLeft = pContext->MaxMCU_ySize;
  }
  if (pContext->TransformationRequired) {
    _TransformRow(pContext);
    pContext->TransformationRequired = 0;
  }
  /* Do the color convertion */
  switch (pContext->ScanType) {
  case YH2V2:
    if ((pContext->MCULinesLeft & 1) == 0) {
      _ConvertH2V2(pContext);
      pContext->BufferIndex = 0;
    } else {
      pContext->BufferIndex = 1;
    }
    break;
  case YH2V1:
    _ConvertH2V1(pContext);
    pContext->BufferIndex = 0;
    break;
  case YH1V2:
    if ((pContext->MCULinesLeft & 1) == 0) {
      _ConvertH1V2(pContext);
      pContext->BufferIndex = 0;
    } else {
      pContext->BufferIndex = 1;
    }
    break;
  case YH1V1:
    _ConvertH1V1(pContext);
    pContext->BufferIndex = 0;
    break;
  case GRAYSCALE:
    _ConvertGray(pContext);
    pContext->BufferIndex = 0;
    break;
  }
  pContext->MCULinesLeft--;
  pContext->TotalLinesLeft--;
  return 0;
}

/*********************************************************************
*
*       GUI_JPEG__GetColorRGB
*
* Purpose:
*   Reads one RGB pixel from the given pointer and increments the pointer
*/
GUI_COLOR GUI_JPEG__GetColorRGB(const U8 ** ppData, unsigned SkipCnt) {
  U32 r, g, b;
  const U8 * pData;
  pData = *ppData;
  r = *(pData + 0);
  g = *(pData + 1);
  b = *(pData + 2);
  (*ppData) += SkipCnt << 2;
  return r | (g << 8) | (b << 16);
}

/*********************************************************************
*
*       GUI_JPEG__GetColorGray
*
* Purpose:
*   Reads one gray pixel from the given pointer and increments the pointer
*/
GUI_COLOR GUI_JPEG__GetColorGray(const U8 ** ppData, unsigned SkipCnt) {
  U32 u;
  const U8 * pData;
  pData = *ppData;
  u = *pData;
  (*ppData) += SkipCnt;
  return u * 0x10101;
}

/*********************************************************************
*
*       GUI_JPEG__InitDraw
*/
int GUI_JPEG__InitDraw(GUI_JPEG_DCONTEXT * pContext) {
  int r;
  /* Get basic file information */
  r = GUI_JPEG__ReadUntilSOF(pContext);
  /* Allocate memory and initialize variables */
  if (r == 0) {
    r = _InitFrame(pContext);
  }
  /* Do 'per scan' initialization */
  if (pContext->IsProgressive) {
    if (r == 0) {
      r = _CalcBanding(pContext);
      if (r == 0) {
        if (pContext->BandingRequired == 0) {
          r = _DecodeProgressive(pContext);
        }
      }
    }
  } else {
    if (r == 0) {
      r = _InitScan(pContext);
    }
  }
  return r;
}

/*********************************************************************
*
*       GUI_JPEG__SetNextBand
*
* Purpose:
*   Initializes decoding of the next band
*/
void GUI_JPEG__SetNextBand(GUI_JPEG_DCONTEXT * pContext) {
  int i;
  /* Increment blocks */
  pContext->FirstBlockOfBand += pContext->NumBlocksPerBand;
  for (i = 0; i < pContext->NumCompsPerFrame; i++) {
    if (pContext->aCompHSamp[0] == 2) {
      pContext->aFirstBlockOfBand[i] = (pContext->FirstBlockOfBand / (2 - pContext->aCompVSamp[i] + 1));
    } else {
      pContext->aFirstBlockOfBand[i] = pContext->FirstBlockOfBand;
    }
  }
  /* Clear coefficient buffer */
  for (i = 0; i < pContext->NumCompsPerFrame; i++) {
    COEFF_BUFFER * pBuffer;
    U8 * pData;
    pBuffer = &pContext->aDC_Coeffs[i];
    pData = (U8 *)GUI_ALLOC_h2p(pBuffer->hData);
    GUI_MEMSET(pData, 0, pBuffer->BlockSize * pBuffer->NumBlocksX * pBuffer->NumBlocksY);
    pBuffer = &pContext->aAC_Coeffs[i];
    pData = (U8 *)GUI_ALLOC_h2p(pBuffer->hData);
    GUI_MEMSET(pData, 0, pBuffer->BlockSize * pBuffer->NumBlocksX * pBuffer->NumBlocksY);
  }
  GUI_MEMSET((U8 *)pContext->aBlockY_MCU, 0, sizeof(pContext->aBlockY_MCU));
  pContext->TotalLinesLeft = pContext->ySize;
  pContext->MCULinesLeft   = 0;
}

/*********************************************************************
*
*       GUI_JPEG__AllocBandingCoeffBuffer
*
* Purpose:
*   Allocates the coefficient buffer for banding scan
*/
int GUI_JPEG__AllocBandingCoeffBuffer(GUI_JPEG_DCONTEXT * pContext) {
  int i;
  /* Allocate coefficient buffer */
  for (i = 0; i < pContext->NumCompsPerFrame; i++) {
    if (_CoeffBufferAllocBanding(pContext, &pContext->aDC_Coeffs[i], i, 1)) {
      return 1;
    }
    if (_CoeffBufferAllocBanding(pContext, &pContext->aAC_Coeffs[i], i, 8)) {
      return 1;
    }
  }
  return 0;
}

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       GUI_JPEG_GetInfoEx
*/
int GUI_JPEG_GetInfoEx(GUI_JPEG_GET_DATA_FUNC * pfGetData, void * p, GUI_JPEG_INFO * pInfo) {
  int r;
  GUI_LOCK();
  GUI_MEMSET((U8 *)&GUI_JPEG__DContext, 0, sizeof(GUI_JPEG__DContext));
  GUI_JPEG__DContext.pParam = p;
  GUI_JPEG__DContext.pfGetData = pfGetData;
  r = GUI_JPEG__ReadUntilSOF(&GUI_JPEG__DContext);
  if (pInfo) {
    pInfo->XSize = GUI_JPEG__DContext.xSize;
    pInfo->YSize = GUI_JPEG__DContext.ySize;
  }
  GUI_UNLOCK();
  return r;
}

/*********************************************************************
*
*       GUI_JPEG_GetInfo
*/
int GUI_JPEG_GetInfo(const void * pFileData, int DataSize, GUI_JPEG_INFO * pInfo) {
  int r;
  GUI_JPEG_PARAM Param;
  Param.FileSize  = DataSize;
  Param.pFileData = (const U8 *)pFileData;
  r = GUI_JPEG_GetInfoEx(GUI_JPEG__GetData, &Param, pInfo);
  return r;
}

/*********************************************************************
*
*       GUI_JPEG_DrawEx
*/
int GUI_JPEG_DrawEx(GUI_JPEG_GET_DATA_FUNC * pfGetData, void * p, int x0, int y0) {
  int r;
  GUI_LOCK();
  r = _Draw(&GUI_JPEG__DContext, pfGetData, p, x0, y0);
  GUI_UNLOCK();
  return r;
}

/*********************************************************************
*
*       GUI_JPEG_Draw
*/
int GUI_JPEG_Draw(const void * pFileData, int DataSize, int x0, int y0) {
  int r;
  GUI_JPEG_PARAM Param;
  Param.FileSize  = DataSize;
  Param.pFileData = (const U8 *)pFileData;
  r = GUI_JPEG_DrawEx(GUI_JPEG__GetData, &Param, x0, y0);
  return r;
}

#endif /* (GUI_SELECT_JPEG == 0) */

/*************************** End of file ****************************/
