# Network-simulator
A C++ model is developed that simulates all the network layers of the network protocol stacks.
PHYSICAL LAYER -> DATA LINK LAYER -> NETWORK LAYER -> TRANSPORT LAYER -> APPLICATION LAYER

# PHYSICAL LAYER
The creation of end devices, communication between them, and a hub network were implemented.
# DATA LINK LAYER
BRIDGES, SWITCH and various access control, flow control (GO_BACK_N, STOP AND WAIT), and error control (CRC and &-bit HAMMING CODE) protocols were implemented in it.

# NETWORK LAYER
ROUTERS were implemented in it. Various protocols, like OSPF AND RIP were included. Apart from these, routing tables and the general topology of the network were also included with the use of the graph and shortest path algorithms. LONGEST MASK MATCHING also a part of it.

# TRANSPORT LAYER
Assigning various ephemeral and well-known ports to various processes UDP dataframe used. Flow control protocols of data link layer were also included in it.

# APPLICATION LAYER
Various protocols like HTTP, SSH, FTP, and DNS were implemented in it.

Add-ons: IPV6 implementation and classful addressing were included.


# SPECIAL IMPROVEMENT IN PROJECT
NOW TWO DEVICES HAVING THESE FILES CAN COMMUNICATE WITH EACH OTHER AND DATA FRAME UDP CAN SIMULATE BETWEEN THEM.
(REQUIREMENT- 
both device must have windows 10 pro for it.
for transfer simulation between two device:
both device must enable message services.
go to ADMISTRATIVE SERVICES AND ENABLE MESSAGING SERVICES.
OPEN CMD- TYPE control admintools
then double click component service
then select services (local)
turn on message services.)

Incase of any doubt/suggestion/technical_problem, feel free to contact on kapilchaudhary8280@gmail.com
