cmake_minimum_required(VERSION 3.12.4)
project(binner VERSION 0.0.0)

find_package(Qt6 REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS Gui)

include_directories(${PROJECT_SOURCE_DIR}/include)

file(GLOB SOURCES "src/*.cpp")
add_executable(binner ${SOURCES})

target_link_libraries(binner Qt6::Widgets)
target_link_libraries(binner Qt6::Gui)

target_compile_features(binner PUBLIC cxx_std_17)
target_compile_options(binner PRIVATE
	$<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
		-Wall -Wextra -Wpedantic -Walloca -Wcast-qual -Wconversion -Wdate-time>
	$<$<CXX_COMPILER_ID:GNU>:
		-Wformat-overflow -Wnull-dereference -Wimplicit-fallthrough=5 -Wmissing-include-dirs
		-Wswitch-enum -Wstrict-aliasing=1 -Wduplicated-branches -Wduplicated-cond -Wshadow -Wundef -Wcast-align=strict -Wlogical-op -Wmissing-declarations -Wredundant-decls>
	$<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>>:
		-Wabstract-vbase-init -Wanon-enum-enum-conversion -Wassign-enum -Watomic-implicit-seq-cst
		-Wbad-function-cast -Wbitfield-constant-conversion -Wc++11-narrowing -Wcast-align -Wchar-subscripts
		-Wcomma -Wctad-maybe-unsupported -Wdeprecated -Wduplicate-enum -Wfor-loop-analysis -Wformat-type-confusion
		-Wfour-char-constants -Wframe-address -Wgnu -Wheader-hygiene -Widiomatic-parentheses -Wint-in-bool-context
		-Wmicrosoft -Wmost>)
set_property(TARGET binner PROPERTY CXX_EXTENSIONS OFF)
