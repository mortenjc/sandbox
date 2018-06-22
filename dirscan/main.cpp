#include <DirScan.h>
#include <vector>

int main(int argc, char * argv[]){
  std::string rootDir = ".";
  std::string initialFilter{""};

  if (argc == 2) {
    initialFilter = argv[1];
  } else if (argc > 2) {
    rootDir = argv[1];
    initialFilter = argv[2];
  }

  DirScan essproj(rootDir, initialFilter);

  essproj.searchLoop();

  return 0;
}
