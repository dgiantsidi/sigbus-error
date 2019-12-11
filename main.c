#include <sys/mman.h>
#include <sys/stat.h>        /* For mode constants */
#include <fcntl.h>           /* For O_* constants */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#define FTRUNCATE_SIZE 1024  // in spdk/dpdk is 135335048

static char g_shm_name[64];

int main(int args, char* argv[]) {
	int trace_fd;
	char* shm_name = "foo";
	fprintf(stdout, "PID : %d\n", getpid());

	snprintf(g_shm_name, sizeof(g_shm_name), "%s", shm_name);

	trace_fd = shm_open("foo", O_RDWR | O_CREAT, 0600);
	if (trace_fd == -1) {
		fprintf(stderr, "could not shm_open spdk_trace\n");
		fprintf(stderr, "errno=%d %s\n", errno, strerror(errno));
	}
	fprintf(stdout, "shm_open() OK!\n");


	if (ftruncate(trace_fd, FTRUNCATE_SIZE) != 0) {
		fprintf(stderr, "could not truncate shm\n");
		exit(EXIT_FAILURE);
	}
	fprintf(stdout, "ftruncate() OK!\n");

	void* g_trace_histories = mmap(NULL, FTRUNCATE_SIZE, PROT_READ | PROT_WRITE,
			MAP_SHARED, trace_fd, 0);

	if (g_trace_histories == MAP_FAILED) {
		fprintf(stderr, "could not mmap shm\n");
	}
	fprintf(stdout, "mmap() OK!\n");

	// sleep(10);

	memset(g_trace_histories, 0, FTRUNCATE_SIZE);

	fprintf(stdout, "memset() OK!\n");
	return 0;
}
