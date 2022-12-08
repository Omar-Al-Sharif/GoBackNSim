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

void Node0::initialize() {
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
