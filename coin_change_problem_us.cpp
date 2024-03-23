#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <stdexcept> // For std::invalid_argument

/**
 * Calculates the minimum number of coins needed to form a given amount using US denominations.
 *
 * @param amount The total amount in cents for which the minimum number of coins is calculated.
 * @return The minimum number of coins needed to form the given amount or -1 if impossible.
 * @throws std::invalid_argument If the amount is negative.
 */
int coinChangeForAllUSD(int amount) {
    if(amount < 0) {
        throw std::invalid_argument("Amount cannot be negative.");
    }

    std::vector<int> dp(amount + 1, amount + 1);
    dp[0] = 0;
    std::vector<int> coins = {1, 5, 10, 25, 50, 100, 200, 500, 1000, 2000, 5000, 10000};

    for (int currentAmount = 1; currentAmount <= amount; ++currentAmount) {
        for (int coinValue : coins) {
            if (coinValue <= currentAmount) {
                dp[currentAmount] = std::min(dp[currentAmount], 1 + dp[currentAmount - coinValue]);
            }
        }
    }

    return dp[amount] > amount ? -1 : dp[amount];
}

/**
 * Logs an error message in a JSON-like format.
 *
 * @param message The error message to log.
 */
void logError(const std::string& message) {
    std::cout << "{\"error\": \"" << message << "\"}\n";
}

/**
 * Runs a test case for the coin change problem and prints the result.
 *
 * @param amount The amount in cents for the test case.
 */
void runTest(int amount) {
    try {
        int result = coinChangeForAllUSD(amount);
        std::cout << "Test with amount " << amount << " cents:\n";
        if (result != -1) {
            std::cout << "  - Minimum coins needed: " << result << std::endl;
        } else {
            std::cout << "  - It's impossible to form the amount with the given denominations." << std::endl;
        }
    } catch (const std::exception& e) {
        logError(e.what());
    }
}

/**
 * The main function that runs several test cases for the coin change problem.
 */
int main() {
    // Expanded set of test amounts including edge cases and challenging scenarios
    std::vector<int> testAmounts = {
        0,         // Edge case: smallest amount
        1,         // Smallest denomination
        4,         // Below smallest coin combination except for 1 cent
        12,        // Small amount requiring multiple coins
        25,        // Exact denomination match
        49,        // Requires multiple denominations
        99,        // Complex combination under a dollar
        100,       // Exact denomination match (1 dollar)
        187,       // Arbitrary amount requiring a mix of denominations
        500,       // Exact denomination match (5 dollars)
        564,       // Arbitrary amount with no exact match
        1000,      // Exact denomination match (10 dollars)
        10000,     // Large amount (100 dollars)
        12345,     // Large, arbitrary amount
        29999,     // Very large amount to test efficiency
        -1,        // Invalid amount (negative)
        50000,     // Edge case: very large amount to test upper bounds
        25005      // Test amount requiring large denominations and change
    };

    for (int amount : testAmounts) {
        runTest(amount);
    }
    return 0;
}
