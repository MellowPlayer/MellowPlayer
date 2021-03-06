#include <MellowPlayer/Infrastructure/Logging/SpdLogger.hpp>
#include <MellowPlayer/Infrastructure/Logging/SpdLoggerFactory.hpp>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Infrastructure;
using namespace std;

unique_ptr<ILogger> SpdLoggerFactory::create(const string& name, const LoggerConfig& loggerConfig) const
{
    return make_unique<SpdLogger>(name, loggerConfig);
}
