# BuildBarn Remote Caching Setup

This directory contains the configuration for BuildBarn remote build caching.

## What is BuildBarn?

BuildBarn is an open-source implementation of the Remote Execution and Remote Caching APIs used by Bazel. It provides:
- **Content Addressable Storage (CAS)**: Stores build artifacts
- **Action Cache (AC)**: Caches build results to avoid redundant builds
- **Remote Execution**: Can distribute builds across multiple workers (not configured here)

## Architecture

```
┌─────────────┐
│   Bazel     │
│   Client    │
└──────┬──────┘
       │ gRPC (port 8980)
       ▼
┌─────────────┐
│ BB-Storage  │  ◄── Stores CAS + AC
└─────────────┘
       │
       ▼
┌─────────────┐
│ BB-Browser  │  ◄── Web UI (http://localhost:8081)
└─────────────┘
```

## Prerequisites

- Docker Desktop installed and running
- Docker Compose available

## Setup Instructions

### 1. Start BuildBarn Services

```powershell
# From the project root directory
docker-compose up -d
```

This starts:
- **bb-storage** on port 8980 (gRPC) and 7980 (HTTP)
- **bb-browser** on port 8081 (Web UI)

### 2. Verify Services are Running

```powershell
# Check running containers
docker-compose ps

# View logs
docker-compose logs -f storage
docker-compose logs -f browser
```

### 3. Access Web UI

Open your browser and navigate to:
```
http://localhost:8081
```

This provides a web interface to explore cached artifacts and action cache entries.

## Using Remote Caching with Bazel

### Build with Remote Cache

```powershell
# Clean build (clears local cache)
bazel clean

# Build with remote caching enabled
bazel build --config=remote-cache //c_project/automotive:automotive_app

# All subsequent builds will use the remote cache
bazel build --config=remote-cache //cpp_project:cpp_app
bazel test --config=remote-cache //cpp_project/tests:all_tests
```

### Make Remote Caching Default (Optional)

To always use remote caching, add this line to `.bazelrc`:

```
build --config=remote-cache
```

Then you can just use:
```powershell
bazel build //...
```

## Verifying Cache Hits

### First Build (Cache Miss)
```powershell
bazel clean
bazel build --config=remote-cache //c_project/automotive:automotive_app
```

Output will show actions being executed.

### Second Build (Cache Hit)
```powershell
# Don't clean - just rebuild
bazel build --config=remote-cache //c_project/automotive:automotive_app
```

Output should show:
```
INFO: 1 process: 1 remote cache hit.
```

### Exploring the Cache

1. Open http://localhost:8081
2. Click on "Content Addressable Storage" to see stored artifacts
3. Click on "Action Cache" to see cached build actions

## Storage Configuration

Current storage limits:
- **CAS**: 10 GB (Content Addressable Storage)
- **AC**: 1 GB (Action Cache)

These can be adjusted in `buildbarn/config/storage.jsonnet`.

## Stopping BuildBarn

```powershell
# Stop services
docker-compose stop

# Stop and remove containers
docker-compose down

# Stop, remove containers, and delete volumes (clears cache)
docker-compose down -v
```

## Troubleshooting

### Connection Refused
- Ensure Docker is running
- Check services: `docker-compose ps`
- View logs: `docker-compose logs storage`

### Cache Not Working
- Verify gRPC port 8980 is accessible
- Check Bazel uses correct config: `--config=remote-cache`
- Ensure `--remote_upload_local_results=true` is set

### Clear Remote Cache
```powershell
# Stop and remove volumes
docker-compose down -v

# Recreate services
docker-compose up -d
```

## Benefits of Remote Caching

1. **Faster CI/CD**: Share cache between CI builds
2. **Team Collaboration**: Developers share build artifacts
3. **Clean Builds**: Faster even after `bazel clean`
4. **Cross-Machine**: Cache persists across different machines

## Advanced Configuration

### Multi-User Setup
To share cache across a team, deploy BuildBarn on a shared server and update:

```
build:remote-cache --remote_cache=grpc://your-server:8980
```

### Monitoring
Access storage metrics at:
```
http://localhost:7980/metrics
```

### Security
For production, enable authentication in `storage.jsonnet`:
```jsonnet
authenticationPolicy: {
  'tls': {
    // TLS configuration
  },
}
```

## References

- [BuildBarn GitHub](https://github.com/buildbarn/bb-storage)
- [Bazel Remote Caching](https://bazel.build/remote/caching)
- [Remote Execution API](https://github.com/bazelbuild/remote-apis)
