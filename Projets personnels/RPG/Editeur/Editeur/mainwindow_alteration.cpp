#include "mainwindow.h"
#include "ui_mainwindow.h"

extern Script*         scripts[NOMBRE_SCRIPTS+1];
extern Alteration*     alterations[NOMBRE_ALTERATIONS+1];

Alteration* MainWindow::getAlteration(int row) const {
    int currentRow = (row == -1) ? ui->alteration_listWidget->currentRow() : row;
    if (currentRow < 0 || currentRow >= NOMBRE_ALTERATIONS || alterations[currentRow+1] == NULL)
        return NULL;
    return alterations[currentRow+1];
}

void MainWindow::setAlterationLabel(Alteration* alteration) {
    char data[64];
    alteration->Ecrire(data);
    ui->alteration_label->setText(latintoQString(data));
}

void MainWindow::on_alteration_listWidget_currentRowChanged(int currentRow) {
    Alteration* alteration = getAlteration(currentRow);
    if (alteration == NULL)
        return;
    setAlterationLabel(alteration);
    ui->alteration_nom_lineEdit->setText(latintoQString(alteration->GetNom()));
    ui->alteration_id_spinBox->setValue(alteration->GetScript() ? alteration->GetScript()->GetId() : 0);
    ui->alteration_postcombat_checkBox->setChecked(alteration->GetPostCombat());
    ui->alteration_postdeces_checkBox->setChecked(alteration->GetPostDeces());
    ui->alteration_priorite_spinBox->setValue(alteration->GetPriorite());
    ui->alteration_id_terrain_spinBox->setValue(alteration->GetScriptTerrain() ? alteration->GetScriptTerrain()->GetId() : 0);
}

void MainWindow::on_alteration_spinBox_valueChanged(int arg1) {
    int i = ui->alteration_listWidget->count();
    while (arg1 > i) {
        alterations[i+1] = new Alteration(i+1, "Sans nom");
        ui->alteration_listWidget->addItem(latintoQString(alterations[i+1]->GetNom()));
        ++i;
    }
    while (arg1 < i) {
        QMessageBox::StandardButton reponse(QMessageBox::question(this,\
            "Confirmer", MESSAGE_CONFIRMATION,\
            QMessageBox::Yes | QMessageBox::No));
        if (reponse == QMessageBox::No) {
            ui->alteration_spinBox->setValue(i);
            return;
        }
        delete alterations[i];
        alterations[i] = NULL;
        delete ui->alteration_listWidget->takeItem(i-1);
        --i;
    }
}

void MainWindow::on_alteration_nom_lineEdit_textEdited(const QString &arg1) {
    Alteration* alteration = getAlteration();
    if (alteration == NULL)
        return;
    alteration->SetNom(arg1.toStdString().c_str());
    ui->alteration_listWidget->currentItem()->setText(arg1);
    setAlterationLabel(alteration);
}

void MainWindow::on_alteration_id_spinBox_valueChanged(int arg1) {
    Alteration* alteration = getAlteration();
    if (alteration == NULL)
        return;
    alteration->SetScript(scripts[arg1]);
    setAlterationLabel(alteration);
}

void MainWindow::on_alteration_postcombat_checkBox_clicked(bool checked) {
    Alteration* alteration = getAlteration();
    if (alteration == NULL)
        return;
    alteration->SetPostCombat(checked);
    setAlterationLabel(alteration);
}

void MainWindow::on_alteration_postdeces_checkBox_clicked(bool checked) {
    Alteration* alteration = getAlteration();
    if (alteration == NULL)
        return;
    alteration->SetPostDeces(checked);
    setAlterationLabel(alteration);
}

void MainWindow::on_alteration_priorite_spinBox_valueChanged(int arg1) {
    Alteration* alteration = getAlteration();
    if (alteration == NULL)
        return;
    alteration->SetPriorite(arg1);
    setAlterationLabel(alteration);
}

void MainWindow::on_alteration_id_terrain_spinBox_valueChanged(int arg1) {
    Alteration* alteration = getAlteration();
    if (alteration == NULL)
        return;
    alteration->SetScriptTerrain(scripts[arg1]);
    setAlterationLabel(alteration);
}
