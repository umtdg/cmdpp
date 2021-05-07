#include <string>
#include <vector>
#include <unordered_map>

namespace libcmd {
    class Readline {

    private:
        std::string prompt;
        std::vector<std::string> vocab;
        std::vector<std::string> matches;

    public:
        explicit Readline(std::string _prompt) :
                prompt(std::move(_prompt)) {}

        std::string operator()();

        void AddToVocab(const std::string &s);

        void GenerateMatches(const char *text);

    private:
        static char **CommandCompletion(const char *text, int start, int end);

        static char *CommandGenerator(const char *text, int state);
    };
} // namespace libcmd
