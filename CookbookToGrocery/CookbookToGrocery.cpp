// CookbookToGrocery.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

 #include "pch.h"
 #include <iostream>

int main()
{
	tesseract::TessBaseAPI tess;

	if (tess.Init("./", "eng"))
	{
		std::cout << "OCRTesseract: Could not initialize tesseract." << std::endl;
		return 1;
	}

	tess.SetPageSegMode(tesseract::PageSegMode::PSM_AUTO);
	tess.SetVariable("save_best_choices", "T");

	// read image
	auto pixs = pixRead("test1.jpg");
	if (!pixs)
	{
		std::cout << "Cannot open input file: " << "test.jpg" << std::endl;
		return 1;
	}

	// recognize
	tess.SetImage(pixs);
	tess.Recognize(0);

	// get result and delete[] returned char* string
	char* raw_results = tess.GetUTF8Text();
	std::string results = std::string(raw_results);
	
	std::vector<std::string> raw_ingredients;
	int position = 0;
	while (results.find('\n\n', position) != std::string::npos) {
		raw_ingredients.push_back(results.substr(position, results.find('\n\n', position) - position));
		position = results.find('\n\n', position) + 1;
	}

	for (int i = 0; i < raw_ingredients.size(); i++) {
		std::cout << "Ingredient " << i << ": " << raw_ingredients[i] << std::endl;
	}

	//TODO: Determine lexer/parser for ingredients
	//Some research needed.
	

	delete[] raw_results;


	// cleanup
	tess.Clear();
	pixDestroy(&pixs);


    std::cout << "Hello World!\n"; 
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
