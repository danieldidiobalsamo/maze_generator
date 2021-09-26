import QtQuick 2.7
import QtQuick.Controls 2.1
import QtQuick.Window 2.0

ApplicationWindow{
	visible: true
	visibility: "FullScreen"	
	color: "lightgray"

	// Maze area
	Item{
		id: mazeArea
		width: parent.width * 0.8
		height: parent.height
	}

	// Settings side bar
	Column{
		width: parent.width * 0.2
		height: parent.height
		anchors.left: mazeArea.right

		spacing: 20

		// Actions

		Text{
			text : "Menu"
			font.pointSize : 20

			anchors.horizontalCenter: parent.horizontalCenter
		}

		Button{
			id: generateButton
			text: "Generate"
			width: parent.width
		}

		Button{
			id: solveButton
			text: "Solve"
			enabled: false
			width: parent.width
		}

		Button{
			id: convertButton
			text: "Convert as PDF"
			enabled: false
			width: parent.width
		}

		Button{
			id: aboutButton
			text: "About"
			enabled: false
			width: parent.width
		}

		Button{
			id: exitButton
			text: "Exit"
			width: parent.width

			onClicked: Qt.quit()
		}

		// Settings

		Text{
			text : "Generation parameters"
			font.pointSize : 20

			anchors.horizontalCenter: parent.horizontalCenter
		}

		Row{
			spacing: 20

			Text{
				text: "Algorithm"
				anchors.verticalCenter: parent.verticalCenter
			}

			ComboBox{
				model: AlgoListModel{}
			}
		}

		Row{
			spacing: 20

			Text{
				text: "Width"
				anchors.verticalCenter: parent.verticalCenter
			}

			SpinBox{
				id: mazeWidthSpinBox
				from : 5.0
			}
		}

		Row{
			spacing: 20

			Text{
				text: "Height"
				anchors.verticalCenter: parent.verticalCenter
			}

			SpinBox{
				from : 5.0
				id: mazeHeightSpinBox
			}
		}

		Row{
			spacing: 20

			Text{
				text: "Starts from "
				anchors.verticalCenter: parent.verticalCenter
			}

			ComboBox{
				model: EntrySideListModel{}
				enabled : false
			}
		}

	}
}