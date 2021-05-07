#include "cmdpp/readline.hpp"
#include "cmdpp/utils.hpp"

#include <readline/readline.h>
#include <readline/history.h>
#include <memory>
#include <algorithm>

namespace libcmd {
    Readline *currentReadline = nullptr;

    std::string Readline::operator()() {
        currentReadline = this;

        rl_attempted_completion_function = &Readline::CommandCompletion;

        char *line = readline(prompt.c_str());
        if (!line) return "";

        std::string res{line};

        if (!IsEmptyOrWhitespace(res))
            add_history(res.c_str());
        else
            res = "";

        free(line);

        return res;
    }

    void Readline::AddToVocab(const std::string &s) {
        if (!IsEmptyOrWhitespace(s)) {
            vocab.push_back(s);
        }
    }

    void Readline::GenerateMatches(const char *text) {
        std::string stext{text};
        for (const std::string &word : vocab) {
            if (word.find(stext) != std::string::npos) {
                matches.push_back(word);
            }
        }
    }

    char **Readline::CommandCompletion(const char *text, int start, int end) {
        // -Wunused-parameter
        (void)start;
        (void)end;

        rl_attempted_completion_over = 1;
        return rl_completion_matches(text, &Readline::CommandGenerator);
    }

    char *Readline::CommandGenerator(const char *text, int state) {
        static size_t match_index = 0;

        if (state == 0) {
            currentReadline->matches.clear();
            match_index = 0;

            currentReadline->GenerateMatches(text);
        }

        if (match_index >= currentReadline->matches.size()) {
            return nullptr;
        } else {
            return strdup(currentReadline->matches[match_index++].c_str());
        }
    }
} // namespace libcmd
