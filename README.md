# bcomm

`bcomm` is a high-performance replacement for the classic Unix `comm` command. It uses a **Bloom Filter** to rapidly identify and skip lines that are definitely not in the intersection of two files, drastically reducing the number of expensive hash table lookups and string comparisons.

## Installation

### Prerequisites
- A C++ compiler (like `g++`)
- `make` utility

### Building and Installing
1.  Clone the repository or navigate to the source directory.
2.  Compile the project:
    ```bash
    make
    ```
3.  Install as a system-wide command:
    ```bash
    sudo make install
    ```
    This moves the `bcomm` binary to `/usr/local/bin/`.

## Usage

### Modes
- `bloom`: Uses the Bloom Filter accelerated algorithm (Recommended).
- `standard`: Runs a baseline test using the traditional `sort` and `comm` tools.

### Example Command
```bash
bcomm bloom file_A.txt file_B.txt
```

## How It Works
1.  **Phase 1**: Reads the first file, populating both a Bloom Filter and a Hash Set.
2.  **Phase 2**: Streams the second file and checks each line against the Bloom Filter.
3.  **Phase 3**: If the filter returns a positive result (potential match), it performs an exact lookup in the Hash Set to eliminate false positives.

## References
Special thanks to **Peter Scott** for the implementation of the MurmurHash3 algorithm used in this project.
Original source: [https://github.com/PeterScott/murmur3](https://github.com/PeterScott/murmur3)
