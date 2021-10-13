import QtQuick 2.7

Rectangle{
	property bool vertical: true

	width : vertical ? 0.05*parent.width  : parent.width
	height : vertical ? parent.height  : 0.05*parent.height

	color : "black"
}