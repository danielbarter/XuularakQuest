mkdir -p build

flags="-std=c++17 -g -Wall -Wextra"

libs="$(sdl2-config --cflags) $(sdl2-config --libs) -lGL"

$CC $flags $libs ./src/XuularakQuest.cpp -o ./build/XuularakQuest
