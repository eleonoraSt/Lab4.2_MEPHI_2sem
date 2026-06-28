#include <QApplication>

#include "..\include\Window.h"
#include "..\tests\testAll.h"

#include <iostream>  // для отладки

int main(int argc, char** argv) {
    /*
    QApplication app(argc, argv);
    Window window;
    window.show();
    return app.exec();
    */
    std::cout << "i did start it\n";
    runAllTests();
    return 0;
}
