#pragma once

#include <string>

class Album {
public:
  Album(std::string name) : name(name) {
    printf("Album: %s\n", name.c_str());
  };

  void addFile(std::string name) {
    printf("   File: %s\n", name.c_str());
    files.insert(name);
  }


private:
  std::string name;
  std::set<std::string> files;
};
