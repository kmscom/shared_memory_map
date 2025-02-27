#pragma once

#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

#include <cstdint>
#include <cstring>
#include <iostream>

#include "info.h"

namespace SharedMemory {
	class Server {
	public:
		virtual ~Server() = default;
		virtual bool create(std::string_view name, std::uint64_t size) = 0;
		virtual bool close() = 0;

		char* get_memory() { return (char *) m_memory; }
		std::uint64_t get_size() const { return m_size; }

	protected:
		std::uint64_t m_size{ k_shared_memory_size };
		std::string   m_name{""};

		volatile void* m_memory{ nullptr };
	};

} // namespace SharedMemory
