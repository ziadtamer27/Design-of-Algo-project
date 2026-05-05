#include <iostream>

using namespace std;

int movecount=0;

// Function to solve the Tower of Hanoi problem using 3 pegs
// we will use it as a part of the 4 pegs solution
void towerofHanoi3(int n_disks, char from_peg, char to_peg, char helper)
{
    if(n_disks ==0)
        return;
    
    towerofHanoi3(n_disks-1, from_peg, helper, to_peg);
    cout<<"Move disk from "<<from_peg<<" to "<<to_peg<<endl;
    movecount++;
    towerofHanoi3(n_disks-1, helper, to_peg, from_peg);
}

// Function to solve the Tower of Hanoi problem using 4 pegs
void towerofHanoi4(int n_disks, char from_peg, char to_peg, char helper1, char helper2)
{
    if(n_disks ==0)
        return;

    if(n_disks ==1)
    {
        cout<<"Move disk from "<<from_peg<<" to "<<to_peg<<endl;
        movecount++;
        return;
    }

    // Move the top k disks from the source peg to the first helper peg using all four pegs
    int k=n_disks/2;
    towerofHanoi4(k, from_peg, helper1, helper2, to_peg);

    // Move the remaining n-k disks from the source peg to the destination peg using the three-peg solution
    towerofHanoi3(n_disks-k, from_peg, to_peg, helper2);

    // Move the k disks from the first helper peg to the destination peg using all four pegs
    towerofHanoi4(k, helper1, to_peg, from_peg, helper2);
}

int main()
{
    int n_disks=8;
    cout<<"The sequence of moves involved in the Tower of Hanoi are : "<<endl;
    towerofHanoi4(n_disks, 'A', 'D', 'B', 'C');
    cout<<"Total moves: "<<movecount<<endl;
    return 0;
}