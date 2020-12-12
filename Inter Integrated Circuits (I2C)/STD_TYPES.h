/********************************************************************************************
 *                                                                                          *
 * File Name   : STD_TYPES.h                                                                      *
 *                                                                                          *
 * Author      : Hesham Elsherbieny                                                         *
 *                                                                                          *
 * contacts:   : h.elsherbieny@gmail.com					                                *
 *                                                                                          *
 * Date        : Dec 2019                                                                   *
 *                                                                                          *
 * Version     : 3.1.1                                                                      *
 *                                                                                          *
 * Description : Specifies Standard Types Library used for the embedded/automotive drivers  *
 *                                                                                          *
 *                                                                                          *
 ********************************************************************************************/

#ifndef TYPES_H_
#define TYPES_H_

/* U8 and its derivatives */
  typedef unsigned char u8;
  typedef unsigned short int u16;
  typedef unsigned long int u32;
  typedef unsigned long long u64;
  typedef signed char s8;
  typedef signed short int s16;
  typedef signed long int s32;
  typedef float f32;
  typedef double f64;
  typedef long double f96;
  typedef u8* pu8;
  typedef u16* pu16;
  typedef u32* pu32;
  typedef s8* ps8;
  typedef s16* ps16;
  typedef s32* ps32;
  
/* UINT8_t and its derivatives */
  typedef u8  uint8_t;
  typedef u16 uint16_t;
  typedef u32 uint32_t;
  typedef u64 uint64_t;
  typedef s8  int8_t;
  typedef s16 int16_t;
  typedef s32 int32_t;
  
  /* Structure Data Type to define Standard error status either 'OK' or NOT OK 'NOK' */
  typedef enum
  {
    OK,
    NOK
  }ERROR_t;
  
  /* Structrue Data Type to define Boolean DataType either 'TRUE' or 'FALSE' */
  typedef enum
  {
    TRUE,
    FALSE
  }bool;

#endif /* TYPES_H_ */
