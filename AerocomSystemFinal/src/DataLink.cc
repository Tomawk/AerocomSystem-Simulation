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

#include "DataLink.h"


Define_Module(DataLink);

void DataLink::initialize()
{
    this->coefficient=getParentModule()->par("coefficient");
    // setDatarate set in bit/s so we need a multiplier to have for example Mbps
    this->datarateMultiplier = getParentModule()->par("datarateMultiplier");
    // generate random initial capacity
    double actualCapacity =  generateDifferentCapacity(0);
    this->oldCapacity = actualCapacity;
    // generate new random target capacity
    this->targetCapacity = generateDifferentCapacity(actualCapacity);

    par("capacity").setDoubleValue(actualCapacity);
    cDatarateChannel *channel = check_and_cast<cDatarateChannel*>(gate("portToO$o")->getTransmissionChannel());
    channel->setDatarate(actualCapacity*this->datarateMultiplier);

    //sending update message to linearly increment capacity
    this->t = tGenerator();
    sendUpdate(this->t/this->coefficient);
}

void DataLink::handleMessage(cMessage *msg)
{
    //if selfmessage change parameter capacity until target (if greater add, if lower subtract)
    if(strcmp(msg->getName(),"update capacity")==0)
    {
        cDatarateChannel *channel = check_and_cast<cDatarateChannel*>(gate("portToO$o")->getTransmissionChannel());
        cancelAndDelete(msg);
        double actualCapacity = par("capacity");
        //changing data rate using capacity
        actualCapacity = actualCapacity + (this->targetCapacity - this->oldCapacity)/this->coefficient;
        par("capacity").setDoubleValue(actualCapacity);
        channel->setDatarate(actualCapacity*this->datarateMultiplier);
        if( abs(this->targetCapacity - actualCapacity) <= 0.000000001)
        {
            this->targetCapacity = generateDifferentCapacity(actualCapacity);
            this->oldCapacity = actualCapacity;
            this->t = tGenerator();
        }
        sendUpdate(this->t/this->coefficient);
        return;
    }

//
    if(strcmp(msg->getName(),"to control tower")==0)
    {
        send(msg, "portToO$o");
    }
}

simtime_t DataLink::tGenerator(){
    //return exponential(0.5,1);
    return lognormal(0.5,0.2,1);
}

//the argument is the capacity from which it must be different
double DataLink::generateDifferentCapacity(double capacity){
    double differentCapacity;
    do
    {
        differentCapacity=uniform(1, 100, 2);
    }
    while(differentCapacity == capacity);
    return differentCapacity;
}


void DataLink::sendUpdate(simtime_t increment)
{
    cMessage *msg = new cMessage("update capacity");

    scheduleAt(simTime()+increment, msg);
}
