#include <string>
#include <vector>
#include <memory>
#include <readline/history.h>

namespace libcmd {
    class Readline {

    private:
        std::string prompt;
        std::vector<std::string> vocab;
        std::vector<std::string> matches;

    public:
        explicit Readline(std::string _prompt);

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
} // namespace libcmd
