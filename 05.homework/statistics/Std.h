#pragma once

#include <cmath>
#include <vector>
#include "IStatistics.h"

class Std : public IStatistics {
public:
	void update(double next) override;
	double eval() const override;
	const char * name() const override;

private:
	double m_sum{};
	std::vector<double> m_values{};
};