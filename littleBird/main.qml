import QtQuick 2.2
import QtQuick.Window 2.1
import QtQuick.Controls 1.1
import QtQuick.Dialogs 1.0
import com.backup 1.0
import QtWinExtras 1.0 as Win
Window {
    id:win
    visible: true
    width: 360
    height: 360
    color: dwm.compositionEnabled ? "transparent" : dwm.realColorizationColor
    //! [color]
    x:100;
    y:200;
    //! [dwm]
    Win.DwmFeatures {
        id: dwm

        topGlassMargin: -1
        leftGlassMargin: -1
        rightGlassMargin: -1
        bottomGlassMargin: -1
    }

    Backup{
        id:backup1
        onConfiguredHadSaved:{
           // applicationWindow1.show();
        }
        onBackupfileCompleted:{

        }
    }

    Text {
        id: text1
        x: 39
        y: 72
        font.pixelSize: 12
    }
    DropArea{
        id:droparea1
        anchors.fill: parent
        onDropped: {
             console.log(drop.urls.toString());
            console.log(targetDir.toString());
            backup1.backupfile(drop.urls,targetDir);  //ListElement
            //applicationWindow1.hide();
        }
    }
    FileDialog{
        id: fileDialog
        title: "Choose a folder"
        selectFolder: true
        onAccepted: folderModel.folder = fileUrl + "/"
    }
    Image {
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.margins: 10
        source: "images/folder.png"
        MouseArea {
            anchors.fill: parent
            anchors.margins: -10
            onClicked: fileDialog.open()
        }
    }
    Component.onCompleted: {
         console.log("QML droparea1\'s C++ type - ", droparea1);
     }
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

//        Button{
//            id:popButton
//            x: 45
//            y: 64
//            width: 100
//            height: 32
//            onClicked:{
//                applicationWindow1.hide();
//                popButton.pressed
//                backup1.openConfiguredWin();
//            }
//        }


