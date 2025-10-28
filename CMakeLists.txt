cmake_minimum_required(VERSION 3.31)

set(PROJECT_NAME ParticleGravity)

project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)

# define a function for adding git dependencies
function(include_dependency libName gitURL gitTag)
    # setup the declare
    FetchContent_Declare(${libName}
        GIT_REPOSITORY ${gitURL}
        GIT_TAG ${gitTag}
        GIT_SHALLOW TRUE
        GIT_PROGRESS TRUE
    )

    FetchContent_MakeAvailable(${libName})
endfunction()

# add raylib support
set(RAYLIB_LIB raylib)
find_package(${RAYLIB_LIB} QUIET)
if (NOT ${RAYLIB_LIB}_FOUND)
    message(STATUS "Getting ${RAYLIB_LIB} from Github")
    include_dependency(${RAYLIB_LIB} https://github.com/raysan5/raylib.git 5.5)
else ()
    message(STATUS "Using local ${RAYLIB_LIB}")
endif ()

find_package(glfw3 CONFIG REQUIRED)
find_package(liblo CONFIG REQUIRED)

# Include directory
set(PROJECT_INCLUDE "${CMAKE_CURRENT_LIST_DIR}/include")

# Shaders directory
set(SHADERS_DIR resources/shaders)

add_executable(${PROJECT_NAME}
    main.cpp
    Scene.h
    Scene.cpp
    Particle.h
    Particle.cpp
    ParticleSystem.h
    ParticleSystem.cpp
    Particle.cpp
    Attractor.h
    AppConfig.h
    OscHandler.h
    SceneCamera.h
)

# Sources
target_sources(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCES})

# Include
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_INCLUDE})

target_link_libraries(${PROJECT_NAME} PRIVATE glfw)
target_link_libraries(${PROJECT_NAME} PRIVATE ${RAYLIB_LIB})
target_link_libraries(${PROJECT_NAME} PRIVATE liblo::liblo liblo::liblo_static)


target_compile_definitions(${PROJECT_NAME}
    PUBLIC
    ASSETS_PATH="${CMAKE_CURRENT_SOURCE_DIR}/assets/"
)

