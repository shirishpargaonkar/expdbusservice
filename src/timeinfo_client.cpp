#include "timeinfo_client.hpp"

namespace com {
namespace example {

timeinfo_client::timeinfo_client(sdbus::IProxy & cdbsbproxy) : timeinfo_proxy(cdbsbproxy)
{
}

timeinfo_client::~timeinfo_client()
{
}

std::string timeinfo_client::GetCurrentTime()
{
	const std::string empty = "";
	return timeinfo_proxy::GetCurrentTime(empty);
}

void timeinfo_client::onOnTopOfTheHour(const std::string& hour)
{
	std::cout << "Signal received. hour: = " << hour << std::endl;
}

}
}
