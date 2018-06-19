#include <DirScan.h>


int main(int argc, char * argv[]){
  std::string rootDir = ".";
  std::string filter = "";

  if (argc == 2) {
    filter = argv[1];
  } else if (argc == 3) {
    rootDir = argv[1];
    filter = argv[2];
  }
  DirScan essproj(rootDir, filter);

  return 0;
}
