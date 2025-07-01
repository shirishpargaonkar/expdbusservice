#ifndef __sdbuscpp__src_timeinfo_server_hpp__adaptor__H__
#define __sdbuscpp__src_timeinfo_server_hpp__adaptor__H__

#include <timeinfo_adaptor.hpp>

namespace com {
namespace example {

class timeinfo_server : public com::example::timeinfo_adaptor
{
	private:
		std::atomic<bool> stop_{false};
		std::thread ehst_;

	public:
		timeinfo_server(sdbus::IObject & dbusobject);
		~timeinfo_server();

		using timeinfo_adaptor::registerAdaptor;
		std::string GetCurrentTime(const std::string & format);
		uint64_t currenttime();
		using timeinfo_adaptor::emitOnTopOfTheHour;
		void emit_hourly_signal();
		void initialize();

};

}
}
#endif
