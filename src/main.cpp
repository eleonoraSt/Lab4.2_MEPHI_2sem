#include <QApplication>

#include "..\include\Window.h"
#include "..\tests\testAll.h"

int main(int argc, char** argv) {
    runAllTests();
    QApplication app(argc, argv);
    Window window;
    window.show();
    return app.exec();
}
