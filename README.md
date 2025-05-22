# boogie
A somewhat correct/somewhat secure crypto library.

## Features
| Feature         | Description                        | Status     |
|-----------------|------------------------------------|------------|
| SHA-1           | Hashing algorithm implementation   | Functional (Contains inefficient/unsafe code)

## Building

```bash
# Clone the repository
git clone https://github.com/username/jerry.git
cd jerry

# Create a build directory
mkdir build && cd build

# Configure and build
# For prod use:
cmake .. 
# Or use the following to enable debug symbols:
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
make

# Run tests
ctest
```

## Resources
* Sha1 RFC: https://www.ietf.org/rfc/rfc3174.txt