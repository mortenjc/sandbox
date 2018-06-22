#include <DirScan.h>
#include <cinttypes>
#include <iostream>
#include <string.h>


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
void DirScan::findSubStr(std::string needle) {
  uint64_t count{0};
  for (auto & string : files) {
    if (string.find(needle) != std::string::npos) {
      count++;
      printf("%s\n", string.c_str());
    }
  }
  printf("found %" PRIu64 " occurances of %s\n", count, needle.c_str());
}

///
///
void DirScan::searchLoop() {
    std::string command;
    while (true) {
      std::cout << "search string (quit)> ";
      std::getline(std::cin, command);
      if (command.empty() or command == "quit") {
        break;
      }
      findSubStr(command);
    };
}


DirScan::DirScan(std::string & rootDir, std::string & filter) {
    files.clear();
    listdir(rootDir, filter);
    printf("directories  : %" PRIu64 "\n", stats.directories);
    printf("total files  : %" PRIu64 "\n", stats.files);
    printf("matched files: %" PRIu64 "\n", stats.matchedfiles);
}
