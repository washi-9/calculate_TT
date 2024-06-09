#include <stdio.h>
/* 文責 遠藤 */

/* 時刻を表す構造体 */
typedef struct time {
    int hours;
    int minutes;
}Time;

/* 工程データを表す構造体 */
typedef struct process {
    char *event; // 工程の名前
    char *information; // 工程の説明
    int nkm; // 工程の距離(km)
    int nup; // 工程のアップ
    int ndown; // 工程のダウン
    int duration; // 工程の所要時間(分)
}Process;

/* 時刻の加算関数 */
Time addTime(Time start, int minutes) {
    Time result;
    result.hours = start.hours + (start.minutes + minutes) / 60; // 時間の加算
    result.minutes = (start.minutes + minutes) % 60; // 分の加算
    return result;
}

/* スケジュールの計算関数 */
void calculateSchedule(Time startTime, Process processes[], int numProcesses ) {
    Time currentTime = startTime;
    int totalDistance = 0, totalUp = 0, totalDown = 0;

    /* 各工程の距離アップダウンを合計する */
    for (int i = 0; i < numProcesses; i++) {
        if (processes[i].nkm > 0) totalDistance += processes[i].nkm;
        if (processes[i].nup > 0) totalUp += processes[i].nup;
        if (processes[i].ndown > 0) totalDown += processes[i].ndown;
    }

    printf("%dkm %ddown %ddown\n\n", totalDistance, totalUp, totalDown);

    for (int i = 0; i < numProcesses; i++) {
        printf("%02d:%02d %s\n",currentTime.hours, currentTime.minutes, processes[i].event);
        if (i == numProcesses - 1) break; // 最後の工程の場合↓を表示しない
        /* 固定の時間の表示の判別(minかhか) */
        int judge = processes[i].duration % 60;
        /* 移動時間が0の場合 */
        if (processes[i].duration == 0) {
            judge = 1;
        }
        /* hourにhに変換された時間を格納 */
        int hour = processes[i].duration / 60;
        printf("  ↓%s ", processes[i].information);
        /* kmで条件分岐 */
        switch (processes[i].nkm) {
            case 0: /* 0kmの場合 */
                /* up downも0であるため時間だけ表示 */
                switch (judge) {
                    case 0: /* h表示 */
                        printf("%dh\n", hour);
                        break;
                    case 30: /*n.5h */
                        printf("%d.5h\n", hour);
                        break;
                    case 1: /* 移動時間が0 */
                        printf("\n");
                        break;
                    default: /* min表示 */
                        printf("%dmin\n", processes[i].duration);
                        break;
                }
                break;
// ここまでが0kmの場合
            case (-1): /* 微km */
                printf("微km ");
                switch (processes[i].nup) {
                    case 0: /* upが0の場合 */
                        break;

                    case (-1): /* 微up */
                        printf("微up ");
                        break;
                    
                    default: /* upがある場合 */
                        printf("%dup ", processes[i].nup);
                        break;
                }
                switch (processes[i].ndown) {
                    case 0: /* downが0の場合 */
                        break;

                    case (-1): /* 微down */
                        printf("微down ");
                        break;
                    
                    default: /* downがある場合 */
                        printf("%ddown ", processes[i].ndown);
                        break;
                }
                switch (judge) {
                    case 0: /* h 表示 */
                        printf("%dh\n", hour);
                        break;
                    case 30: /*n.5h */
                        printf("%d.5h\n", hour);
                        break;
                    case 1: /* 移動時間が0 */
                        printf("\n");
                        break;
                    default: /* min表示 */
                        printf("%dmin\n", processes[i].duration);
                        break;
                }
                break;
// ここまでが微kmの場合
            default: /* 通常のkm */
                printf("%dkm ", processes[i].nkm);
                switch (processes[i].nup) {
                    case 0: /* upが0の場合 */
                        break;

                    case (-1): /* 微up */
                        printf("微up ");
                        break;
                    
                    default: /* upがある場合 */
                        printf("%dup ", processes[i].nup);
                        break;
                }
                switch (processes[i].ndown) {
                    case 0: /* downが0の場合 */
                        break;

                    case (-1): /* 微down */
                        printf("微down ");
                        break;
                    
                    default: /* downがある場合 */
                        printf("%ddown ", processes[i].ndown);
                        break;
                }
                switch (judge) {
                    case 0: /* h 表示 */
                        printf("%dh\n", hour);
                        break;
                    case 30: /*n.5h */
                        printf("%d.5h\n", hour);
                        break;
                    case 1: /* 移動時間が0 */
                        printf("\n");
                        break;
                    default: /* min表示 */
                        printf("%dmin\n", processes[i].duration);
                        break;
                }
                break;
        }
        currentTime = addTime(currentTime, processes[i].duration); //次の時刻を計算
    }
}

int main(void) {
/* 
    [入力の仕方]

    [開始時刻の設定方法]

    開始時刻を6時00分にしたいときは下の「Time start = { , }」を
    「Time start = {6, 0}」という風に書き換える．

    [TT案の作り方]

    Processs[]の定義で第１引数に場所，第２引数に情報(出発準備や昼食)，
    第３引数に距離(km)，第４引数にup，第５引数にup，第６引数にdownを書く．
    ここで注意なのが距離，up，down，時間は必ず"半角"で書くこと．
    特に時間は"分"換算の時間を書くこと．全角で書くとうまく動きません．

    ここで微km，微up，微downにしたいときは-1を入力する．各項目に0を入力する
    とその項目は表示されない．ただしkmが0の場合はup，downも0であるため
    第２引数の情報と時間だけが表示される．
    
    Process processes[] = {
        {"場所", "情報", km(半角), up(半角), down(半角),  時間(半角)}
        ...
    }
    

    例えば　大阪大学 豊中キャンパス
            ↓  12km 348up 31down 50min
            勝尾寺
            ...
            ~~~~

    と入力したいときは

            (大阪大学 豊中キャンパス)*1
            ↓  ()*2 (12)*3 km (348)*4 up (31)*5 down (50)*6 min
            勝尾寺

    のように6つのパーツに分けて

    Process processes[] = {
        {"大阪大学 豊中キャンパス", "", 12, 348, 31, 50},
        {"勝尾寺", "...", ., ., ., .}
        ...
    }

    のように入力すればよい．上の例のような場合は第二引数の情報は空白にすればよい．

    また，「微km」などを使うときは対応する場所に-1を入力する．
*/
// ~~~~~~~~~~~~~~~~~~~~ここより下を編集~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    /* 1         {時,分}  */
    Time start = {6, 0}; // 開始時刻

    /* 工程データのリスト */
    Process processes[] = {
    /* 2 {"場所", "情報", km, up, down ,時間(半角・分)}*/
        {"起床","出発準備、朝食",0, 0, 0, 60},
        {"京大出発", "", 40, 300, 200, 90},
        {"豊中キャンパス", "", -1, -1, -1, 10},
        {"ガンガ", "昼食", 0, 0, 0, 60},
        {"ガンガ出発", "", 237, 3624, 3000, 60*9+30},
        {"恋山形駅", "休憩", 0, 0, 0, 30},
        

// ~~~~~~~~~~~~~~~~~~~~ここより上を編集~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        {"就寝","",0}
    };

    /* スケジュール計算 */
    calculateSchedule(start, processes, sizeof(processes)/sizeof(processes[0]));
    
    return 0;
}


