#include "listdialog.h"
#include "ui_listdialog.h"

listDialog::listDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::listDialog)
{
    ui->setupUi(this);

    ldmedialist = QStringList();
    ldboollist = QStringList();

    medialist_model = new QStandardItemModel();
    medialist_model->setHorizontalHeaderItem(0, new QStandardItem(QObject::tr("Name")));

    //利用setModel()方法将数据模型与QTableView绑定
    ui->listtableView->setModel(medialist_model);
    //设置列宽不可变动，即不能通过鼠标拖动增加列宽
    ui->listtableView->horizontalHeader()->resizeSections(QHeaderView::Fixed);
    //设置表格的各列的宽度值
    ui->listtableView->setColumnWidth(0,300);
    //设置选中时为整行选中
    ui->listtableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    //设置表格的单元为只读属性，即不能编辑
    ui->listtableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //如果你用在QTableView中使用右键菜单，需启用该属性
    ui->listtableView->setContextMenuPolicy(Qt::CustomContextMenu);
}

listDialog::~listDialog()
{
    delete ui;
    delete medialist_model;
}

void listDialog::list()
{
    for(int i=0; i<ldmedialist.size(); i++)
    {
        medialist_model->setItem(i, 0, new QStandardItem(ldmedialist[i]));
    }
}

void listDialog::additem(QString item, QString itembool)
{
    bool has = false;
    for(int i=0; i<ldmedialist.size(); i++)
    {
        if(item == ldmedialist[i])
            has = true;
    }
    if(!has)
    {
        ldmedialist<<item;
        ldboollist<<itembool;
    }
}

void listDialog::on_listtableView_doubleClicked(const QModelIndex &index)
{
    QVariant tempValue = ldboollist[index.row()];
    bool tempFinished = tempValue.toBool();
    emit listPlay(tempFinished, index.data().toString());
}

void listDialog::closeEvent(QCloseEvent *event)
{
    emit listclose();
}
