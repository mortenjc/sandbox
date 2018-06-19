#include <string>


class DirScan {
public:
  DirScan(std::string rootDir);
  //DirScan(std::vector<std::string> dirs, std::vector<std::string> extensions);
private:
  void listdir(const char *name, int indent);

  struct stats_t {
    uint64_t directories{0};
    uint64_t files{0};
    uint64_t matchedfiles{0};
  } stats;
};
