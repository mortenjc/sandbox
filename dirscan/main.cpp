#include <DirScan.h>
#include <vector>
#include <AppSettings.h>
#include <CLI11.hpp>
#include <Album.h>


int main(int argc, char * argv[]){
  AppSettings Settings;
  CLI::App app{"Directory Scanner"};
  app.add_option("-d", Settings.RootDir, "RootDir");
  app.add_option("-f", Settings.Filter, "Filter");
  app.add_flag("-v", Settings.Verbose, "Verbose");
  CLI11_PARSE(app, argc, argv);

  DirScan essproj(Settings);
  auto Entries = essproj.getFiles();

  Album * AlbumPtr = nullptr;
  std::vector<Album> Albums;
  std::string AlbumTitle = "";
  for (auto Entry : Entries) {
    if (Entry.getDir() != AlbumTitle) {
      AlbumTitle = Entry.getDir();
      AlbumPtr = new Album(AlbumTitle);
    }
    AlbumPtr->addFile(Entry.getFile());
  }

  return 0;
}
