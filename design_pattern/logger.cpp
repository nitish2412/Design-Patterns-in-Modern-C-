#include<iostream>
#include<mutex>
#include<thread>
#include<map>
#include <fstream>
using namespace std;

// Enum for logging levels
enum class LogLevel {
    INFO,
    DEBUG,
    WARNING,
    ERROR,
    CRITICAL
};

string logLevelToString(LogLevel level) {
    switch (level) {
        case LogLevel::INFO: return "INFO";
        case LogLevel::DEBUG: return "DEBUG";
        case LogLevel::WARNING: return "WARNING";
        case LogLevel::ERROR: return "ERROR";
        case LogLevel::CRITICAL: return "CRITICAL";
        default: return "UNKNOWN";
    }
}

// Abstract base class for logging handlers
class LogHandler {
    public:
        virtual ~LogHandler() {}
        //virtual void log(const string& message) = 0;
        virtual void log(LogLevel level, const string& message) = 0;
};

class ConsoleLogHandler: public LogHandler{

    public:
        void log(LogLevel level, const string& message) override {
        std::cout << "Console Log: [" << logLevelToString(level) << "] " << message << std::endl;
    }
};

class FileLogHandler: public LogHandler{
    private:
        std::ofstream logFile;

    public:
        
        FileLogHandler(const std::string& fileName) {
            logFile.open(fileName, std::ios::out | std::ios::app);
            if (!logFile.is_open()) {
                throw std::runtime_error("Unable to open log file!");
            }
        }
        void log(LogLevel level, const std::string& message) override {
        logFile << "File Log: [" << logLevelToString(level) << "] " << message << std::endl;
    }
};

class Logger{

    private:
        static Logger* instance;
        static mutex mtx;
        LogLevel currentLogLevel;
        LogHandler *handler; 

        Logger():currentLogLevel(LogLevel::INFO),handler(new ConsoleLogHandler()){
            cout<<"Logger initialise\n";
        }
        ~Logger(){
            cout<<"Destructor is called\n";
        }

        string logLevelToString(LogLevel level) {
            static const map<LogLevel, std::string> logLevelMap = {
                {LogLevel::INFO, "INFO"},
                {LogLevel::DEBUG, "DEBUG"},
                {LogLevel::WARNING, "WARNING"},
                {LogLevel::ERROR, "ERROR"},
                {LogLevel::CRITICAL, "CRITICAL"}
            };
            return logLevelMap.at(level);
        }
    public:
        static Logger* getinstance(){
            if(instance==nullptr){
                lock_guard<mutex> lock(mtx);
                if(instance==nullptr){
                    instance = new Logger();
                }
            }
            return instance;
        }
        Logger(Logger &logger) =delete;
        Logger& operator=(Logger &logger) =delete;

        void setLogLevel(LogLevel level){
            currentLogLevel =level;
        }
        /*void log(LogLevel level,string msg){
            if (level >= currentLogLevel) {
                lock_guard<mutex> lock(mtx);
                //cout<<msg<<endl;
                cout<< "[" << logLevelToString(level) << "] " << msg << std::endl;
            }

        }*/
        // Log a message
        /*void log(const std::string& message) {
            std::lock_guard<std::mutex> lock(mtx);
            handler->log(message);
        }*/
        void log(LogLevel level, const std::string& message) {
            if (level >= currentLogLevel) { // Filter messages below the current log level
                std::lock_guard<std::mutex> lock(mtx);
                handler->log(level, message);
            }
        }
        void setLogHandler(LogHandler *new_handler) {
            std::lock_guard<std::mutex> lock(mtx);
            handler = std::move(new_handler);
        }
};

Logger* Logger::instance=nullptr;
mutex Logger::mtx;

//Test the Logger class
void logMessages(const std::string& prefix) {
    Logger* logger = Logger::getinstance();
    /*for (int i = 1; i <= 5; ++i) {
        logger->log(LogLevel::INFO,prefix + " - Message " + std::to_string(i));
    }*/
    //Logger* logger = Logger::getinstance();
    /*logger->log(LogLevel::INFO, prefix + " - INFO level log.");
    logger->log(LogLevel::DEBUG, prefix + " - DEBUG level log.");
    logger->log(LogLevel::WARNING, prefix + " - WARNING level log.");
    logger->log(LogLevel::ERROR, prefix + " - ERROR level log.");
    logger->log(LogLevel::CRITICAL, prefix + " - CRITICAL level log.");
    */
    logger->setLogLevel(LogLevel::INFO);
    logger->setLogHandler(new ConsoleLogHandler());
    logger->log(LogLevel::INFO, prefix + "- This is an INFO message.");
    logger->log(LogLevel::DEBUG, prefix + "- This is a DEBUG message.");
    logger->log(LogLevel::WARNING, prefix + "- This is a WARNING message.");
    logger->log(LogLevel::ERROR, prefix + "- This is an ERROR message.");
    logger->log(LogLevel::CRITICAL, prefix + "- This is a CRITICAL message.");
    logger->setLogHandler(new FileLogHandler("log.txt"));
    logger->log(LogLevel::INFO, prefix + "- This is an INFO message.");
    logger->log(LogLevel::DEBUG, prefix + "- This is a DEBUG message.");
    logger->log(LogLevel::WARNING, prefix + "- This is a WARNING message.");
    logger->log(LogLevel::ERROR, prefix + "- This is an ERROR message.");
    logger->log(LogLevel::CRITICAL, prefix + "- This is a CRITICAL message.");

}

int main(){
    cout<<"Hello World\n";

    Logger* l1=Logger::getinstance();
    Logger* l2=Logger::getinstance();
    l1->setLogLevel(LogLevel::CRITICAL);
    //l1->log(LogLevel::INFO,"My first log message");
    //l2->log(LogLevel::INFO,"My second log message");
    
    thread t1(logMessages, "Thread 1");
    thread t2(logMessages, "Thread 2");
    t1.join();
    t2.join();
    
    return 0;
}