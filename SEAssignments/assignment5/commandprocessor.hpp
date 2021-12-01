#ifndef COMMANDPROCESSOR_H
#define COMMANDPROCESSOR_H

#include <string>
#include <iostream>
#include <map>
#include <functional>

class CommandProcessor
{
public:
    using comandfunction = std::function<void()>;

    CommandProcessor() {}
    void addCommand(const std::string &command, CommandProcessor::comandfunction cf){
        CommandProcessor::commands_.insert({command, cf});
    }
    void executeCommand(const std::string &command){
        auto p = commands_.find(command);
        if(p != end(commands_))
        {
            auto commandfunc = (*p).second;
            commandfunc();
        }
        else
        {
            std::cout << "Command not found!" << std::endl;
        }
    }

private:
    std::map<std::string, CommandProcessor::comandfunction> commands_;

};

#endif // COMMANDPROCESSOR_H
