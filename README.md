# gRPC boilerplate examples

This repository was made to host some simple gRPC examples which can be used as a boilerplate for bigger projects.

The main aim is to share some of the "aha!" moments which came out while developing with the gRPC C++ library.

## gRPC++

The first examples will be in C++, however I would like to integrate the repository with other languages.

### Compiling

The examples have been developed in Ubuntu, however similar instructions applies also for other Linux distributions.

First install all the dependencies:

```sh
# Build system
sudo apt install -y meson ninja-build

# gRPC and protobuf dependencies
sudo apt install -y protobuf-compiler protobuf-compiler-grpc libprotobuf-dev libgrpc-dev libgrpc++-dev
```

Then `meson` can be used to build the project:

```sh
cd src/cpp
meson build
cd build
ninja
```

The binaries will be contained in a tree matching the source tree, so the `grpc-server-sync` binary can be found in *build/server/sync*.

