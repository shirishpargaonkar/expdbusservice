#include "timeinfo_server.hpp"
#include <iostream>

int main(int argc, char *argv[])
{
	// Create a connection to the session bus
	// return type is std::unique_ptr<sdbus::IConnection>
	auto dbsbconnection = sdbus::createSessionBusConnection();

	// Create D-Bus object.
	// return type is std::unique_ptr<sdbus::IObject>
	sdbus::ObjectPath objectPath{"/com/example/timeinfo"};
	auto dbsbobject = sdbus::createObject(*dbsbconnection, objectPath);

	// Create a timeinfo_server object
	com::example::timeinfo_server ts(*dbsbobject);

	// Request service name on the bus connection
	sdbus::ServiceName serviceName{"com.example.timeinfo"};
	dbsbconnection->requestName(serviceName);

	ts.registerAdaptor();
	ts.initialize();

	// Run the I/O event loop on the bus connection.
	dbsbconnection->enterEventLoop();

	return 0;
}
