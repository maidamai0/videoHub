import sys


def _dash2cap(name):
    try:
        while True:
            idx = name.index("-")
            pre = name[0:idx]
            suf = name[idx + 2:]
            cap = name[idx + 1:idx + 2].capitalize()
            name = pre + cap + suf
    except ValueError:
        pass
    return name


def _main(argv):
    import json
    if len(argv) != 3:
        print("Usage:")
        msg = "    {} path/to/icons.json path/to/Icons.h"
        msg = msg.format(argv[0])
        print(msg)
        sys.exit(1)
    with open(argv[1], "r") as file:
        icons = json.load(file)
    lines = []
    lines.append("#pragma once")
    lines.append(r'''
/**
 * @file font_awesome.h
 * @author auto generated, DON'T edit!
 * @brief fontawesome values
 *
 * @copyright Copyright (c) 2020
 *
 */''')

    lines.append("")
    lines.append(r'#include "QString"')
    lines.append("")
    lines.append("#pragma warning(push)")
    lines.append("#pragma warning(disable : 4566)")
    lines.append("namespace FontAwesomeIcon {")
    prop = 'const QString {} = "{}";'
    for key in icons:
        name = "fa-" + key
        name = _dash2cap(name)
        code = "\\u" + icons[key]["unicode"]
        line = prop.format(name, code)
        lines.append(line)
    lines.append("}  // namespace FontAwesomeIcon")
    lines.append("#pragma warning(pop)")
    with open(argv[2], "w") as file:
        file.write("\n".join(lines))


if __name__ == '__main__':
    _main(sys.argv)
