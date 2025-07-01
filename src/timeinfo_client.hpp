#ifndef __sdbuscpp__src_timeinfo_server_hpp__adaptor__H__
#define __sdbuscpp__src_timeinfo_server_hpp__adaptor__H__

#include <timeinfo_proxy.hpp>
#include <iostream>

namespace com {
namespace example {

class timeinfo_client : public timeinfo_proxy
{
	public:
		timeinfo_client(sdbus::IProxy & cdbsbproxy);
		~timeinfo_client();

		using timeinfo_proxy::registerProxy;
		std::string GetCurrentTime();		// New definition added in this class
		using timeinfo_proxy::GetCurrentTime;	// Since now GetCurrentTime became overloaded
		void onOnTopOfTheHour(const std::string & hour);
};

}
}
#endif
