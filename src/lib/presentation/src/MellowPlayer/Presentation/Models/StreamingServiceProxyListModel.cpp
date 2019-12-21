#include <MellowPlayer/Presentation/Models/StreamingServiceProxyListModel.hpp>

using namespace MellowPlayer::Presentation;

StreamingServiceProxyListModel::StreamingServiceProxyListModel(StreamingServiceListModel* sourceListModel) : _sourceListModel(sourceListModel)
{
    setDynamicSortFilter(false);
    setSourceModel(sourceListModel);
    sort(0);
}

bool StreamingServiceProxyListModel::filterAcceptsRow(int sourceRow, const QModelIndex&) const
{
    StreamingServiceViewModel* viewModel = _sourceListModel->at(sourceRow);

    if (viewModel->sortOrder() == -1)
        viewModel->setSortOrder(sourceRow);

    return _sourceListModel->at(sourceRow)->isEnabled();
}

bool MellowPlayer::Presentation::StreamingServiceProxyListModel::lessThan(const QModelIndex& sourceLeft, const QModelIndex& sourceRight) const
{
    StreamingServiceViewModel* left = _sourceListModel->at(sourceLeft.row());
    StreamingServiceViewModel* right = _sourceListModel->at(sourceRight.row());

    return left->sortOrder() < right->sortOrder();
}

void StreamingServiceProxyListModel::update()
{
    invalidate();
}
