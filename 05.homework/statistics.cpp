#include <cmath>
#include <iostream>
#include <limits>
#include <vector>

class IStatistics {
public:
	virtual ~IStatistics() {}

	virtual void update(double next) = 0;
	virtual double eval() const = 0;
	virtual const char * name() const = 0;
};

class Min : public IStatistics {
public:
	void update(double next) override {
		if (next < m_min) {
			m_min = next;
		}
	}

	double eval() const override {
		if (m_cnt)
			return m_min;
		else
			return std::nan("");
	}

	const char * name() const override {
		return "min";
	}

private:
	double m_min{std::numeric_limits<double>::max()};
	double m_cnt{};
};

class Max : public IStatistics {
public:
	void update(double next) override {
		++m_cnt;
		if (next > m_max) {
			m_max = next;
		}
	}

	double eval() const override {
		if (m_cnt)
			return m_max;
		else
			return std::nan("");
	}

	const char * name() const override {
		return "max";
	}

private:
	double m_max{std::numeric_limits<double>::min()};
	size_t m_cnt{};
};

class Mean : public IStatistics {
public:
	void update(double next) override {
		m_sum += next;
		++m_cnt;
	}

	double eval() const override {
		return m_sum / static_cast<double>(m_cnt);
	}

	const char * name() const override {
		return "mean";
	}

private:
	double m_sum{};
	size_t m_cnt{};
};

class Std : public IStatistics {
public:
	void update(double next) override {
		m_sum += next;
		m_values.push_back(next);
	}

	double eval() const override {
		const double mean = m_sum / static_cast<double>(m_values.size());
		double disp_sum = 0.0;
		for(double val: m_values) {
			disp_sum += (mean - val) * (mean - val);
		}
		return std::sqrt(
			disp_sum / static_cast<double>(m_values.size()));
	}

	const char * name() const override {
		return "std";
	}

private:
	double m_sum{};
	std::vector<double> m_values{};
};

int main() {

	std::vector<IStatistics *> stats;
	stats.push_back(new Min{});
	stats.push_back(new Max{});
	stats.push_back(new Mean{});
	stats.push_back(new Std{});

	double val = 0;
	while (std::cin >> val) {
		for (IStatistics* stat: stats) {
			stat->update(val);
		}
	}

	// Handle invalid input data
	if (!std::cin.eof() && !std::cin.good()) {
		std::cerr << "Invalid input data\n";
		return 1;
	}

	// Print results if any
	for (IStatistics* stat: stats) {
		std::cout << stat->name() << " = " << stat->eval() << std::endl;
	}

	// Clear memory - delete all objects created by new
	for (IStatistics* stat: stats) {
		delete stat;
	}

	return 0;
}