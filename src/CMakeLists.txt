# glob récursif pour .hpp et .cpp
file(GLOB_RECURSE HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp")
file(GLOB_RECURSE SRC_FILES    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

message(STATUS "Headers: ${HEADER_FILES}")
message(STATUS "Sources: ${SRC_FILES}")

set(OUTPUT "shading")

# Déclare l'exécutable avec tous les .cpp et .hpp
add_executable(${OUTPUT}
    ${SRC_FILES}
    ${HEADER_FILES}
)

# Include dirs pour trouver FilePath.hpp, json/Config.hpp, etc.
target_include_directories(${OUTPUT} PRIVATE
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/src/json
)

# Link des bibliothèques (assure-toi que ALL_LIBRARIES contient nlohmann_json)
target_link_libraries(${OUTPUT} PRIVATE
    ${ALL_LIBRARIES}
)

# Propriétés C++17
set_target_properties(${OUTPUT} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)

# Répertoires de sortie
set_target_properties(${OUTPUT} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${OUTPUT_BIN_FOLDER}
    RUNTIME_OUTPUT_DIRECTORY_DEBUG   ${OUTPUT_BIN_FOLDER}
)

# Options de compilation
if (MSVC)
    target_compile_options(${OUTPUT} PRIVATE /W3)
else()
    target_compile_options(${OUTPUT} PRIVATE -Wall -Wextra -pedantic)
endif()
