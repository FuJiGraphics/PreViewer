#pragma once
#include "Core.h"

namespace PreViewer {

	typedef std::chrono::steady_clock sclock;

	//@brief Timer measure time diff between start() and stop()
	class Timer {
	public:
		virtual ~Timer() = default;
		inline void start() { start_time = sclock::now(); }
		inline void stop() { end_time = sclock::now(); }

		inline double elapsed_milli() const
		{
			return std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
		}

		inline double elapsed_sec() const
		{
			return elapsed_milli() * 0.001;
		}

	private:
		sclock::time_point start_time;
		sclock::time_point end_time;
	};
} // namespace Normal