#include <bits/stdc++.h>
using namespace std;
#define fff for
#define iii int
#define vvv vector
#define mmm main
#define ccc cin
#define ooo cout
#define eee endl
#define pb push_back

void solve_trash() {
    iii _x_;
    ccc >> _x_;
    vvv<iii> gg_ez(_x_);
    fff(iii _i_ = 0; _i_ < _x_; ++_i_) {
        ccc >> gg_ez[_i_];
    }
    
    if (_x_ == 0) {
        ooo << 0 << eee;
        return;
    }

    vvv<iii> hhh_hhh(_x_, 1);
    iii bIg_bOi = 1;

    fff(iii kkk = 1; kkk < _x_; ++kkk) {
        fff(iii jjj = 0; jjj < kkk; ++jjj) {
            if (gg_ez[jjj] <= gg_ez[kkk]) {
                hhh_hhh[kkk] = max(hhh_hhh[kkk], hhh_hhh[jjj] + 1);
            }
        }
        bIg_bOi = max(bIg_bOi, hhh_hhh[kkk]);
    }

    iii rrr_es = _x_ - bIg_bOi;
    ooo << rrr_es << eee;
}

iii mmm() {
    ios_base::sync_with_stdio(0); 
    ccc.tie(0);
    iii ttt_t;
    ccc >> ttt_t;
    while (ttt_t--) {
        solve_trash();
    }
    return 0;
}