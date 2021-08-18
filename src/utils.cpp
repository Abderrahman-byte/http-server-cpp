#include <string>
#include <sys/stat.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

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

bool check_ip_address(std::string address) {
    int parts_count = 0;
    std::stringstream address_stream(address);
    std::string part;

    while (getline(address_stream, part, '.')) {
        int part_int;

        try {
            part_int = stoi(part);
        } catch(...) {
            return false;
        }
    
        if (parts_count >= 4) return false;

        if (part_int > 255 || part_int < 0) return false;

        parts_count++;
    }

    return parts_count == 4;
}

void parse_args(int argc, char *argv[], std::string &config_filename) {
    std::vector <std::string> args (argv, argv + argc);

    if (argc <= 1) return ;

    if (argc > 3) {
        std::cout << "[ERROR] Too many arguments" << std::endl;
        show_usage(args[0], 1);
    }

    if (args[1] == "--file" || args[1] == "-f") {
        if (argc >= 3 && args[2] != "") {
            config_filename = args[2];
            return ;
        }

        std::cout << "[ERROR] Missing config file name" << std::endl;
        show_usage(args[0], 1);
    }

    if (args[1] == "--help" || args[1] == "-h") {
        show_usage(args[0], 0);
    } else {
        std::cout << "[ERROR] Invalid arguments" << std::endl;
        show_usage(args[0], 1);
    }
}

extern void show_usage(std::string name, int status) {
    std::cout << "Usage : " << name << " [-f <config_file>]" << std::endl;
    std::cout << "\t-f --file : config file (default : ./config.cfg)" << std::endl;
    std::cout << "\t-h --help : show options" << std::endl;
    exit(status);
}