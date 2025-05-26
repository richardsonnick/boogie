<div align="center">
  <img src="https://media.tenor.com/5YSoSYGxbUMAAAAM/dancing-skeleton.gif" alt="Dancing Skeleton GIF" />
</div>

# boogie
A crypto library with zero external dependencies. 

## Features
| Feature         | Status     |
|-----------------|------------|
| SHA-1           | Functional (Now with chunking!) |

## Usage

```bash
$ echo "Let's boogie" | boogie sha1
# Output:
# 09783186067f1a1adae02d132ca98eaa357d4a8

$ boogie sha1 < bee_movie.txt
# Output:
# 93ae3d6436613af8a6957db81e1701fbc50de7a8
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
# Places binary at boogie/build/bin/boogie

# Run tests
ctest

# Install (may need sudo)
make install 
```

## Resources
* Sha1 RFC: https://www.ietf.org/rfc/rfc3174.txt

<div align="center">
  <a href="https://imgflip.com/i/9uw4fc"><img src="https://i.imgflip.com/9uw4fc.jpg" title="made at imgflip.com"/></a><div><a href="https://imgflip.com/memegenerator"></a></div>
</div>

