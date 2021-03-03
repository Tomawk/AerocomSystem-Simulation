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

#ifndef __AEROCOM_SYSTEM_BUFFER_H_
#define __AEROCOM_SYSTEM_BUFFER_H_

#include <omnetpp.h>

using namespace omnetpp;

/**
 * TODO - Generated class
 */
class Buffer : public cSimpleModule
{
  private:
    cQueue *queue;
    bool busy;
    cOutVector recordsIN_Aircraft0;
    cOutVector recordsENDQ_Aircraft0;
    cOutVector recordsSERV_Aircraft0;
    cOutVector recordsIN_Aircraft1;
    cOutVector recordsENDQ_Aircraft1;
    cOutVector recordsSERV_Aircraft1;
    cOutVector recordsIN_Aircraft2;
    cOutVector recordsENDQ_Aircraft2;
    cOutVector recordsSERV_Aircraft2;
    cOutVector recordsIN_Aircraft3;
    cOutVector recordsENDQ_Aircraft3;
    cOutVector recordsSERV_Aircraft3;
    cOutVector recordsIN_Aircraft4;
    cOutVector recordsENDQ_Aircraft4;
    cOutVector recordsSERV_Aircraft4;
    cOutVector recordsIN_Aircraft5;
    cOutVector recordsENDQ_Aircraft5;
    cOutVector recordsSERV_Aircraft5;
    cOutVector recordsIN_Aircraft6;
    cOutVector recordsENDQ_Aircraft6;
    cOutVector recordsSERV_Aircraft6;
    cOutVector recordsIN_Aircraft7;
    cOutVector recordsENDQ_Aircraft7;
    cOutVector recordsSERV_Aircraft7;


  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual void finish();
};

#endif
