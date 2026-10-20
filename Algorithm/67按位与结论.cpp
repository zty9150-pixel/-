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



*/