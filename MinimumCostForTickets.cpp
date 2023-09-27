int solve(int n, vector<int> days, vector<int> cost, int index, vector<int> &dp) {
    //base case
    if(index >= n)
        return 0;

    if(dp[index] != -1)
        return dp[index];

    //1st day ka pass
    int option1 = cost[0] + solve(n, days, cost, index+1, dp);

    int i;
    //2nd option
    for(i = index; i <= n && days[i] < days[index] + 7; i++);

    int option2 = cost[1] + solve(n, days, cost, i, dp);

    for(i = index; i <= n && days[i] < days[index] + 30; i++);

    int option3 = cost[2] + solve(n, days, cost, i, dp);

    dp[index] = min(option1, min(option2, option3));
    return dp[index];
}

int solveTab(int n, vector<int> &days, vector<int> &cost) {
    vector<int> dp(n+1, INT_MAX);

    dp[n] = 0;

    for(int j = n-1; j >= 0; j--) {
        int option1 = cost[0] + dp[j+1];

        int i;
        for(i = j; i < n && days[i] < days[j] + 7; i++);

        int option2 = cost[1] + dp[i];

        for(i = j; i < n && days[i] < days[j] + 30; i++);

        int option3 = cost[2] + dp[i];
        dp[j] = min(option1, min(option2, option3));

    }
    return dp[0];
}

int solveVfast(int n, vector<int> days, vector<int> cost){
    queue<pair<int,int> > month;
    queue<pair<int,int> > week;

    int ans = 0;

    //step 1: Remove Expired Days
    for(int day : days) {
        while(!month.empty() && month.front().first + 30 <= day)
            month.pop();
        
        while(!week.empty() && week.front().first + 7 <= day)
            week.pop();

        //step 2: push current days cost
        month.push(make_pair(day, ans + cost[2]));
        week.push(make_pair(day, ans + cost[1]));

        ans = min(ans+cost[0], min(month.front().second, week.front().second));
    }
    return ans;
}


int minimumCoins(int n, vector<int> days, vector<int> cost)
{
    //vector<int> dp(n+1, -1);
    return solveVfast(n, days, cost);
}