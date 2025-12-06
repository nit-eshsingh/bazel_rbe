# Bazel C/C++ Project with RBE Support

A comprehensive C and C++ project demonstrating Bazel build system features including:
- Multiple submodules with dependencies
- Third-party library integration
- Unit testing with Google Test
- Complex target relationships

## Project Structure

```
bazel_rbe/
├── WORKSPACE                 # Bazel workspace configuration with external dependencies
├── .bazelrc                  # Bazel build configuration (includes remote cache config)
├── BUILD                     # Root BUILD file
├── bazel.exe                 # Bazel binary (v7.4.1)
├── nlohmann_json.BUILD       # Build file for nlohmann/json third-party library
├── docker-compose.yml        # BuildBarn remote caching services
├── start-buildbarn.ps1       # Script to start BuildBarn
├── stop-buildbarn.ps1        # Script to stop BuildBarn
│
├── buildbarn/                # BuildBarn remote caching configuration
│   ├── README.md             # BuildBarn setup and usage guide
│   └── config/
│       ├── storage.jsonnet   # Storage configuration (CAS + AC)
│       └── browser.jsonnet   # Web UI configuration
│
├── c_project/                # C Language Project
│   ├── BUILD                 # Main C project targets
│   ├── main.c                # C application entry point
│   ├── math_utils.{c,h}      # Math utilities library
│   │
│   ├── string_utils/         # String manipulation submodule
│   │   ├── BUILD
│   │   ├── string_utils.h
│   │   └── string_utils.c
│   │
│   ├── file_io/              # File I/O operations submodule
│   │   ├── BUILD
│   │   ├── file_io.h
│   │   └── file_io.c
│   │
│   ├── data_structures/      # Data structures submodule
│   │   ├── BUILD
│   │   ├── linked_list.{c,h} # Linked list implementation
│   │   └── stack.{c,h}       # Stack implementation
│   │
│   └── automotive/           # Automotive domain modules
│       ├── BUILD             # Main automotive app
│       ├── automotive_main.c # Automotive simulation
│       ├── clutch/           # Clutch system module
│       │   ├── BUILD
│       │   ├── clutch.h
│       │   └── clutch.c
│       ├── brake/            # Brake system module
│       │   ├── BUILD
│       │   ├── brake.h
│       │   └── brake.c
│       ├── gear/             # Gearbox/transmission module
│       │   ├── BUILD
│       │   ├── gear.h
│       │   └── gear.c
│       ├── ev/               # Electric vehicle battery module
│       │   ├── BUILD
│       │   ├── ev_battery.h
│       │   └── ev_battery.c
│       └── powertrain/       # Powertrain/engine module
│           ├── BUILD
│           ├── powertrain.h
│           └── powertrain.c
│
└── cpp_project/              # C++ Language Project
    ├── BUILD                 # Main C++ project targets
    ├── main.cpp              # C++ application entry point
    ├── calculator.{cpp,h}    # Calculator library
    │
    ├── logger/               # Logging utility submodule
    │   ├── BUILD
    │   ├── logger.h
    │   └── logger.cpp
    │
    ├── json_parser/          # JSON parsing submodule (demonstrates third-party deps)
    │   ├── BUILD
    │   ├── json_parser.{cpp,h}              # Simple JSON parser
    │   ├── json_parser_nlohmann.{cpp,h}     # Parser using nlohmann/json library
    │
    ├── network/              # Network client submodule
    │   ├── BUILD
    │   ├── network.h
    │   └── network.cpp
    │
    └── tests/                # Unit tests using Google Test
        ├── BUILD
        ├── calculator_test.cpp
        ├── json_parser_test.cpp
        └── network_test.cpp
```

## Dependencies

### External Dependencies (Third-party)
- **Google Test** (v1.14.0) - C++ testing framework
- **nlohmann/json** (v3.11.3) - JSON library for Modern C++
- **Abseil** (20240116.2) - C++ common libraries

### Internal Dependencies
The project demonstrates various dependency patterns:

**C Project Dependencies:**
```
c_app (binary)
  ├── math_utils (library)
  ├── string_utils (submodule)
  ├── linked_list (submodule)
  └── stack (submodule)
```

**C++ Project Dependencies:**
```
cpp_app (binary)
  ├── calculator (library)
  ├── logger (submodule)
  ├── json_parser (submodule)
  ├── json_parser_with_nlohmann (submodule - uses third-party dep)
  └── network (submodule)
```

## Build Commands

### Build All Targets
```powershell
# Build C project
.\bazel.exe build //c_project:c_app

# Build C++ project
.\bazel.exe build //cpp_project:cpp_app

# Build specific submodule
.\bazel.exe build //c_project/string_utils:string_utils
.\bazel.exe build //cpp_project/logger:logger
```

### Run Applications
```powershell
# Run C application
bazel run //c_project:c_app

# Run C++ application
bazel run //cpp_project:cpp_app

# Run Automotive simulation (NEW!)
bazel run //c_project/automotive:automotive_app
```

### Run Tests
```powershell
# Run all C++ tests
.\bazel.exe test //cpp_project/tests:all_tests

# Run specific test
.\bazel.exe test //cpp_project/tests:calculator_test
.\bazel.exe test //cpp_project/tests:json_parser_test
.\bazel.exe test //cpp_project/tests:network_test
```

### Query Dependencies
```powershell
# Show dependencies of a target
bazel query "deps(//cpp_project:cpp_app)"

# Show reverse dependencies (what depends on this target)
bazel query "rdeps(//..., //cpp_project/logger:logger)"

# Show build graph
bazel query --output graph "//cpp_project:cpp_app" > graph.dot
```

## Remote Caching with BuildBarn

This project includes BuildBarn for remote build caching, which dramatically speeds up builds by caching artifacts.

### Quick Start with Remote Caching

1. **Start BuildBarn Services:**
   ```powershell
   .\start-buildbarn.ps1
   ```
   Or manually:
   ```powershell
   docker-compose up -d
   ```

2. **Build with Remote Cache:**
   ```powershell
   # First build (populates cache)
   bazel clean
   bazel build --config=remote-cache //c_project/automotive:automotive_app
   
   # Second build (uses cache - much faster!)
   bazel build --config=remote-cache //c_project/automotive:automotive_app
   ```

3. **Access Web UI:**
   Open http://localhost:8081 to explore cached artifacts

4. **Stop BuildBarn:**
   ```powershell
   .\stop-buildbarn.ps1
   ```

For detailed information, see [buildbarn/README.md](buildbarn/README.md)

## Automotive Domain Features (NEW!)

The C project now includes comprehensive automotive system modules:

### Modules:
- **Clutch System**: Hydraulic/cable clutch with wear simulation
- **Brake System**: ABS-enabled brakes with temperature and wear tracking
- **Gearbox**: Manual, Automatic, CVT, and DCT transmissions
- **EV Battery**: State of charge, health, charging cycles, range calculation
- **Powertrain**: ICE, Hybrid, and Electric motor simulation

### Run Automotive Simulation:
```powershell
bazel run //c_project/automotive:automotive_app
```

The simulation demonstrates:
- ICE (Internal Combustion Engine) vehicle operation
- Electric Vehicle (EV) with regenerative braking
- Hybrid vehicle with dual power sources

## Bazel Concepts Demonstrated

### 1. Rules
- **cc_library**: Defines C/C++ libraries that can be reused
- **cc_binary**: Defines executable programs
- **cc_test**: Defines test targets using Google Test
- **test_suite**: Groups multiple tests together

### 2. Targets
Each BUILD file defines multiple targets:
- Library targets (reusable code)
- Binary targets (executables)
- Test targets (unit tests)

### 3. Dependencies
- **Local dependencies**: Between modules in the same project
- **External dependencies**: Third-party libraries from GitHub
- **Transitive dependencies**: Automatically resolved by Bazel

### 4. Visibility
- `//visibility:public` - Accessible from anywhere
- `//cpp_project:__subpackages__` - Only accessible within cpp_project

### 5. Third-party Integration
External dependencies are defined in WORKSPACE using `http_archive`:
- Automatic downloading from URLs
- SHA256 verification for security
- Custom BUILD files for dependencies without native Bazel support

## Key Features

### Submodules
Both C and C++ projects are organized into logical submodules:
- Each submodule has its own BUILD file
- Submodules can depend on each other
- Demonstrates proper code organization

### Cross-module Dependencies
The main applications depend on multiple submodules, showing:
- How to reference targets in other packages
- Proper dependency management
- Build graph optimization

### Third-party Libraries
- nlohmann/json for JSON parsing
- Google Test for unit testing
- Shows how to integrate external dependencies

## Build Configuration

The `.bazelrc` file contains:
- Local execution strategy
- Verbose failure reporting
- C++17 standard (note: Windows MSVC ignores -std flag)
- Windows-specific compiler flags

## Notes

- Windows MSVC compiler ignores the `-std=c++17` flag (shows warnings but compiles correctly)
- Tests use Google Test framework as a third-party dependency
- The project structure supports future RBE (Remote Build Execution) integration

## License

This is a demonstration project for learning Bazel build system.