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

#include "Node0.h"

Define_Module(Node0);
static vector<string> sendWindow;
static vector<string> sendWindowError;



//Input vector<strings>
//Processing vector<bitsets> ->> one string of the previous vector
//Output string -> the previous vector<bitsets> transformed into string


//void sendWithError(vector<bitset<8>>& data)
//{
//
//
//
//
//}

void Node0::modificationError(vector<bitset<8>>& data)
{
    int modifiedBit=int(uniform(0,data.size()*8));
    int modifiedChar= modifiedBit / data.size();
    //invert the bit
    data[modifiedChar][modifiedBit]= data[modifiedChar][modifiedBit] ^ 1;
}


void Node0::delayError(double& totalTime)
{
    totalTime+=getParentModule()->par("ED").intValue();
    //Not neccessarily int
}


//void Node0::duplicationError(TransmittedMsg* msg)
//{
//    schdeuleAt(simTime()+getParentModule()->par("DD").intValue(),msg);
//}


//void sendWithError(double& totalTime, TransmittedMsg* msg)
//{
////    TransmittedMsg* msg= new TransmittedMsg("");
//    schdeuleAt(simTime()+totalTime, msg);
//
//}






void Node0::initialize() {
    // TODO - Generated method body

        // If message kind=0 -> configuration msg (from coordinator)
        // cast msg to configuration msg and implement the behaviour accordingly
        // If message kind =1 -> transmitted msg (between nodes)
        // Implement GobackN algorithm

        //Input vector of strings (the buffer)
        //Loop on size V[i]-> string -----> transform vector<bitset<8>>
        //Transform to string before sending

    // TODO - Generated method body
    readFile("input0.txt");
}



void Node0::handleMessage(cMessage *msg) {

    // TODO - Generated method body
}


void Node0::readFile(string fileName)
{



    ifstream fin;
        string line, errorBits, message;
        fin.open(fileName); //open the file

        if (fin.is_open()) //just a safety causal safety check, Not necessary
        {
            while (fin) {
                //read each line of the file.
                getline(fin, line);

                //This part is to divide the line into 2 parts, one for error bits and one the rest of the message.
                errorBits = line.substr(0, 4);
                message = line.substr(5, line.size() - 5);

                cout << line << endl << errorBits << endl << message << endl << endl;

                //push errorBits and message in their vectors
                sendWindow.push_back(message);
                sendWindowError.push_back(errorBits);
            }
        }

        fin.close(); //close the file

}
