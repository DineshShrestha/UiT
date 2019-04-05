import QtQuick 2.1
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.1

import "qrc:/qml/components"

import SceneGraphRendering 1.0

Item {
  id: root

  signal toggleHidBindView

  onToggleHidBindView: hid_bind_view.toggle()
signal updateShipStats(string stats)
onUpdateShipStats: shipstatsLabel.text = stats

  Renderer {
    id: renderer

    anchors.fill: parent

    rcpair_name: rc_pair_cb.currentText

    ComboBox {
      id: rc_pair_cb
      anchors.top: parent.top
      anchors.left: parent.left
      anchors.margins: 5

      width: 128

      opacity: 0.7

      model: rc_name_model
      textRole: "display"
    }

    Button {
      text: "?"
      anchors.top: parent.top
      anchors.right: parent.right
      anchors.margins: 5

      width: 50
      opacity: 0.7

      onClicked: hid_bind_view.toggle()
    }
 Rectangle {
 width: childrenRect.width + 6
 height: childrenRect.height + 6
anchors.right: parent.right
anchors.bottom: parent.bottom
color: "black"
Text {
id: shipstatsLabel
// text: "Heisann"
anchors.rightMargin: 6
anchors.topMargin: 6
color: "white"
  }
}

    HidBindingView {
      id: hid_bind_view
      anchors.fill: parent
      anchors.margins: 50
      visible:false

      states: [
        State{
          name: "show"
          PropertyChanges {
            target: hid_bind_view
            visible: true
          }
        }
      ]

      function toggle() {

        if(state === "") state = "show"
        else state = ""

      }
    }

  }

}

