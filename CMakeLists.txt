cmake_minimum_required(VERSION 3.16)
project(HexEditor)

set(CMAKE_CXX_STANDARD 20)

find_package(PkgConfig REQUIRED)
pkg_search_module(CRYPTO REQUIRED crypto)
pkg_search_module(GLFW REQUIRED glfw3)
pkg_search_module(GLM REQUIRED glm)
pkg_search_module(CRYPTO REQUIRED libcrypto)
pkg_search_module(CAPSTONE REQUIRED capstone)
find_package(OpenGL REQUIRED)
find_package(LLVM REQUIRED CONFIG)

llvm_map_components_to_libnames(demangler)

include_directories(include ${GLFW_INCLUDE_DIRS} ${CAPSTONE_INCLUDE_DIRS} ${LLVM_INCLUDE_DIRS} libs/ImGui/include libs/glad/include)

SET(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -DIMGUI_IMPL_OPENGL_LOADER_GLAD")

if (WIN32)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc -static")
endif (WIN32)

SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -DRELEASE")
SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG")

add_executable(ImHex
        source/main.cpp
        source/window.cpp
        source/utils.cpp
        source/crypto.cpp
        source/patches.cpp

        source/lang/preprocessor.cpp
        source/lang/lexer.cpp
        source/lang/parser.cpp
        source/lang/validator.cpp
        source/lang/evaluator.cpp

        source/providers/file_provider.cpp

        source/views/view_hexeditor.cpp
        source/views/view_pattern.cpp
        source/views/view_pattern_data.cpp
        source/views/view_hashes.cpp
        source/views/view_information.cpp
        source/views/view_help.cpp
        source/views/view_tools.cpp
        source/views/view_strings.cpp
        source/views/view_data_inspector.cpp
        source/views/view_disassembler.cpp

        libs/glad/source/glad.c

        libs/ImGui/source/imgui.cpp
        libs/ImGui/source/imgui_draw.cpp
        libs/ImGui/source/imgui_widgets.cpp
        libs/ImGui/source/imgui_demo.cpp
        libs/ImGui/source/imgui_impl_glfw.cpp
        libs/ImGui/source/imgui_impl_opengl3.cpp
        libs/ImGui/source/ImGuiFileBrowser.cpp
        libs/ImGui/source/TextEditor.cpp

        resource.rc
        )

if (WIN32)
    target_link_libraries(ImHex libglfw3.a libgcc.a libstdc++.a libmagic.a libgnurx.a libtre.a libintl.a libiconv.a shlwapi.lib libcrypto.a libwinpthread.a libcapstone.a libLLVMDemangle.a)
endif (WIN32)

if (UNIX)
    target_link_libraries(ImHex libglfw.so libmagic.so libcrypto.so libdl.so libcapstone.so libLLVMDemangle.so)
endif (UNIX)