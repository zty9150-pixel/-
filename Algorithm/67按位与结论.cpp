/*  1.对于任意 n 个互不相同的正整数，它们的按位或结果至少为 n
    2.按位与：结果只会越来越小（或不变）,二进制1位也会变少或不变。按位或：结果只会越来越大（或不变），二进制1位也会越来越多或不变
    3.GCC builtin 位运算内置函数（竞赛常用，仅GCC/Clang支持）
        1. __builtin_ctz(x) / __builtin_ctzll(x)
        ctz: count trailing zeros
        作用：返回 x 二进制【末尾0的个数】
        注意：x不能为0！ctz用于int，ctzll用于long long
        例：x=8(1000)，末尾3个0，__builtin_ctz(8)=3

        2. __builtin_clz(x) / __builtin_clzll(x)
        clz: count leading zeros
        作用：返回 x 二进制【前导0的个数】
        注意：x不能为0！clz是int(32位)，clzll是long long(64位)
        例：32位int下 x=1(0b000...0001)，前导31个0，__builtin_clz(1)=31

        3. __builtin_popcount(x)
        作用：返回x二进制里【1的总个数】
        popcountll 对应long long类型

        4. __builtin_parity(x)
        作用：统计二进制1的数量的奇偶性
        1的个数是偶数返回0；1的个数是奇数返回1

        5. __builtin_ffs(x)
        ffs: find first set
        作用：从后向前找，返回【最低位1所在位置】（从1开始计数！）
        例：x=8(1000)，最低位1在第4位，返回4
        👉 和 __builtin_ctz 区别：ctz返回0的个数，ffs返回位置，ffs(x)=ctz(x)+1

        6. __builtin_sqrt(x)
        快速整数开平方，返回平方根近似值
    4.结论：一个非零偶数不断除以 2，直到变成奇数，所需次数等于其二进制末尾连续 0 的个数。
        * 原理：
        * 若 x = 2^k * m（m 为奇数），则恰好需要除以 2 共 k 次。
        *
        * 例如：
        * 12 = 1100  -> 2 次
        * 24 = 11000 -> 3 次
        * 40 = 101000 -> 3 次
        * 64 = 1000000 -> 6 次
        *
        * 位运算实现：
        * int k = __builtin_ctz(x);     // int 类型
        * int k = __builtin_ctzll(x);   // long long 类型
        *
        * 相关性质：
        * x & (-x) 可以提取 x 最低位的 1，结果为 2^k。
        * 因此 k = log2(x & -x)。
        *
        * 注意：
        * 1. x = 0 时无法通过除以 2 变成奇数。
        * 2. __builtin_ctz(0) 的行为未定义。
        * 3. __builtin_ctz 通常可在 O(1) 时间内完成。
    5.公式x ^ y = x + y - 2 * (x & y)
        题意关键：每次操作 x--, y++
        => x + y 的总和始终不变！
        总和 S = x + y 是定值。

        要最大化 x^y：
        因为 S固定，x^y = S - 2*(x&y)
        所以要让 x^y 尽可能大，等价于让 (x & y) 尽可能小。

        最小的 x&y 等于 0。
        当 x=0 时，x&y = 0，此时 x^y = x + y = S，达到最大值。
        需要操作次数 = 原始x的值（每次x减1，直到x变成0）



*/