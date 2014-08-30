import QtQuick 2.2
import QtQuick.Controls 1.1
import com.backup 1.0

Rectangle {
    x: 0
    width: 400
    height: 200
    color: "#ffffff"
    transformOrigin: Item.Center
    clip: false
    opacity: 1
    visible: true
    border.color: "#e42424"
    gradient: Gradient {
        GradientStop {
            position: 0.45;
            color: "#ffffff"
        }
        GradientStop {
            position: 0.49;
            color: "#ffffff";
        }
        GradientStop {
            position: 1.00;
            color: "#ffffff";
        }
    }

    Text {
        id: backupFileText
        x: 8
        y: 54
        text: qsTr("backupFile：")
        font.pixelSize: 12
    }

    Text {
        id: logFileText
        x: 8
        y: 89
        width: 42
        height: 13
        text: qsTr("logFile:")
        font.pixelSize: 12
    }

    Button {
        id: saveButton
        x: 93
        y: 155
        text: qsTr("Save")
        onClicked: {

        }
    }

    Button {
        id: cancleButton
        x: 231
        y: 155
        text: qsTr("Cancle")
        onClicked: {
         backup1.saveConfigured();
         Qt.quit();
        }
    }

    Button {
        id: backupFileButton
        x: 343
        y: 49
        width: 49
        height: 21
        text: qsTr("...")
    }

    Button {
        id: logFileButton
        x: 342
        y: 85
        width: 49
        height: 21
        text: qsTr("...")
    }

    TextField {
        id: backupFileComboBox
        x: 86
        y: 50
        width: 251
        height: 20
        placeholderText: qsTr("")
    }

    TextField {
        id: logFileComboBox
        x: 86
        y: 86
        width: 251
        height: 20
        placeholderText: qsTr("")
    }
    Backup{
    id:backup1
    }
}

