import QtQuick 2.12
import QtCharts 2.3
import QtQuick.Controls 2.12
import QtQuick.Dialogs 1.0

Item {
    id: wordsRepetitionsChart
    property var repetitionsCounter: null
    property var createChart: function (repetitions){
        chartView.removeAllSeries()
        chartView.title = "Repetitions"
        // creating new chart series
        var horSeries = chartView.createSeries(ChartView.SeriesTypeBar)

        var categoryAxisX=Qt.createQmlObject('import QtCharts 2.3;BarCategoryAxis {}',chartView);
        categoryAxisX.labelsAngle = -65

        horSeries.axisX = categoryAxisX

        var values = [] // repetitions
        var words = []  // words
        // filling data from RepetitionsCounter
        for (var index in repetitions) {
            words.push(index)
            values.push(repetitions[index])
        }

        // setting data
        categoryAxisX.categories = words
        var mBarSet = horSeries.append("", values)

        chartView.axisY(horSeries).min= 0
        chartView.axisY(horSeries).max= Math.max.apply(null, mBarSet.values)
        // scaling when words less then 15
        chartView.width = Math.min(words.length *150, wordsRepetitionsChart.width)
    }

    states:
        State {
            name: "Running" // when running calculations
            when: repetitionsCounter.running
            PropertyChanges {
                target: chartView
                visible: false
            }
            PropertyChanges {
                target: busyIndicator
                running: true
            }
            PropertyChanges {
                target: stateLabel
                visible: true
            }
            PropertyChanges {
                target: chooseFile
                enabled: false
            }
            PropertyChanges {
                target: progressBar
                visible: repetitionsCounter.countingProgress>0 && repetitionsCounter.countingProgress !== 100
            }
        }




    Connections{
        target: repetitionsCounter

        function onRepetitionsChanged(repetitions){
            createChart(repetitions)
        }
    }

    Column{
        anchors.fill: parent
        bottomPadding: 10
        spacing: 5


        Item{
            width: parent.width
            height: parent.height - chooseFile.height - parent.spacing - parent.bottomPadding

            ChartView {
                objectName: "chartView"
                id:chartView
                width: parent.width
                height: parent.height
                anchors.horizontalCenter: parent.horizontalCenter
                legend.alignment: Qt.AlignBottom
                antialiasing: true
                legend.visible: false
            }
            BusyIndicator{
                objectName: "busyIndicator"
                id: busyIndicator
                anchors.centerIn: parent
                running: false
                Label{// showing current calculation state
                    objectName: "stateLabel"
                    id: stateLabel
                    visible: false
                    text: repetitionsCounter.state
                    anchors.top: parent.bottom
                    anchors.horizontalCenter: parent.horizontalCenter
                    ProgressBar{// showing reading file progress
                        objectName: "progressBar"
                        id: progressBar

                        anchors.top: parent.bottom
                        anchors.horizontalCenter: parent.horizontalCenter
                        height: parent.height
                        width: parent.width
                        visible: false
                        value:repetitionsCounter.countingProgress/100
                    }
                }
            }
        }
        Button{ // show file dialog button
            objectName: "chooseFileButton"
            id: chooseFile
            height: 50
            width: parent.width/2
            anchors.horizontalCenter: parent.horizontalCenter
            text: "Input file..."
            onClicked: fileDialog.visible = true
        }
    }

    FileDialog {
        objectName: "fileDialog"
        id: fileDialog
        title: "Please choose input file"
        folder: shortcuts.home
        visible: false
        onAccepted: {
            repetitionsCounter.setInputFile(fileDialog.fileUrl.toString().slice(8)) // setting input file
            visible = false
            repetitionsCounter.run()// when file choosen start calculations
        }
        onRejected: {

            visible = false
        }

    }
}
