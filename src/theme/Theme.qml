pragma Singleton

import QtQuick 2.13

Item {
    property BaseTheme current: internal.dark

    Item {
        id: internal
        property BaseTheme light: LightTheme{}
        property BaseTheme dark: DarkTheme{}
    }
}
