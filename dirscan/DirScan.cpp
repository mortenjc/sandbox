#include <DirScan.h>
#include <cinttypes>
#include <iostream>
#include <string.h>
#include <vector>


///
///
bool DirScan::filterdir(char * d_name) {
  return (strcmp(d_name, ".") == 0  ||
          strcmp(d_name, "..") == 0 ||
          d_name[0] == '.');
}

///
///
void DirScan::listdir(std::string name, std::string filter) {
  DirState state;

  if (!(state.dir = opendir(name.c_str())))
    return;

  while ((state.entry = readdir(state.dir)) != NULL) {
    if (state.isDirectory()) {
      if (filterdir(state.entry->d_name)) {
          continue;
      }
      stats.directories++;
      auto dirname = name + "/" + state.entry->d_name;
      listdir(dirname, filter);
    } else {
      stats.files++;
      auto filename = name + "/" + state.entry->d_name;
      if (filename.find(filter) != std::string::npos) {
        stats.matchedfiles++;
        files.insert(filename);
        //printf("%s\n", filename.c_str());
      }
    }
  }
  closedir(state.dir);
}

///
///
uint64_t DirScan::findSubStr(std::string needle) {
  uint64_t count{0};
  for (auto & file : files) {
    if (file.find(needle) != std::string::npos) {
      count++;
      printf("%s\n", file.c_str());
    }
  }
  return count;
}

///
///
uint64_t  DirScan::findSubStr(std::vector<std::string> needles) {
  uint64_t count{0};
  for (auto file : files) {
    bool match{true};
    for (auto & needle : needles) {
       match = match && (file.find(needle) != std::string::npos);
    }
    if (match) {
      count++;
      if (printNames) {
        printf("%s\n", file.c_str());
      }
    }
  }
  return count;
}

///
///
void DirScan::searchLoop() {
    std::string command;
    while (true) {
      std::cout << "search string (quit)> ";
      std::getline(std::cin, command);
      std::vector<std::string> tokens;
      char *chars_array = strtok((char *)command.c_str(), "\n ");
      while (chars_array) {
        std::string token(chars_array);
        tokens.push_back(token);
        chars_array = strtok(NULL, "\n ");
      }
      if (command.empty() or command == "quit") {
        break;
      }
      auto res = findSubStr(tokens);
      printf("found %" PRIu64 " occurances of %s\n", res, command.c_str());
    };
}


DirScan::DirScan(std::string & rootDir, std::string & filter) {
    files.clear();
    listdir(rootDir, filter);
    printf("directories  : %" PRIu64 "\n", stats.directories);
    printf("total files  : %" PRIu64 "\n", stats.files);
    printf("matched files: %" PRIu64 "\n", stats.matchedfiles);
}
