// Wojciech Kieloch 339952 2024 SK

#include "Buffer.h"

#include "Tools.h"

#include <cassert>

Buffer::Buffer(unsigned blocksCountArg, unsigned maximalBlockSizeArg)
{
    assert(blocksCountArg > 0 && maximalBlockSizeArg > 0);
    BLOCKS_COUNT = blocksCountArg;
    MAX_BLOCK_SIZE = maximalBlockSizeArg;
    const unsigned totalBufSize = MAX_BLOCK_SIZE * BLOCKS_COUNT;
    data = new char[totalBufSize];
    blockSizes = new unsigned[BLOCKS_COUNT];
    clear();
}

Buffer::~Buffer()
{
    delete[] data;
    delete[] blockSizes;
}

void Buffer::clear()
{
    oldestBlockIdx = 0;
    for (unsigned i = 0; i < BLOCKS_COUNT; i++)
        blockSizes[i] = BLOCK_UNUSED;
}

unsigned Buffer::getBlockSize(unsigned i) const
{
    i %= BLOCKS_COUNT;
    return blockSizes[i];
}

// this function returns true if the oldest block is used.
bool Buffer::processBlock(char *block, unsigned blockId, unsigned blockLen)
{
    assert(blockLen <= MAX_BLOCK_SIZE);
    unsigned rel_id = blockId % BLOCKS_COUNT;
    assert(blockSizes[rel_id] == BLOCK_UNUSED);
    for (unsigned i = 0; i < blockLen; i++)
        getBlock(rel_id)[i] = block[i];
    blockSizes[rel_id] = blockLen;
    Tools::log("Block processing: rel_id: " + std::to_string(rel_id) + " block len: " + std::to_string(blockLen));
    return blockSizes[oldestBlockIdx] != BLOCK_UNUSED;
}

// This function writes data only if the oldestBlock is used.
// returns the number of blocks written.
unsigned Buffer::tryWriteData(int fd)
{
    assert(fd > 0);
    if (blockSizes[oldestBlockIdx] == BLOCK_UNUSED)
        return 0;

    // as the buffer is cyclic, used part, starting from the oldestBlock, can lie on the border of the array.
    // that's why we use two pointers.

    bool splitPresent = false;
    char *fstPtr = oldestBlockPtr();
    char *sndPtr = nullptr;
    unsigned sndSizeInBytes = 0;
    unsigned fstSizeInBytes = 0;
    unsigned i = oldestBlockIdx;
    unsigned numberOfWrittenBlocks = 0;

    while (i < BLOCKS_COUNT)
    {
        if (blockSizes[i] == BLOCK_UNUSED)
            break;
        if (i == BLOCKS_COUNT - 1) // in other words: if the last block is also used.
            splitPresent = true;
        fstSizeInBytes += blockSizes[i];
        blockSizes[i] = BLOCK_UNUSED;
        i++;
    }

    numberOfWrittenBlocks += (i - oldestBlockIdx);
    oldestBlockIdx = i % BLOCKS_COUNT; // oldest block changed.

    if (splitPresent == true)
    {
        sndPtr = data;
        unsigned j = 0;
        while (blockSizes[j] != BLOCK_UNUSED)
        {
            sndSizeInBytes += blockSizes[j];
            blockSizes[j] = BLOCK_UNUSED;
            j++;
        }
        numberOfWrittenBlocks += j;
        oldestBlockIdx = j; // oldest block changed.
    }

    if (sndSizeInBytes == 0)
    {
        Tools::c_write(fd, fstPtr, fstSizeInBytes);
    }
    else
    {
        iovec iov[2];
        iov[0].iov_base = fstPtr;
        iov[0].iov_len = fstSizeInBytes;
        iov[1].iov_base = sndPtr;
        iov[1].iov_len = sndSizeInBytes;
        Tools::c_writev(fd, iov, 2);
    }

    Tools::log("Blocks written: " + std::to_string(numberOfWrittenBlocks));

    return numberOfWrittenBlocks;
}

char *Buffer::getBlock(unsigned i) const
{
    return data + i * MAX_BLOCK_SIZE;
}

char *Buffer::oldestBlockPtr() const
{
    return getBlock(oldestBlockIdx);
}

unsigned Buffer::getBlocksCount() const
{
    return BLOCKS_COUNT;
}

unsigned Buffer::getMaxBlockSize() const
{
    return MAX_BLOCK_SIZE;
}