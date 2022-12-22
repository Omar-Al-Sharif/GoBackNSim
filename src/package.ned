package gobackn;

@license(LGPL);
//
// TODO documentation
//
network Network
{
    @display("bgb=499,243");
    submodules:
        coordinator: Coordinator {
            @display("p=240,43;i=block/cogwheel");
        }
        node0: Node {
            @display("p=94,161;i=device/laptop");
        }
        node1: Node {
            @display("p=386,161;i=device/laptop");
        }
    connections:
        node0.node_out++ --> node1.node_in++;
        node1.node_out++ --> node0.node_in++;
        coordinator.outport++ --> node0.node_in++;
        coordinator.outport++ --> node1.node_in++;
}

