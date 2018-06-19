#include <DirScan.h>
#include <cinttypes>
#include <string.h>


void DirScan::listdir(std::string &name, std::string &filter) {
  DirState state;

  if (!(state.dir = opendir(name.c_str())))
    return;

  while ((state.entry = readdir(state.dir)) != NULL) {
    if (state.isDirectory()) {
      if (strcmp(state.entry->d_name, ".") == 0 || strcmp(state.entry->d_name, "..") == 0 || state.entry->d_name[0] == '.') {
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
        printf("%s\n", filename.c_str());
      }
    }
  }
  closedir(state.dir);
}


DirScan::DirScan(std::string rootDir, std::string filter) {
    listdir(rootDir, filter);
    printf("directories  : %" PRIu64 "\n", stats.directories);
    printf("total files  : %" PRIu64 "\n", stats.files);
    printf("matched files: %" PRIu64 "\n", stats.matchedfiles);
}
