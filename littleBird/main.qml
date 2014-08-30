import QtQuick 2.2
import QtQuick.Window 2.1
import QtQuick.Controls 1.1
import QtQuick.Dialogs 1.0
import com.backup 1.0

Window {
    visible: true
    width: 360
    height: 360

    MouseArea {
        anchors.fill: parent
        onClicked: {
            Qt.quit();
        }
    }

    Text {
        text: qsTr("Hello World")
        anchors.centerIn: parent
    }



    Rectangle {
        id:rectangle1
        x: 0
        y: 8
        width: 300
        height: 122
        color: "black"
        border.color: "#ad6565"
        Button{
            id:popButton
            x: 45
            y: 64
            width: 100
            height: 32
            onClicked:{
                applicationWindow1.hide();
                popButton.pressed
                backup1.openConfiguredWin();
            }
        }
        //   Component.onCompleted: {
        //        console.log("QML droparea1\'s C++ type - ", droparea1);
        //    }

        //    DropArea{
        //        id:droparea1
        //       anchors.fill: parent

        //       onDropped: {
        //           console.log(drop.urls);
        //             backup1.backupfile(drop.urls.toString());  //ListElement
        //            applicationWindow1.hide();
        //            onlogMess11:{
        //               console.log("The backup has been done");
        //                    }
        //       }
        //    }
        //   }



        Backup{
            id:backup1
            onConfiguredHadSaved:{
                applicationWindow1.show();
            }
        }

        CheckBox {
            id: checkBox1
            x: 179
            y: 26
            text: qsTr("Check Box")
        }
//        Button {
//            id: openButton

//            text: qsTr("...")
//            onClicked: fileDialog.open()
//            FileDialog {
//                id: fileDialog

//                folder : musicUrl
//                title: qsTr("Open file")
//              //  nameFilters: [qsTr("MP3 files (*.mp3)"), qsTr("All files (*.*)")]
////                 onAccepted: mediaPlayer.source = fileDialog.fileUrl
//            }
//        }
    }


}
