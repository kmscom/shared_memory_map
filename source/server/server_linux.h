#pragma once

#include <cstdint>
#include <cstring>

#include "server.h"

namespace SharedMemory {
	class ServerLinux : public Server {
	public:
		~ServerLinux() override;
		bool create(std::string_view name, std::uint64_t size) override;
		bool close() override;

	private:
		int m_shm_fd{ -1 };

	};
} // namespace SharedMemory
