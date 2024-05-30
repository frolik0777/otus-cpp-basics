#include <iostream>

#include "IStatistics.h"
#include "Min.h"
#include "Max.h"
#include "Mean.h"
#include "Std.h"
#include "Pct.h"

int main() {

	std::vector<IStatistics *> stats;
	stats.push_back(new Min{});
	stats.push_back(new Max{});
	stats.push_back(new Mean{});
	stats.push_back(new Std{});
	stats.push_back(new Pct{90});
	stats.push_back(new Pct{95});

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