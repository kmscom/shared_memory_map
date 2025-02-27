#pragma once

#include <cstdint>
#include <string_view>

namespace SharedMemory {
	static constexpr std::string_view k_shared_memory_name{"my_shared_memory"};
	static constexpr std::uint64_t k_shared_memory_size{ 4 * 1024 * 1024 };
} // namespace SharedMemory
