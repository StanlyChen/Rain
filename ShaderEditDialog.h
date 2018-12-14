#pragma once
#include <QDialog>
#include "ui_ShaderEditDialog.h"

class ShaderEditDialog : public QDialog
{
    Q_OBJECT;

public:
    ShaderEditDialog();
    ~ShaderEditDialog();

private:
    Ui::Dialog m_ui;
};

