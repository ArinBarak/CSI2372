//Lab 8
//Exercice 2

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <sstream>

class Logger{
private:
    std::ofstream logFile;

    std::string currentTime(){
        std::time_t now = std::time(nullptr);
        char buffer[80];
        std::tm* localtm = std::localtime(&now);
        std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", localtm);
        return std::string(buffer);
    }

public:
    void openLogFile(const std::string& filename){
        logFile.open(filename, std::ios_base::app);
        if(!logFile.is_open()){
            throw std::runtime_error("cannot open file.");
        }
    }

    void closelogFile(){
        if (logFile.is_open()){
            logFile.close();
        }
    }

    Logger& operator<<(const std::string& message){
        if (logFile.is_open()){
            logFile << currentTime() <<" "<< message <<std::endl;
        }

        return *this;
    }
};

enum class LogLevel {
    Info,
    Warning,
    Error
};

std::string toString(LogLevel level){
    switch (level)
    {
    case LogLevel::Info:
        return "INFO";
    case LogLevel::Warning:
        return "WARNING";
    case LogLevel::Error:
        return "ERROR";
    default:
        return "UNKNOWN";
    }
}


void main(){
    Logger logger;
    try{
        logger.openLogFile("log.txt");

        logger << "[INFO] Application started.";
        logger << "[WARNING] Low disk space.";
        logger << "[ERROR] Unable to open configuration file.";
    } catch (const std::exception& e){
        std::cerr << "Exception: "<< e.what()<<std::endl;
    }
}
