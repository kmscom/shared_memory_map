#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

#include <cstdint>
#include <cstring>
#include <iostream>
#include <memory>

#include "info.h"
#include "server.h"
#include "server_linux.h"

using namespace SharedMemory;

int main()
{
	auto shm_server = std::make_unique<SharedMemory::ServerLinux>();
	shm_server->create(k_shared_memory_name, k_shared_memory_size);
	shm_server->close();
	return 0;
}

