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

	private:
		Ui::Dialog m_ui;
	};

}