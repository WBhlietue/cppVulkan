vcpkg install --x-feature=client

cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=C:/Haku/Other/vcpkg/scripts/buildsystems/vcpkg.cmake -DVCPKG_TARGET_TRIPLET=x64-windows -DCMAKE_BUILD_TYPE=Release -G Ninja 
ninja -C build && build\Test.exe

cmake -G Ninja -B build -D CMAKE_TOOLCHAIN_FILE="D:/Documents/C/cRunner/vcpkg/scripts/buildsystems/vcpkg.cmake" -D VCPKG_TARGET_TRIPLET=x64-windows-static -D CMAKE_MSVC_RUNTIME_LIBRARY="MultiThreaded$<$<CONFIG:Debug>:Debug>"
