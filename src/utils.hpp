#include <string>
#include <stdlib.h>
#include <sys/stat.h>

#ifndef _UTILS_H_
#define _UTILS_H_ 1

extern bool check_file_exists(std::string, struct stat*);
extern std::string join_path(std::string, std::string);
extern std::string get_file_content(std::string);
extern std::string get_file_extension(std::string);
extern bool check_ip_address(std::string);
extern void parse_args(int, char *[], std::string &);
extern void show_usage(std::string, int = EXIT_SUCCESS);

#endif