#ifndef MYHOSPITALAPPHF_PATIENT_H
#define MYHOSPITALAPPHF_PATIENT_H
#include <string>
#include <vector>
using namespace std;

class Patient {

public:
    Patient();
    Patient(string fName, string mName, string lName, string suffix, vector<string> ailments, string doctor, int treated, int priority);

    //getters
    const string &getFName() const;
    const string &getMName() const;
    const string &getLName() const;
    const string &getSuffix() const;
    const string &getDoctor() const;
    const vector<string> &getAilments() const;
    int getTreated() const;
    int getPriority() const;

    //setters
    void setFName(const string &fName);
    void setMName(const string &mName);
    void setLName(const string &lName);
    void setSuffix(const string &suffix);
    void setAilments(const vector<string> &ailments);
    void setDoctor(const string &doctor);
    void setTreated(int treated);
    void setPriority(int priority);



private:
    string fName;
    string mName;
    string lName;
    string suffix;
    vector<string> ailments;
    string doctor;
    int treated;
    int priority;
};


#endif //MYHOSPITALAPPHF_PATIENT_H
