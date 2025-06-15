import QtQuick 2.3
import QtQuick.Controls 2.9
import QtQuick.Window 2.2

Item {
    Rectangle {
        width:parent.width
        height:parent.height
        color: "red"

        Text {
            id:title

            width:parent.width
            height:parent.height/10

            anchors {
                left:parent.left
                leftMargin:10

                top:parent.top
                topMargin:10
            }

            text: qsTr("안녕하세요")
            font.pixelSize:25
        }

        Rectangle{
            width:parent.width
            height:1

            color:"#cccccc"      

            anchors.top:title.bottom    
        }

        //ListModel {
        //    id:presetList
        //    
        //    width:parent.width
        //    height:parent.height - title.height
        //
        //    anchors {
        //        left:parent.left
        //        bottom:parent.bottom
        //    }
        //
        //    ListElement {
        //        name:"kim"
        //        age:30
        //    }
        //}
    }
}