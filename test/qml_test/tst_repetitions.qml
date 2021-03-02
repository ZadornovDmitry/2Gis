import QtTest 1.0
import QtQuick 2.5
import QtQuick.Window 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Dialogs 1.2
import QtQml 2.2
import TestController 1.0

import "../../application" as TestApplication

Rectangle {
    id: main_window
    visible: true
    width: Screen.width/2
    height: Screen.height/2
    color: "white"

    TestController{
        id: testController
    }

    TestCase {
        name: "UI Testcase"
        when: windowShown

        function test_1_calc_states() {
            var component = Qt.createComponent("../../application/WordsRepetitionsChart.qml")

            var repetitionsChart = createTemporaryObject(component, main_window, {width: parent.width, height: parent.height, repetitionsCounter: testController})
            verify(repetitionsChart)
            waitForRendering(repetitionsChart)

            var chartView = findChild(repetitionsChart, "chartView")
            verify(chartView)

            compare(chartView.count, 0, "chart must be empty")

            var busyIndicator = findChild(repetitionsChart, "busyIndicator")
            verify(busyIndicator)

            var progressBar = findChild(repetitionsChart, "progressBar")
            verify(progressBar)

            var stateLabel = findChild(repetitionsChart, "stateLabel")
            verify(stateLabel)

            var btn = findChild(repetitionsChart, "chooseFileButton")
            verify(btn)

            compare(busyIndicator.running, false, "busyIndicator state error")
            compare(progressBar.visible, false, " progressBar visibility error")
            compare(stateLabel.visible, false, " stateLabel visibility error")
            compare(btn.enabled, true, " file dialog button have to be enabled")

            testController.setRunning(true)


            compare(repetitionsChart.state, "Running")


            compare(busyIndicator.running, true, "BusyIndicator state error")
            compare(progressBar.visible, false, " ProgressBar visibility error")
            compare(stateLabel.visible, true, " StateLabel visibility error")
            compare(btn.enabled, false, " file dialog button have to be disabled")


            testController.setState("test")
            compare(stateLabel.text, "test", " StateLabel text error")

            testController.setCountingProgress(50)
            compare(progressBar.visible, true, " ProgressBar visibility error")
            compare(progressBar.value, 0.5, " ProgressBar value error")

            testController.reset()
            component.destroy()
        }

        function test_2_chart() {
            var component = Qt.createComponent("../../application/WordsRepetitionsChart.qml")

            var repetitionsChart = createTemporaryObject(component, main_window, {width: parent.width, height: parent.height, repetitionsCounter: testController})
            verify(repetitionsChart)
            waitForRendering(repetitionsChart)
            var map = {"aaaa":2, "bbbb":3}
            repetitionsChart.createChart(map)

            var chartView = findChild(repetitionsChart, "chartView")
            verify(chartView)
            waitForRendering(chartView)
            compare(chartView.count, 1, "Have to be only one series")
            compare(chartView.series(0).at(0).values, [2,3], "Wrong values in set")
            compare(chartView.title, "Repetitions", "Wrong chart title ")
            compare(chartView.series(0).axisX.categories, ['aaaa','bbbb'], "Wrong categories in X axis")
            component.destroy()
        }

        function test_3_file_dialog_button(){

            var component = Qt.createComponent("../../application/WordsRepetitionsChart.qml")

            var repetitionsChart = createTemporaryObject(component, main_window, {width: parent.width, height: parent.height, repetitionsCounter: testController})
            verify(repetitionsChart)
            waitForRendering(repetitionsChart)

            var btn = findChild(repetitionsChart, "chooseFileButton")
            verify(btn)

            var fileDialog = findChild(repetitionsChart, "fileDialog")
            verify(fileDialog)

            compare(fileDialog.visible, false, "filedialog must be hidden")
            compare(btn.text, "Input file...", "Wrong file dialog button text");

            mouseClick(btn)

            compare(fileDialog.visible, true, "file dialog not showed")

            component.destroy()
        }
    }


}
