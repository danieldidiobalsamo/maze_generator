import QtQuick 2.7

Item{

	width: 0.02*parent.width
	height: 0.02*parent.height

	Wall{
		id: north
		vertical: false
		anchors.top: parent.top		
	}

	Wall{
		id: west
		vertical: true
		anchors.left: parent.left		
	}

	Wall{
		id: south
		vertical: false
		anchors.bottom: parent.bottom	
	}

	Wall{
		id: east
		vertical: true
		anchors.right: parent.right		
	}
}