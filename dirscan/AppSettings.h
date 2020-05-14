#pragma once

#include <string>

struct AppSettings {
  std::string RootDir {"."};
  std::string Filter {""};
  bool Verbose;
};
