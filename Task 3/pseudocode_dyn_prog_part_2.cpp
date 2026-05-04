FUNCTION DP_4Peg(n) :
    // Set all values to infinity first
    CREATE dp[0..n] = INF

    // Base cases
    dp[0] = 0
    dp[1] = 1

    FOR i FROM 2 TO n :
FOR t FROM 1 TO i - 1 :
    // Calculate cost for this split
    moves = 2 * dp[t] + (2 ^ (i - t) - 1)

    // Save if this is better
    IF moves < dp[i] :
    dp[i] = moves
    split[i] = t

    // Return the minimum moves for n disks
    RETURN dp[n]

    PROCEDURE Solve(n, src, dst, aux1, aux2) :
    IF n == 0 : RETURN

    t = split[n]  // get the best split for n disks

    // Move top t disks to a buffer peg
    Solve(t, src, aux1, dst, aux2)

    // Move the rest using only 3 pegs
    Move3Peg(n - t, src, dst, aux2)

    // Move the buffer disks to the destination
    Solve(t, aux1, dst, src, aux2)