#include "cmdpp/readline.hpp"
#include "cmdpp/utils.hpp"

#include <readline/readline.h>
#include <readline/history.h>
#include <memory>

namespace libcmd {
    std::string Readline::operator()() {
        char *line = readline(prompt.c_str());
        if (!line) return "";

        std::string res{line};

        if (is_empty_or_whitespace(res))
            res = "";

        if (!res.empty())
            add_history(line);

        free(line);

        return res;
    }

    void Readline::AddToVocab(const std::string &s) {
        if (!is_empty_or_whitespace(s)) {
            vocab.push_back(s);
        }
    }
} // namespace libcmd
