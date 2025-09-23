#ifndef CLIENT_H
#define CLIENT_H

#include <stddef.h>

static void append_data(char **data, size_t *size, const char *buf, size_t len);

void http_get(const char *url, char **out_data, size_t *out_size);

void https_get(const char *url, const char *path, char **out_data,
	       size_t *out_size);

#endif