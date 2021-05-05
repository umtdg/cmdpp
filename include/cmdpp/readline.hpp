#include <string>

namespace libcmd {
    class Readline {
    private:
        std::string prompt;

    public:
        explicit Readline(std::string _prompt) :
                prompt(std::move(_prompt)) {}

        std::string operator()();
    };
} // namespace libcmd
