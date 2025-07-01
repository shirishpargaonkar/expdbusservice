#include "timeinfo_client.hpp"

int main(int argc, char *argv[])
{
	// Create a connection to the session bus
	// return type is std::unique_ptr<sdbus::IConnection>
	auto dbsbconnection = sdbus::createSessionBusConnection();

	// Create a proxy.
	sdbus::ObjectPath objectPath{"/com/example/timeinfo"};
	sdbus::ServiceName serviceName{"com.example.timeinfo"};
	auto dbsbproxy = sdbus::createProxy(*dbsbconnection, serviceName, objectPath);

	com::example::timeinfo_client tc(*dbsbproxy);
	tc.registerProxy();

	std::cout << "Current time: " << tc.currenttime() << std::endl;
	std::cout << "Current time: " << tc.GetCurrentTime() << std::endl;
	std::string epoch = "epoch";
	std::cout << "Current time: " << tc.GetCurrentTime(epoch) << std::endl;
	std::string epoc = "epoc";
	std::cout << "Current time: " << tc.GetCurrentTime(epoc) << std::endl;

	// Run the I/O event loop on the bus connection.
	dbsbconnection->enterEventLoop();

	return 0;
}
