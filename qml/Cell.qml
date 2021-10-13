import QtQuick 2.7

Item{

	property var walls

	width: 0.02*parent.width
	height: 0.02*parent.height

	Wall{
		id: west
		vertical: true
		anchors.left: parent.left		
		visible: walls[0]
	}
	
	Wall{
		id: south
		vertical: false
		anchors.bottom: parent.bottom	
		visible: walls[1]
	}

	Wall{
		id: east
		vertical: true
		anchors.right: parent.right	
		visible: walls[2]	
	}

	Wall{
		id: north
		vertical: false
		anchors.top: parent.top		
		visible: walls[3]
	}

}