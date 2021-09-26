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

	}
}