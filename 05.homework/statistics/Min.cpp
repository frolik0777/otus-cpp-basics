#include "Min.h"
#include <cmath>

void Min::update(double next) {
    if (next < m_min) {
        m_min = next;
    }
    ++m_cnt;
}

double Min::eval() const {
    if (m_cnt)
        return m_min;
    else
        return std::nan("");
}

const char * Min::name() const {
    return "min";
}