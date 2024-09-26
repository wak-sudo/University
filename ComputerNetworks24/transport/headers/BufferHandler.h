// Wojciech Kieloch 339952 2024 SK

#pragma once

#include <set>

#include "Buffer.h"

class BufferHandler
{
    std::set<unsigned> notYetRecived; // id -> time since asked.
    Buffer *buffer;
    unsigned totalNumberOfBlocks;
    unsigned lastBlockSize;
    unsigned numberOfBlocksWritten;
    int fileDesc;

    void fillNotYetRecived(unsigned oldFstElement, unsigned blocksWritten);
    bool addToNotYetRecived(unsigned i);
public:
    typedef std::set<unsigned>::const_iterator c_iter;
    c_iter begin() const;
    c_iter end() const;
    bool allBlocksRecived() const;
    unsigned getBlockSize(c_iter it) const; 
    unsigned getMaxBlockSize() const;
    unsigned getNumberOfBlocks() const;
    unsigned getNumberOfWrittenBlocks() const;

    //void passTime(unsigned deltaMS);
    //void markRequested(c_iter constIt);
    void recieve(unsigned fragStart, char* data, unsigned blockLen);

    BufferHandler(unsigned fileSize, unsigned destFileDesc);
    ~BufferHandler();
    void reinit(unsigned fileSize, unsigned destFileDesc);
    void printNotYetRecived();
};