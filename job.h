/*
 * Copyright (c) 2018 Mark Heily <mark@heily.com>
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

#ifndef _JOB_H
#define _JOB_H

#include <stdbool.h>
#include <sys/types.h>
#include <unistd.h>

#ifdef __linux__
#include "queue.h"
#else
#include <sys/queue.h>
#endif /* <sys/queue.h> */

/* Max length of a job ID. Equivalent to FILE_MAX */
#define JOB_ID_MAX 255

enum job_state {
	JOB_STATE_UNKNOWN,
	JOB_STATE_STARTING,
	JOB_STATE_RUNNING,
	JOB_STATE_STOPPING,
	JOB_STATE_STOPPED,
	JOB_STATE_ERROR
};

struct job {
	LIST_ENTRY(job) entries;
	pid_t pid;
	enum job_state state;
	bool exited;
	int last_exit_status, term_signal;
	size_t incoming_edges;

	/* Items below here are parsed from the manifest */
    char **before, **after;
    char *id;
    char *description;
    bool enable, enable_globbing;
    char **environment_variables;
    gid_t gid;
    bool init_groups;
    bool keep_alive;
    char *title;
    char **argv;
    char *root_directory;
    char *standard_error_path;
    char *standard_in_path;
    char *standard_out_path;
    mode_t umask;
    uid_t uid;
	char *user_name;
    char *working_directory;
    char **options;
};

int job_start(struct job *);
void job_free(struct job *);

//TODO: move to parser.h
int parse_job_file(struct job **, const char *, const char *);

#endif /* _JOB_H */