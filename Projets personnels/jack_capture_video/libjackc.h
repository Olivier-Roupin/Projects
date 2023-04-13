#ifdef __cplusplus
extern "C" {
#endif
#include "das_config.h"

#define _GNU_SOURCE 1 // For asprintf

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <unistd.h>
#include <sndfile.h>
#include <pthread.h>
#include <math.h>
#include <stdarg.h>

#include <termios.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <sys/time.h>
#include <sys/resource.h>

#include <jack/jack.h>

#include <libgen.h>
#include <sys/wait.h>

#include "sema.h"

#include "atomic.h"

#include "vringbuffer.h"

char **read_config(int *argc,int max_size);

void append_argv(char **v1,const char **v2,int len1,int len2,int max_size);

void init_arguments(int argc, char *argv[]);

void init_various(void);

void wait_until_recording_finished(void);

void stop_recording_and_cleanup(void);

float* vu_vec(void);
float* buffer_pointer(void);
int buffer_pos(void);
float buffer_min(void);
float buffer_max(void);
int vu_vec_len(void);
int vu_new(void);

#ifdef __cplusplus
}
#endif
