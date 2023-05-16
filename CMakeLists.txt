#prerequis :
#1 - install Vcpkg, Cmake latest stable release, Powershell latest stable release
#2 - Ajouter Vcpkg aux variables d'environnements dans PATH (si installé a la racine de C) : C:\vcpkg
#3 - Install Sfml 64 bit : vcpkg install sfml:x64-windows 
#4 - Ajouter le chemin jusqu'aux fichiers de debug de la sfml installés avec Vcpkg aux variables d'environnements dans PATH : C:\vcpkg\installed\x64-windows\debug\bin
#5 - Redemarrer windows
#6 - Generer la solution utilisant cmake. dans le dossier du CmakeList.txt
#7 - Ouvrir la solution et generer la solution
#
cmake_minimum_required(VERSION 3.8)
project(2DEngine)

# Set C++ standard to C++20
set(CMAKE_CXX_STANDARD 20)

# Tell CMake to use Vcpkg for package management
set(VCPKG_TARGET_TRIPLET "x64-windows-debug")
set(CMAKE_TOOLCHAIN_FILE C:/vcpkg/scripts/buildsystems/vcpkg.cmake)

find_package(SFML 2.5 COMPONENTS system window graphics REQUIRED)

# Add source files

set(SOURCES
    src/GameEngine.cpp
    src/main.cpp
    src/Mobs.cpp
    src/Player.cpp
    src/WindowManager.cpp
    src/Module/DrawableSprite.cpp
)

# Add header files
set(HEADERS
    src/headers/Entity.h
    src/headers/EventHandler.h
    src/headers/GameEngine.h
    src/headers/IEvent.h
    src/headers/Mobs.h
    src/headers/Player.h
    src/headers/WindowManager.h

)

# Add executable target
add_executable(2DEngine ${SOURCES} ${HEADERS})

# Tell CMake to link against the required Vcpkg packages
target_link_libraries(2DEngine sfml-graphics sfml-window sfml-system)