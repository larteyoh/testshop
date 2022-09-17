import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import "." as NeroshopComponents
import "../../fonts/FontAwesome"//import FontAwesome 1.0

Row {//RowLayout {
    id: paginationBar
    spacing: 5
    property alias firstButton: backButton
    property alias secondButton: forwardButton
    property alias numberField: currentPageTextField
    property int currentIndex: 0
    property int count: 0
    property string buttonColor: "#50446f"//NeroshopComponents.Style.neroshopPurpleColor
    property real buttonRadius: 5
    property real radius: buttonRadius
    
    Button {
        id: backButton
        text: qsTr("%1 Previous").arg("\uf359")//qsTr("<")//solid: f104 (<), 
        width: 150
        property bool disabled: (paginationBar.currentIndex == 0)//visible: (paginationBar.currentIndex != 0)
        background: Rectangle {
            color: paginationBar.buttonColor
            radius: paginationBar.buttonRadius
            opacity: (backButton.disabled) ? 0.5 : 1.0
        }        
        contentItem: Text {
            text: backButton.text
            color: "#ffffff"
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }
    }

    TextField {
        id: currentPageTextField
        width: 50
        //readOnly: true
        text: qsTr((parent.currentIndex + 1).toString())
        inputMethodHints: Qt.ImhDigitsOnly // for Android and iOS - typically used for input of languages such as Chinese or Japanese
        validator: RegExpValidator{ regExp: /[0-9]*/ }
        selectByMouse: true
        color: "black" // textColor
        
        background: Rectangle { 
            //color: (NeroshopComponents.Style.darkTheme) ? "transparent": "#101010"//"#101010" = rgb(16, 16, 16)
            //border.color: "#696969" // dim gray//"#ffffff"
            //border.width: (NeroshopComponents.Style.darkTheme) ? 1 : 0
            radius: paginationBar.radius
            //opacity: 0.0
        }        
    }

    Button {
        id: forwardButton
        text: qsTr("Next %1").arg(FontAwesome.arrowAltCircleRight)//qsTr(">")// solid: "\uf105" (>)
        width: 150
        property bool disabled: (paginationBar.currentIndex == (count - 1))
        background: Rectangle {
            color: paginationBar.buttonColor
            radius: paginationBar.buttonRadius
            opacity: (forwardButton.disabled) ? 0.5 : 1.0
        }
        contentItem: Text {
            text: forwardButton.text
            color: "#ffffff"
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter 
            //font.family: FontAwesome.fontFamily
            //font.weight: Font.Bold
        }        
    }
}
