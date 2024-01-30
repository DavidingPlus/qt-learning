#include "widget.h"
#include "./ui_widget.h"

Widget::Widget(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::Widget) {
    ui->setupUi(this);

    //数字按钮绑定
    connect(ui->num0, &QPushButton::clicked, [ = ]() {
        this->OnClicked(Num, "0");
    });
    connect(ui->num1, &QPushButton::clicked, [ = ]() {
        this->OnClicked(Num, "1");
    });
    connect(ui->num2, &QPushButton::clicked, [ = ]() {
        this->OnClicked(Num, "2");
    });
    connect(ui->num3, &QPushButton::clicked, [ = ]() {
        this->OnClicked(Num, "3");
    });
    connect(ui->num4, &QPushButton::clicked, [ = ]() {
        this->OnClicked(Num, "4");
    });
    connect(ui->num5, &QPushButton::clicked, [ = ]() {
        this->OnClicked(Num, "5");
    });
    connect(ui->num6, &QPushButton::clicked, [ = ]() {
        this->OnClicked(Num, "6");
    });
    connect(ui->num7, &QPushButton::clicked, [ = ]() {
        this->OnClicked(Num, "7");
    });
    connect(ui->num8, &QPushButton::clicked, [ = ]() {
        this->OnClicked(Num, "8");
    });
    connect(ui->num9, &QPushButton::clicked, [ = ]() {
        this->OnClicked(Num, "9");
    });

    //运算符按钮绑定
    connect(ui->Add, &QPushButton::clicked, [ = ]() {
        this->OnClicked(Op, "+");
    });
    connect(ui->Sub, &QPushButton::clicked, [ = ]() {
        this->OnClicked(Op, "-");
    });
    connect(ui->Mul, &QPushButton::clicked, [ = ]() {
        this->OnClicked(Op, "×");
    });
    connect(ui->Div, &QPushButton::clicked, [ = ]() {
        this->OnClicked(Op, "÷");
    });

    //其他按钮绑定
    connect(ui->Dot, &QPushButton::clicked, [ = ]() {
        this->OnClicked(Dot, ".");
    });
    connect(ui->Back, &QPushButton::clicked, [ = ]() {
        this->OnClicked(Back, "Back");//这个不显示
    });
    connect(ui->Clear, &QPushButton::clicked, [ = ]() {
        this->OnClicked(Clear, "Clear");//这个不显示
    });
    connect(ui->Equal, &QPushButton::clicked, [ = ]() {
        this->OnClicked(Equal, "=");//这个不显示
    });
    connect(ui->Sgn, &QPushButton::clicked, [ = ]() {
        this->OnClicked(Sgn, "+/-"); //这个不显示
    });
}

Widget::~Widget() {
    delete ui;
}


//用一个静态变量来记录等于号里面的结果
static QString _Value = QString();
static BtnType _Type = Null;
void Widget::OnClicked(BtnType _type, QString _btn) {   //点击按钮调用槽函数
    switch (_type) {
        case Num: { //数字
                if (this->op.isEmpty()) {      //如果op是空的表示是操作数1
                    this->num1 += _btn;
                    //这两步操作是为了解决整数部分0叠加的问题 就是00000002这种
                    if(!this->num1.contains('.')) { //注意加上不包含'.'表示是整数部分的条件
                        double Num1 = this->num1.toDouble();
                        this->num1 = QString::number(Num1);
                    }
                } else { //非空 则输入的是操作数2
                    this->num2 += _btn;
                    if(!this->num2.contains('.')) {
                        double Num2 = this->num2.toDouble();
                        this->num2 = QString::number(Num2);
                    }
                }
                break;
            }
        case Op: { //操作数
                //操作数1不能为空 否则无法输入
                if(this->num1.isEmpty()) {
                    //但是这里面有一个特殊情况 就是按了等于再按操作符的情况 这个时候根据等于的计算 num1为空
                    if(_Type == Equal) { //实现等于之后接着计算
                        this->num1 = _Value;
                        ui->lineEdit->setText(_Value);
                        _Type = Null;//不要忘了把这个置为空
                        goto Next;//跳转到下面去
                    }
                    return;
                }
                //实现连算
                if(!this->op.isEmpty() && !this->num2.isEmpty()) { //把之前的结果算出来 并更新变量的值
                    this->OnClicked(Equal, "=");
                    this->num1 = _Value;
                    ui->lineEdit->setText(_Value);
                }
Next:
                this->op = _btn;
                break;
            }
        case Dot: { //点
                if (this->op.isEmpty()) {    //如果op是空的表示是操作数1
                    //要判断操作数有没有点并且是不是为空
                    if(!this->num1.isEmpty() && !this->num1.contains('.'))  //contains 是否包含某个字符
                        this->num1 += _btn;
                } else {
                    if(!this->num2.isEmpty() && !this->num2.contains('.')) //contains 是否包含某个字符
                        this->num2 += _btn;
                }
                break;
            }
        case Equal: {//等于
                //判断异常 如果三个没值就没办法调用 =
                if(this->num1.isEmpty() || this->num2.isEmpty() || this->op.isEmpty())
                    return;
                //将字符转化为小数 toDouble
                double Num1 = this->num1.toDouble();
                double Num2 = this->num2.toDouble();
                double ans = 0;
                if(this->op == '+')
                    ans = Num1 + Num2;
                else if(this->op == '-')
                    ans = Num1 - Num2;
                else if(this->op == "×")
                    ans = Num1 * Num2;
                else if(this->op == "÷") {
                    if(Num2 == 0.0) {
                        ui->lineEdit->setText("除数不能为0");
                        //清除
                        this->num1.clear();
                        this->num2.clear();
                        this->op.clear();
                        return;
                    } else
                        ans = Num1 / Num2;
                }
                //显示运算结果
                _Value = QString::number(ans);
                _Type = Equal;
                ui->lineEdit->setText(_Value);
                //清除 这里不能直接调用函数 因为Clear执行完过后最后面会有个显示运算会把文本清空，但是我想让他呆在画面上
                this->num1.clear();
                this->num2.clear();
                this->op.clear();
                return;
            }
        case Back: {//退格
                if(!this->num1.isEmpty() && !this->num2.isEmpty()) //删除操作数2
                    this->num2.chop(1);//chop 删除n个字符
                else if(!this->num1.isEmpty() && !this->op.isEmpty()) //删除运算符
                    this->op.chop(1);
                else if(!this->num1.isEmpty())//删除操作数1
                    this->num1.chop(1);
                break;
            }
        case Clear: { //清除
                this->num1.clear();
                this->num2.clear();
                this->op.clear();
                break;
            }
        case Sgn: {//正负号
                if(this->num1.isEmpty())//num1为空 显然num2也为空
                    return;
                if(!this->num1.isEmpty() && this->op.isEmpty()) { //显然这时num2为空
                    double Num1 = this->num1.toDouble();
                    this->num1 = QString::number(-Num1);
                } else if(!this->num1.isEmpty() && !this->op.isEmpty() && !this->num2.isEmpty()) { //这时处理num2
                    double Num2 = this->num2.toDouble();
                    this->num2 = QString::number(-Num2);
                }
                break;
            }
        default:
            break;
    }
    //显示运算
    ui->lineEdit->setText(this->num1 + this->op + this->num2);
}


