#ifndef CLIENT_H
#define CLIENT_H

#include <stddef.h>
#include "error.h"

static api_err_t append_data(char **data, size_t *size, const char *buf,
			     size_t len);

api_err_t http_get(const char *url, char **out_data, size_t *out_size);

api_err_t https_get(const char *url, const char *path, char **out_data,
		    size_t *out_size);

#endif