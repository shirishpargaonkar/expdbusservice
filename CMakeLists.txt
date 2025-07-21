cmake_minimum_required(VERSION 3.10)
project(timeinfo_example)

include(GNUInstallDirs)

find_package(sdbus-c++ REQUIRED)

set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/interface)
set(GEN_DIR ${CMAKE_CURRENT_SOURCE_DIR}/generated)
set(INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(SVC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/service)
set(XML2CPP sdbus-c++-xml2cpp)

include_directories(${INC_DIR} ${GEN_DIR} /usr/local/include)
link_directories(/usr/local/lib)

add_custom_command(
  OUTPUT ${GEN_DIR}/timeinfo_adaptor.hpp
         ${GEN_DIR}/timeinfo_proxy.hpp
  COMMAND mkdir -p ${CMAKE_CURRENT_SOURCE_DIR}/generated
  COMMAND ${XML2CPP} --adaptor=${GEN_DIR}/timeinfo_adaptor.hpp
                     --proxy=${GEN_DIR}/timeinfo_proxy.hpp
                     ${INT_DIR}/timeinfo.xml
  DEPENDS ${INT_DIR}/timeinfo.xml
  COMMENT "Generating sdbus-c++ adaptor and proxy"
)

add_custom_target(generate_apheaders
  DEPENDS ${GEN_DIR}/timeinfo_adaptor.hpp ${GEN_DIR}/timeinfo_proxy.hpp
)

add_executable(timeinfo_server ${SRC_DIR}/timeinfo_server.cpp ${SRC_DIR}/timeinfo_smain.cpp ${GEN_DIR}/timeinfo_adaptor.hpp)
target_link_libraries(timeinfo_server sdbus-c++ systemd)

add_executable(timeinfo_client ${SRC_DIR}/timeinfo_client.cpp ${SRC_DIR}/timeinfo_cmain.cpp ${GEN_DIR}/timeinfo_proxy.hpp)
target_link_libraries(timeinfo_client sdbus-c++ systemd)

install(TARGETS timeinfo_server timeinfo_client RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
install(FILES ${SVC_DIR}/com.example.timeinfo.service DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/dbus-1/services)

