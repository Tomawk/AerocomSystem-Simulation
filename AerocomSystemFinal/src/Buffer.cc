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

#include "Buffer.h"
#include "AerocomMessage_m.h"

Define_Module(Buffer);

void Buffer::initialize()
{
    this->queue=new cQueue("myQ");
    this->busy = false;
    this->recordsIN_Aircraft0.setName("Buffer In[0]");
    this->recordsENDQ_Aircraft0.setName("Buffer EndQ[0]");
    this->recordsSERV_Aircraft0.setName("Buffer Serv[0]");
    this->recordsIN_Aircraft1.setName("Buffer In[1]");
    this->recordsENDQ_Aircraft1.setName("Buffer EndQ[1]");
    this->recordsSERV_Aircraft1.setName("Buffer Serv[1]");
    this->recordsIN_Aircraft2.setName("Buffer In[2]");
    this->recordsENDQ_Aircraft2.setName("Buffer EndQ[2]");
    this->recordsSERV_Aircraft2.setName("Buffer Serv[2]");
    this->recordsIN_Aircraft3.setName("Buffer In[3]");
    this->recordsENDQ_Aircraft3.setName("Buffer EndQ[3]");
    this->recordsSERV_Aircraft3.setName("Buffer Serv[3]");
    this->recordsIN_Aircraft4.setName("Buffer In[4]");
    this->recordsENDQ_Aircraft4.setName("Buffer EndQ[4]");
    this->recordsSERV_Aircraft4.setName("Buffer Serv[4]");
    this->recordsIN_Aircraft5.setName("Buffer In[5]");
    this->recordsENDQ_Aircraft5.setName("Buffer EndQ[5]");
    this->recordsSERV_Aircraft5.setName("Buffer Serv[5]");
    this->recordsIN_Aircraft6.setName("Buffer In[6]");
    this->recordsENDQ_Aircraft6.setName("Buffer EndQ[6]");
    this->recordsSERV_Aircraft6.setName("Buffer Serv[6]");
    this->recordsIN_Aircraft7.setName("Buffer In[7]");
    this->recordsENDQ_Aircraft7.setName("Buffer EndQ[7]");
    this->recordsSERV_Aircraft7.setName("Buffer Serv[7]");
}

void Buffer::handleMessage(cMessage *msg)
{
    // if to control tower insert in queue
    if(strcmp(msg->getName(),"to control tower")==0)
    {
        //insert in queue until served
        this->queue->insert(msg);

        AerocomMessage* aerocom_msg = check_and_cast<AerocomMessage*>(msg);
        switch(aerocom_msg->getAircraftIndex()){
        case 0:
            this->recordsIN_Aircraft0.record(SimTime().dbl());
            break;
        case 1:
            this->recordsIN_Aircraft1.record(SimTime().dbl());
            break;
        case 2:
            this->recordsIN_Aircraft2.record(SimTime().dbl());
            break;
        case 3:
            this->recordsIN_Aircraft3.record(SimTime().dbl());
            break;
        case 4:
            this->recordsIN_Aircraft4.record(SimTime().dbl());
            break;
        case 5:
            this->recordsIN_Aircraft5.record(SimTime().dbl());
            break;
        case 6:
            this->recordsIN_Aircraft6.record(SimTime().dbl());
            break;
        case 7:
            this->recordsIN_Aircraft7.record(SimTime().dbl());
            break;
        }

        if(!this->busy){
            msg = check_and_cast<AerocomMessage*>(this->queue->pop());
            AerocomMessage* aerocom_msg1 = check_and_cast<AerocomMessage*>(msg);
            switch(aerocom_msg1->getAircraftIndex()){
            case 0:
                this->recordsENDQ_Aircraft0.record(SimTime().dbl());
                break;
            case 1:
                this->recordsENDQ_Aircraft1.record(SimTime().dbl());
                break;
            case 2:
                this->recordsENDQ_Aircraft2.record(SimTime().dbl());
                break;
            case 3:
                this->recordsENDQ_Aircraft3.record(SimTime().dbl());
                break;
            case 4:
                this->recordsENDQ_Aircraft4.record(SimTime().dbl());
                break;
            case 5:
                this->recordsENDQ_Aircraft5.record(SimTime().dbl());
                break;
            case 6:
                this->recordsENDQ_Aircraft6.record(SimTime().dbl());
                break;
            case 7:
                this->recordsENDQ_Aircraft7.record(SimTime().dbl());
                break;
            }
            send(msg, "portToO2$o");
            this->busy = true;
        }
    }
    if(strcmp(msg->getName(),"served")==0)
    {
        AerocomMessage* aerocom_msg2 = check_and_cast<AerocomMessage*>(msg);
        switch(aerocom_msg2->getAircraftIndex()){
        case 0:
            this->recordsSERV_Aircraft0.record(SimTime().dbl());
            break;
        case 1:
            this->recordsSERV_Aircraft1.record(SimTime().dbl());
            break;
        case 2:
            this->recordsSERV_Aircraft2.record(SimTime().dbl());
            break;
        case 3:
            this->recordsSERV_Aircraft3.record(SimTime().dbl());
            break;
        case 4:
            this->recordsSERV_Aircraft4.record(SimTime().dbl());
            break;
        case 5:
            this->recordsSERV_Aircraft5.record(SimTime().dbl());
            break;
        case 6:
            this->recordsSERV_Aircraft6.record(SimTime().dbl());
            break;
        case 7:
            this->recordsSERV_Aircraft7.record(SimTime().dbl());
            break;
        }
        cancelAndDelete(msg);
        if(!(this->queue->isEmpty()))
        {
            AerocomMessage *msg2 = check_and_cast<AerocomMessage*>(this->queue->pop());
            switch(msg2->getAircraftIndex()){
            case 0:
                this->recordsENDQ_Aircraft0.record(SimTime().dbl());
                break;
            case 1:
                this->recordsENDQ_Aircraft1.record(SimTime().dbl());
                break;
            case 2:
                this->recordsENDQ_Aircraft2.record(SimTime().dbl());
                break;
            case 3:
                this->recordsENDQ_Aircraft3.record(SimTime().dbl());
                break;
            case 4:
                this->recordsENDQ_Aircraft4.record(SimTime().dbl());
                break;
            case 5:
                this->recordsENDQ_Aircraft5.record(SimTime().dbl());
                break;
            case 6:
                this->recordsENDQ_Aircraft6.record(SimTime().dbl());
                break;
            case 7:
                this->recordsENDQ_Aircraft7.record(SimTime().dbl());
                break;
            }
            send(msg2,"portToO2$o");
        }
        else
        {
            this->busy = false;
        }

    }
}

void Buffer::finish(){
    delete this->queue;
}
