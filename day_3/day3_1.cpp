#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <regex>
#include <cstdlib>
#include <limits>
#include <bits/stdc++.h>
 

int read_two_lines(std::vector<std::string> &input) {
	std::string token;
	std::string line;
	std::ifstream ReadFile("input");

	while (getline(ReadFile, line)) {
		//std::cout << "Line: " << line << "\n";
		std::istringstream linestream(line);
		std::string words;
		size_t pos = 0;
		std::string token;

		linestream >> words;
		while ((pos = words.find(',')) != std::string::npos) {
			token = words.substr(0, pos);
			input.push_back(token);
			//std::cout << "Word: " << token << std::endl;
			words.erase(0, pos + 1);
		}
		//std::cout << "Last word: " << words << std::endl;
		input.push_back(words);
		input.push_back(",");
	}
	ReadFile.close();
	return 0;
}

int read_paths(std::vector<std::string> &input, std::unordered_set<std::tuple<int,int>> &first_path, std::unordered_set<std::tuple<int,int>> &second_path) {
	std::unordered_set<std::tuple<int,int>> current_path;
	std::tuple<int,int> current_position = {0,0};
	bool is_next_second = false;
	std::smatch sm;
	std::string direction;
	int step;
	
	for (int i=0; (size_t)i<input.size(); i++) {
		int x;
		int y;
		std::tie (x, y) = current_position;
		std::cout << "Current position: " << x << ", " << y << "\n\n";
		std::cout << "Selected: " << input[i] << "\n";

		if (input[i] == ",") {
			// Store path
			if (is_next_second) {
				second_path = current_path;
			} else {
				first_path = current_path;
			}

			// Reset
			std::get<0>(current_position) = 0;
			std::get<1>(current_position) = 0;
			current_path = {};
			is_next_second = true;
			continue;
		}

		// Get the new position
		std::regex_match (input[i], sm, std::regex("(\\w)(\\d+)"));
		direction = sm[1];
		step = std::stoi(sm[2]);
		
		if (direction=="R") {
			for (int s=x+1; s<=x+step; s++) {
				//std::cout << "Position: " << s << "," << y << "\n";
				current_position = {s,y}; 	
				current_path.push_back(current_position);
			}
		} else if (direction=="L") {
			for (int s=x-1; x-step<=s; s--) {	
				//std::cout << "Position: " << s << "," << y << "\n";
				current_position = {s,y}; 	
				current_path.push_back(current_position);
			}
		} else if (direction=="U") {
			for (int s=y+1; s<=y+step; s++) {
				//std::cout << "Position: " << x << "," << s << "\n";
				current_position = {x,s};
				current_path.push_back(current_position);
			}
		} else if (direction=="D") {
			for (int s=y-1; y-step<=s; s--) {
				//std::cout << "Position: " << x << "," << s << "\n";
				current_position = {x,s};
				current_path.push_back(current_position);	
			}
		}
	
		// Current wire path:
		//std::cout << "Current wire path:\n";
		//int res_x;
		//int res_y;
		//for (int i=0; (size_t)i<current_path.size(); i++) {
		//	std::tie (res_x, res_y) = current_path[i];
		//        std::cout << res_x << "," << res_y << " / ";
		//        if ((size_t)i == current_path.size()-1) {
		//                std::cout << "\n";
		//        }                 
		//}                         
		
	}
	return 0;
}

int find_intersections(std::unordered_set<std::tuple<int,int>> &first_path, std::unordered_set<std::tuple<int,int>> &second_path, std::unordered_set<std::tuple<int, int>> &intersections) {
	int f_x;
	int f_y;
	int s_x;
	int s_y;
	std::cout << "Looking for intersections\n";
	
	for (int i=0; (size_t)i<first_path.size(); i++) {
		std::tie (f_x, f_y) = first_path[i];
		//std::cout << "First X: " << f_x << ", First Y: " << f_y << std::endl;
		for (int j=0; (size_t)j<second_path.size(); j++) {
			std::tie (s_x, s_y) = second_path[j];
			//std::cout << "Second X: " << s_x << ", Second Y: " << s_y << "\n";
			if (f_x == s_x && f_y == s_y) {
				std::cout << "Bingo: " << f_x << ", " << f_y << "\n";
				intersections.push_back(first_path[i]); 
			}
		}
	}
	return 0;
}

int main() {
	std::vector<std::string> input = {};	
	std::unordered_set<std::tuple<int,int>> first_path;
	std::unordered_set<std::tuple<int,int>> second_path;	
	std::unordered_set<std::tuple<int,int>> intersections;

	// Read file and store data into a vector
	int res = read_two_lines(input);
	if (res != 0) {
		std::cout << "Reallocation error";
		return 1;
	}

	//// Display read data
	//std::cout << "Input: \n";
	//for (int i=0; (size_t)i<input.size(); i++) {
	//        std::cout << input[i] << ',';
	//        if ((size_t)i == input.size()-1) {
	//                std::cout << "\n";
	//        }
	//}

	std::cout << "\n";
	res = read_paths(input, first_path, second_path);
	if (res != 0) {
		std::cout << "Paths reading error";
		return 1;
	}

	//// Display only the first wire path
	//std::cout << "First wire path:\n";
	//int res_x;
	//int res_y;
	//for (int i=0; (size_t)i<first_path.size(); i++) {
	//	std::tie (res_x, res_y) = first_path[i];
	//        std::cout << res_x << "," << res_y << " / ";
	//        if ((size_t)i == first_path.size()-1) {
	//                std::cout << "\n";
	//        }
	//}

	// find the intersections
	res = find_intersections(first_path, second_path, intersections);

	std::cout << "\n";
	if (res != 0) {
		std::cout << "Intersection calculation error";
		return 1;
	}

	// Display only the intersections
	std::cout << "Intersections:\n";
	int res_x;
	int res_y;
	for (int i=0; (size_t)i<intersections.size(); i++) {
		std::tie (res_x, res_y) = intersections[i];
	        std::cout << res_x << "," << res_y << " / ";
	        if ((size_t)i == intersections.size()-1) {
	                std::cout << "\n";
	        }
	}

	// calculate the manhattan distance and get the lowest one
	int distance = std::numeric_limits<int>::max();
	int d;
	for (int i=0; (size_t)i<intersections.size(); i++) {
		std::tie (res_x, res_y) = intersections[i];
		d = std::abs(res_x) + std::abs(res_y);	
		if (distance > d) {
			distance = d;
		}
	}
	std::cout << "\nManathan distance: " << distance << std::endl;
	return 0;
}

