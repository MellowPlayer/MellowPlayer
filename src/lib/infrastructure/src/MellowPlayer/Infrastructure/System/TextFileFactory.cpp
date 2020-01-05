#include "TextFile.hpp"
#include "TextFileFactory.hpp"

using namespace std;
using namespace MellowPlayer::Infrastructure;

shared_ptr<ITextFile> TextFileFactory::create(const QString& path)
{
    return make_shared<TextFile>(path);
}