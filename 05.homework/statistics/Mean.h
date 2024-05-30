#pragma once

#include <cmath>
#include "IStatistics.h"

class Mean : public IStatistics {
public:
	void update(double next) override;
	double eval() const override;
	const char * name() const override;

private:
	double m_sum{};
	size_t m_cnt{};
};