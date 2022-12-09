#ifndef __GOBACKNSIM_NODE0_H_
#define __GOBACKNSIM_NODE0_H_

#include <omnetpp.h>

#include <vector>
#include <bitset>
#include "TransmittedMsg_m.h"

#include <iostream>
#include <string>
#include <fstream>



using namespace std;
using namespace omnetpp;

/**
 * TODO - Generated class
 */
class Node0 : public cSimpleModule
{
  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);

  public:

    void modificationError();
    void lossError();
    void duplicationError();
    void delayError();
    void sendWithError(double totalTime);
    void applyErrors();
    void initializeParameters();
    void setMsgData();

    void readFile(string fileName);

  private:
    vector<bitset<8>> data;
    TransmittedMsg* transmittedMsg;
    double totalTime;
    string errorFlags;











};

#endif
