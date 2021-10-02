import QtQuick 2.7

Item{

	width: 0.02*parent.width
	height: 0.02*parent.height

	Wall{
		vertical: false
		id: north
		anchors.top: parent.top		
	}

	Wall{
		vertical: true
		id: west
		anchors.left: parent.left		
	}

	Wall{
		vertical: false
		id: south
		anchors.bottom: parent.bottom	
	}

	Wall{
		vertical: true
		id: east
		anchors.right: parent.right		
	}
}