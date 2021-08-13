project('grpc-c++-boilerplate', 'cpp',
         version : '0.1',
         default_options : ['warning_level=3'])

cpp = meson.get_compiler('cpp')

protoc = find_program('protoc', required : true)
grpc_plugin = find_program('grpc_cpp_plugin', required : true)

grpc_dep = dependency('grpc', required : true, method : 'pkg-config')
grpcpp_dep = dependency('grpc++', required : true, method : 'pkg-config')
protobuf_dep = dependency('protobuf', required : true, method : 'pkg-config')

protoc_args = meson.get_cross_property('protoc_args', [])

proto_gen = generator(protoc,
                      output : ['@BASENAME@.pb.cc', '@BASENAME@.pb.h'],
                      arguments : protoc_args + ['--proto_path=@SOURCE_DIR@/../proto', '--cpp_out=@BUILD_DIR@', '@INPUT@'])

grpc_proto_gen = generator(protoc,
                           output : ['@BASENAME@.grpc.pb.cc', '@BASENAME@.grpc.pb.h'],
                           arguments : protoc_args + ['--proto_path=@SOURCE_DIR@/../proto', '--grpc_out=@BUILD_DIR@', '--plugin=protoc-gen-grpc=' + grpc_plugin.path(), '@INPUT@'])

proto_sources = ['../proto/boiler.proto']
proto_include = include_directories('../proto')

proto_generated = []
proto_generated += proto_gen.process(proto_sources)
proto_generated += grpc_proto_gen.process(proto_sources)

common_include = include_directories('common')

cxxopts_proj = subproject('cxxopts')
cxxopts_dep = cxxopts_proj.get_variable('cxxopts_dep')

subdir('server/sync')
subdir('client/sync')
