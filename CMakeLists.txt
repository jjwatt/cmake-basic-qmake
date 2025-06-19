cmake_minimum_required(VERSION 3.15)
project(QMakeExternalProjectExample)

# Include the ExternalProject module to make its commands available.
include(ExternalProject)

# Find the qmake executable. The `REQUIRED` keyword will cause CMake to
# fail with a clear error if it cannot be found.
find_program(QMAKE_EXECUTABLE qmake REQUIRED)

# This is the path to the qmake project's source code.
# IT MUST MATCH YOUR ACTUAL DIRECTORY NAME.
set(QMAKE_PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/simple-qmake-project) # <-- THE FIX IS HERE

# This is where the qmake project will be built.
set(QMAKE_PROJECT_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/qmake_build)

ExternalProject_Add(
    simple_qmake_project
    
    # --- Source Location ---
    # Tell ExternalProject where to find the source code on our local disk.
    SOURCE_DIR ${QMAKE_PROJECT_SOURCE_DIR}
    
    # --- Configure Step ---
    # We now pass the correct path to the .pro file. ExternalProject runs this
    # command inside QMAKE_PROJECT_BINARY_DIR.
    CONFIGURE_COMMAND ${QMAKE_EXECUTABLE} ${QMAKE_PROJECT_SOURCE_DIR}/simple_qt.pro
    
    # --- Build Step ---
    # This command runs the build tool (e.g., make, nmake) to compile the application.
    BUILD_COMMAND ${CMAKE_MAKE_PROGRAM}
    
    # --- Install Step ---
    # We are not installing anything, so we specify an empty command.
    INSTALL_COMMAND ""
    
    # --- Directories ---
    # Explicitly tell ExternalProject where to build the project.
    BINARY_DIR ${QMAKE_PROJECT_BINARY_DIR}
)

# Optional: Add a custom target to make it easier to find and run the executable.
# NOTE: The executable name comes from the `TARGET` variable in your .pro file.
add_executable(simple_qt_app IMPORTED GLOBAL)
set_property(
    TARGET simple_qt_app PROPERTY IMPORTED_LOCATION
    ${QMAKE_PROJECT_BINARY_DIR}/simple_qt_app
)

# Make our custom target depend on the ExternalProject target to ensure it's built first.
add_dependencies(simple_qt_app simple_qmake_project)
