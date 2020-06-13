import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.12

// Import our custom QML component "MyDatabase", defined in main.cpp.
import org.mydb 1.0

Window {
    id: window
    title: Qt.application.name

    width: 320
    height: 180
    visible: true

    MyDatabase {
        id: mydb
    }

    ColumnLayout {
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.margins: 10

        spacing: 10

        RowLayout {
            Layout.fillWidth: true

            TextField {
                id: mInputText
                Layout.fillWidth: true
                focus: true

                placeholderText: "1-10"
                validator: IntValidator { bottom:0; top: 10 }
                Keys.onReleased: {
                    console.log("key release event")
                    if(text.length > 0){
                         mButtonSearch.enabled = true
                    }
                    else {
                        mButtonSearch.enabled = false
                    }
                }
            }

            Button {
                id: mButtonSearch
                text: "SEARCH"
                enabled: false
                onClicked: {
                    console.log("button click event")
                    mOutputText.text = mydb.search(mInputText.text)
                }
            }
        }

        Label {
            id: mOutputText
            text: "..."
            Layout.alignment: Qt.AlignHCenter
        }
    }
}
