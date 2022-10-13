#include <Feedback.h>

auto m_logger = spdlog::basic_logger_mt("Telnet client", "logs/TLog.txt");

Feedback::Feedback() {};

Feedback::Feedback(int r, std::string s) {
    m_result = r;
    m_message = s;
};

Feedback::~Feedback() {};


void Log(std::string s) {
    m_logger->info(s);
    m_logger->flush_on(spdlog::level::debug);
}

void Feedback::Set_Result(int r) {
    m_result = r;
}

int Feedback::Get_Result() {
    return m_result;
}

void Feedback::Set_Message(std::string s) {
    m_message = s;
}

std::string Feedback::Get_Message() {
    return m_message;
}

void Feedback::Set_Feedback(int i, std::string s) {
    m_result = i;
    m_message = s;

    Log(s);
}


void Feedback::Get_Feedback(int &i, std::string &s) {
    i = m_result;
    s = m_message;
}
