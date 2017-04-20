#pragma once

#include <stdint.h>

namespace kiwi {

	class Timer
	{
	public:
		Timer();

		void start();
		void stop();
		void pause();
		void resume();
		uint32_t get_ticks() const;
		uint32_t get_ticks_since_last_call();
		bool is_started() const;
		bool is_paused() const;

	private:
		static uint32_t get_ticks_internal();

		uint32_t start_ticks_;
		uint32_t paused_ticks_;
		uint32_t last_call_ticks_;
		bool paused_;
		bool started_;
	};

}
