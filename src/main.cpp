#include "cli/CommandHandler.h"

int main(int argc, char* argv[]){

    CommandHandler handler;
    handler.handle(argc, argv);    
    
    return 0;
}