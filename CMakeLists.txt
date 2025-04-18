cmake_minimum_required(VERSION 3.10)
project(NodeBasedImageProcessorCpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC_SEARCH_PATHS "${CMAKE_CURRENT_SOURCE_DIR}/include")

set(OpenCV_DIR "D:/vcpkg/installed/x64-windows/share/opencv4")
set(Qt5_DIR "D:/vcpkg/installed/x64-windows/share/qt5-base")

find_package(OpenCV REQUIRED)
find_package(Qt5 COMPONENTS Widgets REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS} include)

add_executable(NodeBasedImageProcessorCpp
    src/main.cpp 
    src/MainWindow.cpp

    src/ImageInputNode.cpp 
    src/OutputNode.cpp
    src/BrightnessContrastNode.cpp 
    src/ColorChannelSplitter.cpp 
    src/BlurNode.cpp 
    src/ThresholdNode.cpp
    src/EdgeDetectionNode.cpp
    src/BlendNode.cpp
    src/NoiseGenerationNode.cpp
    src/ConvolutionFilterNode.cpp

    src/NodeGraph.cpp
    
    include/MainWindow.h   # This ensures AUTOMOC runs on MainWindow.h
    include/Node.h
    include/ImageInputNode.h
    include/BrightnessContrastNode.h
    include/OutputNode.h
    include/BlurNode.h
    include/ThresholdNode.h
    include/EdgeDetectionNode.h
    include/BlendNode.h
    include/NoiseGenerationNode.h
    include/ConvolutionFilterNode.h
    include/ColorChannelSplitter.h
    include/NodeGraph.h
)

target_link_libraries(NodeBasedImageProcessorCpp
    ${OpenCV_LIBS}
    Qt5::Widgets
    Qt5::Core
)
