#include "ShaderEditDialog.h"
#include "QLabel"
#include "ShaderManager.h"
#include <QComboBox>

namespace Rain
{

	ShaderEditDialog::ShaderEditDialog()
		:QDialog()
	{
		setWindowTitle("Shader Edit");
		m_ui.setupUi(this);

		std::set<std::string> shadernames = ShaderManager::singleton().listShaders();

		for (std::string shadername : shadernames)
		{
			m_ui.comboBox->addItem( QString::fromStdString(shadername) );
		}

		connect(m_ui.comboBox, QOverload<const QString&>::of(&QComboBox::currentIndexChanged),
			[=](const QString &text) {
			std::string shaderContent;
			if (ShaderManager::singleton().getShader(text.toStdString(), shaderContent))
				m_ui.textEdit->setText(QString::fromStdString(shaderContent));
		}
		);
	}

	void ShaderEditDialog::onItemSelect(const QString& name)
	{
		std::string shaderContent;
		if(ShaderManager::singleton().getShader(name.toStdString(), shaderContent))
			m_ui.textEdit->setText(QString::fromStdString(shaderContent));
	}


	ShaderEditDialog::~ShaderEditDialog()
	{
	}

}
