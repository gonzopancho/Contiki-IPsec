/*
 * Copyright (c) 2010, Swedish Institute of Computer Science.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the Institute nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE INSTITUTE AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE INSTITUTE OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * This file is part of the Contiki operating system.
 *
 * $Id: phase.h,v 1.1 2010/02/18 20:58:59 adamdunkels Exp $
 */

/**
 * \file
 *         Common functionality for phase optimization in duty cycling radio protocols
 * \author
 *         Adam Dunkels <adam@sics.se>
 */

#ifndef PHASE_H
#define PHASE_H

#include "net/rime/rimeaddr.h"
#include "sys/rtimer.h"
#include "lib/list.h"
#include "lib/memb.h"

struct phase {
  struct phase *next;
  rimeaddr_t neighbor;
  rtimer_clock_t time;
};

struct phase_list {
  list_t *list;
  struct memb *memb;
};

#define PHASE_LIST(name, num) LIST(phase_list_list);                              \
                              MEMB(phase_list_memb, struct phase, num);           \
                              struct phase_list name = { &phase_list_list, &phase_list_memb }

void phase_init(struct phase_list *list);
void phase_wait(struct phase_list *list,  const rimeaddr_t *neighbor,
                rtimer_clock_t cycle_time, rtimer_clock_t wait_before);
void phase_register(const struct phase_list *list, const rimeaddr_t * neighbor,
                    rtimer_clock_t time);


#endif /* PHASE_H */