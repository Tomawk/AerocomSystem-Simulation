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

#include "Controller.h"
#include "AerocomMessage_m.h"


Define_Module(Controller);


void Controller::initialize()
{
    //retrieving constants
    this->S = getParentModule()->par("S");
    this->X = getParentModule()->par("X");
    this->timeToServe = getParentModule()->par("timeToServe");
    this->lock = false;
    this->capacityI = -1;
    this->capacityI1 = -1;
    this->capacityI2 = -1;
    this->dlSelectionProcessing = false;
    this->servingDL = 0;
    this->queue = new cQueue("msgQ");
    this->recordsIN.setName("Aircraft In");
    this->recordsENDQ.setName("Aircraft EndQ");
    this->recordsSERV.setName("Aircraft Serv");
    createNewMessage( kGenerator(), "to control tower");


}


void Controller::handleMessage(cMessage *msg)
{
    //if received a message of end dl selection
    if(strcmp(msg->getName(),"dl selection end")==0){
        dlSelection(this->capacityI, this->servingDL);
        this->dlSelectionProcessing = false;
        send(this->messageToServe, "portToDL$o", this->servingDL);
        this->recordsSERV.record(SimTime().dbl());
        this->lock = true;
        cMessage *msg2 = new cMessage("unlock");
        msg2->setSchedulingPriority(1);
        scheduleAt(simTime()+this->timeToServe,msg2);
        cancelAndDelete(msg);
        return;
    }
    if(strcmp(msg->getName(),"to control tower")==0)
    {
        createNewMessage(kGenerator(),"to control tower");
        cChannel *channel = getParentModule()->gate("portToO$o",this->servingDL)->getTransmissionChannel();
        // control if the system is processing a dl selection or queue is not empty or channel busy
        this->recordsIN.record(SimTime().dbl());
        if(this->dlSelectionProcessing || !this->queue->isEmpty() || channel->isBusy() || this->lock)
        {
            this->queue->insert(msg);
            if(channel->isBusy())
            {
                cMessage *msg2 = new cMessage("serve next message");
                scheduleAt(channel->getTransmissionFinishTime(), msg2);
            }
        }
        else
        {
            //updating capacities last transmissions
            this->queue->insert(msg);
            this->messageToServe =check_and_cast<AerocomMessage*>(this->queue->pop());
            this->recordsENDQ.record(SimTime().dbl());
            controllerSend(this->capacityI, this->capacityI1, this->capacityI2, this->servingDL, this->X,
                    this->S, this->dlSelectionProcessing, this->messageToServe, this->timeToServe, this->lock);
        }
    }

    if(strcmp(msg->getName(),"serve next message")==0)
    {
        if(this->queue->isEmpty())
        {
            cancelAndDelete(msg);
            return;
        }
        // control if last transmission ended
        cChannel *channel = getParentModule()->gate("portToO$o",this->servingDL)->getTransmissionChannel();
        if(channel->isBusy() || this->lock || this->dlSelectionProcessing)
        {
            if(channel->isBusy())
            {
                scheduleAt(channel->getTransmissionFinishTime(), msg);
            }
            else
            {
                cancelAndDelete(msg);
            }
            return;
        }
        cancelAndDelete(msg);
        this->messageToServe = check_and_cast<AerocomMessage*>(this->queue->pop());
        this->recordsENDQ.record(SimTime().dbl());
        controllerSend(this->capacityI, this->capacityI1, this->capacityI2, this->servingDL, this->X,
                       this->S, this->dlSelectionProcessing, this->messageToServe, this->timeToServe, this->lock);
        return;
    }

    if(strcmp(msg->getName(),"unlock")==0)
    {
        cancelAndDelete(msg);
        this->lock = false;
        if(!this->queue->isEmpty())
        {
            cMessage *msg2 = new cMessage("serve next message");
            scheduleAt(simTime()+this->timeToServe, msg2);
        }
    }

}

void Controller::finish(){

    delete this->queue;
}

simtime_t Controller::kGenerator(){
    //return exponential(0.5,0);
    return lognormal(0.5,0.2,0);
}

void Controller::createNewMessage(simtime_t k, const char* text){
    //creating new message
    AerocomMessage *msg = new AerocomMessage(text);
    msg->setAircraftIndex(getParentModule()->getIndex());
    msg->setBitLength(12800);
    //scheduling new message
    scheduleAt(simTime()+k, msg);
}

void Controller::controllerSend(double &capacityI, double &capacityI1, double &capacityI2, int &servingDL, double X,
        simtime_t S, bool &dlSelectionProcessing, AerocomMessage* messageToServe, simtime_t timeToServe, bool &lock){
    capacityI2 = capacityI1;
    capacityI1 = capacityI;
    //less than 0 first transmission
    if((((capacityI2 - capacityI1)*100 / capacityI2) > X) || (capacityI1 < 0))
    {
       dlSelectionProcessing = true;
       cMessage *msg = new cMessage("dl selection end");
       scheduleAt(simTime()+S, msg);
    }
    else
    {
       updateCapacityServingDL(capacityI, servingDL);
       send(messageToServe, "portToDL$o", servingDL);
       this->recordsSERV.record(SimTime().dbl());
       // it may happen that it tries to send 2 message simultaneously because of the serve next message
       // so we need to lock
       lock = true;
       cMessage *msg2 = new cMessage("unlock");
       msg2->setSchedulingPriority(1);
       scheduleAt(simTime()+timeToServe,msg2);
    }
}

void Controller::dlSelection(double &capacityI, int &servingDL){
    cModule *datalink;
    capacityI = -1;
    double temp;
    for (int i=0; i<5; i++)
    {
        datalink = gate("portToDL$o",i)->getNextGate()->getOwnerModule();
        //saving a capacity
        temp=datalink->par("capacity");
        //comparing capacities
        if(capacityI < temp){
            capacityI = temp;
            servingDL = i;
        }
    }
}

void Controller::updateCapacityServingDL(double &capacityI, int servingDL){
    cModule *datalink;
    datalink = gate("portToDL$o",servingDL)->getNextGate()->getOwnerModule();
    capacityI =datalink->par("capacity");
}


