// This page displays the product page upon clicking on a product in the catalog view
import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import FontAwesome 1.0
import neroshop.CurrencyExchangeRates 1.0

import "../components" as NeroshopComponents

Page {
    id: productPage
    background: Rectangle {
        color: "transparent"
    }
    property var model: null//property string productId: ""
    function openSellerPage() {
        pageLoader.setSource("qrc:/qml/pages/ProfilePage.qml");//, {"model": [""]})
    }
    
    Flickable {
        anchors.fill: parent
        anchors.margins: 20
        contentWidth: width; contentHeight: productPageLayout.childrenRect.height
        clip: true
        ScrollBar.vertical: ScrollBar {
            policy: ScrollBar.AsNeeded
        }
        
        RowLayout {
            id: productPageLayout
            width: parent.width//anchors.fill: parent//height: parent.height//width: parent.width // Layout height should be set automatically
            spacing: 0
            Flow {
                id: productPageFlow
                Layout.fillWidth: true//Layout.preferredWidth: parent.parent.width//Layout.fillWidth: true; Layout.fillHeight: true
                Layout.maximumWidth: parent.parent.width
                spacing: 30
                // Column 1
                Column {
                    id: productImageColumn
                    //width: parent.width / 2//Layout.fillWidth: true//; Layout.fillHeight: true
                    spacing: 10
                    
                    Rectangle {
                        id: productImageRect
                        width: 625/*parent.parent.width*/; height: 524//600
                        color: "transparent"; border.color: "#ffffff"
                        // Product image
                        Image {
                            id: productImage
                            source: "file:///" + productPage.model.product_image_file////"image://catalog?id=%1".arg(productPage.model.product_id)
                            anchors.centerIn: parent
                            width: productImage.minImageSize; height: width
                            fillMode: Image.PreserveAspectFit
                            mipmap: true
                            asynchronous: true
                            property real minImageSize: 512//576
                            onStatusChanged: {
                                if(status == Image.Ready) {
                                    console.log("original size", sourceSize)
                                    width = (sourceSize.width < productImage.minImageSize) ? sourceSize.width : productImage.minImageSize
                                    height = (sourceSize.height < productImage.minImageSize) ? sourceSize.height : productImage.minImageSize
                                }
                            }
                        }
                    }
                    // Product gallery (up to 6 images maximum)
                    Row {////ListView {
                        id: productImageGallery
                        width: productImageRect.width; height: 100
                        ////orientation: ListView.Horizontal
                        spacing: 5
                        Repeater {
                            id: productImageRepeater
                            model: Backend.getProductImages(productPage.model.product_id)//6
                            delegate: Rectangle {
                                color: "transparent"; border.color: "#ffffff"
                                width: 100/*Math.min((parent.width / productImageRepeater.count) - (productImageGallery.spacing * (productImageRepeater.count - 1)), 100)*/; height: parent.height
                                Image {
                                    source: "file:///" + modelData.name////"image://catalog?id=%1&image_id=%2".arg(productPage.model.product_id).arg(modelData.image_id)
                                    anchors.fill: parent
                                    fillMode: Image.PreserveAspectFit
                                    mipmap: true
                                    asynchronous: true
                                    MouseArea {
                                        anchors.fill: parent
                                        acceptedButtons: Qt.LeftButton
                                        onClicked: { 
                                            productImage.source = parent.source
                                        }
                                    }
                                }
                                MouseArea {
                                    anchors.fill: parent
                                    onPressed: mouse.accepted = false
                                    cursorShape: Qt.PointingHandCursor
                                    hoverEnabled: true
                                    onEntered: parent.border.color = "#4169e1"
                                    onExited: parent.border.color = "#ffffff"
                                }
                            }
                        } // Repeater
                    }
                }
                // Column 2
                Column {
                    //Layout.fillWidth: true
                    //Layout.fillHeight: true
                    // Product details
                    /*width: parent.width*/// Layout should automatically set the height based on its children's height
                    spacing: 5
                    // Product name
                    TextArea {
                        id: productNameText
                        text: qsTr(productPage.model.product_name)
                        color: (NeroshopComponents.Style.darkTheme) ? "#ffffff" : "#000000"
                        readOnly: true
                        wrapMode: Text.Wrap //Text.Wrap moves text to the newline when it reaches the width
                        selectByMouse: true
                        font.bold: true
                        font.pointSize: 20
                        background: Rectangle { color: "transparent" }
                        padding: 0; leftPadding: 0
                    }
                    // Prices            
                    Column {
                        spacing: 5//10
                        Row {
                            spacing: 5
                                
                            Image {
                                id: moneroSymbol
                                source: "qrc:/images/monero_symbol_white.png"
                                visible: priceMonero.visible
                                width: 24; height: 24
                                fillMode:Image.PreserveAspectFit
                                mipmap: true
                            }
                                
                            TextField { 
                                id: priceMonero
                                text: qsTr("%1").arg(CurrencyExchangeRates.convertToXmr(Number(productPage.model.price), productPage.model.currency).toFixed(Backend.getCurrencyDecimals("XMR")))//.arg("XMR") // TODO: allow users to specificy their preferred number of digits
                                color: (NeroshopComponents.Style.darkTheme) ? "#ffffff" : "#000000"
                                anchors.verticalCenter: moneroSymbol.verticalCenter
                                font.bold: true
                                font.pointSize: 16
                                readOnly: true
                                selectByMouse: true
                                background: Rectangle {
                                    color: "transparent"
                                }
                                padding: 0; leftPadding: 0 // With the padding at zero, we can freely set the Row spacing
                            }
                        }
                        
                        TextField {
                            id: priceFiat
                            anchors.left: parent.left
                            text: qsTr("%1%2 %3").arg(Backend.getCurrencySign(productPage.model.currency)).arg(Number(productPage.model.price).toFixed(Backend.getCurrencyDecimals(productPage.model.currency))).arg(productPage.model.currency)
                            color: (NeroshopComponents.Style.darkTheme) ? "#ffffff" : "#000000"
                            font.bold: !priceMonero.visible ? true : false
                            font.pointSize: !priceMonero.visible ? 16 : Qt.application.font.pointSize
                            readOnly: true
                            selectByMouse: true
                            background: Rectangle {
                                color: "transparent"
                            }
                            padding: 0; leftPadding: 0 // With the padding at zero, we can freely set the Row spacing
                        } 
                    }
                    // Product ratings stars and ratings count
                    Row { 
                        id: starsRow
                        //spacing: 5
                        property real avg_stars: Backend.getProductAverageStars(productPage.model.product_id)
                        property int star_ratings_count: Backend.getProductStarCount(productPage.model.product_id)
                        //Component.onCompleted: console.log("avg stars", starsRow.avg_stars)
                        Repeater {
                            model: 5
                            delegate: Text {
                                text: (starsRow.star_ratings_count <= 0) ? qsTr(FontAwesome.star) : ((starsRow.avg_stars > index && starsRow.avg_stars < (index + 1)) ? qsTr(FontAwesome.starHalfStroke) : qsTr(FontAwesome.star)) // not sure?
                                color: ((index + 1) > Math.ceil(starsRow.avg_stars) || (starsRow.star_ratings_count <= 0)) ? "#777" : "#ffb344" // good!
                                font.bold: true
                                font.family: FontAwesome.fontFamily                            
                            }       
                        }
                        Text {
                            text: qsTr(" %1"/* ratings"*/).arg((starsRow.star_ratings_count <= 0) ? "No reviews yet" : "(" + starsRow.star_ratings_count + " reviews)")
                            color: (NeroshopComponents.Style.darkTheme) ? "#ffffff" : "#000000"
                        }
                    }
                    // Stock status
                    Text {
                        id: stockStatusText
                        property bool status: (stock_available > 0)
                        property int stock_available: Backend.getStockAvailable(productPage.model.product_id)
                        text: qsTr(status ? "In stock" : "Out of stock")
                        color: status ? "#31652c" : "#d61f1f"
                        font.bold: true
                    }
                    // Sold by
                    Row {
                        spacing: 5
                        //width: 200//;height: 30
                        //clip: true
                        Text {
                            text: qsTr("Sold by")
                            color: (NeroshopComponents.Style.darkTheme) ? "#ffffff" : "#000000"
                            font.bold: true
                        }
                        // Seller name
                        TextArea {
                            id: sellerNameText
                            property string displayName: Backend.getDisplayNameById(productPage.model.seller_id)
                            text: qsTr(displayName.length > 0 ? displayName : productPage.model.seller_id)
                            color: "#4169e1"//royalblue
                            font.bold: true
                            //font.underline: true
                            readOnly: true
                            wrapMode: Text.Wrap //Text.Wrap moves text to the newline when it reaches the width
                            selectByMouse: true
                            background: Rectangle { color: "transparent" }
                            padding: 0; leftPadding: 0
                            MouseArea {
                                anchors.fill: parent
                                hoverEnabled: true
                                onClicked: productPage.openSellerPage()
                                onEntered: parent.color = "blue"
                                onExited: parent.color = "#4169e1"
                            }
                        }
                    }
                    // Condition
                    Row {
                        spacing: 5
                        Text {
                            text: qsTr("Condition")
                            color: (NeroshopComponents.Style.darkTheme) ? "#ffffff" : "#000000"
                            font.bold: true
                        }
                        Text {
                            id: conditionText
                            text: qsTr(productPage.model.condition)
                            color: (NeroshopComponents.Style.darkTheme) ? "#ffffff" : "#000000"
                            //font.bold: true
                        }
                    }
                    // Description
                    Column {
                        spacing: 5
                        Text {
                            text: qsTr("Description")
                            color: (NeroshopComponents.Style.darkTheme) ? "#ffffff" : "#000000"
                            font.bold: true
                        }            
                        ScrollView {
                            width: 500/*productDescText.contentWidth*/; height: productDescText.contentHeight//250
                            TextArea {
                                id: productDescText
                                text: qsTr(productPage.model.product_description)
                                color: (NeroshopComponents.Style.darkTheme) ? "#ffffff" : "#000000"
                                readOnly: true
                                wrapMode: Text.Wrap //Text.Wrap moves text to the newline when it reaches the width
                                selectByMouse: true
                                background: Rectangle { color: "transparent" }//(NeroshopComponents.Style.darkTheme) ? (NeroshopComponents.Style.themeName == "PurpleDust" ? "#17171c" : "#1d1d1d") : "#c9c9cd" }
                                padding: 0; leftPadding: 0
                            }
                        }
                    }
                    // Controls
                    Column {
                        Layout.fillHeight: true
                        spacing: 10
                        // Quantity box
                        SpinBox {
                            id: quantityBox
                            anchors.horizontalCenter: parent.horizontalCenter//Layout.alignment: Qt.AlignHCenter//anchors.horizontalCenter: parent.horizontalCenter
                            from: 1; to: Math.max(1, stockStatusText.stock_available)//10////(Backend.getCartMaximumQuantity() - User.cartQuantity)
                        }
                        // Buttons row?
                        Column {
                            spacing: 5
                            // Add to cart button
                            Button {
                                id: cartButton
                                anchors.horizontalCenter: parent.horizontalCenter//Layout.alignment: Qt.AlignHCenter
                                width: 500; height: 50//Layout.preferredWidth: 500; Layout.preferredHeight: 50
                                hoverEnabled: true
                                text: qsTr("Add to cart")
                                property string color: "#ff6600"
                                property string lightColor: "#ff7e29"
                                property string darkColor: "#d65600"
                                background: Rectangle {
                                    color: parent.hovered ? cartButton.lightColor : cartButton.color
                                    border.color: cartButton.darkColor
                                    border.width: 2
                                    radius: 3
                                }
                                contentItem: Text {
                                    text: parent.text
                                    color: "#ffffff"
                                    horizontalAlignment: Text.AlignHCenter
                                    verticalAlignment: Text.AlignVCenter
                                }
                                onClicked: {
                                    User.addToCart(productPage.model.product_id, quantityBox.value)
                                }
                                MouseArea {
                                    anchors.fill: parent
                                    onPressed: mouse.accepted = false
                                    cursorShape: Qt.PointingHandCursor
                                }
                            }
                            // Add to favorites button
                            Button {
                                id: favoritesButton
                                anchors.horizontalCenter: parent.horizontalCenter//Layout.alignment: Qt.AlignHCenter
                                width: 500; height: 50//Layout.preferredWidth: 500; Layout.preferredHeight: 50
                                hoverEnabled: true
                                text: qsTr("Add to favorites")
                                property string color: "#d62929"
                                property string lightColor: "#dd4b4b"
                                property string darkColor: "#b42222"
                                background: Rectangle {
                                    color: parent.hovered ? favoritesButton.lightColor : favoritesButton.color////parent.hovered ? (parent.down ? favoritesButton.darkColor : favoritesButton.lightColor) : favoritesButton.color
                                    border.color: favoritesButton.darkColor//parent.hovered ? favoritesButton.color : favoritesButton.lightColor
                                    border.width: 2
                                    radius: 3
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
                            // Message seller button
                            Button {
                                id: chatSellerButton
                                anchors.horizontalCenter: parent.horizontalCenter//Layout.alignment: Qt.AlignHCenter
                                width: 500; height: 50//Layout.preferredWidth: 500; Layout.preferredHeight: 50
                                hoverEnabled: true
                                text: qsTr("Chat")
                                property string color: "#53469f"
                                property string lightColor: "#6c60b9"
                                property string darkColor: "#483d8b"
                                background: Rectangle {
                                    color: parent.hovered ? (parent.down ? chatSellerButton.darkColor : chatSellerButton.lightColor) : chatSellerButton.color
                                    border.color: chatSellerButton.darkColor
                                    border.width: 2
                                    radius: 3
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
                    }
                }
            }
        }
    }
}
