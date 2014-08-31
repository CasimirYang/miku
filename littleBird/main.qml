import QtQuick 2.2
import QtQuick.Window 2.1
import QtQuick.Controls 1.1
import QtQuick.Dialogs 1.0
import com.backup 1.0
import QtWinExtras 1.0 as Win
Window {
    id:window1
    visible: true
    width: 360
    height: 80
    color: dwm.compositionEnabled ? "transparent" : dwm.realColorizationColor
    //! [color]
    x:950;
    y:650;
    //! [dwm]
    Win.DwmFeatures {
        id: dwm

        topGlassMargin: -1
        leftGlassMargin: -1
        rightGlassMargin: -1
        bottomGlassMargin: -1
    }

    Backup{
        id:backupEvent
        onConfiguredHadSaved:{
           // applicationWindow1.show();
        }
        onBackupfileCompleted:{
         statusText.text="Done";
        }
    }

    Text {
        id: processText
        anchors.fill: parent
        font.pixelSize: 12
        visible: true;
    }
    Text {
        id: statusText
        x:window1.width-36
        y:window1.height-15
        visible: true
        text: "Ready"
    }
    DropArea{
        id:droparea1
        z:2
        anchors.fill: parent

        onDropped: {
            console.log(drop.urls.toString());
            console.log(targetDir.toString());
          //   statusText.text="Running";
            backupEvent.backupfile(drop.urls,targetDir);  //ListElement
        }
    }
    FileDialog{
        id: fileDialog
        title: "Choose a folder"
        selectFolder: true
        onAccepted: backupEvent.saveConfigured(fileUrl.toString());

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
//    Component.onCompleted: {
//         console.log("QML droparea1\'s C++ type - ", droparea1);
//     }
//    Rectangle {
//        id:animation1
//        x:100
//        visibleChildren:hide();
//        y:200
//        width: animation.width; height: animation.height
//        AnimatedImage { id: animation; source: "images/animation.gif"}
//        visible:hide();
//    }
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
//                backupEvent.openConfiguredWin();
//            }
//        }


