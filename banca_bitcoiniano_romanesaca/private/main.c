#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

typedef struct {
    uint64_t ron;
    uint64_t btc;
    uint64_t totalLiquidity;
} Pool;

typedef struct {
    uint64_t ron;
    uint64_t btc;
    uint64_t liquidity;
} User;

Pool pool = {0, 0, 0};
User user = {250, 0, 0};

void init_pool(uint64_t ron, uint64_t btc) {
    if (pool.ron == 0 && pool.btc == 0) {
        pool.ron = ron;
        pool.btc = btc;
        pool.totalLiquidity = sqrt(ron * btc);
        printf("[STATUS] Pool initialized: RON = %llu, BTC = %llu, Total Liquidity = %llu\n", pool.ron, pool.btc, pool.totalLiquidity);
    } else {
        printf("[STATUS] Pool already initialized!\n");
    }
    
}

void add_liquidity(uint64_t ron, uint64_t btc) {
    if (ron > user.ron || btc > user.btc) {
        printf("\n[STATUS] Insufficient funds to add liquidity!\n");
        return;
    }
    double ron_ratio = (double)ron / pool.ron;
    double btc_ratio = (double)btc / pool.btc;
    uint64_t liquidity_minted = pool.totalLiquidity * (ron_ratio < btc_ratio ? ron_ratio : btc_ratio);

    pool.ron += ron;
    pool.btc += btc;
    pool.totalLiquidity += liquidity_minted;

    user.ron -= ron;
    user.btc -= btc;
    user.liquidity += liquidity_minted;

    printf("\n[STATUS] Added liquidity: RON = %llu, BTC = %llu, Total Liquidity = %llu\n", pool.ron, pool.btc, pool.totalLiquidity);
}

void remove_liquidity(uint64_t liquidity) {
    if (liquidity > user.liquidity) {
        printf("\n[STATUS] Insufficient liquidity to remove.\n");
        return;
    }
    uint64_t ron_to_remove = liquidity * pool.ron / pool.totalLiquidity;
    uint64_t btc_to_remove = liquidity * pool.btc / pool.totalLiquidity;

    pool.ron -= ron_to_remove;
    pool.btc -= btc_to_remove;
    pool.totalLiquidity -= liquidity;

    user.ron += ron_to_remove;
    user.btc += btc_to_remove;
    user.liquidity -= liquidity;

    printf("\n[STATUS] Removed liquidity: RON = %llu, BTC = %llu, Total Liquidity = %llu\n", pool.ron, pool.btc, pool.totalLiquidity);
}

void swap_ron_btc(uint64_t ron) {
    if (ron > user.ron || ron == 0) {
        printf("\n[STATUS] Insufficient RON to swap.\n");
        return;
    }

    uint64_t btc_out = pool.btc - ((pool.ron * pool.btc) / (pool.ron + ron));

    pool.ron += ron;
    pool.btc -= btc_out;

    user.ron -= ron;
    user.btc += btc_out;

    printf("\n[STATUS] Swapped RON for BTC: RON = %llu, BTC = %llu, BTC out = %llu\n", pool.ron, pool.btc, btc_out);
}

void swap_btc_ron(uint64_t btc) {
    if (btc > user.btc || btc == 0) {
        printf("\n[STATUS] Insufficient BTC to swap.\n");
        return;
    }

    uint64_t ron_out = ((pool.ron * btc) / (pool.btc + btc));

    pool.btc += btc;
    pool.ron -= ron_out;

    user.btc -= btc;
    user.ron += ron_out;

    printf("\n[STATUS] Swapped BTC for RON: RON = %llu, BTC = %llu, RON out = %llu\n", pool.ron, pool.btc, ron_out);
}

void display_user_assets() {
    printf("\n[STATUS] User assets: RON = %llu, BTC = %llu, Liquidity = %llu\n", user.ron, user.btc, user.liquidity);
}

void buy_flag() {
    if (user.ron >= 748 && user.btc >= 500) {
        printf("\n[STATUS] Flag purchased! HCamp{_m4573r_0f_UNISWAPv2_1n_4c710n_}\n");
        user.ron -= 748;
        user.ron -= 500;
    } else {
        printf("\n[STATUS] Insufficient funds.\n");
    }
}

void afis() {
    printf("||====================================================================||\n");
    printf("||//$\\\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\//$\\\\||\n");
    printf("||(100)================| BANCA BITCOINIANO-ROMANA |==============(100)||\n");
    printf("||\\\\$//        ~         '------========--------'                \\\\$//||\n");
    printf("||<< /        /$\\              // ____ \\\\                         \\ >>||\n");
    printf("||>>|  13    //B\\\\            // ///..) \\\\         L38036133B   13 |<<||\n");
    printf("||<<|        \\\\R//           || <||  >\\  ||                        |>>||\n");
    printf("||>>|         \\$/            ||  $$ --/  ||      O Suta Bitcoini   |<<||\n");
    printf("||<<|      L38036133B        *\\\\  |\\_/  //*  seria                 |>>||\n");
    printf("||>>|  37                     *\\\\/___\\_//*    2024                 |<<||\n");
    printf("||<<\\     Liquidity      ________/FeDEX\\_________               37 />>||\n");
    printf("||//$\\                    ~|TIMISOARA, ROMANIA|~                  /$\\\\||\n");
    printf("||(100)==================  O SUTA BITCOINI-RONI =================(100)||\n");
    printf("||\\\\$//\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\\\$//||\n");
    printf("||====================================================================||\n");
    printf("\n");
}

void meniu() {
    printf("\n");
    printf("[1] Add Liquidity\n");
    printf("[2] Remove Liquidity\n");
    printf("[3] Swap RON for BTC\n");
    printf("[4] Swap BTC for RON\n");
    printf("[5] Display User Assets\n");
    printf("    Enter your choice > ");
}

int main() {

    setvbuf(stdout, NULL, _IONBF, 0);

    afis();
    init_pool(500, 500);

    while (1) {
        int choice;
        uint64_t amount;

        meniu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("        Enter amount of RON to add: ");
                scanf("%llu", &amount);
                printf("        Enter amount of BTC to add: ");
                uint64_t btcAmount;
                scanf("%llu", &btcAmount);
                add_liquidity(amount, btcAmount);
                break;
            case 2:
                printf("        Enter amount of liquidity to remove: ");
                scanf("%llu", &amount);
                remove_liquidity(amount);
                break;
            case 3:
                printf("        Enter amount of RON to swap: ");
                scanf("%llu", &amount);
                swap_ron_btc(amount);
                break;
            case 4:
                printf("        Enter amount of BTC to swap: ");
                scanf("%llu", &amount);
                swap_btc_ron(amount);
                break;
            case 5:
                display_user_assets();
                break;
            case 1337:
                buy_flag();
                break;
            default:
                printf("\n[STATUS] Invalid choice. Please try again.\n");
                break;
        }
    }

    return 0;
}
