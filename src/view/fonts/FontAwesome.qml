pragma Singleton

import QtQuick 2.13

Item {
    id:fonts
//    readonly property string regular: internal.fontAwesomeRegular.name
    readonly property string solid: internal.fontAwesomeSolid.name
    readonly property string brands: internal.fontAwesomeBrands.name

    Item {
        id: internal

        readonly property FontLoader fontAwesomeRegular: FontLoader {
            source: "./Font Awesome 5 Free-Regular-400.otf"
        }

        readonly property FontLoader fontAwesomeSolid: FontLoader {
            source: "./Font Awesome 5 Free-Solid-900.otf"
        }

        readonly property FontLoader fontAwesomeBrands: FontLoader {
            source: "./Font Awesome 5 Brands-Regular-400.otf"
        }
    }
}
