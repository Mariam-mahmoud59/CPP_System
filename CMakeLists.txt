cmake_minimum_required(VERSION 3.16)
project(POSApp)

set(CMAKE_CXX_STANDARD 17)

find_package(Qt6 COMPONENTS Widgets Sql REQUIRED)

add_executable(POSApp WIN32 main.cpp MainWindow.cpp DashboardScreen.cpp SalesScreen.cpp InventoryScreen.cpp ReportsScreen.cpp)

target_link_libraries(POSApp Qt6::Widgets Qt6::Sql)