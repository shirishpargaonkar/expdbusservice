#include "timeinfo_server.hpp"
#include <iomanip>
#include <chrono>
#include <thread>
#include <iostream>

namespace com {
namespace example {

timeinfo_server::timeinfo_server(sdbus::IObject & dbusobject) : timeinfo_adaptor(dbusobject)
{
}

timeinfo_server::~timeinfo_server()
{
	stop_ = true;
}

void timeinfo_server::initialize()
{
	std::thread t([this](){emit_hourly_signal();});
	t.detach();
}

void timeinfo_server::emit_hourly_signal()
{
	while (stop_ == false) {
		// Calculate time until next top of the hour
		auto now = std::chrono::system_clock::now();
		auto next_hour = std::chrono::time_point_cast<std::chrono::hours>(now) + std::chrono::hours(1);

		std::this_thread::sleep_until(next_hour);
		if (stop_) break;

		// Format hour string, e.g., "10:00"
		std::time_t tt = std::chrono::system_clock::to_time_t(next_hour);
		char buf[6];
		std::strftime(buf, sizeof(buf), "%H:00", std::localtime(&tt));
		std::string hour(buf);

		emitOnTopOfTheHour(hour);
	}
}

std::string timeinfo_server::GetCurrentTime(const std::string& format)
{
	if (format == "epoch")
		return std::to_string(timeinfo_server::currenttime());
	else {
		std::time_t timet;
		std::tm * tmptr;
		std::ostringstream oss;

		timet = static_cast<std::time_t>(timeinfo_server::currenttime());
		tmptr = std::localtime(&timet);
		oss << std::put_time(tmptr, "%Y-%m-%d %H:%M:%S");

		return oss.str();
	}
}

// returns seconds since epoch
uint64_t timeinfo_server::currenttime()
{
	// now() returns an object of class time_point
	auto now = std::chrono::system_clock::now();

	// time_since_epoch() returns an object of class duration
	auto duration = std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch());

	// duration in nanoseconds is the time since epoch.
	// It is cast to seconds and the count of seconds is returned.
	// This is equivalent of time_t returned by time() system call.

	return duration.count();
}

}
}
