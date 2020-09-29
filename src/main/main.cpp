#include <MellowPlayer/Application/Program.hpp>

using namespace MellowPlayer::Application;

int main(int argc, char** argv)
{
#ifdef Q_OS_WIN
    // Init resources embedded in static libraries
    Q_INIT_RESOURCE(infrastructure);
    Q_INIT_RESOURCE(presentation);
    Q_INIT_RESOURCE(imports);
#endif

    return Program::main(argc, argv);
}
