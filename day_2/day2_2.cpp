#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iterator>
#include <algorithm>

int read_file(std::vector<int> &input) {
	// Create a text string, which is used to output the text file
	std::string token;
	
	// Read from the text file
	std::ifstream MyReadFile("input");

	// Use a while loop together with the getline() function to read the file line by line
	while (getline (MyReadFile, token, ',')) {
		// Output the text from the file
		//std::cout << token << '\n';
		input.push_back(std::stoi(token));
	}
	
	// Close the file
	MyReadFile.close();
	
	return 0;
}

void calculate(std::vector<int> &input) {

	int result;

	for(int i=0; (size_t)i<input.size(); i=i+4) {
		int operator_ = input[i];
		//std::cout << "Operator: " << operator_ << "\n";
		
		if (operator_==1) {
			result = input[input[i+1]] + input[input[i+2]];
			//std::cout << ' ' << input[input[i+1]] << " + " << input[input[i+2]] << " = " << input[input[i+1]] + input[input[i+2]] << '\n';
		} else if (operator_==2) {
			result = input[input[i+1]] * input[input[i+2]];
			//std::cout << ' ' << input[input[i+1]] << " * " << input[input[i+2]] << " = " << input[input[i+1]] * input[input[i+2]] << '\n';
		} else if (operator_==99) {
			std::cout << "Finish!\n";
			break;
		} else {
			std::cout << "Something wrong...\n";
			break;
		}
		input[input[i+3]] = result;
		 
		//for (int i=0; i<input.size(); i++) {
		//	std::cout << input[i] << ',';

		//	if ((i+1)%4 == 0){
		//		std::cout << " / ";
		//	} 
		//	if (i == input.size()-1) {
		//		std::cout << "\n";
		//	}
		//}
	}
}

int main(){
	std::vector<int> input;

	// Read file and store data into a vector
	int res = read_file(input);
	if (res == -1) {
		std::cout << "Reallocation error";
		return 1;
	}

	std::vector<int> copied_input = input;

	// Display read data
	//std::cout << "Array: ";
	//for (int i=0; (size_t)i<input.size(); i++) {
	//	copied_input.push_back(input[i]);

	//	std::cout << input[i] << ',';

	//	if ((i+1)%4 == 0){
	//		std::cout << " / ";
	//	} 
	//	if ((size_t)i == input.size()-1) {
	//		std::cout << "\n";
	//	}
	//}

	for (int x=0; x<99; x++) {
		//input[1] = x;
		for (int y=0; y<99; y++) {
			input[1] = x;
			input[2] = y;
			std::cout << "\n* x=" << x << ", y=" << y << "\n";

			std::cout << "Array: ";
			//for (int i=0; (size_t)i<input.size(); i++) {
			//	std::cout << input[i] << ',';

			//	if ((i+1)%4 == 0){
			//		std::cout << " / ";
			//	} 
			//	if ((size_t)i == input.size()-1) {
			//		std::cout << "\n";
			//	}
			//}

			// Calculate and display the result
			calculate(input);
			std::cout << "	Result: " << input[0];
			if (input[0] == 19690720) {
				std::cout << "\n\nFound!";
				return EXIT_SUCCESS;
			}
			else {
				input = copied_input;
			}
			
			//std::cout << "New array: ";
			//for (int i=0; (size_t)i<input.size(); i++) {
			//	std::cout << input[i] << ',';

			//	if ((i+1)%4 == 0){
			//		std::cout << " / ";
			//	} 
			//	if ((size_t)i == input.size()-1) {
			//		std::cout << "\n";
			//	}
			//}

			//fprintf(stderr, "Result: ");
			//for (int i=0; i<input.size; i++){
			//	fprintf(stderr, "%d,", input.data[i]);
			//}
			//fprintf(stderr, "\n");
		}
	}
	return EXIT_SUCCESS; //=0
}
