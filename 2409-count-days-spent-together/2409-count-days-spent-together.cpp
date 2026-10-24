class Solution {

    static constexpr int DAY_COUNT[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    int convertDateToNum(string &date) {

        int month = stoi(date.substr(0, 2)) - 1;
        int day = stoi(date.substr(3, 2));
        for(int m = 0; m < month; m++) {
            day += DAY_COUNT[m];
        }
        return day;
    }

public:
    int countDaysTogether(string arriveAlice, string leaveAlice, string arriveBob, string leaveBob) {
        
        int aliceStart = convertDateToNum(arriveAlice);
        int aliceEnd = convertDateToNum(leaveAlice);
        int bobStart = convertDateToNum(arriveBob);
        int bobEnd = convertDateToNum(leaveBob);

        if(aliceStart > bobEnd || bobStart > aliceEnd) return 0; //no overlap

        return min(aliceEnd, bobEnd) - max(aliceStart, bobStart) + 1;
    }
};