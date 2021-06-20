#pragma once

#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Blink
{
	class BLINK_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger(){ return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger(){ return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

// Core Log Macros
#define BL_CORE_TRACE(...)     ::Blink::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define BL_CORE_INFO(...)      ::Blink::Log::GetCoreLogger()->info(__VA_ARGS__)
#define BL_CORE_WARN(...)      ::Blink::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define BL_CORE_ERROR(...)     ::Blink::Log::GetCoreLogger()->error(__VA_ARGS__)
#define BL_CORE_CRITICAL(...)  ::Blink::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Core Log Macros
#define BL_TRACE(...)          ::Blink::Log::GetClientLogger()->trace(__VA_ARGS__)
#define BL_INFO(...)           ::Blink::Log::GetClientLogger()->info(__VA_ARGS__)
#define BL_WARN(...)           ::Blink::Log::GetClientLogger()->warn(__VA_ARGS__)
#define BL_ERROR(...)          ::Blink::Log::GetClientLogger()->error(__VA_ARGS__)
#define BL_CRITICAL(...)       ::Blink::Log::GetClientLogger()->critical(__VA_ARGS__)