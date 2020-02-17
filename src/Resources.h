#pragma once
#include <map>
#include <algorithm>
#include <fstream>
#include <vector>
#include <string>
#include <filesystem>

namespace fs = std::filesystem;

std::string ConvertSpaces2_(std::string text);

std::vector<fs::path> GetFilesInFolder(std::string folder, std::string filetype);