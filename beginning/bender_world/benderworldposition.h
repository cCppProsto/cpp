#ifndef BENDERPOSITION_H
#define BENDERPOSITION_H

#include "common.h"

struct benderWorldPosition
{
    benderWorldPosition();
    benderWorldPosition(int, int);

    void set(int, int);

    const int &l()const;
    const int &r()const;

    benderWorldPosition &operator=(const benderWorldPosition&);
    benderWorldPosition &operator+=(eWorldDirection);
    bool operator==(const benderWorldPosition&);

private:
    int mLine{-1};
    int mRow{-1};
};

// auxiliary functions
benderWorldPosition operator+(benderWorldPosition aPos, eWorldDirection aDirection);

#endif // BENDERPOSITION_H
