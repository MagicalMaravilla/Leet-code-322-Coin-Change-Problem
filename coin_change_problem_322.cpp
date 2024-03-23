#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

/**
 * Calculates the minimum number of coins needed to form a given amount with any set of denominations.
 *
 * @param coins The vector of coin denominations available.
 * @param amount The total amount for which the minimum number of coins is calculated.
 * @return The minimum number of coins needed to form the given amount or -1 if impossible.
 */
int coinChange(const std::vector<int>& coins, int amount) {
    if (amount < 0) {
        return -1; // Return -1 if the amount is negative as it's invalid input.
    }

    std::vector<int> dp(amount + 1, amount + 1);
    dp[0] = 0; // Base case: no coins are needed for amount 0.

    for (int currentAmount = 1; currentAmount <= amount; ++currentAmount) {
        for (int coin : coins) {
            if (coin <= currentAmount) {
                dp[currentAmount] = std::min(dp[currentAmount], 1 + dp[currentAmount - coin]);
            }
        }
    }

    return dp[amount] > amount ? -1 : dp[amount];
}

int main() {
    // Example test case: Solve the coin change problem for a set of arbitrary denominations.
    std::vector<int> denominations = {1, 2, 5}; // Example set of denominations.
    int targetAmount = 11; // Example target amount.
    
    int result = coinChange(denominations, targetAmount);

    if (result != -1) {
        std::cout << "The minimum number of coins needed: " << result << std::endl;
    } else {
        std::cout << "It's impossible to form the target amount with the given denominations." << std::endl;
    }

    return 0;
}
