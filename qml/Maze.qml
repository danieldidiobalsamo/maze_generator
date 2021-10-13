import QtQuick 2.7

Grid{

	id: maze

	anchors.fill: parent
	property int mazeWidth
	property int mazeHeight

	columns: mazeWidth
	rows: mazeHeight

	columnSpacing: 0
	rowSpacing: 0

	Repeater{
		model: rows * columns

		Cell{
			walls: backend.getCell(index / mazeWidth, index % mazeWidth)
		}
	}
}