#include "TextFile.hpp"
#include <QFile>
#include <QTextStream>
#include <QtCore/QFileInfo>

using namespace MellowPlayer::Infrastructure;

TextFile::TextFile(const QString& path) : _path(path)
{

}

bool TextFile::exists() const
{
    return QFileInfo(_path).exists();
}

QString TextFile::read() const
{
    QFile file(_path);
    if (file.open(QFile::ReadOnly | QFile::Text))
    {
        QTextStream in(&file);
        return in.readAll();
    }
    return "";
}

void TextFile::write(const QString& content)
{
    QFile file(_path);
    if (file.open(QFile::WriteOnly | QFile::Text))
    {
        QTextStream in(&file);
        in << content;
        file.close();
    }
}
