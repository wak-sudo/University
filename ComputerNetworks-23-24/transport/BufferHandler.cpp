// Wojciech Kieloch 339952 2024 SK

#include "BufferHandler.h"

#include <iostream>
#include <cassert>

#include "Constants.h"
#include "Tools.h"

#include "panic.h"

void BufferHandler::fillNotYetRecived(unsigned oldFstElement, unsigned blocksWritten)
{
    const unsigned newElement = oldFstElement + buffer->getBlocksCount();
    for (unsigned i = 0; i < blocksWritten; i++)
        if (!addToNotYetRecived(newElement + i))
            break;
}

bool BufferHandler::addToNotYetRecived(unsigned i)
{
    const unsigned blocksCount = buffer->getBlocksCount();
    if (i < totalNumberOfBlocks && notYetRecived.size() < blocksCount)
        notYetRecived.insert(i);
    else
        return false;

    // Invariant:
    // biggest element in NotYetRecived - smallest element in NotYetRecived < blocksCount

    if (notYetRecived.size() != 0)
    {
        unsigned biggestEl = *notYetRecived.rbegin();
        unsigned smallestEl = *notYetRecived.begin();
        if (biggestEl - smallestEl >= blocksCount)
        {
            printNotYetRecived();
            panic("BufferHandler::addToNotYetRecived -> Right: " + std::to_string(biggestEl) + " Left: " + std::to_string(smallestEl), false);
        }
    }

    return true;
}

unsigned BufferHandler::getNumberOfBlocks() const
{
    return totalNumberOfBlocks;
}

unsigned BufferHandler::getNumberOfWrittenBlocks() const
{
    return numberOfBlocksWritten;
}

unsigned BufferHandler::getBlockSize(c_iter it) const
{
    assert(it != notYetRecived.end());
    if (*it == totalNumberOfBlocks - 1) // if it is the last block.
        return lastBlockSize;
    return buffer->getMaxBlockSize();
}

BufferHandler::c_iter BufferHandler::begin() const { return notYetRecived.begin(); }

BufferHandler::c_iter BufferHandler::end() const { return notYetRecived.end(); }

BufferHandler::BufferHandler(unsigned fileSize, unsigned destFileDesc)
{
    buffer = new Buffer(Constants::BLOCKS_IN_BUFFER, Constants::MAX_BLOCK_SIZE);
    reinit(fileSize, destFileDesc);
}

BufferHandler::~BufferHandler()
{
    delete buffer;
}

unsigned BufferHandler::getMaxBlockSize() const
{
    return buffer->getMaxBlockSize();
}

void BufferHandler::reinit(unsigned fileSizeArg, unsigned destFileDesc)
{
    notYetRecived.clear();
    buffer->clear();
    numberOfBlocksWritten = 0;

    unsigned reminder = fileSizeArg % buffer->getMaxBlockSize();

    lastBlockSize = reminder;
    if (reminder == 0)
        lastBlockSize = buffer->getMaxBlockSize();

    totalNumberOfBlocks = fileSizeArg / buffer->getMaxBlockSize();
    if (reminder != 0)
        totalNumberOfBlocks++;

    Tools::log("Number of blocks:" + std::to_string(totalNumberOfBlocks) + " last block size: " + std::to_string(lastBlockSize));

    fileDesc = destFileDesc;
    for (unsigned i = 0; addToNotYetRecived(i); i++) // initial fill.
        ;

#ifdef DEBUG
    printNotYetRecived();
#endif
}

void BufferHandler::recieve(unsigned fragStart, char *data, unsigned blockLen)
{
    const unsigned blockId = fragStart / buffer->getMaxBlockSize();
    if (notYetRecived.find(blockId) != notYetRecived.end())
    {
        bool canBeWritten = buffer->processBlock(data, blockId, blockLen);
        if (canBeWritten)
        {
            unsigned numberOfElementsWritten = buffer->tryWriteData(fileDesc);
            assert(numberOfElementsWritten > 0);
            numberOfBlocksWritten += numberOfElementsWritten;
            const auto smallestIt = notYetRecived.begin();
            const unsigned fstValueInSet = *smallestIt;
            notYetRecived.erase(smallestIt);
            fillNotYetRecived(fstValueInSet, numberOfElementsWritten);
        }
        else
            notYetRecived.erase(blockId);
    }
}

void BufferHandler::printNotYetRecived()
{
    for (const auto &entry : notYetRecived)
    {
        std::cout << entry << " ";
    }
    std::cout << std::endl;
}

bool BufferHandler::allBlocksRecived() const
{
    return totalNumberOfBlocks <= numberOfBlocksWritten;
}