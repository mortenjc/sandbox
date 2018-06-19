#include <dirent.h>
#include <string>
#include <set>

struct stats_t {
  uint64_t directories{0};
  uint64_t files{0};
  uint64_t matchedfiles{0};
};

class DirState {
public:
  DIR * dir;
  struct dirent *entry;
  bool isDirectory() const {return entry->d_type == DT_DIR; }
};

class DirScan {
public:

  DirScan(std::string rootDir, std::string filter);

private:
  void listdir(std::string &name, std::string &filter);

  struct stats_t stats;
};
