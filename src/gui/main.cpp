#if defined(NEROSHOP_USE_QT) && defined(NEROSHOP_USE_DOKUN_UI) // if both are defined at the same time
#error "You can ONLY define a single GUI library at a time"
#endif

#if defined(NEROSHOP_USE_QT)
#if defined(NEROSHOP_USE_QT_WIDGETS)
#include <QApplication> // For QWidget based Qt applications (QWidget depends on QApplication), but we will be using QML so no need for this
#endif
#include <QGuiApplication> // requires Qt5::Gui
#include <QQmlApplicationEngine> // requires Qt5::Qml
#include <QQmlContext> // QQmlContext *	QQmlApplicationEngine::rootContext()
#include <QQmlComponent> //#include <QQuickView> // requires Qt5::Quick - we're not using QQuickView for now//#include <QQmlComponent>
#include <QStandardPaths>// requires Qt::Core (since Qt 5.0)
#elif defined(NEROSHOP_USE_DOKUN_UI)
#include <dokun_ui.hpp>
using namespace dokun;
#else
// do nothing else
#endif

// neroshop (includes both the core headers and the gui headers)
#include "../neroshop.hpp"
using namespace neroshop;
//lua_State * neroshop::lua_state = luaL_newstate();

using WalletProxy = gui::Wallet;

int main(int argc, char *argv[]) {
    #if defined(NEROSHOP_USE_QT)
    std::cout << "Using Qt version: " << qVersion() << "\n";
    // On Linux desktop, use QApplication since the Qt Labs Platform module uses Qt Widgets as a fallback on platforms that do not have a native platform file dialog implementation available. See https://doc.qt.io/qt-5/qml-qt-labs-platform-filedialog.html#availability
    #if defined(NEROSHOP_USE_QT_WIDGETS)
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);
    #else
    QGuiApplication app(argc, argv);
    #endif
    
    QQmlApplicationEngine engine;
    //--------------------------
    ////////////////////////////////////////////////////////
    // load all icon images
    if(!Icon::load_all()) {
        neroshop::print("Failed to load all icons", 1);
    }
    unsigned char * data = Icon::get<unsigned char *>("upload");
    int size = Icon::get<int>("upload");
    // Print icon information
    std::cout << "Icon info (upload): \n" << "data=" << data << "\n" << "size=" << size << "\n";

    ////////////////////////////////////////////////////////    
    // Configuration file must be loaded right after Qt Application object has been created so that we can get the correct config location
    // open configuration script
    neroshop::open_configuration_file();
    // initialize (sync) database
    //std::string theme = Script::get_string(neroshop::get_lua_state(), "neroshop.theme");
    //if(neroshop::string::lower(theme) == "dark") "NeroshopComponents.Style.darkTheme = true"
    //else if(neroshop::string::lower(theme) == "light") "NeroshopComponents.Style.darkTheme = false"
    // ...
    //QObject * whot = object->findChild<QObject *>("NeroshopComponents.Style");
    //if (whot) qml_theme_str->setProperty("darkTheme", false);
    // Load from qrc file using "qrc:/"
    ////QQmlComponent component(&engine, QUrl::fromLocalFile("../qml/components/Style.qml")); // same as://QQuickView view; view.setSource(QUrl::fromLocalFile("MyItem.qml")); view.show();
    ////assert(component.status() == QQmlComponent::Ready); // #include <assert.h>
    /*if(component.status == QQmlComponent::Error) {//!= QQmlComponent::Ready) {
        throw std::runtime_error("Damn, the component wasn't ready");
    }*/
    ////QObject *object = component.create(); // same as://QObject *object = view.rootObject();
    //QQuickItem *item = qobject_cast<QQuickItem*>(object);
    ////QQmlProperty(object, "darkTheme").write(QVariant(true));////object->setProperty("Style.darkTheme", QVariant(true)); // https://doc.qt.io/qt-5/qobject.html
    ////QObject *style = qvariant_cast<QObject*>(object->property("Style"));
    ////style->setProperty("darkTheme", true);
    //delete object;
    // ...    
    // ...
    ////qRegisterMetaType<std::string>("std::string");
    // custom macros
    engine.rootContext()->setContextProperty("neroshopQtVersion", qVersion());
    engine.rootContext()->setContextProperty("neroshopAppDirPath", QCoreApplication::applicationDirPath());
    engine.rootContext()->setContextProperty("neroshopVersion", NEROSHOP_VERSION);
    engine.rootContext()->setContextProperty("neroshopWalletDir", NEROSHOP_DEFAULT_WALLET_PATH);//QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation));
    engine.rootContext()->setContextProperty("neroshopDataDir", NEROSHOP_DEFAULT_DATABASE_PATH);
    engine.rootContext()->setContextProperty("neroshopConfigDir", NEROSHOP_DEFAULT_CONFIGURATION_PATH);
    engine.rootContext()->setContextProperty("neroshopResourcesDir", QCoreApplication::applicationDirPath() + "/" + NEROSHOP_RESOURCES_FOLDER); // defined in icon.hpp//engine.rootContext()->setContextProperty("neroshopResourcesFolder", NEROSHOP_RESOURCES_FOLDER); // defined in icon.hpp
    // create neroshop directories - datadir and configdir
    if(!std::filesystem::is_directory(NEROSHOP_DEFAULT_WALLET_PATH.toStdString())) {
        neroshop::print(std::string("Creating directory \"") + NEROSHOP_DEFAULT_WALLET_PATH.toStdString() + "\"", 3);
        if(!std::filesystem::create_directories(NEROSHOP_DEFAULT_WALLET_PATH.toStdString())) {
            throw std::runtime_error("Failed to create neroshop datadir");
            return 1;
        }
    }
    // register custom (class) modules
    //qmlRegisterSingletonType(QUrl("qml/style.qml"), "neroshop.Styles", 1, 0, "style");
    ////qmlRegisterType<neroshop::gui::Wallet/*WalletProxy*/>("neroshop.Wallet", 1, 0, "Wallet"); // Usage: import neroshop.Wallet  ...  Wallet { id: wallet }
    // we can also register an instance of a class instead of the class itself
    //gui::Wallet wallet;
    engine.rootContext()->setContextProperty("Wallet", new WalletProxy());//qmlRegisterUncreatableType<WalletProxy>("neroshop.Wallet", 1, 0, "Wallet", "Wallet cannot be instantiated directly.");
    //--------------------------
    // When using qrc.qml to store images, use: QUrl(QStringLiteral("qrc:///main.qml"))
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));//("../main.qml");//("main.qml");//(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty()) {
        return -1;
    }
    return app.exec(); // starts 'event loop'
    #endif
    ////////////////////////////////////////////////////////
    #if defined(NEROSHOP_USE_DOKUN_UI)
    std::cout << "Using dokun-ui\n";
    #ifdef DOKUN_USE_GLFW
    std::cout << "Using GLFW\n";
    #endif
    // First, initialize engine
    if(!dokun::Engine::open()) {
        std::cout << DOKUN_UI_TAG "engine failed to initialize" << std::endl;
        return 1;
    }    
    // Create window
    gui::MainWindow * window = new gui::MainWindow();
    window->create("neroshop", 1280, 720, 0);
    //window->set_vertical_synchronization(true);
    window->show();
    
    while(window->is_open()) {
        window->set_viewport(window->get_client_width(), window->get_client_height()); // causes "X connection to ? broken (explicit kill or server shutdown)." error
        window->clear(32, 32, 32);	        
        
        window->poll_events();
        
        window->update();
    }
    window->destroy();
    Engine::close(); // will call glfwTerminate();
    #endif
    ////////////////////////////////////////////////////////
    return 0;
}
