import QtQuick 2.7
import QtQuick.Controls 2.1
import QtQuick.Window 2.0

ApplicationWindow{
	visibility: "FullScreen"	
	color: "lightgray"

	Item{
		id: mazeArea
		width: parent.width * 0.8
		height: parent.height
	}

	Column{
		width: parent.width * 0.2
		height: parent.height
		anchors.left: mazeArea.right
	}
}