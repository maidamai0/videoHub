import xml.etree.ElementTree as XmlTree
import xml.dom.minidom as XmlDom
import os


def createResource():
    root = XmlTree.Element("RCC")
    content = XmlTree.SubElement(root, "qresource", {"prefix": "/"})
    iterate_directory(".", content)

    f = open("resource.qrc", "w+")
    f.write(pretty_xml(root))
    f.close()


def iterate_directory(dir, content):
    for dirpath, _, filenames in os.walk(dir):
        for filename in filenames:
            if filename.endswith(".qrc") | filename.endswith(".py") | filename.endswith(".json") | filename.endswith(".txt"):
                continue
            file_path = os.path.join(dirpath, filename)
            file_path = file_path.replace("\\", "/")
            file_path = file_path[2:]
            XmlTree.SubElement(content, "file").text = file_path


def pretty_xml(root):
    raw_string = XmlTree.tostring(root, "utf-8")
    # four space
    return XmlDom.parseString(raw_string).toprettyxml(indent="    ")


if __name__ == "__main__":
    createResource()
