#include <iostream>
using namespace std;

int main()
{
    long long N, M;
    cin >> N >> M;

    const long long LIMIT = 1000000000;
    long long X = 0;
    long long power = 1;

    for (int i = 0; i <= M; ++i)
    {
        X += power;
        if (X > LIMIT)
        {
            cout << "inf" << endl;
            return 0;
        }
        if (power > LIMIT)
            break;

        if (N > 0 && power > LIMIT / N)
        {
            break;
        }
        power *= N;
    }
    cout << X << endl;
    return 0;
}
