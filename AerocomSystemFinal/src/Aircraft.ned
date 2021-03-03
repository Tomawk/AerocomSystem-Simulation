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

package AerocomSystemFinal.src;

module Aircraft
{
    
    parameters:
        int servingDL = 0;
        double S @unit(s);
        double X;
        int coefficient;
        int datarateMultiplier;
        double timeToServe @unit(s);
        @display("i=device/lan-bus");
  
    gates:
        inout portToO[5];
    submodules:

        controller: Controller {
            @display("p=301,147");
        }

        dataLink[5]: DataLink {
            @display("p=161,57,r,70");
        }
        
    connections:
        for i=0..4 {
            dataLink[i].portToO <--> portToO++;
        	dataLink[i].portToC <--> controller.portToDL++;
        }

}
