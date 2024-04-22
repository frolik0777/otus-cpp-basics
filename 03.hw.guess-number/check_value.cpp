#include <iostream>
#include <ctime>
#include <fstream>
#include <limits>


static const std::string high_scores_filename = "high_scores.txt";
static int g_max_value = 100;
static int g_level = 2;


void print_help(std::ostream & file) {
	file << "Usage:" << std::endl;
	file << "\t -help           Show this message and exit" << std::endl;
	file << "\t -max <value>    Set the max random value to guess, default is " << g_max_value << std::endl;
	file << "\t -level <value>  Set the difficulty game level (1..3), default is " << g_level << std::endl;
	file << "\t -table          Show the high score table" << std::endl;
	file << "\t -table-full     Show the full high score table" << std::endl;
	file << std::endl;
	file << "\t Don't use options -level and -max together" << std::endl;
}

int get_next_high_score(std::ifstream & in_file, int & high_score) {
	if (in_file.fail()) {
		return -1;
	}

	// ignore all spaces
	char next_char = in_file.peek();
	while (next_char == ' ')  {
		in_file.ignore();
		next_char = in_file.peek();
	}

	if (!std::isdigit(next_char)) {
		return -1;
	}

	// Read the high score next
	in_file >> high_score;
	return 0;
}

// Write new high score to the records table
// line format: <username> score1 score2 .. scoreN
int write_highscore(const std::string & user_name, const int attempts_count) {

	const std::string tmp_file = high_scores_filename + "_";
	std::remove(tmp_file.c_str());

	std::ifstream in_file{high_scores_filename, std::ios_base::in};
	if (!in_file.is_open()) {
		std::cout << "Failed to open file: " << high_scores_filename << "!" << std::endl;
		return -1;
	}
	std::ofstream out_file{tmp_file, std::ios_base::app};
	if (!out_file.is_open()) {
		std::cout << "Failed to open file: " << tmp_file << "!" << std::endl;
		return -1;
	}

	bool added = false;
	while (true) {
		std::string user_name_r;
		int high_score = 0;

		// Read the username first
		in_file >> user_name_r;
		if (in_file.fail()){
			break;
		}

		out_file << user_name_r;
		while (get_next_high_score(in_file, high_score) == 0) {
			out_file << ' ' << high_score;
		}

		if (user_name_r == user_name) {
			// Append new result for the user
			out_file << ' ' << attempts_count;
			added = true;
		}

		out_file << std::endl;
	}

	if (!added) {
		// Append new user and results to the table
		out_file << user_name << ' ';
		out_file << attempts_count;
		out_file << std::endl;
	}

	std::remove(high_scores_filename.c_str());
	std::rename(tmp_file.c_str(), high_scores_filename.c_str());

	return 0;
}


// Read the high score file and print all results
int print_highscore_table(const bool bests_only) {
	std::ifstream in_file{high_scores_filename};
	if (!in_file.is_open()) {
		std::cout << "Failed to open file for read: " << high_scores_filename << "!" << std::endl;
		return -1;
	}

	if (!bests_only) {
		std::cout << "Full ";
	}
	std::cout << "High scores table:" << std::endl;

	std::string username;
	while (true) {
		// Read the username first
		in_file >> username;
		if (in_file.fail()) {
			break;
		}

		std::cout << username;

		if (bests_only) {
			// print best result only
			int hscore_best = std::numeric_limits<int>::max();
			int high_score = hscore_best;
			bool best_found = false;
			while (get_next_high_score(in_file, high_score) == 0) {
				hscore_best = std::min(high_score, hscore_best);
				best_found = true;
			}
			if (best_found) {
				std::cout << '\t' << hscore_best;
			} else {
				std::cout << "\t <no data>";
			}
		}
		else {
			// print all results
			int high_score = 0;
			while (get_next_high_score(in_file, high_score) == 0) {
				std::cout << '\t' << high_score;
			}
		}
		std::cout << std::endl;
	}
	return 0;
}


// parse application arguments
void parse_arguments(int argc, char** argv) {

	int max_value = 0;
	int level = 0;

	while (argc) {
		const std::string arg_value{ argv[0] };
		--argc;
		++argv;
		if (arg_value == "-help") {
			print_help(std::cout);
			std::exit(EXIT_SUCCESS);
		}
		else if (arg_value == "-max") {
			if (argc == 0) {
				std::cerr << "Missing parameter for argument \"" << arg_value << "\"" << std::endl;
				std::exit(EXIT_FAILURE);
			}
			max_value = std::stoi(argv[0]);
			if (max_value < 1) {
				std::cerr << "Wrong argument value for \"" << arg_value << "\"" << std::endl;
				std::exit(EXIT_FAILURE);
			}
			--argc;
			++argv;
		}
		else if (arg_value == "-level") {
			if (argc == 0) {
				std::cerr << "Missing parameter for argument \"" << arg_value << "\"" << std::endl;
				std::exit(EXIT_FAILURE);
			}
			level = std::stoi(argv[0]);
			switch(level) {
				case 1: g_max_value = 10; break;
				case 2: g_max_value = 50; break;
				case 3: g_max_value = 100; break;
				default:
					std::cerr << "Wrong argument value for \"" << arg_value << "\"" << std::endl;
					std::exit(EXIT_FAILURE);
					break;
			}			
			--argc;
			++argv;
		}
		else if (arg_value == "-table") {
			print_highscore_table(true);
			std::exit(EXIT_SUCCESS);
		}
		else if (arg_value == "-full-table") {
			print_highscore_table(false);
			std::exit(EXIT_SUCCESS);
		}
		else {
			std::cerr << "Unknown argument \"" << arg_value << "\"" << std::endl;
			print_help(std::cerr);
			std::exit(EXIT_FAILURE);
		}
	}

	if (level && max_value) {
		std::cerr << "Ambiguous usage of arguments -max and -level" << std::endl;
		print_help(std::cerr);
		std::exit(EXIT_FAILURE);
	}
}


int main(int argc, char** argv) {

	parse_arguments(--argc, ++argv);

	// initialize the target value as a random one
	std::srand(std::time(nullptr)); // use current time as seed for random generator
	const int target_value = std::rand() % g_max_value;

	// print the debug inforamation
	std::cout << "[DEBUG] target_value = " << target_value << std::endl;
	std::cout << "[DEBUG] max_value = " << g_max_value << std::endl;

	// Ask about name
	std::cout << "Hi! Enter your name, please:" << std::endl;
	std::string user_name;
	std::cin >> user_name;

	int attempts_count = 0;
	int current_value = 0;

	bool not_win = true;

	std::cout << "Enter your guess:" << std::endl;

	do {
		++attempts_count;
		std::cin >> current_value;

		if (current_value < target_value) {
			std::cout << "less than " << current_value << std::endl;
		}
		else if (current_value > target_value) {
			std::cout << "greater than " << current_value << std::endl;
		}
		else {
			std::cout << "you win! attempts = " << attempts_count << std::endl;
			break;
		}

	} while(true);

	if (write_highscore(user_name, attempts_count) != 0) {
		std::cerr << "Unable to store results to the file " << high_scores_filename << std::endl;
		return EXIT_FAILURE;;
	}
	if (print_highscore_table(true) != 0) {
		std::cerr << "Unable to read results frome the file " << high_scores_filename << std::endl;
		return EXIT_FAILURE;;
	}

	return EXIT_SUCCESS;
}