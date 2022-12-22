#include "Node.h"

Define_Module(Node);
static vector<string> sendWindow;
static vector<string> sendWindowError;
queue<TransmittedMsg*> slidingWindow;
int seqNumber = 0;
int ackNumber = 0;

// Input vector<strings>
// Processing vector<bitsets> ->> one string of the previous vector
// Output string -> the previous vector<bitsets> transformed into string

void Node::modificationError()
{
    int modifiedBit = int(uniform(0, data.size() * 8));
    int modifiedChar = modifiedBit / data.size();
    // invert the bit
    data[modifiedChar][modifiedBit] = data[modifiedChar][modifiedBit] ^ 1;
}

void Node::delayError()
{
    totalTime += getParentModule()->par("ED").intValue();
    // Not neccessarily int

}

void Node::duplicationError()
{
    sendWithError(totalTime);
    double DD = getParentModule()->par("DD").doubleValue();
    sendWithError(totalTime + DD);
}

void Node::sendWithError(double totalTime)
{
    //  TransmittedMsg* msg= new TransmittedMsg("");
    // schdeuleAt(simTime()+totalTime, msg);
    sendDelayed(transmittedMsg, totalTime, "node_out", 0); //not sure
}

void Node::applyErrors()
{
    if (errorFlags[1] == '1') // Loss error will dominate
    {
        return;
    }
    else
    {
        if (errorFlags[0] == '1') // Modification error
        {
            modificationError();
        }

        if (errorFlags[3] == '1') // Delay error
        {
            delayError();
        }

        if (errorFlags[2] == '1') // Duplication error
        {
            duplicationError();
            return;
        }

        sendWithError(totalTime);
    }
}

int Node::circularInc(int frameExpected)
{
    int windowSize = getParentModule()->par("WS").intValue();
    if (frameExpected >= windowSize)
        frameExpected -= windowSize;
    else
        frameExpected++;
    // return (frameExpected + windowSize) % (windowSize + 1);
    return frameExpected;
}

void Node::setMsgData()
{
    transmittedMsg->setKind(1);
}

void Node::initializeParameters()
{
}

int Node::messageType(cMessage *msg)
{
    return msg->getKind();
}

void Node::dataToChar()
{
    for (int i = 0; i < data.size(); i++)
    {
        charData.push_back((char)data[i].to_ulong());
    }
}

void Node::charToData()
{
    data.clear();
    for (int i = 0; i < charData.size(); i++)
    {
        std::bitset<8> character(charData[i]);
        data.push_back(character);
    }
}

void Node::framing()
{
    dataToChar();
    vector<char> temp;
    for (char i : charData)
    {
        if (i == '/' || i == '$')
            temp.push_back('/');
        temp.push_back(i);
    }
    charData = temp;
    // inserting flag at the beginning and the end of the message
    charData.insert(charData.begin(), '$');
    charData.insert(charData.end(), '$');
    charToData();
    string payload(charData.begin(), charData.end());
    transmittedMsg->setPayload(payload.c_str());
}

void Node::deframing()
{
    charData.clear();
    string payload = transmittedMsg->getPayload();
    for (int i = 0; i < payload.length(); i++)
        charData.push_back(payload[i]);
    charData.erase(charData.begin() + charData.size() - 1);
    charData.erase(charData.begin());
    vector<char> temp;
    for (int i = 0; i < charData.size();)
    {
        if (charData[i] == '/') // if ESC char, ignore it and take the next
        {
            temp.push_back(charData[i + 1]);
            i = i + 2;
        }
        else
        {
            temp.push_back(charData[i]);
            i++;
        }
    }
    charData = temp;
}

int Node::parityByteCalc(vector<bitset<8> > dataToCheck)
{
    std::bitset<8> parityByte = dataToCheck[0];
    for (int i = 1; i < dataToCheck.size(); i++)
    {
        parityByte = parityByte ^ dataToCheck[i];
    }
    return parityByte.to_ulong();
}

void Node::stringToBitset(string string)
{
    for (int i = 0; i < string.size(); i++)
    {
        data.push_back(bitset<8>(string[i]));
    }
}

bool Node::isBetween(int number)
{
    int start = slidingWindow.front()->getSeqNumber();
    int end = slidingWindow.back()->getSeqNumber();
    if(((start <= number) && (number < end)) || ((end < start) && (start <= number)) || (number < end) && (end < start))
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Node::initialize()
{
    // TODO - Generated method body
    //readFile("input0.txt");
    //initializeParameters();
}

void Node::handleMessage(cMessage *msg)
{
    // TODO - Generated method body
    // If message kind=0 -> configuration msg (from coordinator)
    // cast msg to configuration msg and implement the behaviour accordingly
    // If message kind =1 -> transmitted msg (between nodes)
    // Implement GobackN algorithm

    // get minimum value between remaining messages i the buffer and sliding window size

    //Sender node received a configuration message from coordinator
    if(messageType(msg) == 0)
    {
        //The intended node reads from the meant file
        if(strcmp(this->getName(), "node0") == 0)
        {
            readFile("input0.txt");
        }
        else if(strcmp(this->getName(), "node1") == 0)
        {
            readFile("input1.txt");
        }
        //creating sliding window
        int windowSize = sendWindow.size();
        int slidingWindowSize = getParentModule()->par("WS").intValue();
        //This line resulted in build error
        //int size = min(sendWindow.size(), getParentModule()->par("WS").intValue());
        int size = min(windowSize, slidingWindowSize);
        TransmittedMsg* tempMsg = new TransmittedMsg;
        for (int i = 0; i < size; i++)
        {
            tempMsg->setPayload((*sendWindow.begin()).c_str());
            tempMsg->setSeqNumber(seqNumber);
            seqNumber = circularInc(seqNumber);
            slidingWindow.push(tempMsg);
            sendWindow.erase(sendWindow.begin());
        }
        for (int i = 0; i < size; i++)
        {
            stringToBitset(slidingWindow.front()->getPayload());
            //slidingWindow.push(slidingWindow.front());
            slidingWindow.pop();
            transmittedMsg->setFrameType(0); // Frame of data
            framing();
            transmittedMsg->setParity(parityByteCalc(data));
            slidingWindow.push(transmittedMsg);
            applyErrors();
        }
    }
    //Transmitted messages are either frames of data intended for the receiver to process
    //or control frames either acks or nack meant for the sender to process
    //then consequently move the sliding window or re-send the window to the receiver
    else
    {
        TransmittedMsg *received = check_and_cast<TransmittedMsg *>(msg);
        //frame received is a frame of data -> receiver process this frame
        if(received->getFrameType() == 0)
        {
            //calculate parity byte and compare it with that of the received message
            //If bytes are equal
            // 1-check if the frame number is the expected on otherwise discard
            // 2-deframe the payload if the frame is the expected one
            // 3-send an ack to the sender applying the loss probability in the ini
            // 4-increase ack number (for cumulative acks)

            //else
            //send a nack frame to the sender
        }
    }

    // Input vector of strings (the buffer)
    // Loop on size V[i]-> string -----> transform vector<bitset<8>>
    // Transform to string before sending
}

void Node::readFile(string fileName)
{

    ifstream fin;
    string line, errorBits, message;
    fin.open(fileName); // open the file

    if (fin.is_open()) // just a safety causal safety check, Not necessary
    {
        while (fin)
        {
            // read each line of the file.
            getline(fin, line);

            // This part is to divide the line into 2 parts, one for error bits and one the rest of the message.
            errorBits = line.substr(0, 4);
            message = line.substr(5, line.size() - 5);

            cout << line << endl
                 << errorBits << endl
                 << message << endl
                 << endl;

            // push errorBits and message in their vectors
            sendWindow.push_back(message);
            sendWindowError.push_back(errorBits);
        }
    }

    fin.close(); // close the file
}
