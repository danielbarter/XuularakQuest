mkdir -p build

flags="-std=c++17 -g -Wall -Wextra"

libs="$(sdl2-config --cflags) $(sdl2-config --libs) -lvulkan"

$CC $flags $libs ./src/*.cpp -o ./build/XuularakQuest
