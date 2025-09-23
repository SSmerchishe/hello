#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

#include "keys.h"
#include "client.h"

int main(int argc, char *argv[])
{
	int res = 0;

	if (!(res = keys_headler(argc, argv)) && argc != 1) {
		return res == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
	}

	char *data = NULL;
	size_t size = 0;

	const char *host = "iss.moex.com";
	const char *path =
		"/iss/history/engines/stock/markets/shares/securities/SBER.json?from=2024-01-01&till=2024-01-03";
	https_get(host, path, &data, &size);

	printf("Полученно %zu байт.\n", size);
	printf("Ответ:\n\n%.*s\n", (int)size, data);

	free(data);

	return res == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}