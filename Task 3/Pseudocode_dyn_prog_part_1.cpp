FUNCTION Frame_Stewart_8_Disks() :
    // Start with base cases
    dp[0] = 0
    dp[1] = 1

    // Fill table from 2 to 8
    FOR n FROM 2 TO 8:
// Try every possible split point t
// Pick the one that gives fewest moves
dp[n] = MIN over t in[1..n - 1] of :
    2 * dp[t] + (2 ^ (n - t) - 1)

    // Answer is stored here
    RETURN dp[8]   // Returns: 33

    PROCEDURE Move_8_Disks(n, src, dst, aux1, aux2) :
    IF n == 0 : RETURN

    t = optimal_split[n]  // best split for n disks

    // Move top t disks to a buffer peg
    Move_8_Disks(t, src, aux1, dst, aux2)

    // Move remaining disks using only 3 pegs
    Move_3Peg(n - t, src, dst, aux2)

    // Move the buffer disks to the destination
    Move_8_Disks(t, aux1, dst, src, aux2)