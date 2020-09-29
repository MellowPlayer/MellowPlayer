#include <MellowPlayer/Presentation/ViewModels/ClipBoardViewModel.hpp>
#include <QApplication>
#include <QClipboard>

using namespace MellowPlayer::Presentation;

ClipBoardViewModel::ClipBoardViewModel() : QmlSingleton("ClipBoard", this)
{

}

void ClipBoardViewModel::setText(const QString& text)
{
    qApp->clipboard()->setText(text);
    _copiedText = text;
    emit copiedTextChanged();
}

bool ClipBoardViewModel::canPaste() const
{
    return !qApp->clipboard()->text().isEmpty();
}

QString ClipBoardViewModel::copiedText() const
{
    return _copiedText;
}
