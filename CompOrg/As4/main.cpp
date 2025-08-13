#include "emulator.h"


int main(int argc, char* argv[]){
    Emulator* emulator = new Emulator(argv[1]);
    emulator->start();

    delete(emulator);
}