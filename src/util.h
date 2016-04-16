/*
 * Copyright (c) 2016 Mark Heily <mark@heily.com>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#ifndef _RELAUNCHD_UTIL_H_
#define _RELAUNCHD_UTIL_H_

#include <stdarg.h>
#include <limits.h>

static inline void
path_sprintf(char (*buf)[PATH_MAX], const char *format, ...)
{
	int len;
	va_list args;

	if (buf == NULL)
		errx(1, "null pointer");
	
	va_start(args, format);
	len = vsnprintf((char *)buf, sizeof(*buf), format, args);
	va_end(args);
	
	if (len < 0) 
		err(1, "vsnprintf(3)");
        if (len >= (int)sizeof(*buf)) {
                errno = ENAMETOOLONG;
		err(1, "vsnprintf(3)");
        }
}

/* Make a directory idempotently */
static inline void
mkdir_idempotent(const char *path, mode_t mode)
{
	if (mkdir(path, mode) < 0) {
		if (errno == EEXIST)
			return;

		err(1, "mkdir(2)");
	}
}

#endif /* _RELAUNCHD_UTIL_H_ */