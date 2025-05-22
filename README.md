# boogie
A somewhat correct/somewhat secure crypto library.

## Features
| Feature         | Description                        | Status     |
|-----------------|------------------------------------|------------|
| SHA-1           | Hashing algorithm implementation   | Functional (Contains inefficient/unsafe code)

## Usage

```bash
$ echo "Let's boogie" | boogie sha1
# Output:
# 09783186067f1a1adae02d132ca98eaa357d4a8f
```

## Building

```bash
# Clone the repository
git clone https://github.com/NickR23/boogie.git
cd boogie

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

<div align="center">
  <img src="https://media.tenor.com/5YSoSYGxbUMAAAAM/dancing-skeleton.gif" alt="Dancing Skeleton GIF" />
</div>
