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

#include "ControlTower.h"

Define_Module(ControlTower);

void ControlTower::initialize()
{
    this->timeToServe = par("timeToServe");
}

void ControlTower::handleMessage(cMessage *msg)
{
    if(strcmp(msg->getName(),"to control tower")==0)
    {
        //serve a message
        msg->setName("served");
        scheduleAt(simTime()+this->timeToServe,msg);
    }
    else
    {
        send(msg,"portToO$o");
    }
}
