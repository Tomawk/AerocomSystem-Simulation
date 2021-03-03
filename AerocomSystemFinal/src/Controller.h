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

#ifndef __AEROCOM_SYSTEM_CONTROLLER_H_
#define __AEROCOM_SYSTEM_CONTROLLER_H_

#include <omnetpp.h>
#include "AerocomMessage_m.h"

using namespace omnetpp;

/**
 * TODO - Generated class
 */
class Controller : public cSimpleModule
{
  private:
    simtime_t S;
    double X;
    simtime_t timeToServe;
    int servingDL;
    double capacityI, capacityI1, capacityI2;
    bool dlSelectionProcessing;
    bool lock;
    AerocomMessage *messageToServe;
    cQueue *queue;
    cOutVector recordsIN;
    cOutVector recordsENDQ;
    cOutVector recordsSERV;
  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual void finish();
    virtual void createNewMessage(simtime_t k, const char* text);
    virtual void dlSelection(double &capacityI, int &servingDL);
    virtual void updateCapacityServingDL(double &capacityI, int servingDL);
    virtual void controllerSend(double &capacityI, double &capacityI1, double &capacityI2, int &servingDL, double X,
        simtime_t S, bool &dlSelectionProcessing, AerocomMessage* messageToServe, simtime_t timeToServe, bool &lock);
    virtual simtime_t kGenerator();
};

#endif
