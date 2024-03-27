#ifndef _PDR_H
#define _PDR_H
/*******************************************************************************
 *
 * Module Name: pdr.h
 *
 * Copyright 2004 VXI Technology Inc. as an unpublished work.
 * All rights reserved.
 *
 * The information contained herein is confidential property of VXI Technology,
 * Inc.  The use, copying, transfer, or disclosure of such information is
 * prohibited except by express written agreement with VXI Technology, Inc.
 *
 * First written on 13 October 2004 by Paul Mecklenburg
 *
 * Module Description:
 *   The header file for PDR.  Portable/Paul's Data Representation.
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/ioctl.h>
#include <pthread.h>
#include <errno.h>
#include <malloc.h>

/*******************************************************************************
 * Typedefs
 ******************************************************************************/

typedef int stream_t;

/*******************************************************************************
 * Defines
 ******************************************************************************/

#define stream_close(s) close((s))
#define stream_write(s,b,c) write((s),(b),(c))
#define stream_read(s,b,c) read((s),(b),(c))

#define PDR_ALIGN     0x00000001
#define PDR_NOMALLOC  0x00000002
#define PDR_ENCODE    0x00010000
#define PDR_DECODE    0x00020000
#define PDR_FREE      0x00030000
#define PDR_OP_MASK   0xFFFF0000
#define PDR_FLAG_MASK 0x0000FFFF

/*
 * This buffer needs to be 32-bit aligned (in size)
 */
#define PDR_IBUFSZ 16384
#define PDR_0BUFSZ 1024

#define PDR_NOOP(a) a

#define PDR_CAST(a) ((int (*)(struct pdr_buffer *, void *, uint32_t))(a))

#define PDR_STREAM(p) ((p)->sd)

/*******************************************************************************
 * Structs
 ******************************************************************************/
struct pdr_buffer {
  uint8_t *outbuf;   /* send buffer */
  uint8_t *inbuf;    /* recv buffer */
  size_t pdr_outbuf_size;
  size_t pdr_inbuf_size;
  size_t outpos;                     /* write position in send buffer */
  size_t inpos;                      /* read position in recv buffer */
  size_t intotal;                    /* total used space in recv buffer */
  stream_t sd;                       /* handle to McBSP stream link */
  pthread_mutex_t write_mutex;       /* buffer write lock */
  pthread_mutex_t read_mutex;        /* buffer read lock */
};

/*******************************************************************************
 * Functions
 ******************************************************************************/

stream_t stream_open(int link, int port);
int pdr_init(struct pdr_buffer *buf, stream_t sd);
int pdr_destroy(struct pdr_buffer *buf);
void pdr_read_reset(struct pdr_buffer *buf);
int stream_next(stream_t s);
int stream_done(stream_t s);
int stream_set_recv_timeout(stream_t s, int infinite, unsigned long msec);

/*******************************************************************************
 * (More) Typedefs  -- This is down here because it depends on the
 * earlier typedef an also on the Structs section.
 ******************************************************************************/

typedef int (*pdr_func_t)(struct pdr_buffer *, void *, uint32_t);

/*******************************************************************************
 * Function name: pdr_flush
 *   Returns:     0 on success, otherwise err
 *   buf:         the buffer to flush
 * Created by:    Paul Mecklenburg
 * Description:   Force the buffer to be written to the stream.
 ******************************************************************************/
static inline int pdr_flush(struct pdr_buffer *buf) {
  int err;

  if (buf->outpos) {
    err = stream_write(buf->sd, buf->outbuf, buf->outpos);

    if (err < 0)
      return errno;
    if (err != buf->outpos)
      return EIO;
    
    buf->outpos = 0;
  }

  return 0;
}

/*******************************************************************************
 * Function name: pdr_read_lock
 *   Returns:     0 on success, otherwise err
 *   buf:         lock the buffer
 * Created by:    Paul Mecklenburg
 * Description:   place a "soft" lock on the buffer (it is only observed by other lock calls)
 ******************************************************************************/
static inline int pdr_read_lock(struct pdr_buffer *buf) {
  return pthread_mutex_lock(&buf->read_mutex);
}

/*******************************************************************************
 * Function name: pdr_read_unlock
 *   Returns:     0 on success, otherwise err
 *   buf:         the buffer to unlock
 * Created by:    Paul Mecklenburg
 * Description:   remove the "soft" lock
 ******************************************************************************/
static inline int pdr_read_unlock(struct pdr_buffer *buf) {
  return pthread_mutex_unlock(&buf->read_mutex);
}

/*******************************************************************************
 * Function name: pdr_write_lock
 *   Returns:     0 on success, otherwise err
 *   buf:         lock the buffer
 * Created by:    Paul Mecklenburg
 * Description:   place a "soft" lock on the buffer (it is only observed by other lock calls)
 ******************************************************************************/
static inline int pdr_write_lock(struct pdr_buffer *buf) {
  return pthread_mutex_lock(&buf->write_mutex);
}

/*******************************************************************************
 * Function name: pdr_write_unlock
 *   Returns:     0 on success, otherwise err
 *   buf:         the buffer to unlock
 * Created by:    Paul Mecklenburg
 * Description:   remove the "soft" lock
 ******************************************************************************/
static inline int pdr_write_unlock(struct pdr_buffer *buf) {
  return pthread_mutex_unlock(&buf->write_mutex);
}

/*******************************************************************************
 * Function name: pdr_read
 *   Returns:     0 on success, otherwise err
 *   buf:         the buffer to fill
 * Created by:    Paul Mecklenburg
 * Description:   Read more data into the buffer from the stream.
 ******************************************************************************/
static inline int pdr_read(struct pdr_buffer *buf) {
  int err;
  size_t left;

  left = buf->intotal - buf->inpos;
  if (left) {
    memmove(buf->inbuf, &buf->inbuf[buf->inpos], left);
    buf->intotal = left;
  }
  else
    buf->intotal = 0;

  buf->inpos = 0;
  left = buf->pdr_inbuf_size - buf->intotal;

  err = stream_read(buf->sd, &buf->inbuf[buf->intotal], left);
  
  /*
   * error happened while reading
   */
  if (err < 0)
    return errno;

  /*
   * still looking for more data, but there is none to be had :(
   */
  if (err == 0)
    return EIO;

  buf->intotal += err;

  return 0;
}

/*******************************************************************************
 * Function name: pdr_align
 *   Returns:     0 on success, otherwise err
 *   buf:         the buffer 32-bit align
 *   op:          the current operation being performed (decode, encode, etc)
 * Created by:    Paul Mecklenburg
 * Description:   Align the buffer to the next 32-bit boundry.
 ******************************************************************************/
static inline int pdr_align(struct pdr_buffer *buf, uint32_t op) {
  switch (op & PDR_OP_MASK) {
  case PDR_ENCODE:
    if (buf->outpos & 0x3) {
      buf->outpos = (buf->outpos + 4) & ~0x3;
    }
    break;
  case PDR_DECODE:
    if (buf->inpos & 0x3) {
      buf->inpos = (buf->inpos + 4) & ~0x3;
    }
    break;
  }
  
  return 0;
}

/*
 * NOTE:
 * The next two functions could be combined by adding an op parameter.  This
 * would be more consistent with the rest of the architecture.
 */

/*******************************************************************************
 * Function name: pdr_get_out
 *   Returns:     0 on success, otherwise err
 *   buf:         the buffer to get some data from
 *   amount:      the amount of space to get from the buffer
 * Created by:    Paul Mecklenburg
 * Description:   Retrieve an amount of space from the buffer for writing.
 ******************************************************************************/
static inline void * pdr_get_out(struct pdr_buffer *buf, size_t amount, int * err) {
  void *data;

  if (buf->pdr_outbuf_size - buf->outpos < amount) {
    if ((*err = pdr_flush(buf)))
      return NULL;
  }
  
  data = &buf->outbuf[buf->outpos];
  buf->outpos += amount;

  return data;
}

/*******************************************************************************
 * Function name: pdr_get_in
 *   Returns:     0 on success, otherwise err
 *   buf:         the buffer to get some data from
 *   amount:      the amount of space to get from the buffer
 * Created by:    Paul Mecklenburg
 * Description:   Retrieve an amount of data from the buffer for reading.
 ******************************************************************************/
static inline void * pdr_get_in(struct pdr_buffer *buf, size_t amount, int * err) {
  void *data;

  *err = 0;
  if (buf->intotal - buf->inpos < amount)
    *err = pdr_read(buf);

  if (*err)
    return NULL;

  if (buf->intotal - buf->inpos < amount) {
    *err = EIO;
    return NULL;
  }

  data = &buf->inbuf[buf->inpos];
  buf->inpos += amount;

  return data;
}

/*
 * This define is used to generate a set of similar functions in this header.
 * It is not to be used elsewhere.
 */

#define PDR_DEFINE_SIMPLE(func, type, hton, ntoh) \
static inline int func(struct pdr_buffer *buf, type *var, uint32_t op) { \
  type *tmp; \
  int err; \
  \
  switch((op) & PDR_OP_MASK) { \
  case PDR_ENCODE: \
    tmp = pdr_get_out(buf, sizeof(*var), &err); \
    if (!tmp) \
      return err; \
    *tmp = hton(*var); \
    if (op & PDR_ALIGN) \
      return pdr_align(buf, op); \
    return 0; \
 \
  case PDR_DECODE: \
    tmp = pdr_get_in(buf, sizeof(*var), &err); \
    if (!tmp) \
      return err; \
    *var = ntoh(*tmp); \
    if (op & PDR_ALIGN) \
      return pdr_align(buf, op); \
    return 0; \
 \
  case PDR_FREE: \
    return 0; \
 \
  default: \
    return EINVAL; \
  } \
}

/*
 * This is code generating a set of encode/decode/free functions
 * for primative data types.
 */

/*******************************************************************************
 * Function name: pdr_u32
 *   Returns:     0 on success, otherwise err
 *   buf:         pdr_buffer
 *   var:         pointer to a primative to encode/decode/...
 *   op:          operation to be performed (PDR_ENCODE, PDR_DECODE, PDR_FREE)
 *                  optionally OR'ed with PDR_ALIGN to make it consume 32-bits.
 * Created by:    Paul Mecklenburg
 * Description:   Encode or decode a 32-bit unsigned integer.
 ******************************************************************************/
PDR_DEFINE_SIMPLE(pdr_u32, uint32_t, htonl, ntohl)
#define pdr_enum pdr_u32

/*******************************************************************************
 * Function name: pdr_s32
 *   Returns:     0 on success, otherwise err
 *   buf:         pdr_buffer
 *   var:         pointer to a primative to encode/decode/...
 *   op:          operation to be performed (PDR_ENCODE, PDR_DECODE, PDR_FREE)
 *                  optionally OR'ed with PDR_ALIGN to make it consume 32-bits.
 * Created by:    Paul Mecklenburg
 * Description:   Encode or decode a 32-bit signed integer.
 ******************************************************************************/
PDR_DEFINE_SIMPLE(pdr_s32, int32_t, htonl, ntohl)

/*******************************************************************************
 * Function name: pdr_u16
 *   Returns:     0 on success, otherwise err
 *   buf:         pdr_buffer
 *   var:         pointer to a primative to encode/decode/...
 *   op:          operation to be performed (PDR_ENCODE, PDR_DECODE, PDR_FREE)
 *                  optionally OR'ed with PDR_ALIGN to make it consume 32-bits.
 * Created by:    Paul Mecklenburg
 * Description:   Encode or decode a 16-bit unsigned integer.
 ******************************************************************************/
PDR_DEFINE_SIMPLE(pdr_u16, uint16_t, htons, ntohs)

/*******************************************************************************
 * Function name: pdr_s16
 *   Returns:     0 on success, otherwise err
 *   buf:         pdr_buffer
 *   var:         pointer to a primative to encode/decode/...
 *   op:          operation to be performed (PDR_ENCODE, PDR_DECODE, PDR_FREE)
 *                  optionally OR'ed with PDR_ALIGN to make it consume 32-bits.
 * Created by:    Paul Mecklenburg
 * Description:   Encode or decode a 16-bit signed integer.
 ******************************************************************************/
PDR_DEFINE_SIMPLE(pdr_s16, int16_t, htons, ntohs)

/*******************************************************************************
 * Function name: pdr_u8
 *   Returns:     0 on success, otherwise err
 *   buf:         pdr_buffer
 *   var:         pointer to a primative to encode/decode/...
 *   op:          operation to be performed (PDR_ENCODE, PDR_DECODE, PDR_FREE)
 *                  optionally OR'ed with PDR_ALIGN to make it consume 32-bits.
 * Created by:    Paul Mecklenburg
 * Description:   Encode or decode a 8-bit unsigned integer.
 ******************************************************************************/
PDR_DEFINE_SIMPLE(pdr_u8, uint8_t, PDR_NOOP, PDR_NOOP)
#define pdr_char pdr_u8

/*******************************************************************************
 * Function name: pdr_s8
 *   Returns:     0 on success, otherwise err
 *   buf:         pdr_buffer
 *   var:         pointer to a primative to encode/decode/...
 *   op:          operation to be performed (PDR_ENCODE, PDR_DECODE, PDR_FREE)
 *                  optionally OR'ed with PDR_ALIGN to make it consume 32-bits.
 * Created by:    Paul Mecklenburg
 * Description:   Encode or decode a 8-bit signed integer.
 ******************************************************************************/
PDR_DEFINE_SIMPLE(pdr_s8, int8_t, PDR_NOOP, PDR_NOOP)

/*******************************************************************************
 * Function name: pdr_f32
 *   Returns:     0 on success, otherwise err
 *   buf:         pdr_buffer
 *   var:         pointer to a primative to encode/decode/...
 *   op:          operation to be performed (PDR_ENCODE, PDR_DECODE, PDR_FREE)
 *                  optionally OR'ed with PDR_ALIGN to make it consume 32-bits.
 * Created by:    Paul Mecklenburg
 * Description:   Encode or decode a 32-bit ieee754 float
 ******************************************************************************/
PDR_DEFINE_SIMPLE(pdr_f32, float, htonl, PDR_NOOP)

#undef PDR_DEFINE_SIMPLE

/*******************************************************************************
 * Function name: pdr_f64
 *   Returns:     0 on success, otherwise err
 *   buf:         pdr_buffer
 *   var:         pointer to a primative to encode/decode/...
 *   op:          operation to be performed (PDR_ENCODE, PDR_DECODE, PDR_FREE)
 *                  optionally OR'ed with PDR_ALIGN to make it consume 32-bits.
 * Created by:    Paul Mecklenburg
 * Description:   Encode or decode a 64-bit double
 ******************************************************************************/
static inline int pdr_f64(struct pdr_buffer *buf, double *var, uint32_t op) {
  uint64_t *tmp;
  int err;

  switch((op) & PDR_OP_MASK) {
  case PDR_ENCODE:
    tmp = pdr_get_out(buf, sizeof(*var), &err);
    if (!tmp)
      return err;
    *tmp = htonl(*(uint32_t*)var);
    *(tmp + sizeof(uint32_t)) = htonl(*(uint32_t*)(var + sizeof(uint32_t)));
    if (op & PDR_ALIGN)
      return pdr_align(buf, op);
    return 0;

  case PDR_DECODE:
    tmp = pdr_get_in(buf, sizeof(*var), &err);
    if (!tmp)
      return err;
    *(uint32_t*)var = ntohl(*tmp);
    *(uint32_t*)(var + sizeof(uint32_t)) = ntohl(*(tmp + sizeof(uint32_t)));
    if (op & PDR_ALIGN)
      return pdr_align(buf, op);
    return 0;

  case PDR_FREE:
    return 0;

  default:
    return EINVAL;
  }
}

     /*
      * These are defines, but are used like functions so I have them in
      * the function section.
      */

/*******************************************************************************
 * Function name: pdr_array
 *   Returns:     0 on success, otherwise err
 *   buf:         pdr_buffer
 *   var:         a static array variable
 *   func:        The pdr_* function which operates on the elements of this array.
 *   op:          operation to be performed (PDR_ENCODE, PDR_DECODE, PDR_FREE)
 * Created by:    Paul Mecklenburg
 * Description:   Encode or decode a static array.
 * Note:          This function always 32-bit aligns.
 ******************************************************************************/
#define pdr_array(buf, var, func, op) \
({ \
  int _i, _bad; \
  for (_i = 0, _bad = 0; !_bad && _i < (sizeof(var)/sizeof((var)[0])); _i++) \
    _bad = func(buf, &(var)[_i], (op) & ~PDR_ALIGN); \
  if (!_bad) \
    _bad = pdr_align(buf, op); \
  _bad; \
})

/*******************************************************************************
 * Function name: pdr_2d_array
 *   Returns:     0 on success, otherwise err
 *   buf:         pdr_buffer
 *   var:         a static array variable
 *   func:        The pdr_* function which operates on the elements of this array.
 *   op:          operation to be performed (PDR_ENCODE, PDR_DECODE, PDR_FREE)
 * Created by:    Joe Miller
 * Description:   Encode or decode a static array 2-dimensional array.
 * Note:          This function always 32-bit aligns.
 *                Instead of looping through both dimensions of the array,
 *                consider the array to be 1 x (m*n) instead of m x n.
 ******************************************************************************/
#define pdr_2d_array(buf, var, func, op) \
({ \
  int _i, _bad; \
  for (_i = 0, _bad = 0; !_bad && _i < (sizeof(var)/sizeof((var)[0][0])); _i++) \
    _bad = func(buf, &(var)[0][_i], (op) & ~PDR_ALIGN); \
  if (!_bad) \
    _bad = pdr_align(buf, op); \
  _bad; \
})

/*******************************************************************************
 * Function name: pdr_variable_array
 *   Returns:     0 on success, otherwise err
 *   buf:         pdr_buffer
 *   var:         a struct with: len and data members.  Where len is a u32 telling
 *                  how many elements data points to.  And data is a pointer to
 *                  malloc'd memory.
 *                  E.G.  struct {
 *                          uint32_t len;
 *                          uint16_t *data;
 *                        } var;
 *   func:        The pdr_* function which operates on the elements of this array.
 *   op:          operation to be performed (PDR_ENCODE, PDR_DECODE, PDR_FREE)
 *   maxlen:      Maximum length of the variable length array - 0 indicates no maximum length
 * Created by:    Paul Mecklenburg
 * Description:   Encode or decode a variable length array.
 * Note:          This function always 32-bit aligns.
 ******************************************************************************/
#define pdr_variable_array(buf, var, func, op, maxlen) \
({ \
  int _i, _bad; \
  _bad = pdr_u32(buf, &(var).len, (op) | PDR_ALIGN); \
  if((maxlen) && ((var).len > maxlen)) { \
    EX1629_TEE_ERROR("%s:%d, PDR (op %#08x) var array (%s) bad len (%#08x)\n", \
      __FILE__, __LINE__, (op), #var, (var).len ); \
    _bad = EINVAL; \
  } \
  if ((((op) & PDR_OP_MASK) == PDR_DECODE) && (!((op) & PDR_NOMALLOC)) && !_bad){ \
    (var).data = malloc(sizeof((var).data[0]) * (var).len); \
    EX1629_TEE_ERROR("%s:%d, PDR (op %#08x) var array (%s) couldn't malloc %i bytes of memory at %p\n", \
      __FILE__, __LINE__, (op), #var, sizeof((var).data[0]) * (var).len, (var).data ); \
  } \
  if ((var).len > 0 && !(var).data) { \
    EX1629_TEE_ERROR("%s:%d, PDR (op %#08x) var array (%s) has length %i but no data\n", \
      __FILE__, __LINE__, (op), #var, (var).len); \
    _bad = ENOMEM; \
  } \
  for (_i = 0; !_bad && _i < (var).len; _i++) \
    _bad = func(buf, &(var).data[_i], (op) & ~PDR_ALIGN); \
  if (!_bad && ((((op) & PDR_OP_MASK) == PDR_FREE) && (!((op) & PDR_NOMALLOC)) )) { \
    free((var).data); \
    (var).data = NULL; \
  } \
  if (!_bad) \
    _bad = pdr_align(buf, op); \
  _bad; \
})

#endif /* _PDR_H */
