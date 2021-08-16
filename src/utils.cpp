#include <string>
#include <sys/stat.h>
#include <fstream>

#include "utils.hpp"

bool check_file_exists(std::string filename, struct stat* file_stat) {
    if (file_stat != NULL) {
        return stat(filename.c_str(), file_stat) == 0;
    }

    struct stat filestat;
    return stat(filename.c_str(), &filestat) == 0;
}

std::string join_path(std::string parent, std::string child) {
    int path_start = child.find_first_not_of("./");
    parent = parent.substr(0, parent.find_last_not_of("/") + 1);

    if (path_start > 0 && path_start < child.length()) {
        child = child.substr(child.find_first_not_of("./"));
    } else if (path_start >= child.length()) {
        child = "";
    }

    return parent + "/" + child;
}

std::string get_file_content(std::string filename) {
    std::ifstream file(filename);

    if (file.is_open()) {
        std::string content;
        std::string templine;

        while(getline(file, templine)) {
            content += templine + "\n";
        }

        file.close();

        return content;
    }

    return "";
}

std::string get_file_extension(std::string filename) {
    int slash_pos = filename.find_last_of("/");
    int dot_pos;
    
    if (slash_pos >= 0 && slash_pos + 1 < filename.length()) {
        filename = filename.substr(slash_pos + 1);
    } else if (slash_pos + 1 >= filename.length() ) {
        return "";
    }

    dot_pos = filename.find_last_of(".");

    if (dot_pos <= 0 || dot_pos + 1 >= filename.length()) return "";
    else return filename.substr(dot_pos + 1);
}