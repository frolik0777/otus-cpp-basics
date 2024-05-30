#include "Std.h"

void Std::update(double next) {
    m_sum += next;
    m_values.push_back(next);
}

double Std::eval() const {
    const double mean = m_sum / static_cast<double>(m_values.size());
    double disp_sum = 0.0;
    for(double val: m_values) {
        disp_sum += (mean - val) * (mean - val);
    }
    return std::sqrt(
        disp_sum / static_cast<double>(m_values.size()));
}

const char * Std::name() const {
    return "std";
}