#include <DirScan.h>
#include <cinttypes>
#include <iostream>
#include <string.h>
#include <vector>
#include <CLI11.hpp>

///
///
bool DirScan::filterdir(char * d_name) {
  return (strcmp(d_name, ".") == 0  ||
          strcmp(d_name, "..") == 0 ||
          d_name[0] == '.');
}

void DirScan::removeLastSlash(std::string &str) {
  if (str.back() == '/') {
    str.pop_back();
  }
}

///
///
void DirScan::listdir(std::string name) {
  DirState state;

  if (!(state.dir = opendir(name.c_str())))
    return;

  while ((state.entry = readdir(state.dir)) != NULL) {
    // Ignore . .. and hidden dirs .*
    if (state.isDirectory()) {
      if (filterdir(state.entry->d_name)) {
          continue;
      }
      //printf("DEBUG: readdir: %s\n", state.entry->d_name);
      stats.directories++;

      auto dirname = name + "/" + state.entry->d_name;
      listdir(dirname);
    } else {
      stats.files++;
      auto e = new DirEntry(name, state.entry->d_name);
      auto filename = name + "/" + state.entry->d_name;

      stats.matchedfiles++;
      files.push_back(*e);
      if (Settings.Verbose) {
        e->print();
      }
    }
  }
  closedir(state.dir);
}


DirScan::DirScan(AppSettings & settings) : Settings(settings) {
    files.clear();
    removeLastSlash(Settings.RootDir);

    listdir(Settings.RootDir);

    printf("directories  : %" PRIu64 "\n", stats.directories);
    printf("total files  : %" PRIu64 "\n", stats.files);
    printf("matched files: %" PRIu64 "\n", stats.matchedfiles);
}
