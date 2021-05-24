//
// Copyright 2020 Staysail Systems, Inc. <info@staysail.tech>
// Copyright 2018 Capitar IT Group BV <info@capitar.com>
// Copyright 2019 Devolutions <info@devolutions.net>
//
// This software is supplied under the terms of the MIT License, a
// copy of which should be located in the distribution where this
// file was obtained (LICENSE.txt).  A copy of the license may also be
// found online at https://opensource.org/licenses/MIT.
//

#ifndef PLATFORM_ZEPHYR_IPC_H
#define PLATFORM_ZEPHYR_IPC_H

#include "core/nng_impl.h"
#include "core/stream.h"

#ifdef NNG_PLATFORM_ZEPHYR
#include "platform/zephyr/zephyr_aio.h"

#include <sys/types.h> // For mode_t

struct nni_ipc_conn {
	nng_stream      stream;
	nni_zephyr_pfd * pfd;
	nni_list        readq;
	nni_list        writeq;
	bool            closed;
	nni_mtx         mtx;
	nni_aio *       dial_aio;
	nni_ipc_dialer *dialer;
	nng_sockaddr    sa;
	nni_reap_node   reap;
};

struct nni_ipc_dialer {
	nng_stream_dialer sd;
	nni_list          connq; // pending connections
	bool              closed;
	nni_mtx           mtx;
	nng_sockaddr      sa;
	nni_atomic_u64    ref;
	nni_atomic_bool   fini;
};

extern int nni_zephyr_ipc_alloc(
    nni_ipc_conn **, nni_sockaddr *, nni_ipc_dialer *);
extern void nni_zephyr_ipc_init(nni_ipc_conn *, nni_zephyr_pfd *);
extern void nni_zephyr_ipc_start(nni_ipc_conn *);
extern void nni_zephyr_ipc_dialer_rele(nni_ipc_dialer *);

#endif // NNG_PLATFORM_ZEPHYR

#endif // PLATFORM_ZEPHYR_IPC_H