#include <string>
#include <vector>

namespace libcmd {
    class Readline {
    private:
        std::string prompt;
        std::vector<std::string> vocab; // Does nothing for now

    public:
        explicit Readline(std::string _prompt) :
                prompt(std::move(_prompt)) {}

        std::string operator()();

        void AddToVocab(const std::string &s);

    private:
        static char **CommandCompletion(const char *text, int start, int end);

        static char *CommandGenerator(const char *text, int state);
    };
} // namespace libcmd
