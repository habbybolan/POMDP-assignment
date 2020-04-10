# POMDP-assignment

A representiation of a POMDP that is 3x4 size, represented as <br />
![statespace](https://github.com/habbybolan/POMDP-assignment/blob/master/statespace.png)
<br />   
where 6 states have 2 walls, 3 with 1 wall, and 2 terminal states with respective rewards +1 and -1 <br />
Given a set of observations, if there is 1 or 2 walls around it (or ends state), the actions to perform in the state space, as well as the initial state the agent is in, if there is one.

Calculates the agents belief state, or the probability of the state that the agent would be in.

actions (up,up,up) <br />
observations (2,2,2) walls <br />
no start state <br />

![state1](https://github.com/habbybolan/POMDP-assignment/blob/master/state1.png)

actions (up,up,up) <br />
observations (1,1,1) walls <br />
no start state <br />

![state2](https://github.com/habbybolan/POMDP-assignment/blob/master/state2.png)

actions (right,right,up) <br />
observations (1,1,end) <br />
start state (2,3) <br />

![state3](https://github.com/habbybolan/POMDP-assignment/blob/master/state3.png)

actions (up,right,right, right) <br />
observations (2,2,1,1) walls <br />
start state (1,1) <br />

![state4](https://github.com/habbybolan/POMDP-assignment/blob/master/state4.png)


