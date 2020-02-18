#include "Resources.h"

using namespace std;

string ConvertSpaces2_(string text)
{
	while (true)
	{
		std::size_t pos = text.find(" ");

		if (pos == std::string::npos)
			break;

		text = text.replace(pos, 1, "_");
	}
	return text;
}

//get path vector of all files of given type
vector<fs::path> GetFilesInFolder(string folder, string filetype)
{
	vector<fs::path> paths;

	for (const auto & entry : fs::directory_iterator(folder))
	{
		//check if the file has the correct filetype
		if (entry.path().extension().string() == filetype)
		{
			paths.push_back(entry.path());
		}
	}

	//sort the files in alphabetical order
	sort(paths.begin(), paths.end());

	return paths;
}
