cmake_minimum_required(VERSION 3.16)
project(GuiSensor VERSION 0.1 LANGUAGES CXX)

# Set standar C++ yang digunakan
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Aktifkan fitur otomatis Qt
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# Set versi Qt
set(QT_VERSION_MAJOR 6)

# Cari Qt6 dan komponen yang dibutuhkan
find_package(Qt6 REQUIRED COMPONENTS Widgets SerialPort PrintSupport LinguistTools)

# Definisikan file terjemahan
set(TS_FILES GuiSensor_id_ID.ts)
set(QT_CREATOR_SKIP_VCPKG_SETUP ON)
add_definitions(-DQT_NO_VERSION_TAGGING)
file(GLOB SOURCES CONFIGURE_DEPENDS "widgets/*.cpp")

# Definisikan semua sumber daya proyek secara eksplisit (hindari GLOB)
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
    utils/SerialHandler.h
    utils/SerialHandler.cpp
)

# Tambahkan file terjemahan ke proyek (tidak sebagai sumber kompilasi)
set(TRANSLATION_FILES
    ${TS_FILES}
)

# Membuat executable untuk proyek Qt
qt_add_executable(GuiSensor
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES}
)

# Membuat file terjemahan untuk Qt
qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TRANSLATION_FILES})

# Menambahkan library yang diperlukan
target_link_libraries(GuiSensor PRIVATE
    Qt6::Widgets
    Qt6::SerialPort
    Qt6::PrintSupport
)

# Set properti target untuk Windows dan macOS
set_target_properties(GuiSensor PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.GuiSensor
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)
target_include_directories(GuiSensor PRIVATE
    ${CMAKE_SOURCE_DIR}/widgets
    ${CMAKE_SOURCE_DIR}/utils
)

# Instalasi untuk executable
include(GNUInstallDirs)
install(TARGETS GuiSensor
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Finalisasi executable
qt_finalize_executable(GuiSensor)
