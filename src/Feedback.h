#ifndef FEEDBACK
#define FEEDBACK

#include <string>

class Feedback{
    public:

    Feedback();
    Feedback(int r, std::string s);
    ~Feedback();

    void Set_Result(int r);
    int Get_Result();

    void Set_Message(std::string s);
    std::string Get_Message();

    /**
     * @brief Set values in Feedback object
     * 
     * @param i feedback number (e.g. errorcode)
     * @param s feedback message (e.g. errormessage)
     */
    void Set_Feedback(int i, std::string s);

    /**
     * @brief Get Values from feedbackobject  
     * 
     * @param i reference to int for result
     * @param s reference to string for resultmessage
     */
    void Get_Feedback(int &i, std::string &s);

    bool Ok(){
        if (m_result != 0)
        {
            return false;
        }
        
        return true;
    }

    private:

    int m_result = 0;
    std::string m_message = "";

};
#endif // FEEDBACK