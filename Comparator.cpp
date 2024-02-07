#include "Comparator.h"

bool LessThanByPriority::operator()(const Patient &lhs, const Patient &rhs) {
    return (lhs.getPriority() > rhs.getPriority());
}