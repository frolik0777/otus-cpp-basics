#pragma once

#include <limits>
#include "IStatistics.h"

class Min : public IStatistics {
public:
	void update(double next) override;
	double eval() const override;
	const char * name() const override;

private:
	double m_min{std::numeric_limits<double>::max()};
	double m_cnt{};
};