#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

vector<char> instruction;
vector<vector<int>> params;

class RegisterMachine{
    private:
        vector<int> registers;
    public:
        RegisterMachine(const int n) {
            registers.resize(n);
        }
        void input(int n) {
            //set R_0 to n
            registers[0] = n;
        }
        void input(int n, int m) {
            //set R_0, R_1 to n, m
            registers[0] = n;
            registers[1] = m;
        }
        void set(int n) {
            //set R_n to 0
            registers[n] = 0;
        }
        void incr(int n) {
            //increment R_n by one
            registers[n]++;
        }
        void transfer(int n, int m) {
            //transfer contents of R_n to R_m
            registers[m] = registers[n];
        }
        bool compare(int n, int m) {
            if (registers[n]==registers[m]) {
                return true;
            }
            return false;
        }
        int get(int n) {
            //get contents of R_n
            return registers[n];
        }
        void print() {
            //print contents of all Rs
            for (const int &n : registers) {
                cout << n << "   ";
            }
            cout << '\n';
        }
};

int run(RegisterMachine reg) {
    int curr = 1;
    char func;
    int a, b, c;
    do {
        reg.print();
        func = instruction[curr-1];
        cout<< func << '\n';
        switch (func) {
            case 'Z': 
                a = params[curr-1][0];
                reg.set(a);
                curr++;
                break;
            case 'S':
                a = params[curr-1][0];
                reg.incr(a);
                curr++;
                break;
            case 'T':
                a = params[curr-1][0];
                b = params[curr-1][1];
                reg.transfer(a, b);
                curr++;
                break;
            case 'J':
                a = params[curr-1][0];
                b = params[curr-1][1];
                c = params[curr-1][2];
                if (reg.compare(a, b)) curr = c;
                else {curr ++;}
                break;
            case 'H':
                return reg.get(0);
                break;
        }
    } while (func!='H');
    return -1;
}

int main() {
    ifstream fin("registerprogram.txt");
    char func;
    vector<int> pars(3);
    while (fin >> func) {
        fill(pars.begin(), pars.end(), 0);
        instruction.push_back(func);
        int temp;
        cout << func;
        switch (func) {
            case 'Z':
                {
                    fin >> pars[0];
                    params.push_back(pars);
                    break;
                }
            case 'S':
                {   
                    fin >> pars[0];
                    params.push_back(pars);
                    break;
                }       
            case 'T':
                {
                    fin >> pars[0] >> pars[1];
                    params.push_back(pars);
                    break;
                }
            case 'J':
                {
                    fin >> pars[0] >> pars[1] >> pars[2];
                    params.push_back(pars);
                    break;
                }
            case 'H':
                {
                    params.push_back(pars);
                    break;
                }
        }
        cout << pars[0] << pars[1] << pars[2] << " ";
    }
    int n, m;
    cout << "\ninput n: ";
    cin >> n;
    cout << "input m: ";
    cin >> m;
    RegisterMachine regi(20);
    if (m==-1) {
        regi.input(n);
    }
    else {
        regi.input(n, m);
    }
    int output = run(regi);
    cout << "\nFINAL OUTPUT: " << output;
}

/*
Register Machines
Infinite number of registers which can each store a number.
Four operations:
Z(n) = Set R_n to 0
S(n) = increment R_n by 1
T(m, n) = transfer/copy contents of R_m to R_n
J(m, n, i) = if contents of R_m and R_n are the same, go to instruction i. Otherwise, go to next instruction.

Limitations/notes:
Register #s start at 0, not 1 like in the packet. Also, they're finite here
can't handle negative numbers or very large numbers, slower with big numbers
J(0, 0, i) is equivalent to a loop, combine with another conditional to make a while loop

n-1 (packet example)
input: n; output:n-1;
Z 1
J 0 1 9
Z 2
S 1
J 0 1 8
S 2
J 0 0 4
T 2 0
H

Addition
input: n, m; output: n + m
Z 2
Z 3
J 0 2 7
S 2
S 3
J 0 0 3
Z 2
J 1 2 12
S 2
S 3
J 0 0 8
T 3 0
H

Subtraction
input: n, m with n>m; output: n - m
Z 2
J 0 1 6
S 1
S 2
J 0 0 2
T 2 0
H

Multiplication
input: n, m; output: n * m
Z 3
Z 4
J 1 3 11
Z 2
J 0 2 9
S 2
S 4
J 0 0 5
S 3
J 0 0 3
T 4 0
H

Square
input: n; output: n^2
T 0 1
Z 3
Z 4
J 1 3 12
Z 2
J 0 2 10
S 2
S 4
J 0 0 6
S 3
J 0 0 4
T 4 0
H


*/