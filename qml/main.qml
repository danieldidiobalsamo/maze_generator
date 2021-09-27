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

		Grid{
			
			anchors.horizontalCenter: parent.horizontalCenter
			
			columns :2
			rows : 4

			columnSpacing : 20
			rowSpacing : 10
			verticalItemAlignment: Grid.AlignVCenter
			
			// Generation algorithm

			Text{text: "Algorithm"}

			ComboBox{
				id: generationAlgoComboBox
				model: AlgoListModel{}
			}


			// Maze width

			Text{
				text: "Width"
			}

			SpinBox{
				id: mazeWidthSpinBox
				from : 5.0
			}

			// Maze height

			Text{
				text: "Height"
			}

			SpinBox{
				from : 5.0
				id: mazeHeightSpinBox
			}

			// Entry side

			Text{text: "Starts from"}

			ComboBox{
				id : entrySideComboBox
				model: EntrySideListModel{}
				enabled : false
			}
		}
	}
}