#pragma once

#include <string>
#include <vector>
#include "IStatistics.h"

class Pct : public IStatistics {
public:
	explicit Pct(const size_t percentil);
	void update(double next) override;
	double eval() const override;
	const char * name() const override;

private:
	const std::string m_name;
	const size_t m_percentil;
	mutable std::vector<double> m_values{};
};