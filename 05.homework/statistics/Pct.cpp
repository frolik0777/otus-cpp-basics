#include "Pct.h"
#include <algorithm>
#include <cmath>

Pct::Pct(const size_t percentil):
    m_name{"pct" + std::to_string(percentil)},
    m_percentil{percentil}
{

}

void Pct::update(double next) {
    m_values.push_back(next);
}

double Pct::eval() const {
    std::sort(m_values.begin(), m_values.end());
    const size_t indx = m_values.size() *  m_percentil / 100;
    if (indx < m_values.size()) {
        return m_values[indx];
    }
    else
        return std::nan("");
}

const char * Pct::name() const {
    return m_name.c_str();
}