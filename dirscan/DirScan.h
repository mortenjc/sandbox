#include <dirent.h>
#include <string>
#include <vector>
#include <AppSettings.h>

class DirEntry {
public:
  DirEntry(std::string dir, std::string file) : Dir(dir), File(file) {}
  void print() { printf("%s %s\n", Dir.c_str(), File.c_str());}
private:
  std::string Dir;
  std::string File;
};

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

  DirScan(AppSettings & settings);

  static void removeLastSlash(std::string &str);

  std::vector<DirEntry> getFiles() {return files;}

private:
  AppSettings Settings;
  void listdir(std::string name);

  bool filterdir(char * d_name);

  struct stats_t stats;
  std::vector<DirEntry> files;
};
