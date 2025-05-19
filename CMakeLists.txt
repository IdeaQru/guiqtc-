cmake_minimum_required(VERSION 3.16)
project(GuiSensor VERSION 0.1 LANGUAGES CXX)

# Set standard C++ version used
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)


# Gunakan forward slash sebagai pemisah path
set(CMAKE_PREFIX_PATH "C:/Qt/6.9.0/msvc2022_64")

set(CMAKE_CXX_EXTENSIONS OFF)

# Enable Qt's automatic handling of UIC, MOC, and RCC
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# Set Qt version major
set(QT_VERSION_MAJOR 6)


# Add MSVC specific compiler options
if(MSVC)
    add_compile_options(/Zc:__cplusplus)
endif()

# Find the required Qt components
find_package(Qt6 REQUIRED COMPONENTS Widgets SerialPort PrintSupport LinguistTools WebEngineWidgets)

# Define translation files
set(TS_FILES GuiSensor_id_ID.ts)

# Skip VCPKG setup and set Qt-specific flags
set(QT_CREATOR_SKIP_VCPKG_SETUP ON)
add_definitions(-DQT_NO_VERSION_TAGGING)

# Define project sources explicitly
set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    qcustomplot.cpp
    qcustomplot.h
    widgets/SensorCards/SensorCards.h
    widgets/SensorCards/SensorCards.cpp
    widgets/SensorCards/SensorCards.ui
    widgets/IndividualGraphs/IndividualGraphs.h
    widgets/IndividualGraphs/IndividualGraphs.cpp
    widgets/IndividualGraphs/IndividualGraphs.ui
    widgets/CombinedGraph/CombinedGraphs.h
    widgets/CombinedGraph/CombinedGraphs.cpp
    widgets/CombinedGraph/CombinedGraphs.ui
    widgets/Maps/maps.ui
    widgets/Maps/maps.h
    widgets/Maps/maps.cpp
    utils/SerialHandler.h
    utils/SerialHandler.cpp
)
# qt_add_resources(GuiSensor "resources.qrc")
# Add translation files (not as compile sources)
set(TRANSLATION_FILES ${TS_FILES})

# Create the Qt executable
qt_add_executable(GuiSensor
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES}
    resources.qrc
)

# Create translations for Qt
qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TRANSLATION_FILES})

# Link the necessary Qt libraries
target_link_libraries(GuiSensor PRIVATE
    Qt6::Widgets
    Qt6::SerialPort
    Qt6::PrintSupport
    Qt6::WebEngineWidgets
    Qt6::Quick
    Qt6::QuickWidgets
)

# Set proper target properties for Windows/macOS
set_target_properties(GuiSensor PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.GuiSensor
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

# Include directories for widgets and utils
target_include_directories(GuiSensor PRIVATE
    ${CMAKE_SOURCE_DIR}/widgets
    ${CMAKE_SOURCE_DIR}/utils
)

# Include the project root directory
include_directories(${CMAKE_SOURCE_DIR})

# Install the executable
include(GNUInstallDirs)
install(TARGETS GuiSensor
    BUNDLE DESTINATION . 
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Finalize the Qt executable
qt_finalize_executable(GuiSensor)
