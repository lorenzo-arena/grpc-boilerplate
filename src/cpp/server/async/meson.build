sources = ['main.cc',
           'AsyncServer.cc',
           'AsyncRPCManager.cc',
           'UnaryRequestManager.cc',
           proto_generated]

executable('grpc-server-async',
           sources,
           dependencies : [ grpc_dep, grpcpp_dep, protobuf_dep, thread_dep ],
           install : true,
           include_directories : [proto_include, common_include])
