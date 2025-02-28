#include "calcui.h"
#include "ui_calcui.h"
#include "logic.h"

CalcUI::CalcUI(QWidget *parent) : QWidget(parent), ui(new Ui::CalcUI)
{
    ui->setupUi(this);
    setFixedSize(450, 650);
    QPalette pal = palette();
    pal.setBrush(QPalette::Window, QBrush(QColor(245, 245, 220), Qt::SolidPattern));
    setPalette(pal);

    connect(ui->nums_group, QOverload<QAbstractButton *>::of(&QButtonGroup::buttonClicked), this, &CalcUI::onNumsBtnClicked);
}

CalcUI::~CalcUI() { delete ui; }

void CalcUI::onNumsBtnClicked(QAbstractButton *btn)
{
    ui->lineEdit->insert(btn->text());

}

void CalcUI::on_pushButton_13_clicked()
{
    string expression = ui->lineEdit->text().toStdString();
    vector<string> tokens = get_token(expression);
    vector<string> postfix = convert_to_postfix(tokens);
    double result = calculate_postfix(postfix);
    ui->lineEdit->setText(QString::number(result));
}

void CalcUI::on_pushButton_15_clicked()
{
    ui->lineEdit->setText("");
}
