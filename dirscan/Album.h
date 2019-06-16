#pragma once

#include <string>

class Album {
public:
  Album(std::string name) : name(name) {};

  void addFile(std::string name) { files.insert(name); }
private:
  std::string name;
  std::set<std::string> files;
};
