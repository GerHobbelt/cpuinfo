#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#if !defined(_WIN32)

#include <unistd.h>
#include <fcntl.h>

#endif

#include "monolithic_examples.h"

#if defined(BUILD_MONOLITHIC)
#define main		cpuinfo_dump_main
#endif

#if !defined(_WIN32)

#define BUFFER_SIZE 4096
static char buffer[BUFFER_SIZE];

#define CPUINFO_PATH "/proc/cpuinfo"

int main(int argc, const char** argv) {
	int file = open(CPUINFO_PATH, O_RDONLY);
	if (file == -1) {
		fprintf(stderr, "Error: failed to open %s: %s\n", CPUINFO_PATH, strerror(errno));
		return EXIT_FAILURE;
	}

	/* Only used for error reporting */
	size_t position = 0;
	char* data_start = buffer;
	ssize_t bytes_read;
	do {
		bytes_read = read(file, buffer, BUFFER_SIZE);
		if (bytes_read < 0) {
			fprintf(stderr,
				"Error: failed to read file %s at position %zu: %s\n",
				CPUINFO_PATH,
				position,
				strerror(errno));
			return EXIT_FAILURE;
		}

		position += (size_t)bytes_read;
		if (bytes_read > 0) {
			fwrite(buffer, 1, (size_t)bytes_read, stdout);
		}
	} while (bytes_read != 0);

	if (close(file) != 0) {
		fprintf(stderr, "Error: failed to close %s: %s\n", CPUINFO_PATH, strerror(errno));
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

#else

int main(int argc, const char** argv) {
	fprintf(stderr, "Error: no cpuinfo_dump support.\n");
	return EXIT_FAILURE;
}

#endif
