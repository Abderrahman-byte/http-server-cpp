#include <string>
#include <vector>

#ifndef _MIME_TYPE_H_
#define _MIME_TYPE_H_ 1

#define FALLBACK_MIME "text/plain"

typedef struct {
    std::string mimetype;
    std::string extension;
} mime_type_t;

extern std::string get_mime_type (std::string);
extern void init_mimetypes();
extern std::vector<mime_type_t> mimetypes;

#endif