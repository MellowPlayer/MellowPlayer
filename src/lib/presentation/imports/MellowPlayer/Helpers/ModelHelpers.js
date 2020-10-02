.pragma library

function getQtObject(model) {
    return model.qtObject;
}

function getItemsIndex(model) {
    return model.itemsIndex
}

function moveItem(visualModel, item, drag) {
    visualModel.items.move(drag.source.visualIndex, item.visualIndex)
}