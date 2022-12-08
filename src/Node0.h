//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#ifndef __GOBACKNSIM_NODE0_H_
#define __GOBACKNSIM_NODE0_H_

#include <omnetpp.h>
#include <vector>
#include <bitset>
#include "TransmittedMsg_m.h"

using namespace omnetpp;
using namespace std;

/**
 * TODO - Generated class
 */
class Node0 : public cSimpleModule
{
  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);

  public:
    void modificationError(vector<bitset<8>>& data);
    void lossError(double& totalTime);
    void duplicationError(double& totalTime);
    void delayError(double& totalTime);
    void sendWithError();

};

#endif
