cmake_minimum_required(VERSION 3.10)

set (CMAKE_CXX_STANDARD 17)

# 设置项目名称
project(image_narrator)

# 查找OpenCV库
find_package(OpenCV REQUIRED)

# 指定libraw的头文件路径
include_directories(/opt/homebrew/Cellar/libraw/0.21.1/include)

# 添加一个可执行文件
add_executable(image_narrator convert.cpp)

# 链接OpenCV库
target_link_libraries(image_narrator ${OpenCV_LIBS})

# 链接libraw库
target_link_libraries(image_narrator /opt/homebrew/Cellar/libraw/0.21.1/lib/libraw.dylib)

# 添加一个自定义命令
add_custom_target(run
    COMMAND image_narrator
    DEPENDS image_narrator
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)
