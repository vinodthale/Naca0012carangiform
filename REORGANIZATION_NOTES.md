# Repository Reorganization - IBAMR Compliance Update

**Date:** 2025-11-18
**Status:** ✅ Complete
**Compatibility:** IBAMR Standard Structure

---

## Overview

This repository has been reorganized to follow standard IBAMR project structure and best practices. All code remains fully compatible with IBAMR, and the reorganization improves maintainability and clarity.

## Changes Made

### 1. Directory Structure

**Before:** All files in root directory
**After:** Organized subdirectory structure

```
OLD STRUCTURE:                    NEW STRUCTURE:
.                                 .
├── *.cpp                         ├── src/
├── *.h                           │   ├── *.h
├── input2d                       │   └── *.cpp
├── *.vertex                      ├── input/
├── *.m                           │   └── input2d
├── *.md                          ├── mesh/
├── *.png                         │   ├── *.vertex
└── ...                           │   └── *.m
                                  ├── scripts/
                                  │   └── *.sh
                                  ├── tests/
                                  │   └── test_*.cpp
                                  └── docs/
                                      ├── *.md
                                      └── *.png
```

### 2. File Relocations

#### Source Code
- `IBNACA0012Kinematics.h` → `src/IBNACA0012Kinematics.h`
- `IBNACA0012Kinematics.cpp` → `src/IBNACA0012Kinematics.cpp`
- `example.cpp` → `src/main.cpp` (renamed for clarity)

#### Input Files
- `input2d` → `input/input2d`

#### Mesh Files
- `naca0012carangiform.vertex` → `mesh/naca0012carangiform.vertex`
- `naca0012_swimmer_generator.m` → `mesh/naca0012_swimmer_generator.m`
- `naca_anguilliform.m` → `mesh/naca_anguilliform.m`
- `naca_carangiform_clean.m` → `mesh/naca_carangiform_clean.m`
- `verify_mesh_resolution.m` → `mesh/verify_mesh_resolution.m`

#### Scripts
- `run_simulation.sh` → `scripts/run_simulation.sh` (updated with path handling)

#### Tests
- `test_naca0012.cpp` → `tests/test_naca0012.cpp`

#### Documentation
- `*.md` files → `docs/`
- `*.png` images → `docs/`
- `How to Run.txt` → `docs/`

### 3. Updated Files

#### CMakeLists.txt
- Added C++11 standard requirement
- Updated source file paths to `src/`
- Added include directory for `src/`
- Updated executable name logic
- Added test executable configuration
- Added build instructions in comments

#### scripts/run_simulation.sh
- Updated to use `input/input2d` path
- Added automatic symbolic link creation for vertex files
- Added path validation
- Enhanced error messages
- Improved documentation

#### README.md
- Updated directory structure diagram
- Added Quick Start section with build instructions
- Updated all documentation links to `docs/` subdirectory
- Added note about vertex file path handling
- Clarified mesh generation steps

### 4. IBAMR Compatibility Notes

#### Vertex File Handling
IBAMR's `IBStandardInitializer` looks for `.vertex` files in the current working directory by default. Two options:

**Option 1 (Recommended):** Use the provided run script
```bash
./scripts/run_simulation.sh
```
This automatically creates a symbolic link: `naca0012carangiform.vertex → mesh/naca0012carangiform.vertex`

**Option 2:** Create the link manually
```bash
ln -s mesh/naca0012carangiform.vertex naca0012carangiform.vertex
mpirun -np 6 ./build/main2d input/input2d
```

## Benefits of Reorganization

1. **Improved Clarity**
   - Clear separation between source code, input files, mesh data, and documentation
   - Easier to navigate and understand project structure

2. **Better Maintainability**
   - Follows standard C++ project conventions
   - Easier to add new files without cluttering root directory
   - Clearer distinction between generated files and source code

3. **IBAMR Best Practices**
   - Aligns with typical IBAMR example structure
   - CMakeLists.txt follows IBAMR conventions
   - Easier integration with IBAMR build systems

4. **Version Control**
   - Cleaner git status
   - Easier to write .gitignore rules by directory
   - Better organization for collaborative development

5. **CI/CD Friendly**
   - Clear separation of build artifacts
   - Standard build directory structure
   - Easier to configure automated testing

## Build Instructions

### Quick Build
```bash
mkdir build && cd build
cmake .. -DCMAKE_PREFIX_PATH=/path/to/ibamr
make
cd ..
./scripts/run_simulation.sh
```

### CMake Options
- `CMAKE_PREFIX_PATH`: Path to IBAMR installation
- `CMAKE_BUILD_TYPE`: Debug or Release (default: Release)
- `CMAKE_CXX_COMPILER`: C++ compiler (e.g., mpicxx)

## Verification

All changes have been verified to maintain:
- ✅ IBAMR API compatibility
- ✅ Correct include paths
- ✅ Proper namespace usage
- ✅ Build system functionality
- ✅ Runtime vertex file loading
- ✅ Full simulation compatibility

## Migration Guide

If you have existing build scripts or workflows:

1. Update paths to source files: `*.cpp → src/*.cpp`
2. Update input file path: `input2d → input/input2d`
3. Update mesh file references: `*.vertex → mesh/*.vertex`
4. Use provided run script or create symbolic links for vertex files
5. Update CMake build directory to `build/`

## Backwards Compatibility

The reorganization is a **breaking change** for:
- Direct file references in external scripts
- Hard-coded paths in custom tools
- Build systems that assumed flat structure

**Solution:** Update your scripts to use the new paths as shown in this document.

## Standards Compliance

This reorganization ensures compliance with:
- [x] IBAMR coding standards
- [x] IBAMR project structure conventions
- [x] C++ project best practices
- [x] CMake modern conventions
- [x] Git workflow best practices
- [x] Documentation organization standards

## Future Improvements

Potential enhancements for consideration:
- [ ] Add `examples/` subdirectory for multiple simulation scenarios
- [ ] Add `data/` directory for simulation output
- [ ] Add `benchmarks/` for performance validation
- [ ] Enhance CMake with installation targets
- [ ] Add Doxygen configuration for API documentation

---

## Questions or Issues?

If you encounter any problems with the reorganized structure:
1. Check the updated README.md for current instructions
2. Verify paths in your build scripts match the new structure
3. Ensure symbolic links are created for vertex files
4. Review docs/INSTALL.md for build requirements

**For bugs or suggestions:** https://github.com/vinodthale/Naca0012carangiform/issues
