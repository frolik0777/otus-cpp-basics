#include "Max.h"

void Max::update(double next) {
    ++m_cnt;
    if (next > m_max) {
        m_max = next;
    }
}

double Max::eval() const {
    if (m_cnt)
        return m_max;
    else
        return std::nan("");
}

const char * Max::name() const {
    return "max";
}
