/*******************************************************************************
 *
 * Module Name: pdr.c
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
 *   The source file for PDR.  Portable/Paul's Data Representation.  This file
 *   is pretty empty because most of pdr is inlined.
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/

#include "pdr.h"
#include <driver.h>

/*******************************************************************************
 * Functions
 ******************************************************************************/

/*******************************************************************************
 * Function name: stream_open
 *   Returns:     new open McBSP stream, -1 on error
 *   link:        the link to open (0-2 generally)
 * Created by:    Paul Mecklenburg
 * Description:   open a McBSP stream
 ******************************************************************************/
stream_t stream_open(int link, int port) {
  char buf[64];
  stream_t sd;

  sprintf(buf, "/dev/an%c%u", link + 'a', port);
  sd = open(buf, O_RDWR);
  return sd;
}

/*******************************************************************************
 * Function name: stream_next
 *   Returns:     0 on success, otherwise error
 *   s:           the stream to act on
 * Created by:    Paul Mecklenburg
 * Description:   skip to the next transport layer frame
 ******************************************************************************/
int stream_next(stream_t s) {
  return ioctl(s, EX1629_McBSP_RECV_NEXT);
}

/*******************************************************************************
 * Function name: stream_done
 *   Returns:     0 on success, otherwise error
 *   s:           the stream to act on
 * Created by:    Paul Mecklenburg
 * Description:   mark the current transport layer frame as done
 ******************************************************************************/
int stream_done(stream_t s) {
  return ioctl(s, EX1629_McBSP_SEND_DONE);
}

/*******************************************************************************
 * Function name: stream_set_recv_timeout
 *   Returns:     0 on success, otherwise error
 *   s:           the stream to act on
 *   infinite:    boolean, sets the link to infinite timeout
 *   msec:        if (infinite = FALSE), millisecond timeout
 * Created by:    Paul Mecklenburg
 * Description:   set s' recv timeout
 ******************************************************************************/
int stream_set_recv_timeout(stream_t s, int infinite, unsigned long msec) {
  struct mcbsp_timeout tm;

  tm.infinite = infinite;
  tm.msec = msec;

  return ioctl(s, EX1629_McBSP_RECV_TIMEOUT, &tm);
}

/*******************************************************************************
 * Function name: pdr_init
 *   Returns:     0 on success, otherwise err
 *   buf:         new pdr_buffer to initialize
 *   sd:          stream descriptor for this buffer to use
 * Created by:    Paul Mecklenburg
 * Description:   Initialize a new pdr_buffer.
 ******************************************************************************/
int pdr_init(struct pdr_buffer *buf, stream_t sd)
{
  buf->sd = sd;
  
  buf->pdr_outbuf_size = PDR_0BUFSZ;
  buf->outbuf = memalign(sysconf(_SC_PAGESIZE), buf->pdr_outbuf_size);
  if(!buf->outbuf)
    return -1;
  
  buf->pdr_inbuf_size = PDR_IBUFSZ;
  buf->inbuf = memalign(sysconf(_SC_PAGESIZE), buf->pdr_inbuf_size);
  if(!buf->inbuf)
  {
    free(buf->outbuf);
    return -1;
  }
  
  buf->intotal = 0;
  buf->inpos = 0;
  buf->outpos = 0;
  pthread_mutex_init(&buf->write_mutex, NULL);
  pthread_mutex_init(&buf->read_mutex, NULL);
  return 0;
}


/*******************************************************************************
 * Function name: pdr_destory
 *   Returns:     0 on success, otherwise err
 *   buf:         the pdr_buffer to destory
 * Created by:    Paul Mecklenburg
 * Description:   Destroys the given pdr_buffer
 ******************************************************************************/
int pdr_destroy(struct pdr_buffer *buf) {
  int err = 0;
  free(buf->outbuf);
  free(buf->inbuf);
  err = pthread_mutex_destroy(&buf->write_mutex) || err;
  err = pthread_mutex_destroy(&buf->read_mutex) || err;
  return err;
}

void pdr_read_reset(struct pdr_buffer *buf)
{
  buf->intotal = 0;
  buf->inpos = 0;
}
