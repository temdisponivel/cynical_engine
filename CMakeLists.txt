cmake_minimum_required(VERSION 3.8)
project(cynical_engine)

set(CMAKE_C_STANDARD 99)

# DEPENDENCIES
set(DEP_ROOT_DIR ${CMAKE_SOURCE_DIR}/dependencies)
set(DEP_DIR ${DEP_ROOT_DIR}/x86)

#################### GLFW  ###########################
add_definitions(-DGLFW_DLL)

set(GLFW_DIR "${DEP_DIR}/glfw")
set(GLFW_LIB_DIR "${GLFW_DIR}/lib")
set(GLFW_BIN_DIR "${GLFW_DIR}/bin/")

set(GLFW_LIBRARIES "-L${GLFW_LIB_DIR} -lglfw3")

#################### GLEW ##############################
set(GLEW_DIR "{DEP_DIR}/glew")
set(GLEW_LIB_DIR "${DEP_DIR}/glew/lib")
set(GLEW_BIN_DIR "${DEP_DIR}/glew/bin/")

set(GLEW_LIBRARIES "-L${GLEW_LIB_DIR} -lglew32")

################### OpenGL ###########################
set(GL_LIBRARIES "-lopengl32 -lglu32 -lgdi32")

################### INCLUDING ########################
include_directories(${DEP_ROOT_DIR}/include)
include_directories(include)

################### BUILDING AND LINKING #############
set(SOURCE_FILES main.c include/cynical_math.h include/cynical_camera.h include/cynical_entity.h engine/math/cynical_math.c engine/graphics/cynical_camera.c engine/entity/cynical_entity.c)
add_executable(cynical_engine ${SOURCE_FILES})

target_link_libraries(cynical_engine "${GL_LIBRARIES} ${GLFW_LIBRARIES} ${GLEW_LIBRARIES}")

################### POST-BUILD ################################
file(COPY ${GLFW_BIN_DIR} DESTINATION .)
file(COPY ${GLEW_BIN_DIR} DESTINATION .)