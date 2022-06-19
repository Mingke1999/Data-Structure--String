#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

/*
* author mingke deng
* Deterministic Finite Automata DFA also referred to as a finite state machine(FSM)
* DFA contains states "start" and "finish"
* Example:matching pattern "abac"
* vertice 0 match nothing, not start
* vertice 1 if (a) stay if c go back beginning since ac not match start
* vertice 2 matched a(b),if b or c go back beginnning since a'bb' and a'bc' not matching any
* vertice 3 matched ab(a), if a again ->aba'a' go vertica 1, if b go back vertice 2 aba'b'
* vertice 4 success aba(c)
*/
int state = 0; //record the matching state

void start(char c) //?a
{
    if (c == 'a') {
        state = 1;    //start
    }
    else{
        state = 0;    //matching nothing
    }
    
}

void state1(char c){ //a_

    if (c == 'a') {
        state = 1; //a'a' might be the next start
    }else if (c == 'c') {
        state = 0;    //ac matches nothing
    }else if (c=='b') {  //a'b'
        state = 2;
    }
}

void state2(char c){//ab_

    if (c == 'b' || c == 'c') { //bb, bc match nothing
        state = 0;
    }
    else if (c == 'a') {   //ab'a'
        state = 3;
    }
}

void state3(char c){ //aba_

    if (c == 'a') { //aba'a' //might be another start
        state = 1;
    }
    else if (c == 'b') {    //ab'ab'
        state = 2;
    }
    else if(c=='c') {   
        state = 4;    //matched 'abac'
    }
}

bool checkMatch(char str[]){
    int len = strlen(str);
    bool isMatched = false;

    for (int i = 0; i < len; i++){
        if (state == 0){
            start(str[i]);
        }else if (state == 1){
            state1(str[i]);
        }
        else if (state == 2) {
            state2(str[i]);
        }
        else if (state == 3) {
            state3(str[i]);
        }else {
            isMatched = false;
        }
        if (state == 4) {
            isMatched = true;
            break;
        }
        else {
            isMatched = false;
        }
    }
    return isMatched;
}

int main() {
	printf("Deterministic Finite Automata DFA\n");

    char matching[] = "qwerabacasdf";
    if (checkMatch(matching)) {
        printf("The pattern was found");
    }else{
        printf("The text was not matched");
    }
	return 0;
}
