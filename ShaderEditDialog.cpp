#include "ShaderEditDialog.h"
#include "QLabel"
#include "ShaderManager.h"
#include <QComboBox>
#include <QPushButton>
namespace Rain
{

	ShaderEditDialog::ShaderEditDialog()
		:QDialog( )
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
            onItemSelect(text);
        }
		);

        connect(m_ui.apply_btn, SIGNAL(clicked()), this, SLOT(onApplyClicked()));
        connect(m_ui.cancel_btn, SIGNAL(clicked()), this, SLOT(onCancelClicked()));
        onItemSelect(QString::fromStdString(*shadernames.begin()));
	}

    void ShaderEditDialog::onApplyClicked(bool bChecked /*= false*/)
    {
        std::string oldContent;
        ShaderManager::singleton().getShader(m_curShaderName, oldContent);
        std::string newContent = m_ui.textEdit->toPlainText().toStdString();
        if (newContent != oldContent)
        {
            ShaderManager::singleton().setShader(m_curShaderName, std::move(newContent), nullptr);
            emit shaderChanged( );
        }
    }

    void ShaderEditDialog::onCancelClicked(bool bChecked/* = false*/)
    {
        std::string shaderContent;
        if (ShaderManager::singleton().getShader(m_curShaderName, shaderContent))
            m_ui.textEdit->setText(QString::fromStdString(shaderContent));
    }

	void ShaderEditDialog::onItemSelect(const QString& name)
	{
        m_curShaderName = name.toStdString();
		std::string shaderContent;
		if(ShaderManager::singleton().getShader(m_curShaderName, shaderContent))
			m_ui.textEdit->setText(QString::fromStdString(shaderContent));
	}


	ShaderEditDialog::~ShaderEditDialog()
	{
	}

}
