// Wojciech Kieloch 339952 2024 SK

#pragma once

class Buffer
{
    // Local constants:
    const unsigned BLOCK_UNUSED = 0;
    unsigned BLOCKS_COUNT;
    unsigned MAX_BLOCK_SIZE;

    char *data;
    unsigned *blockSizes; // if 0, then unused.
    unsigned oldestBlockIdx;
    char *getBlock(unsigned i) const;
    char *oldestBlockPtr() const;

public:
    Buffer(unsigned blocksCountArg, unsigned maximalBlockSizeArg);
    ~Buffer();
    void clear();
    unsigned getBlockSize(unsigned i) const;
    unsigned getBlocksCount() const;
    unsigned getMaxBlockSize() const;
    bool processBlock(char *block, unsigned blockId, unsigned blockLen);
    unsigned tryWriteData(int fd);
};