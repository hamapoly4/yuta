#ifndef ___CLASS_CONTROL
#define ___CLASS_CONTROL    // インクルードカード

/* 抽象クラス定義 */
class Control {
public:
    static const unsigned char ALL_SIZE = 21;
    static const unsigned char LAP_SIZE = 7;
    static const unsigned char DOUBLE_SIZE = 14;

    /* 純粋仮想関数 */
    virtual int getTurn() = 0;  // モータの操作量を取得する関数

protected:
    int measured_value; // 観測値
    int diff;           // 偏差
    int old_diff;       // 過去の偏差
    int i;              // I制御をした回数
    int sum;            // 合計
    int Pvalue;         // P制御値
    int Ivalue;         // I制御値
    int Dvalue;         // D制御値
    int turn;           // 操作量

    /* コンストラクタ定義（インライン） */
    Control()
        : old_diff(0), i(0), sum(0)
    {
        ;
    }
};

#endif // ___CLASS_CONTROL
