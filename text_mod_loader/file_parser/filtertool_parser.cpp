#include "pch.h"
#include "filtertool_parser.h"
#include "parse_result.h"
#include "util.h"

namespace tml {

void parse_filtertool_file(std::istream& stream, ParseResult& parse_result) {
    // Discard the first line (root category header)
    std::string line;
    std::getline(stream, line);

    auto started_description_category = false;
    for (; std::getline(stream, line);) {
        auto first_non_space =
            std::ranges::find_if_not(line, [](auto chr) { return std::isspace(chr); });
        auto last_non_space = std::ranges::find_if_not(std::ranges::reverse_view(line),
                                                       [](auto chr) { return std::isspace(chr); });

        const std::string_view trimmed{first_non_space, last_non_space.base()};

        if (trimmed.starts_with("#<") && trimmed.ends_with('>')) {
            if (!started_description_category) {
                const CaseInsensitiveStringView category_name{trimmed.begin() + 2,
                                                              trimmed.end() - 1};

                static const constexpr CaseInsensitiveStringView description = "description";
                if (category_name.find(description) != CaseInsensitiveStringView::npos) {
                    // This is a dedicated description category
                    // Discard existing comments, and get them from this category's children instead
                    parse_result.discard_comments();
                    started_description_category = true;
                    continue;
                }
            }

        } else if (!is_command(trimmed)) {
            // Must be a comment, add to the list
            parse_result.add_comment(line);
            continue;
        }

        // This is either a command, or a (non-description) category, which both mark the end of
        // the description.
        // Seek back to the start of this line, to leave the stream in a good state, then quit
        stream.seekg(-(ptrdiff_t)line.size(), std::ios::cur);
        break;
    }
}

}  // namespace tml
