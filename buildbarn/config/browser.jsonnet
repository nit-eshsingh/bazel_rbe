// BuildBarn Browser Configuration
// Web UI for exploring the remote cache

{
  blobstore: {
    contentAddressableStorage: {
      grpc: {
        address: 'bb-storage:8980',
        metadata: {
          add: {
            'build.bazel.remote.execution.v2.requestmetadata-bin': {
              inline: std.base64(''),
            },
          },
        },
      },
    },
    actionCache: {
      grpc: {
        address: 'bb-storage:8980',
        metadata: {
          add: {
            'build.bazel.remote.execution.v2.requestmetadata-bin': {
              inline: std.base64(''),
            },
          },
        },
      },
    },
  },
  maximumMessageSizeBytes: 16 * 1024 * 1024,
  listenAddress: ':80',
  defaultInstanceName: '',
}
