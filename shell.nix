with (import <nixpkgs> {});

mkShell rec {
  buildInputs = [
    # compilers
    gcc
    clang

    # debugging tools
    gdb
    valgrind

    # libraries
    SDL2
    libglvnd
                ];

  # environment for CLANGD
  # CPATH=$CLANGD_PATH emacs
  CLANGD_PATH = builtins.concatStringsSep ":" [

    # C++ stdlib headers
    "${gcc-unwrapped}/include/c++/${gcc.version}"
    "${gcc-unwrapped}/include/c++/${gcc.version}/x86_64-unknown-linux-gnu"

    # libc headers
    "${glibc.dev}/include"

    # compiler specific headers
    "${clang}/resource-root/include"

    # SDL headers
    "${SDL2.dev}/include"

    # opengl headers
    "${libglvnd.dev}/include"

  ];
}
