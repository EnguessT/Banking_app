cmake_minimum_required(VERSION 3.20)
project(banking VERSION 1.0 LANGUAGES C)

# Compiler warnings
add_compile_options(-Wall -Wextra -Werror)

# Find GTK3
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

# Include directories
include_directories(
    ${PROJECT_SOURCE_DIR}/include
    ${GTK3_INCLUDE_DIRS}
)

# Source files
set(SOURCES
    src/ui/main_window.c
    src/ui/client_window.c
    src/ui/admin_window.c
    src/ui/registration.c
	src/ui/widgets.c
	src/db/database_context.c
	src/core/buttons_callback.c
	src/core/verifications.c
    src/main.c
)

# Executable
add_executable(final ${SOURCES})

# Link libraries
target_link_libraries(final
    PRIVATE
        sqlite3
        ${PROJECT_SOURCE_DIR}/libs/bcrypt.a
        ${GTK3_LIBRARIES}
)
