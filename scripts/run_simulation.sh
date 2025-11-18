#!/bin/bash
# ==============================================================================
# NACA0012 Carangiform Swimmer - Simulation Runner
# ==============================================================================
# IBAMR-compatible simulation execution script with proper path handling
# Usage: ./scripts/run_simulation.sh (run from project root)
# ==============================================================================

# Number of MPI processes
NPROCS=6

# Input file (relative to project root)
INPUT_FILE="input/input2d"

# Executable (assumes build directory exists)
EXECUTABLE="./build/main2d"

# Ensure we're running from project root
if [ ! -f "CMakeLists.txt" ]; then
    echo "Error: Please run this script from the project root directory"
    echo "Usage: ./scripts/run_simulation.sh"
    exit 1
fi

# Create symbolic link to mesh directory so IBAMR can find vertex files
# IBAMR's IBStandardInitializer looks for .vertex files relative to run directory
if [ ! -e "naca0012carangiform.vertex" ]; then
    ln -sf mesh/naca0012carangiform.vertex naca0012carangiform.vertex
    echo "Created symbolic link: naca0012carangiform.vertex -> mesh/naca0012carangiform.vertex"
fi

# Run simulation
echo "=========================================="
echo "Starting NACA0012 Carangiform Simulation"
echo "=========================================="
echo "Processors: $NPROCS"
echo "Input file: $INPUT_FILE"
echo "Time: $(date)"
echo "=========================================="

mpirun -np $NPROCS $EXECUTABLE $INPUT_FILE

echo ""
echo "=========================================="
echo "Simulation completed at: $(date)"
echo "=========================================="