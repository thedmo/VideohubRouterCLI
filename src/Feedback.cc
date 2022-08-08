#include <Feedback.h>

Feedback::Feedback(){};
Feedback::~Feedback(){};

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
}


void Feedback::Get_Feedback(int &i, std::string &s){
    i = m_result;
    s = m_message;
}
