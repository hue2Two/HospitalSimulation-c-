#include "Patient.h"

Patient::Patient() : fName(""), mName(""), lName(""), suffix(""), doctor(""), treated(0), priority(0) {}

Patient::Patient(string fName, string mName, string lName, string suffix, vector<string> ailments, string doctor, int treated, int priority)
        : fName(fName), mName(mName), lName(lName), suffix(suffix), ailments(ailments), doctor(doctor), treated(treated), priority(priority) {}

const string &Patient::getFName() const {
    return fName;
}

const string &Patient::getMName() const {
    return mName;
}

const string &Patient::getLName() const {
    return lName;
}

const string &Patient::getSuffix() const {
    return suffix;
}

const string &Patient::getDoctor() const {
    return doctor;
}

const vector<string> &Patient::getAilments() const {
    return ailments;
}

int Patient::getTreated() const {
    return treated;
}

int Patient::getPriority() const {
    return priority;
}

void Patient::setFName(const string &fName) {
    this->fName = fName;
}

void Patient::setMName(const string &mName) {
    this->mName = mName;
}

void Patient::setLName(const string &lName) {
    this->lName = lName;
}

void Patient::setSuffix(const string &suffix) {
    this->suffix = suffix;
}

void Patient::setAilments(const vector<string> &ailments) {
    this->ailments = ailments;
}

void Patient::setDoctor(const string &doctor) {
    this->doctor = doctor;
}

void Patient::setTreated(int treated) {
    this->treated = treated;
}

void Patient::setPriority(int priority) {
    this->priority = priority;
}
