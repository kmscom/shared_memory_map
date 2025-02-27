#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

#include <cstdint>
#include <cstring>
#include <iostream>

#include "info.h"
#include "server.h"
#include "server_linux.h"

using namespace std;

namespace SharedMemory {
	ServerLinux::~ServerLinux() { 
		this->close();
	}

	bool ServerLinux::close() {
		if (m_memory != nullptr) {
			munmap((void *) m_memory, m_size);
			m_memory = nullptr;
		}

		if (m_shm_fd != -1) {
			::close(m_shm_fd);
			shm_unlink(m_name.data());
			m_shm_fd = -1;
		}

		return true;
	}

	bool ServerLinux::create(std::string_view name, std::uint64_t size) {
		this->close();

		m_name = name;
		int m_shm_fd = shm_open(m_name.data(), O_CREAT | O_RDWR, 0666);
		if (m_shm_fd == -1)
		{
			perror("shm_open error");
			return false;
		}

		if (ftruncate(m_shm_fd, size) == -1) {
			perror("shm_ftruncate error");
			return false;
		}

		m_memory = mmap(0, size, PROT_READ | PROT_WRITE, MAP_SHARED, m_shm_fd, 0);
		if (m_memory == MAP_FAILED)
		{
			m_memory = nullptr;
			perror("mmap failed");
			return false;
		}

		return true;
	}

} // namespace SharedMemory

