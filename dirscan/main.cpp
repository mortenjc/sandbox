#include <DirScan.h>
#include <vector>
#include <AppSettings.h>
#include <CLI11.hpp>


int main(int argc, char * argv[]){
  AppSettings Settings;
  CLI::App app{"Directory Scanner"};
  app.add_option("-d", Settings.RootDir, "RootDir");
  app.add_option("-f", Settings.Filter, "Filter");
  app.add_flag("-v", Settings.Verbose, "Verbose");
  CLI11_PARSE(app, argc, argv);

  DirScan essproj(Settings);
  auto files = essproj.getFiles();


  return 0;
}
