#include "ShaderEditDialog.h"
#include "QLabel"


ShaderEditDialog::ShaderEditDialog()
    :QDialog()
{
    setWindowTitle("Shader Edit");
    m_ui.setupUi(this);

}


ShaderEditDialog::~ShaderEditDialog()
{
}
