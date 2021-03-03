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

package AerocomSystemFinal.simulations;

import ned.DatarateChannel;
import AerocomSystemFinal.src.Buffer;
import AerocomSystemFinal.src.ControlTower;
import AerocomSystemFinal.src.Aircraft;

network aerocom_system
{
    parameters:
        int numAircraft;
    
    submodules:

        Aircrafts[numAircraft]: Aircraft {
            @display("p=120,80,ri,200");
        }
        Tower: ControlTower {
            @display("p=120,280,ri,200");
        }
        Buffer: Buffer {
            numAir = numAircraft;
            @display("p=120,180");
        }
    connections:
        for i=0..numAircraft-1 {
            Aircrafts[i].portToO++ <--> DatarateChannel <--> Buffer.portToO1++;
            Aircrafts[i].portToO++ <--> DatarateChannel <--> Buffer.portToO1++;
            Aircrafts[i].portToO++ <--> DatarateChannel <--> Buffer.portToO1++;
            Aircrafts[i].portToO++ <--> DatarateChannel <--> Buffer.portToO1++;
            Aircrafts[i].portToO++ <--> DatarateChannel <--> Buffer.portToO1++;
        }
        Buffer.portToO2 <--> Tower.portToO;
}
