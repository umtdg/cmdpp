#include "cmdpp/readline.hpp"
#include "cmdpp/utils.hpp"

#include <readline/readline.h>
#include <readline/history.h>
#include <memory>

namespace libcmd {
    Readline *currentReadline = nullptr;

    std::string Readline::operator()() {
        currentReadline = this;

        rl_attempted_completion_function = &Readline::CommandCompletion;

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

    char **Readline::CommandCompletion(const char *text, int start, int end) {
        // -Wunused-parameter
        (void)start;
        (void)end;

        rl_attempted_completion_over = 1;
        return rl_completion_matches(text, &Readline::CommandGenerator);
    }

    char *Readline::CommandGenerator(const char *text, int state) {
        static std::vector<std::string> matches;
        static size_t match_index = 0;

        if (state == 0) {
            matches.clear();
            match_index = 0;

            std::string stext{text};
            size_t text_len = stext.size();
            for (const auto& word : currentReadline->vocab) {
                if (word.size() >= text_len && word.compare(0, text_len, stext) == 0) {
                    matches.push_back(word);
                }
            }
        }

        if (match_index >= matches.size()) {
            return nullptr;
        } else {
            return strdup(matches[match_index++].c_str());
        }
    }
} // namespace libcmd
