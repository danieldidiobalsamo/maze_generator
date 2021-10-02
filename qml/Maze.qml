import QtQuick 2.7

Grid{

	anchors.fill: parent
	property int mazeWidth
	property int mazeHeight

	columns: mazeWidth
	rows: mazeHeight

	columnSpacing: 0
	rowSpacing: 0

	// tmp for testing, next step = using signal / slot 
	Component.onCompleted:{
		backend.generateMaze();
		refresh();
	}

	Repeater{
		model: columns

		Repeater{
			model: rows

			Cell{}
		}

	}

	function refresh(){
		visible: true

		for(let row=0; row < mazeHeight; ++row)
		{
			for(let col=0; col < mazeHeight; ++col)
			{
				let walls = backend.getCell(row, col);
				console.log(walls)

				// next step = modify visual maze cells

			}

		}

	}
}