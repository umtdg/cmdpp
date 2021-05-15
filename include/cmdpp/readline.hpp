#ifndef CMDPP_READLINE_HPP
#define CMDPP_READLINE_HPP

#include <string>
#include <vector>

namespace cmdpp {
    class Readline {
    private:
        std::string prompt;
        std::vector<std::string> vocab;
        std::vector<std::string> matches;

        bool useColor = false;

    public:
        explicit Readline(const std::string &_prompt, bool _useColor = true);

        ~Readline() = default;

        std::string operator()();

        void AddToVocab(const std::string &s);

        Readline(const Readline &) = delete;
        Readline(Readline &&) = delete;
        Readline &operator=(const Readline &) = delete;
        Readline &operator=(Readline &&) = delete;

    private:
        void GenerateMatches(const char *text);

        static char **CommandCompletion(const char *text, int start, int end);

        static char *CommandGenerator(const char *text, int state);
    };
} // namespace cmdpp

#endif // #ifndef CMDPP_READLINE_HPP
