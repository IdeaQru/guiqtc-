# Buat direktori build baru untuk release
mkdir build-release
cd build-release

# Konfigurasi CMake untuk release
cmake -S .. -B . -G "Visual Studio 17 2022" -A x64 -DCMAKE_BUILD_TYPE=Release

# Build aplikasi
cmake --build . --config Release

# Hasil build akan berada di direktori build-release/Release/
