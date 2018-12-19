#pragma once
#include <QDialog>
#include "ui_ShaderEditDialog.h"


namespace Rain
{

	class ShaderEditDialog : public QDialog
	{
		Q_OBJECT;

	public:
		ShaderEditDialog();
		~ShaderEditDialog();

	public slots:
		void onItemSelect(const QString& name);
        void onApplyClicked(bool bChecked = false);
        void onCancelClicked(bool bChecked = false);

    signals:
        void shaderChanged();

	private:
		Ui::Dialog m_ui;
        std::string m_curShaderName;
	};

}