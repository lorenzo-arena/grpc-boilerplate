sources = ['main.cc',
           'BoilerplateService.cc',
           'SyncServer.cc',
           proto_generated]

executable('grpc-server-sync',
           sources,
           dependencies : [ grpc_dep, grpcpp_dep, protobuf_dep ],
           install : true,
           include_directories : [proto_include, common_include])
