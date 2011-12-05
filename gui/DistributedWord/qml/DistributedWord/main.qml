import QtQuick 1.0

Rectangle {
    width: 360
    height: 360

    TextEdit {
        id: text_edit1
        x: 0
        y: 24
        width: 360
        height: 336
        text: qsTr("")
        font.pixelSize: 12
    }

    TextInput {
        id: text_input_ip
        x: 0
        y: 0
        width: 178
        height: 24
        text: qsTr("host")
        font.pixelSize: 12
    }

    TextInput {
        id: text_input_port
        x: 178
        y: 0
        width: 95
        height: 24
        text: qsTr("port")
        font.pixelSize: 12
    }

    MouseArea {
        id: mouse_area1
        x: 273
        y: 0
        width: 87
        height: 24
    }
}
