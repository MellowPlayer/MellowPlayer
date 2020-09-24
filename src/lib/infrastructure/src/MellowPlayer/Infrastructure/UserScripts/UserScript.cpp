#include <MellowPlayer/Infrastructure/Helpers/FileHelper.hpp>
#include <MellowPlayer/Infrastructure/UserScripts/UserScript.hpp>
#include <QDebug>
#include <QDir>
#include <QUuid>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Infrastructure;

bool UserScriptDirectory::create() const
{
    QString path = FileHelper::userScriptsDirectory();
    QDir qDir(path);
    if (!qDir.exists())
        return qDir.mkpath(path);
    return true;
}

QString UserScriptDirectory::generateFileName() const
{
    return path() + QDir::separator() + QUuid::createUuid().toString() + ".js";
}

QString UserScriptDirectory::path() const
{
    return FileHelper::userScriptsDirectory();
}

bool UserScript::import(const QString& sourcePath)
{
    QString sourceUrl = sourcePath;
    sourceUrl = sourceUrl.replace("file://", "");
    UserScriptDirectory directory;
    bool exists = QFile::exists(sourceUrl);
    if (directory.create() && exists)
    {
        QString destinationPath = directory.generateFileName();
        _path = destinationPath;
        qInfo() << "importing" << sourceUrl << " to " << destinationPath;
        if (QFile::copy(sourceUrl, destinationPath))
            return load(destinationPath);
        return true;
    }
    return false;
}

bool UserScript::load(const QString& path)
{
    qDebug() << "loading" << path;
    _path = path;

    QFile file(path);
    if (file.open(QFile::ReadOnly))
    {
        auto content = file.readAll();
        _code = QString::fromUtf8(content);
        return true;
    }
    return false;
}

void UserScript::removeFile()
{
    QFile::remove(_path);
}
