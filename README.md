

vcpkg install --x-feature=client

cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=C:/Haku/Other/vcpkg/scripts/buildsystems/vcpkg.cmake -DVCPKG_TARGET_TRIPLET=x64-windows -G Ninja
ninja -C build && build\Test.exe 
