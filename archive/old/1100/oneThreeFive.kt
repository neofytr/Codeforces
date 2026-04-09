fun answer(dp: IntArray, num: Int): Int {
    if (num <= 0) return 0
    if (dp[num] != -1) return dp[num]

    return when (num) {
        1 -> dp[num] = 1
        2 -> dp[num] = 2
        3 -> dp[num] = 3
        4 -> dp[num] = 1
        5 -> dp[num] = 0
        else -> dp[num] = minOf(
            1 + answer(dp, num - 1),
            answer(dp, num - 3),
            answer(dp, num - 5)
        )
    }
}

fun solve() {
    val n = readln().toInt()
    val dp = IntArray(n + 1) { -1 }
    println(answer(dp, n))
}

fun main() {
    val t = readln().toInt()
    repeat(t) {
        solve()
    }
}
