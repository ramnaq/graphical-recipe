#include "controller.hpp"

Controller* controller;

int main(int argc, char *argv[]) {
    controller = new Controller();
    controller->run(argc, argv);
    
    delete controller;
    return 0;
}

#include "c_handlers.hpp"
