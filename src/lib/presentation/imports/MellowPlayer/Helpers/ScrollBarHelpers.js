.pragma library

function isActive(scrollBar) {
    return scrollBar.size !== 1 && scrollBar.visible;
}