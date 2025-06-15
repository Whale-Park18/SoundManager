import QtQuick 2.9
import QtQuick.Controls 2.9
import QtQuick.Window 2.2

import "qml"

Window {
    id:window
    width: 960
    height: 720
    visible: true

    title: "SoundManager"

    SideBar{
       width: parent.width/4
       height:parent.height
    
       anchors {
           left:parent.left
           top:parent.top
       }
    }
}
