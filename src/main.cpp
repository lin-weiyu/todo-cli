#include "cli/CommandHandler.h"

#include <exception>
#include <iostream>

int main(int argc, char* argv[]){
    try{
        CommandHandler handler;
        handler.handle(argc, argv);    
        return 0;
    }
    catch (const std::exception& e){
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
}