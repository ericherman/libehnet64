/* ehnet64.h 64 versions of ntohl and htonl as ntoh64 and hton64
Copyright (C) 2017 Eric Herman <eric@freesa.org>

This work is free software: you can redistribute it and/or modify it
under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or (at
your option) any later version.

This work is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
License for more details.
*/

/*
The header arpa/inet.h declares:

       uint32_t htonl(uint32_t host32);
       uint32_t ntohl(uint32_t net32);

       uint16_t htons(uint16_t host16);
       uint16_t ntohs(uint16_t net16);

however, nothing for 64 bit ... below we #define these:

       uint64_t hton64(uint64_t host64);
       uint64_t ntoh64(uint64_t net64);
*/

#ifndef EHNET64_H
#define EHNET64_H

#ifdef __cplusplus
extern "C" {
#endif

#if HAVE_ENDIAN_H
#include <endian.h>
#define hton64(x) htobe64(x)
#define ntoh64(x) be64toh(x)
#else /* HAVE_ENDIAN_H */

#if HAVE_BYTESWAP_H
#include <byteswap.h>
#endif /* HAVE_BYTESWAP_H */

#if (defined(bswap_64) || HAVE_BSWAP_64)
#define ehnet64_bswap_64(x) bswap_64(x)
#endif /* ifdef bswap_64 */

#if (defined(bswap_32) || HAVE_BSWAP_32)
#define ehnet64_bswap_32(x) bswap_32(x)
#endif /* ifdef bswap_32 */

#ifndef ehnet64_bswap_32
/* okay fine, we'll roll our own by hand */
#define ehnet64_bswap_32(x) \
	((((x) & 0xff000000) >> 24) | (((x) & 0x00ff0000) >>  8) | \
	 (((x) & 0x0000ff00) <<  8) | (((x) & 0x000000ff) << 24))
#endif /* ehnet64_bswap_32 */

#if HAVE_STDINT_H
#include <inttypes.h>		/* uint64_t uint32_t */
#endif /* HAVE_INTTYPES_H */

#if HAVE_STDINT_H
#include <stdint.h>		/* uint64_t uint32_t */
#endif /* HAVE_STDINT_H */

#ifndef ehnet64_bswap_64
#define ehnet64_bswap_64(x) \
	((((uint64_t)ehnet64_bswap_32((uint32_t)x) << 32) | \
          ((uint64_t)ehnet64_bswap_32((uint32_t)(x >> 32)))))
#endif /* ehnet64_bswap_64 */

#define ehnet64_bigendian_host (ehnet64_bswap_32(1U) == 1U)

#define hton64(x) (ehnet64_bigendian_host ? (uint64_t)x : ehnet64_bswap_64(x))

#define ntoh64(x) (ehnet64_bigendian_host ? (uint64_t)x : ehnet64_bswap_64(x))

#endif /* HAVE_ENDIAN_H */

#ifdef __cplusplus
}
#endif

#endif /* EHNET64_H */
