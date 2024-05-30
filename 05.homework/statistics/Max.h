#pragma once

#include <limits>
#include <cmath>
#include "IStatistics.h"

class Max : public IStatistics {
public:
	void update(double next) override;
	double eval() const override;
	const char * name() const override;

private:
	double m_max{std::numeric_limits<double>::lowest()};
	size_t m_cnt{};
};