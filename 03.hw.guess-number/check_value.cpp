#include <iostream>
#include <ctime>
#include <fstream>


static const std::string high_scores_filename = "high_scores.txt";
static int max_value = 100;


// Write new high score to the records table
int write_highscore(const std::string & user_name, const int attempts_count) {
	// We should open the output file in the append mode - we don't want
	// to erase previous results.
	std::ofstream out_file{high_scores_filename, std::ios_base::app};
	if (!out_file.is_open()) {
		std::cout << "Failed to open file for write: " << high_scores_filename << "!" << std::endl;
		return -1;
	}

	// Append new results to the table:
	out_file << user_name << ' ';
	out_file << attempts_count;
	out_file << std::endl;
	return 0;
}


// Read the high score file and print all results
int print_highscore_table() {
	std::ifstream in_file{high_scores_filename};
	if (!in_file.is_open()) {
		std::cout << "Failed to open file for read: " << high_scores_filename << "!" << std::endl;
		return -1;
	}

	std::cout << std::endl << "High scores table:" << std::endl;

	std::string username;
	int high_score = 0;
	while (true) {
		// Read the username first
		in_file >> username;
		// Read the high score next
		in_file >> high_score;
		// Ignore the end of line symbol
		in_file.ignore();

		if (in_file.fail()) {
			break;
		}

		// Print the information to the screen
		std::cout << username << '\t' << high_score << std::endl;
	}
	return 0;
}


// parse application arguments
void parse_arguments(int argc, char** argv) {
	while (argc) {
		const std::string arg_value{ argv[0] };
		--argc;
		++argv;
		if (arg_value == "-max") {
			if (argc == 0) {
				std::cerr << "Missing parameter for argument \"" << arg_value << "\"" << std::endl;
				std::exit(EXIT_FAILURE);
			}
			max_value = std::stoi(argv[0]);
			--argc;
			++argv;
		}
		else if (arg_value == "-table") {
			print_highscore_table();
			std::exit(EXIT_SUCCESS);
		}
		else {
			std::cerr << "Unknown argument \"" << arg_value << "\"" << std::endl;
			std::exit(EXIT_FAILURE);
		}
	}
}


int main(int argc, char** argv) {

	parse_arguments(--argc, ++argv);

	// Ask about name
	std::cout << "Hi! Enter your name, please:" << std::endl;
	std::string user_name;
	std::cin >> user_name;

	// initialize the target value as a random one
	std::srand(std::time(nullptr)); // use current time as seed for random generator
	const int target_value = std::rand() % max_value;

	// print the debug inforamation
	std::cout << "[DEBUG] target_value = " << target_value << std::endl;
	std::cout << "[DEBUG] max_value = " << max_value << std::endl;

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
	if (print_highscore_table() != 0) {
		std::cerr << "Unable to read results frome the file " << high_scores_filename << std::endl;
		return EXIT_FAILURE;;
	}

	return EXIT_SUCCESS;
}