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
    char *distance; // 工程の距離
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

    for (int i = 0; i < numProcesses; i++) {
        printf("%02d:%02d %s\n",currentTime.hours, currentTime.minutes, processes[i].event);
        if (i == numProcesses - 1) break; // 最後の工程の場合↓を表示しない
        /* 固定の時間の表示の判別(minかhか) */
        int judge = processes[i].duration % 60;
        /* 移動時間が0の場合 */
        if (processes[i].duration == 0) {
            judge = 1;
        }
        int hour = processes[i].duration / 60;
        switch(judge) {
            case 0: /* h 表示 */
                printf("  ↓%s %dh\n", processes[i].distance, hour);
                break;
            case 30: /*n.5h */
                printf("  ↓%s %d.5h\n", processes[i].distance, hour);
                break;
            case 1: /* 移動時間が0 */
                printf("  ↓%s \n", processes[i].distance);
                break;
            default:
                printf("  ↓%s %dmin\n", processes[i].distance, processes[i].duration);
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

    Processs[]の定義で第一引数に場所，第二引数に距離，アップや昼食，買い出しなどの情報，
    第三引数に時間を書く．ここで注意なのが時間は必ず"半角"で"分"換算の時間を書くこと．
    全角で書くとうまく動きません．
    
    Process processes[] = {
        {"場所", "距離やupの情報", 時間(半角)}
        ...
    }
    

    例えば　大阪大学 豊中キャンパス
            ↓  12km 348up 31down 50min
            勝尾寺
            ...
            ~~~~

    と入力したいときは

            (大阪大学 豊中キャンパス)*1
            ↓  (12km 348up 31down)*2 (50)*3 min
            勝尾寺

    のように3つのパーツに分けて

    Process processes[] = {
        {"大阪大学 豊中キャンパス", "12km 348up 31down", 50},
        {"勝尾寺", "...", ...}
        ...
    }

    のように入力すればよい
*/
// ~~~~~~~~~~~~~~~~~~~~ここより下を編集~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    /* 1         {時,分}  */
    Time start = {6, 0}; // 開始時刻

    /* 工程データのリスト */
    Process processes[] = {
    /* 2 {"場所", "情報", 時間(半角・分)}*/
        {"ガンガ","昼食", 80},
        

// ~~~~~~~~~~~~~~~~~~~~ここより上を編集~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        {"就寝","",0}
    };

    /* スケジュール計算 */
    calculateSchedule(start, processes, sizeof(processes)/sizeof(processes[0]));
    
    return 0;
}


