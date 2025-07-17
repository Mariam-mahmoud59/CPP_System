# cmake_minimum_required(VERSION 3.16)
# project(POSApp)

# set(CMAKE_CXX_STANDARD 17)

# find_package(Qt6 COMPONENTS Widgets Sql PrintSupport REQUIRED)

# # Enable Qt's MOC
# set(CMAKE_AUTOMOC ON)

# add_executable(POSApp WIN32
#     main.cpp
#     MainWindow.cpp MainWindow.h
#     DashboardScreen.cpp DashboardScreen.h
#     SalesScreen.cpp SalesScreen.h
#     InventoryScreen.cpp InventoryScreen.h
#     ReportsScreen.cpp ReportsScreen.h
#     Bill.h
#     BillDialog.cpp BillDialog.h
#     LoginDialog.cpp LoginDialog.h
# )

# target_link_libraries(POSApp Qt6::Widgets Qt6::Sql Qt6::PrintSupport)
cmake_minimum_required(VERSION 3.16)
project(POSApp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_PREFIX_PATH "D:/Qt/6.9.1/mingw_64")

# ✅ أضيفي PrintSupport
find_package(Qt6 COMPONENTS Widgets Sql PrintSupport REQUIRED)

add_executable(POSApp WIN32
    main.cpp
    MainWindow.cpp MainWindow.h
    DashboardScreen.cpp DashboardScreen.h
    SalesScreen.cpp SalesScreen.h
    InventoryScreen.cpp InventoryScreen.h
    ReportsScreen.cpp ReportsScreen.h
    LoginDialog.cpp LoginDialog.h
    BillDialog.cpp BillDialog.h
)


target_link_libraries(POSApp Qt6::Widgets Qt6::Sql Qt6::PrintSupport)
