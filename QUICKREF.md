# Quick Reference - Automotive Modules & Remote Caching

## Automotive Modules Overview

### Available Components

| Module | Description | Key Features |
|--------|-------------|--------------|
| **Clutch** | Clutch system simulation | Engagement control, wear tracking, hydraulic/cable |
| **Brake** | Brake system with ABS | Pressure control, ABS activation, pad wear, temperature |
| **Gear** | Transmission/gearbox | Manual, Automatic, CVT, DCT, gear ratios |
| **EV Battery** | Electric vehicle battery | SOC, health, range calculation, charge cycles |
| **Powertrain** | Engine/motor simulation | ICE, Hybrid, Electric, torque, power, RPM |

### Build Commands

```powershell
# Build automotive app
bazel build //c_project/automotive:automotive_app

# Build specific module
bazel build //c_project/automotive/clutch:clutch
bazel build //c_project/automotive/brake:brake
bazel build //c_project/automotive/gear:gear
bazel build //c_project/automotive/ev:ev_battery
bazel build //c_project/automotive/powertrain:powertrain

# Build all automotive modules
bazel build //c_project/automotive:automotive_all

# Run simulation
bazel run //c_project/automotive:automotive_app
```

### Module Dependencies

```
automotive_app
├── clutch
├── brake
├── gear
├── ev_battery
└── powertrain
```

All modules are independent - you can build and use them separately!

## Remote Caching Commands

### Setup BuildBarn

```powershell
# Start services (first time may take a minute to download images)
.\start-buildbarn.ps1

# Or manually
docker-compose up -d

# Check status
docker-compose ps

# View logs
docker-compose logs -f storage
```

### Using Remote Cache

```powershell
# Clean build with remote cache
bazel clean
bazel build --config=remote-cache //...

# Build specific targets with cache
bazel build --config=remote-cache //c_project/automotive:automotive_app
bazel build --config=remote-cache //cpp_project:cpp_app
bazel test --config=remote-cache //cpp_project/tests:all_tests

# See cache statistics
bazel info --config=remote-cache

# Run with remote cache
bazel run --config=remote-cache //c_project/automotive:automotive_app
```

### Cache Verification

**First Build (Cache Miss):**
```powershell
bazel clean
bazel build --config=remote-cache //c_project/automotive:automotive_app
# Will show: "X processes: Y internal, Z local"
```

**Second Build (Cache Hit):**
```powershell
bazel build --config=remote-cache //c_project/automotive:automotive_app
# Will show: "1 process: 1 remote cache hit"
```

### BuildBarn Management

```powershell
# Stop services (keep cache)
.\stop-buildbarn.ps1   # Option 1

# Stop and remove containers (keep cache)
docker-compose down

# Stop and delete cache (fresh start)
docker-compose down -v

# Restart services
docker-compose restart
```

### Monitoring

- **Web UI**: http://localhost:8081
- **Metrics**: http://localhost:7980/metrics
- **gRPC**: localhost:8980

### Storage Info

- **CAS (Content Addressable Storage)**: 10 GB
- **AC (Action Cache)**: 1 GB
- **Location**: `./buildbarn/storage-cas/` and `./buildbarn/storage-ac/`

## Complete Build Matrix

| Project | Command | Remote Cache |
|---------|---------|--------------|
| C App | `bazel run //c_project:c_app` | Add `--config=remote-cache` |
| C++ App | `bazel run //cpp_project:cpp_app` | Add `--config=remote-cache` |
| Automotive | `bazel run //c_project/automotive:automotive_app` | Add `--config=remote-cache` |
| All Tests | `bazel test //cpp_project/tests:all_tests` | Add `--config=remote-cache` |
| Everything | `bazel build //...` | Add `--config=remote-cache` |

## Troubleshooting

### Docker Not Running
```powershell
# Start Docker Desktop
Start-Process "C:\Program Files\Docker\Docker\Docker Desktop.exe"
# Wait ~30 seconds, then run start-buildbarn.ps1
```

### Cache Not Working
```powershell
# Verify BuildBarn is running
docker-compose ps

# Check connectivity
curl http://localhost:7980

# View storage logs
docker-compose logs storage
```

### Clear Everything and Start Fresh
```powershell
# Stop and remove everything
docker-compose down -v

# Clean Bazel
bazel clean --expunge

# Restart BuildBarn
.\start-buildbarn.ps1

# Rebuild
bazel build --config=remote-cache //...
```

## Performance Tips

1. **Always use remote cache for large builds**
2. **Share cache across team** - deploy BuildBarn on a shared server
3. **Monitor cache hit rate** in Web UI
4. **Clean local cache periodically** - `bazel clean`
5. **Use `--config=remote-cache`** for CI/CD pipelines

## Dependencies Graph

```
Automotive App Dependencies:
  clutch ─┐
  brake ──┤
  gear ───┼─> automotive_app
  ev ─────┤
  powertrain ─┘

Remote Caching Flow:
  Bazel Client ──gRPC──> bb-storage ──> CAS + AC
                                    │
                                    └──> bb-browser (Web UI)
```

## Next Steps

1. Build automotive app: `bazel run //c_project/automotive:automotive_app`
2. Start BuildBarn: `.\start-buildbarn.ps1`
3. Build with cache: `bazel build --config=remote-cache //...`
4. Open Web UI: http://localhost:8081
5. Observe cache hits on rebuild!
