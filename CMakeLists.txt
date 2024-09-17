cmake_minimum_required(VERSION 3.16)

project(drecognize LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

find_package(OpenCV REQUIRED)

include_directories(/usr/include/tesseract)
include_directories(/usr/include/leptonica)

add_executable(drecognize
  main.cpp
  Digit.hpp
  ILocation.hpp
  Position.hpp        Position.cpp
  Target.hpp          Target.cpp

  ImageProcessing.hpp ImageProcessing.cpp
  DigitRecognition.hpp  DigitRecognition.cpp
)
target_link_libraries(drecognize Qt${QT_VERSION_MAJOR}::Core ${OpenCV_LIBS} -ltesseract -lleptonica)

include(GNUInstallDirs)
install(TARGETS drecognize
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
