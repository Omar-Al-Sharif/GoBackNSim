#include "Node0.h"

Define_Module(Node0);
static vector<string> sendWindow;
static vector<string> sendWindowError;



//Input vector<strings>
//Processing vector<bitsets> ->> one string of the previous vector
//Output string -> the previous vector<bitsets> transformed into string


void Node0::modificationError()
{
    int modifiedBit=int(uniform(0,data.size()*8));
    int modifiedChar= modifiedBit / data.size();
    //invert the bit
    data[modifiedChar][modifiedBit]= data[modifiedChar][modifiedBit] ^ 1;
}


void Node0::delayError()
{
    totalTime+=getParentModule()->par("ED").intValue();
    //Not neccessarily int
}


void Node0::duplicationError()
{
    sendWithError(totalTime);
    double DD=getParentModule()->par("DD").doubleValue();
    sendWithError(totalTime+DD);
}



void Node0::sendWithError(double totalTime)
{
//  TransmittedMsg* msg= new TransmittedMsg("");
    //schdeuleAt(simTime()+totalTime, msg);
    sendDelayed(transmittedMsg,totalTime,"node0_out", 1);
}


void Node0::applyErrors()
{
    if (errorFlags[1]=='1') //Loss error will dominate
    {
        return;
    }
    else
    {
        if(errorFlags[0]=='1') //Modification error
        {
            modificationError();
        }
    
        if(errorFlags[3]=='1') //Delay error
        {
            delayError();
        }

        if(errorFlags[2]=='1') //Duplication error
        {
             duplicationError();
             return; 
        }

        sendWithError(totalTime);
    }

}


void Node0::setMsgData()
{
    transmittedMsg->setKind(1);
}

void Node0::initializeParameters()
{

}


void Node0::initialize()
{
    // TODO - Generated method body
    readFile("input0.txt");
    initializeParameters();
    // If message kind=0 -> configuration msg (from coordinator)
    // cast msg to configuration msg and implement the behaviour accordingly
    // If message kind =1 -> transmitted msg (between nodes)
    // Implement GobackN algorithm

    // Input vector of strings (the buffer)
    // Loop on size V[i]-> string -----> transform vector<bitset<8>>
    // Transform to string before sending

    
   applyErrors();
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
