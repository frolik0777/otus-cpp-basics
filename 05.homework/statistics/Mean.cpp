#include "Mean.h"

void Mean::update(double next) {
    m_sum += next;
    ++m_cnt;
}

double Mean::eval() const {
    return m_sum / static_cast<double>(m_cnt);
}

const char * Mean::name() const {
    return "mean";
}