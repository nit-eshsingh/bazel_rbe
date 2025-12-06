// BuildBarn Storage Configuration
// This configures the Content Addressable Storage (CAS) and Action Cache (AC)

{
  blobstore: {
    contentAddressableStorage: {
      'local': {
        keyLocationMapOnBlockDevice: {
          file: {
            path: '/storage-cas/key_location_map',
            sizeBytes: 16 * 1024 * 1024,
          },
        },
        keyLocationMapMaximumGetAttempts: 8,
        keyLocationMapMaximumPutAttempts: 32,
        oldBlocks: 8,
        currentBlocks: 24,
        newBlocks: 1,
        blocksOnBlockDevice: {
          source: {
            file: {
              path: '/storage-cas/blocks',
              sizeBytes: 10 * 1024 * 1024 * 1024,  // 10 GB CAS storage
            },
          },
          spareBlocks: 3,
        },
        persistent: {
          stateDirectoryPath: '/storage-cas/persistent_state',
          minimumEpochInterval: '300s',
        },
      },
    },
    actionCache: {
      'local': {
        keyLocationMapOnBlockDevice: {
          file: {
            path: '/storage-ac/key_location_map',
            sizeBytes: 16 * 1024 * 1024,
          },
        },
        keyLocationMapMaximumGetAttempts: 8,
        keyLocationMapMaximumPutAttempts: 32,
        oldBlocks: 8,
        currentBlocks: 24,
        newBlocks: 1,
        blocksOnBlockDevice: {
          source: {
            file: {
              path: '/storage-ac/blocks',
              sizeBytes: 1 * 1024 * 1024 * 1024,  // 1 GB Action Cache storage
            },
          },
          spareBlocks: 3,
        },
        persistent: {
          stateDirectoryPath: '/storage-ac/persistent_state',
          minimumEpochInterval: '300s',
        },
      },
    },
  },
  httpListenAddress: ':7980',
  grpcServers: [{
    listenAddresses: [':8980'],
    authenticationPolicy: { allow: {} },
  }],
  allowActionCacheUpdatesForInstances: [''],
  maximumMessageSizeBytes: 16 * 1024 * 1024,
}
