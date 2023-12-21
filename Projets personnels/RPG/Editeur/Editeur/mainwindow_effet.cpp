#include "mainwindow.h"
#include "ui_mainwindow.h"

extern Effet*          effets[NOMBRE_EFFETS+1];
extern Script*         scripts[NOMBRE_SCRIPTS+1];

Effet* MainWindow::getEffet(int row) const {
    int currentRow = (row == -1) ? ui->effet_listWidget->currentRow() : row;
    if (currentRow < 0 || currentRow >= NOMBRE_EFFETS || effets[currentRow+1] == NULL)
        return NULL;
    return effets[currentRow+1];
}

void MainWindow::setEffetLabel(Effet* effet) {
    char data[32];
    effet->Ecrire(data);
    ui->effet_label->setText(latintoQString(data));
}

void MainWindow::on_effet_listWidget_currentRowChanged(int currentRow) {
    Effet* effet = getEffet(currentRow);
    if (effet == NULL)
        return;
    setEffetLabel(effet);
    ui->effet_script_spinBox->setValue(effet->GetScript() ? effet->GetScript()->GetId() : 0);
    ui->effet_element_spinBox->setValue(effet->GetElement());
    ui->effet_disponibilite_comboBox->setCurrentIndex(effet->GetDisponibilite());
    ui->effet_choixcible_checkBox->setChecked(effet->GetChoix_Cible());
    ui->effet_choixfaction_checkBox->setChecked(effet->GetChoix_Faction());
    ui->effet_choixquantite_checkBox->setChecked(effet->GetChoix_Quantite());
    ui->effet_defautcible_comboBox->setCurrentIndex(-effet->GetDefaut_Cible());
    ui->effet_defautfaction_comboBox->setCurrentIndex(effet->GetDefaut_Faction());
    ui->effet_defautquantite_comboBox->setCurrentIndex(effet->GetDefaut_Quantite());
}

void MainWindow::on_effet_spinBox_valueChanged(int arg1) {
    int i = ui->effet_listWidget->count();
    while (arg1 > i) {
        effets[i+1] = new Effet(i+1);
        ui->effet_listWidget->addItem(QString(effets[i+1]->GetId()));
        ++i;
    }
    while (arg1 < i) {
        QMessageBox::StandardButton reponse(QMessageBox::question(this,\
            "Confirmer", MESSAGE_CONFIRMATION,\
            QMessageBox::Yes | QMessageBox::No));
        if (reponse == QMessageBox::No) {
            ui->effet_spinBox->setValue(i);
            return;
        }
        delete effets[i];
        effets[i] = NULL;
        delete ui->effet_listWidget->takeItem(i-1);
        --i;
    }
}

void MainWindow::on_effet_script_spinBox_valueChanged(int arg1) {
    Effet* effet = getEffet();
    if (effet == NULL)
        return;
    effet->SetScript(scripts[arg1]);
    setEffetLabel(effet);
}

void MainWindow::on_effet_element_spinBox_valueChanged(int arg1) {
    Effet* effet = getEffet();
    if (effet == NULL)
        return;
    effet->SetElement(arg1);
    setEffetLabel(effet);
}

void MainWindow::on_effet_disponibilite_comboBox_currentIndexChanged(int index) {
    Effet* effet = getEffet();
    if (effet == NULL)
        return;
    effet->SetDisponibilite(index);
    setEffetLabel(effet);
}

void MainWindow::on_effet_choixcible_checkBox_clicked(bool checked) {
    Effet* effet = getEffet();
    if (effet == NULL)
        return;
    effet->SetChoix_Cible(checked);
    setEffetLabel(effet);
}

void MainWindow::on_effet_choixfaction_checkBox_clicked(bool checked) {
    Effet* effet = getEffet();
    if (effet == NULL)
        return;
    effet->SetChoix_Faction(checked);
    setEffetLabel(effet);
}

void MainWindow::on_effet_choixquantite_checkBox_clicked(bool checked) {
    Effet* effet = getEffet();
    if (effet == NULL)
        return;
    effet->SetChoix_Quantite(checked);
    setEffetLabel(effet);
}

void MainWindow::on_effet_defautcible_comboBox_currentIndexChanged(int index) {
    Effet* effet = getEffet();
    if (effet == NULL)
        return;
    effet->SetDefaut_Cible(-index);
    setEffetLabel(effet);
}

void MainWindow::on_effet_defautfaction_comboBox_currentIndexChanged(int index) {
    Effet* effet = getEffet();
    if (effet == NULL)
        return;
    effet->SetDefaut_Faction(index);
    setEffetLabel(effet);
}

void MainWindow::on_effet_defautquantite_comboBox_currentIndexChanged(int index) {
    Effet* effet = getEffet();
    if (effet == NULL)
        return;
    effet->SetDefaut_Quantite(index);
    setEffetLabel(effet);
}
