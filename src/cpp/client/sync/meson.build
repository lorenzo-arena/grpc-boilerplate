sources = ['main.cc',
           'BoilerplateClient.cc',
           proto_generated]

executable('grpc-client-sync',
           sources,
           dependencies : [ grpc_dep, grpcpp_dep, protobuf_dep, cxxopts_dep ],
           install : true,
           include_directories : [proto_include, common_include])
