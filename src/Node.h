#ifndef __GOBACKNSIM_NODE0_H_
#define __GOBACKNSIM_NODE0_H_

#include <omnetpp.h>

#include <vector>
#include <queue>
#include <bitset>
#include "TransmittedMsg_m.h"
#include "ConfigurationMsg_m.h"

#include <iostream>
#include <string>
#include <fstream>



using namespace std;
using namespace omnetpp;

/**
 * TODO - Generated class
 */
class Node : public cSimpleModule
{
  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);

  public:
    //utility functions for errors
    void modificationError();
    void lossError();
    void duplicationError();
    void delayError();
    void sendWithError(double totalTime);
    void applyErrors();

    //Reading from input text files
    void readFile(string fileName);

    //reset private data members each message
    void initializeParameters();

    //utility functions for Go back N
    void setMsgData();
    void stringToBitset(string string);
    void dataToChar();
    void charToData();
    void framing();
    void deframing();

    int parityByteCalc(vector<bitset<8> > dataToCheck);
    int messageType(cMessage *msg);
    int circularInc(int frameExpected);

    bool isBetween(int number);

  private:
    vector<bitset<8> > data;
    vector<char> charData;

    TransmittedMsg* transmittedMsg;
    double totalTime;
    string errorFlags;

};

#endif
