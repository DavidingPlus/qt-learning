#ifndef MYBUTTON_H
#define MYBUTTON_H

#include <QPushButton>

enum BtnsType {
    blank,
    flag,
    ask
};

class MyButton : public QPushButton {
    Q_OBJECT
public:
    explicit MyButton(QWidget* parent = nullptr);

    bool _isFlagMax = false; //flag数量是否达到上限

    bool _isMine = false;//默认为否表示下面不为雷 如果为雷左键点击则触发雷

    int _Minearound = 0; //周围雷的数量

    bool _is_handled = false; //有没有被处理过,这一点在后面递归的时候非常有用

    void __init__();
protected:
    void mousePressEvent(QMouseEvent* e);//鼠标点击事件

signals:
    void flag_changed(bool ok);//true代表 减1 false 代表加1

    void gameisover();//踩到雷 游戏结束信号

    void isClicked();//处理被点击之后
private:
    int _type = blank; //按钮现在所处的状态
};

#endif // MYBUTTON_H
