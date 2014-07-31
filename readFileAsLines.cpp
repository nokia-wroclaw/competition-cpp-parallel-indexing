#include <fstream>
#include "readFileAsLines.hpp"

std::vector<std::string> readFileAsLines(std::string const& file)
{
  std::ifstream infile;
  infile.open(file);
  if(not infile.is_open())
    throw std::runtime_error{"unable to open file: " + file};

  std::vector<std::string> out;
  std::string              line;
  while( std::getline(infile, line) )
    out.push_back(line);

  return out;
}
