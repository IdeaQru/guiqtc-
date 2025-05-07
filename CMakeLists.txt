cmake_minimum_required(VERSION 3.16)
project(GuiSensor VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# 1. Tambahkan modul SerialPort dan PrintSupport untuk QCustomPlot
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets SerialPort PrintSupport LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets SerialPort PrintSupport LinguistTools)
set(TS_FILES GuiSensor_id_ID.ts)

# 2. Tambahkan file QCustomPlot ke dalam sumber
set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    qcustomplot.cpp  # Pastikan file ini ada di folder proyek
    qcustomplot.h     # Pastikan file ini ada di folder proyek
    widgets/SensorCards/SensorCards.h
    widgets/SensorCards/SensorCards.cpp
    widgets/SensorCards/SensorCards.ui
    widgets/IndividualGraphs/IndividualGraphs.h
    widgets/IndividualGraphs/IndividualGraphs.cpp
    widgets/IndividualGraphs/IndividualGraphs.ui
    widgets/CombinedGraph/CombinedGraphs.h
    widgets/CombinedGraph/CombinedGraphs.cpp
    widgets/CombinedGraph/CombinedGraphs.ui
    utils/SerialHandler.h
    utils/SerialHandler.cpp
    ${TS_FILES}
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(GuiSensor
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    if(ANDROID)
        add_library(GuiSensor SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(GuiSensor
            ${PROJECT_SOURCES}
        )
    endif()
    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

# 3. Link library Qt yang diperlukan
# 3. Link library Qt yang diperlukan
target_link_libraries(GuiSensor PRIVATE 
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::SerialPort
    Qt${QT_VERSION_MAJOR}::PrintSupport
)

# Tambahkan EntryPoint hanya jika menggunakan Qt6
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    target_link_libraries(GuiSensor PRIVATE Qt6::EntryPoint)
endif()


# 4. Set properties tambahan (opsional)
if(${QT_VERSION} VERSION_LESS 6.1.0)
    set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.GuiSensor)
endif()
set_target_properties(GuiSensor PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS GuiSensor
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
# Di CMakeLists.txt
set(CMAKE_GENERATOR "Visual Studio 17 2022" -A x64)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(GuiSensor)
endif()
