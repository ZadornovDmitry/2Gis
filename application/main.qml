import QtQuick 2.12
import QtQuick.Window 2.12
import RepetitionsCounter 1.0




Window {
    id: window

    minimumHeight: 500
    minimumWidth: 800

    width: 800
    height: 500

    visible: true
    title: qsTr("Test 2Gis")

    RepetitionsCounter{
        id: repetitionsCounter_
    }
    WordsRepetitionsChart{
        anchors.fill: parent
        repetitionsCounter: repetitionsCounter_
    }
}
