#include "ProcessFactory.hpp"
#include "Process.hpp"

using namespace std;
using namespace MellowPlayer::Infrastructure;

shared_ptr<IProcess> ProcessFactory::create(const QString& name)
{
    return make_shared<Process>(name);
}
