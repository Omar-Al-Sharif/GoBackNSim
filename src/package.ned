package gobacknsim;

@license(LGPL);
//
// TODO documentation
//
network Network
{
    
    submodules:
        coordinator: Coordinator;
    	node0: Node0;
    	node1: Node1;
    	
    connections:
        
        //Connecting the nodes with the coordinator
        
        node0.node0_out++ --> coordinator.inport++;
        coordinator.outport++ --> node0.node0_in++;
        node1.node1_out++ --> coordinator.inport++;
    	coordinator.outport++ --> node1.node1_in++;
    	
    	//Connecting the nodes with each others
    	
    	node0.node0_out++ --> node1.node1_in++;
    	node1.node1_out++ --> node0.node0_in++;
         
}


