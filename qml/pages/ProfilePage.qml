// This page represents the user's profile where all the user's listings, contact information, etc. will be displayed
import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.12 // ColorOverlay

import FontAwesome 1.0

import "../components" as NeroshopComponents

Page {
    id: profilePage
    background: Rectangle {
        color: "transparent"
    }
    property var userModel: Backend.getUser(productModel.seller_id)
    property var productModel: null // <- the product listing that redirected user to this profile page
    property var ratingsModel: Backend.getSellerRatings(productModel.seller_id)
    property var listingsModel: Backend.getInventory(productModel.seller_id)//Backend.getListingsBySearchTerm(productModel.seller_id)

    ColumnLayout {
        anchors.fill: parent
        anchors.bottomMargin: 10
        spacing: 0//10 - topMargin already set for profilePictureRect
        
        // Back button
        Button {
            id: backButton
            Layout.alignment: Qt.AlignTop | Qt.AlignLeft
            Layout.leftMargin: 24; Layout.topMargin: 20
            implicitWidth: contentItem.contentWidth + 40; implicitHeight: contentItem.contentHeight + 20
            text: qsTr("←  Back")//"⇦  Back")
            hoverEnabled: true
            contentItem: Text {
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                text: backButton.text
                color: "#ffffff"
            }
            background: Rectangle {
                radius: 5
                color: backButton.hovered ? NeroshopComponents.Style.neroshopPurpleColor : "#50446f"
            }
            onClicked: {
                pageLoader.setSource("qrc:/qml/pages/ProductPage.qml", {"model": productModel})
            }
            MouseArea {
                anchors.fill: parent
                onPressed: mouse.accepted = false
                cursorShape: Qt.PointingHandCursor
            }
        }        
        
            ColumnLayout {
                Layout.alignment: Qt.AlignTop | Qt.AlignLeft
                Layout.leftMargin: 24; Layout.rightMargin: Layout.leftMargin
                Layout.topMargin: 20 
                Layout.fillWidth: true
                
                Rectangle {
                    id: profileCard
                    Layout.fillWidth: true//width: parent.width//width: 400//
                    Layout.preferredHeight: 300//height: 500//
                    color: (bannerImage.status != Image.Ready) ? "royalblue" : "transparent"
                    radius: 7

                    Image {
                        id: bannerImage
                        source: "file:///" + "/home/sid/Downloads/monero-support-your-local-cypherpunk-1920x1080.png"//"path/to/cover_art.jpg"
                        width: parent.width; height: (parent.height - infoRect.height)//parent.height////anchors.fill: parent
                        fillMode: Image.PreserveAspectCrop
                        mipmap: true
                        // Apply rounded rectangle mask (radius)
                        layer.enabled: true
                        layer.effect: OpacityMask {
                            maskSource: Rectangle {
                                radius: profileCard.radius
                                width: profileCard.width
                                height: profileCard.height - infoRect.height // height is different from profileCard's height so we can't use profileCard directly or it'll cause issues
                            }
                        }
                    }
            
                    // Bottom rect
                    Rectangle {
                        id: infoRect
                        anchors.bottom: parent.bottom
                        anchors.left: parent.left // so that margins will also apply to left and right sides
                        anchors.right: parent.right
                        width: profileCard.width//400
                        height: profileCard.height - 150//profileCard.height / 2
                        color: profilePictureRect.border.color//"#0e0e11"//"transparent"
                        radius: profileCard.radius
                    }
            
                    // Hide radius in between profileCard and infoRect
                    Rectangle {
                        width: infoRect.width - (parent.border.width * 2); height: infoRect.height / 2
                        anchors.left: parent.left; anchors.leftMargin: 0
                        anchors.right: parent.right; anchors.rightMargin: 0
                        anchors.top: infoRect.top; anchors.topMargin: -10
                        color: infoRect.color
                        border.width: parent.border.width; border.color: infoRect.color
                        radius: 0
                    }
            
                    Rectangle {
                        id: profilePictureRect
                        anchors.left: parent.left; anchors.leftMargin: 10//30
                        anchors.top: parent.top; anchors.topMargin: 50
                    
                        width: 128//Layout.preferredWidth: 128
                        height: width//Layout.preferredHeight: Layout.preferredWidth
                        color: infoRect.color// originally no color was set for this so the default was white
                        radius: 5
                        border.width: 7
                        border.color: NeroshopComponents.Style.getColorsFromTheme()[1]//"#343434"//"#808080"//"#0e0e11"//"#000000"//"#ffffff"

                        Image {
                            id: profilePicture
                            source: !userModel.hasOwnProperty("avatar") ? "qrc:/assets/images/mask.png" : "image://avatar?id=%1&image_id=%2".arg(userModel.key).arg(userModel.avatar.name)
                            anchors.centerIn: parent
                            width: parent.width - (profilePictureRect.border.width * 2); height: width
                            fillMode: Image.PreserveAspectFit
                            mipmap: true
                            asynchronous: true
                            // Apply rounded rectangle mask (radius)
                            layer.enabled: true
                            layer.effect: OpacityMask {
                                maskSource: profilePictureRect
                            }
                        }
                    }
                    // user identity column
                    Column {
                        id: nameIdColumn
                        anchors.top: profilePictureRect.bottom
                        anchors.left: profilePictureRect.left
                        anchors.leftMargin: profilePictureRect.border.width
                        // display name
                        Text {
                            text: userModel.hasOwnProperty("display_name") ? userModel.display_name : ""
                            font.pixelSize: 16//32
                            font.bold: true
                            color: (NeroshopComponents.Style.darkTheme) ? "#ffffff" : "#000000"
                        }
                        // user id
                        TextArea {
                            text: userModel.monero_address
                            font.pixelSize: 16
                            //font.bold: true
                            color: (NeroshopComponents.Style.darkTheme) ? "#d0d0d0" : "#464646"
                            readOnly: true
                            wrapMode: Text.Wrap //Text.Wrap moves text to the newline when it reaches the width
                            selectByMouse: true
                            //background: Rectangle { color: "transparent" }
                            padding: 0; leftPadding: 0
                            width: Math.min(infoRect.width, mainWindow.minimumWidth)//200
                        }
                    }
                    // buttonsRow
                    Row {
                        id: buttonsRow
                        layoutDirection: Qt.RightToLeft
                        anchors.right: parent.right; anchors.rightMargin: 24
                        anchors.top: profilePictureRect.top
                        anchors.topMargin: profilePicture.height / 3
                        spacing: 10
                        property real buttonRadius: 6
                        property string buttonColor: infoRect.color//NeroshopComponents.Style.neroshopPurpleColor
                
                        Button {
                            width: contentItem.contentWidth + 30; height: contentItem.contentHeight + 20
                            text: qsTr("Message")
                            background: Rectangle {
                                color: buttonsRow.buttonColor
                                radius: buttonsRow.buttonRadius
                            }
                            contentItem: Text {
                                text: parent.text
                                color: "#ffffff"
                                horizontalAlignment: Text.AlignHCenter
                                verticalAlignment: Text.AlignVCenter
                            }
                            onClicked: {}
                            MouseArea {
                                anchors.fill: parent
                                onPressed: mouse.accepted = false
                                cursorShape: Qt.PointingHandCursor
                            }
                        }
                        
                        Button {
                            width: contentItem.contentWidth + 30; height: contentItem.contentHeight + 20
                            text: qsTr("Rate")
                            background: Rectangle {
                                color: buttonsRow.buttonColor
                                radius: buttonsRow.buttonRadius
                            }
                            contentItem: Text {
                                text: parent.text
                                color: "#ffffff"
                                horizontalAlignment: Text.AlignHCenter
                                verticalAlignment: Text.AlignVCenter
                            }
                            onClicked: {}
                            MouseArea {
                                anchors.fill: parent
                                onPressed: mouse.accepted = false
                                cursorShape: Qt.PointingHandCursor
                            }
                        }
                    }
                    // stats column
                    Column {
                        id: statsRow
                        anchors.top: nameIdColumn.bottom
                        anchors.topMargin: 10
                        anchors.left: profilePictureRect.left
                        anchors.leftMargin: profilePictureRect.border.width
                        property int textIconSpacing: 5
                        property real iconSize: 24
                        width: profileCard.width
                        // stats row
                        Row {
                            id: statsRowActual
                            spacing: 100
                            // reputation
                            Column {
                                spacing: statsRow.textIconSpacing
                                // Deprecated/Replaced with hint (tooltip). Remove this soon!
                                /*Text {
                                    text: "Reputation"
                                    font.pixelSize: 16//32
                                    color: (NeroshopComponents.Style.darkTheme) ? "#ffffff" : "#000000"
                                }*/
                                
                                Row { // place thumbs in this row
                                    spacing: 5
                                Rectangle {
                                    //anchors.verticalCenter: parent.verticalCenter
                                    //anchors.left: parent.left; anchors.leftMargin: width / 2
                                    id: reputationRect
                                    width: 100; height: 32
                                    color: "transparent"
                                    border.color: "#ffffff"
                                    radius: 3
                                    property bool hovered: false
                                    
                                    Row {
                                        anchors.centerIn: parent
                                        spacing: 5
                                        Item {
                                            id: ratingIconRect
                                            anchors.verticalCenter: parent.verticalCenter
                                            width: childrenRect.width
                                            height: childrenRect.height
                                    
                                            Image {
                                                id: ratingIcon
                                                source: "qrc:/assets/images/rating.png"
                                                width: statsRow.iconSize; height: width
                                                mipmap: true
                                            }
                                
                                            ColorOverlay {
                                                anchors.fill: ratingIcon
                                                source: ratingIcon
                                                color: "#ffd700"//"#e6c200"
                                                visible: ratingIcon.visible
                                            }
                                        }
                                    
                                        Text {
                                            anchors.verticalCenter: parent.verticalCenter
                                            text: Backend.getSellerReputation(ratingsModel) + "%"
                                            font.pixelSize: 16
                                            color: (NeroshopComponents.Style.darkTheme) ? "#ffffff" : "#000000"
                                        }
                                    }
                                    
                                    NeroshopComponents.Hint {
                                        visible: parent.hovered
                                        height: contentHeight + 20; width: contentWidth + 20
                                        text: qsTr("Reputation")
                                        pointer.visible: false;// delay: 0
                                    }
                                    
                                    MouseArea { 
                                        anchors.fill: parent
                                        hoverEnabled: true
                                        onEntered: parent.hovered = true
                                        onExited: parent.hovered = false
                                    }
                                }
                                // thumbs up/thumbs down
                        Rectangle {
                            anchors.top: parent.children[0].top
                            width: 50 + thumbsUpCountText.contentWidth; height: reputationRect.height
                            color: "transparent"
                            border.color: "#ffffff"
                            radius: 3
                            Row {
                                anchors.centerIn: parent
                                spacing: 5
                                Item {
                                    id: thumbsUpImageItem
                                            anchors.verticalCenter: parent.verticalCenter
                                            width: childrenRect.width//statsRow.iconSize
                                            height: childrenRect.height
                                            visible: (thumbsUpImage.status === Image.Ready)
                                    Image {
                                        id: thumbsUpImage
                                        source: "qrc:/assets/images/thumbs_up.png"
                                        width: 18; height: width
                                        mipmap: true
                                    }
                            
                                    ColorOverlay {
                                        id: thumbsUpImageOverlayer
                                        anchors.fill: thumbsUpImage
                                        source: thumbsUpImage
                                        color: "green"//"#506a1a"
                                        visible: thumbsUpImage.visible
                                    }
                                }
                                Text {
                                    id: fallbackThumbsUpIcon
                                    anchors.verticalCenter: parent.verticalCenter
                                    text:qsTr(FontAwesome.thumbsUp)
                                    visible: !thumbsUpImageItem.visible
                                    font.bold: true
                                    color: thumbsUpImageOverlayer.color
                                }
                                Text {
                                    id: thumbsUpCountText
                                            anchors.verticalCenter: parent.verticalCenter
                                            text: Backend.getSellerGoodRatings(ratingsModel)
                                            font.pixelSize: 16
                                            color: (NeroshopComponents.Style.darkTheme) ? "#ffffff" : "#000000"
                                        }
                            }
                          } // thumbsUp Rect
                          // thumbs down rect
                          Rectangle {
                            anchors.top: parent.children[0].top
                            width: 50 + thumbsDownCountText.contentWidth; height: reputationRect.height
                            color: "transparent"
                            border.color: "#ffffff"
                            radius: 3
                            Row {
                                anchors.centerIn: parent
                                spacing: 5
                                Item {
                                    id: thumbsDownImageItem
                                            anchors.verticalCenter: parent.verticalCenter
                                            width: childrenRect.width//statsRow.iconSize
                                            height: childrenRect.height
                                            visible: (thumbsDownImage.status === Image.Ready)
                                    Image {
                                        id: thumbsDownImage
                                        source: "qrc:/assets/images/thumbs_down.png"
                                        width: 18 + 2; height: width
                                        mipmap: true
                                    }
                            
                                    ColorOverlay {
                                        id: thumbsDownImageOverlayer
                                        anchors.fill: thumbsDownImage
                                        source: thumbsDownImage
                                        color: "red"//"firebrick"
                                        visible: thumbsDownImage.visible
                                    }
                                }
                                Text {
                                    id: fallbackThumbsDownIcon
                                    anchors.verticalCenter: parent.verticalCenter
                                    text:qsTr(FontAwesome.thumbsDown)
                                    visible: !thumbsDownImageItem.visible
                                    font.bold: true
                                    color: thumbsDownImageOverlayer.color
                                }
                                Text {
                                    id: thumbsDownCountText
                                            anchors.verticalCenter: parent.verticalCenter
                                            text: Backend.getSellerBadRatings(ratingsModel)
                                            font.pixelSize: 16
                                            color: (NeroshopComponents.Style.darkTheme) ? "#ffffff" : "#000000"
                                        }
                            }
                          } // thumbsDown Rect
                                
                                } // row containing both thumbs and reputation
                            } // column for reputation text/reputation stats (can be safely removed)
                            
                        } // end of statsRow
                    } // end of statsCol
            
                    // TODO: show mail letter icon for email, location icon for location, Link icon for website
                } // profileCard (Rectangle)
            } // ColumnLayout
        
            // Tabs
            Rectangle {
                id: tabsRect
                Layout.alignment: Qt.AlignTop | Qt.AlignLeft
                Layout.topMargin: 20; 
                Layout.leftMargin: 24; Layout.rightMargin: Layout.leftMargin
                Layout.fillWidth: true
                Layout.preferredHeight: 50
                color: "royalblue"//NeroshopComponents.Style.neroshopPurpleColor//infoRect.color
                radius: 0//profileCard.radius
                Row {       
                    id: tabButtonRow
                    anchors.bottom: parent.bottom//anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left; anchors.leftMargin: 10
                    spacing: 0////15
                    property real buttonRadius: 5
                    property string buttonCheckedColor: tabLayout.tabItemColor
                    property string buttonUncheckedColor: tabsRect.color
                    Button {
                        id: listingsTabButton
                        width: (tabsRect.width / tabButtonRow.children.length) - tabButtonRow.anchors.leftMargin/*!listingsCountRect.visible ? 100 : 100 + listingsCountText.contentWidth*/; height: 40
                        text: qsTr("Listings")
                        autoExclusive: true
                        checkable: true
                        checked: true // default
                        background: Rectangle {
                            color: parent.checked ? tabButtonRow.buttonCheckedColor : tabButtonRow.buttonUncheckedColor
                            radius: tabButtonRow.buttonRadius
                            
                            // To hide bottom radius
                            Rectangle {
                                anchors.left: parent.left
                                anchors.bottom: parent.bottom
                                width: parent.width
                                height: 5
                                color: parent.color//"pink"// <- for testing
                            }
                        }
                        contentItem: Item {
                            anchors.fill: parent
                            Row { 
                                anchors.centerIn: parent
                                spacing: 10
                                Text {
                                    text: listingsTabButton.text
                                    color: "#ffffff"
                                    anchors.verticalCenter: parent.verticalCenter
                                    font.bold: true
                                }
                            
                                Rectangle {
                                    id: listingsCountRect
                                    anchors.verticalCenter: parent.verticalCenter
                                    width: listingsCountText.contentWidth + 15; height: 20
                                    color: "#101010"//tabLayout.tabItemColor
                                    radius: 3
                                    visible: Number(listingsCountText.text) > 0 && !listingsTabButton.checked
                                    Text {
                                        id: listingsCountText
                                        anchors.horizontalCenter: parent.horizontalCenter
                                        anchors.verticalCenter: parent.verticalCenter
                                        text: (profilePage.listingsModel != null) ? profilePage.listingsModel.length : "0"
                                        color: "#ffffff"
                                        font.pixelSize: 12
                                    }
                                }
                            }
                        }
                        onClicked: {
                            tabLayout.currentIndex = 0
                        }
                    }
                    
                    Button {
                        id: ratingsTabButton
                        width: (tabsRect.width / tabButtonRow.children.length) - tabButtonRow.anchors.leftMargin/*!ratingsCountRect.visible ? 100 : 100 + ratingsCountText.contentWidth*/; height: 40
                        text: qsTr("Ratings")
                        autoExclusive: true
                        checkable: true
                        background: Rectangle {
                            color: parent.checked ? tabButtonRow.buttonCheckedColor : tabButtonRow.buttonUncheckedColor
                            radius: tabButtonRow.buttonRadius
                            
                            // To hide bottom radius
                            Rectangle {
                                anchors.left: parent.left
                                anchors.bottom: parent.bottom
                                width: parent.width
                                height: 5
                                color: parent.color
                            }
                        }
                        contentItem: Item {
                            anchors.fill: parent
                            Row {
                                anchors.centerIn: parent
                                spacing: 10
                                Text {
                                    text: ratingsTabButton.text
                                    color: "#ffffff"
                                    anchors.verticalCenter: parent.verticalCenter
                                    font.bold: true
                                }
                            
                                Rectangle {
                                    id: ratingsCountRect
                                    anchors.verticalCenter: parent.verticalCenter
                                    width: ratingsCountText.contentWidth + 15; height: 20
                                    color: "#101010"//tabLayout.tabItemColor
                                    radius: 3
                                    visible: Number(ratingsCountText.text) > 0 && !ratingsTabButton.checked
                                    Text {
                                        id: ratingsCountText
                                        anchors.horizontalCenter: parent.horizontalCenter
                                        anchors.verticalCenter: parent.verticalCenter
                                        text: Backend.getSellerRatingsCount(ratingsModel)
                                        color: "#ffffff"
                                        font.pixelSize: 12
                                    }
                                }
                            }
                        }
                        onClicked: {
                            tabLayout.currentIndex = 1
                        }
                    }
                }
            }
        // StackLayout
        StackLayout {
            id: tabLayout
            Layout.alignment: Qt.AlignTop | Qt.AlignLeft
            Layout.leftMargin: 24; Layout.rightMargin: Layout.leftMargin
            Layout.preferredWidth: tabsRect.width; Layout.fillHeight: true
            currentIndex: 0
            property string tabItemColor: NeroshopComponents.Style.getColorsFromTheme()[1]//"#101010"//NeroshopComponents.Style.getColorsFromTheme()[0]//"transparent"//""
            Rectangle {
                id: listingsTabItem
                color: tabLayout.tabItemColor
                // StackLayout child Items' Layout.fillWidth and Layout.fillHeight properties default to true
            }
            Rectangle {
                id: ratingsTabItem
                color: tabLayout.tabItemColor
                // StackLayout child Items' Layout.fillWidth and Layout.fillHeight properties default to true
                
                Flickable {
                    anchors.fill: parent
                    contentWidth: parent.width; contentHeight: (ratingsList.delegateHeight * ratingsList.count) + (ratingsList.spacing * (ratingsList.count - 1))
                    clip: true
                    /*ScrollBar.vertical: ScrollBar {
                        policy: ScrollBar.AsNeeded
                    }*/
                ListView {
                    id: ratingsList
                    /*property int margins: 10
                    anchors.left: parent.left; anchors.top: parent.top
                    anchors.margins: margins*/
                    anchors.fill: parent//width: parent.width
                    property real margins: 15
                    anchors.topMargin: ratingsList.margins; anchors.bottomMargin: anchors.topMargin
                    //height: childrenRect.height
                    model: profilePage.ratingsModel
                    spacing: 10
                    property real delegateHeight: 100
                    delegate: Rectangle {
                        anchors.left: parent.left; anchors.right: parent.right
                        anchors.leftMargin: ratingsList.margins; anchors.rightMargin: anchors.leftMargin
                        width: parent.width; height: ratingsList.delegateHeight
                        color: index % 2 === 0 ? "#f0f0f0" : "#e0e0e0"
                        radius: 3
                        // Display review data using Text elements
                        Text {
                            id: commentsLabel
                            anchors.left: parent.left
                            anchors.leftMargin: 10
                            text: "Comments: " + modelData.comments
                        }
                        Text {
                            id: scoreLabel
                            anchors.right: parent.right
                            anchors.rightMargin: 10
                            anchors.top: parent.top
                            text: "Score: " + modelData.score
                        }
                        Text {
                            anchors.right: parent.right
                            anchors.rightMargin: 10
                            anchors.top: scoreLabel.bottom
                            text: "Rater ID: " + modelData.rater_id
                        }
                    }
                }
                } // ScrollView
            }
        }
    } // root ColumnLayout
} // end of Page
