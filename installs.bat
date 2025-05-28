cd thirdparty
cd glfw
cmake -B build -S . -G Ninja -DCMAKE_INSTALL_PREFIX=./glfw-instal
cmake --build build --target install