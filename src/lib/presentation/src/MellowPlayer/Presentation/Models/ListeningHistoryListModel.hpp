#pragma once

#include "QQmlObjectListModel.hpp"
#include <MellowPlayer/Presentation/ViewModels/ListeningHistory/ListeningHistoryEntryViewModel.hpp>

namespace MellowPlayer::Presentation
{
    using ListeningHistoryListModel = ProgressiveQQmlObjectListModel<ListeningHistoryEntryViewModel>;
}
