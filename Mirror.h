#pragma once
#include "Point.h"

template <class Tp>
class FlatMirror {
public:
    FlatMirror(Tp begin, Tp end): begin_(begin), end_(end) {}
protected:
    Point<Tp> begin_, end_;
};
