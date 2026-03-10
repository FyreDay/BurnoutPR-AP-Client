#pragma once
#include <thread>
#include <string>
#include <mutex>
#include <queue>
#include <iostream>

class Logger {
public:
	static Logger& Get() {
		static Logger instance;
		return instance;
	}
    void Start() {
        std::cout << "Start Logger!";
        std::thread([this]() {
            while (true) {
                std::string message;
                {
                    std::unique_lock<std::mutex> lock(m_Mutex);
                    m_CV.wait(lock, [this] { return !m_Queue.empty(); });

                    message = m_Queue.front();
                    m_Queue.pop();
                }
                std::cout << message << std::endl;
            }
            }).detach();
    }


    void Log(const std::string& msg) {
        {
            std::lock_guard<std::mutex> lock(m_Mutex);
            m_Queue.push(msg);
        }
        m_CV.notify_one(); 
    }

private:
    Logger() {} // Private constructor
    std::queue<std::string> m_Queue;
    std::mutex m_Mutex;
    std::condition_variable m_CV;
};
