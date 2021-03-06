/**
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

#include <os/os.h>

#include <util/cbmem.h>

#include <console/console.h>

#include "log/log.h"


static int
log_console_append(struct log *log, void *buf, int len)
{
    struct log_entry_hdr *hdr;

    if (!console_is_init()) {
        return (0);
    }

    if (!console_is_midline) {
        hdr = (struct log_entry_hdr *) buf;
        console_printf("[ts=%lussb, mod=%u level=%u] ",
                (unsigned long) hdr->ue_ts, hdr->ue_module,
                hdr->ue_level);
    }

    console_write((char *) buf + LOG_ENTRY_HDR_SIZE, len - LOG_ENTRY_HDR_SIZE);

    return (0);
}

static int
log_console_read(struct log *log, void *dptr, void *buf, uint16_t offset,
        uint16_t len)
{
    /* You don't read console, console read you */
    return (OS_EINVAL);
}

static int
log_console_walk(struct log *log, log_walk_func_t walk_func, void *arg)
{
    /* You don't walk console, console walk you. */
    return (OS_EINVAL);
}

static int
log_console_flush(struct log *log)
{
    /* You don't flush console, console flush you. */
    return (OS_EINVAL);
}

int
log_console_handler_init(struct log_handler *handler)
{
    handler->log_type = LOG_TYPE_STREAM;
    handler->log_read = log_console_read;
    handler->log_append = log_console_append;
    handler->log_walk = log_console_walk;
    handler->log_flush = log_console_flush;
    handler->log_arg = NULL;

    return (0);
}

