#include <DirScan.h>
#include <dirent.h>
#include <cinttypes>
#include <string.h>


void DirScan::listdir(const char *name, int indent)
{
    DIR *dir;
    struct dirent *entry;

    if (!(dir = opendir(name)))
        return;

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_DIR) {
            char path[1024];
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0 || entry->d_name[0] == '.')
                continue;
            stats.directories++;
            snprintf(path, sizeof(path), "%s/%s", name, entry->d_name);
            printf("%*s[%s]\n", indent, "", entry->d_name);
            listdir(path, indent + 2);
        } else {
            stats.files++;
            if (strstr(entry->d_name, ".pdf") != NULL) {
              stats.matchedfiles++;
              printf("%*s- %s\n", indent, "", entry->d_name);
            }
        }
    }
    closedir(dir);

}

DirScan::DirScan(std::string rootDir) {
    listdir(rootDir.c_str(), 4);
    printf("directories  : %" PRIu64 "\n", stats.directories);
    printf("total files  : %" PRIu64 "\n", stats.files);
    printf("matched files: %" PRIu64 "\n", stats.matchedfiles);
}
