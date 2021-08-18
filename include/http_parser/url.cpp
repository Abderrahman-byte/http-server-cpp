#include <string>
#include <vector>
#include <sstream>

#include "utils.hpp"
#include "url.hpp"

void parse_url(url_t* url, std::string unparsed_url) {
    int sep_pos = unparsed_url.find('?');
    std::string unparsed_query = "";

    if (sep_pos < 0) {
        url->path = unparsed_url;
        return ;
    }

    url->path = unparsed_url.substr(0, sep_pos);
    unparsed_query = unparsed_url.substr(sep_pos + 1);

    parse_search_query(&url->searchquery, unparsed_query);
}

//
void parse_search_query(std::vector<queryfield_t>* query, std::string unparsed_query) {
    std::string field_str;
    std::stringstream unparsed_query_stream(unparsed_query);

    while (getline(unparsed_query_stream, field_str, '&')) {
        int del_pos = field_str.find('=');
        queryfield_t field;

        if (del_pos >= 0) {
            field.name = trim(field_str.substr(0, del_pos));
            field.value = trim(field_str.substr(del_pos + 1));

            if (field.name.length() > 0 && field.value.length() > 0) {
                query->push_back(field);
            }
        }
    }
}