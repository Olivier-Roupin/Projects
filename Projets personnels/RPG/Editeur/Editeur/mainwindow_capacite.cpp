#include "mainwindow.h"
#include "ui_mainwindow.h"

extern Effet*          effets[NOMBRE_EFFETS+1];
extern Capacite*       capacites[NOMBRE_CAPACITES+1];

Capacite* MainWindow::getCapacite(int row) const {
    int currentRow = (row == -1) ? ui->capacite_listWidget->currentRow() : row;
    if (currentRow < 0 || currentRow >= NOMBRE_CAPACITES || capacites[currentRow+1] == NULL)
        return NULL;
    return capacites[currentRow+1];
}

void MainWindow::setCapaciteLabel(Capacite* capacite) {
    char data[64];
    capacite->Ecrire(data);
    ui->capacite_label->setText(latintoQString(data));
}

void MainWindow::on_capacite_listWidget_currentRowChanged(int currentRow) {
    Capacite* capacite = getCapacite(currentRow);
    if (capacite == NULL)
        return;
    setCapaciteLabel(capacite);
    ui->capacite_nom_lineEdit->setText(latintoQString(capacite->GetNom()));
    ui->capacite_description_lineEdit->setText(latintoQString(capacite->GetDescription()));
    ui->capacite_coutmagie_spinBox->setValue(capacite->GetCoutMagie());
    ui->capacite_coutmagiep_spinBox->setValue(capacite->GetCoutMagieP());
    ui->capacite_coutvie_spinBox->setValue(capacite->GetCoutVie());
    ui->capacite_coutviep_spinBox->setValue(capacite->GetCoutVieP());
    ui->capacite_id_spinBox->setValue(capacite->GetEffet() ? capacite->GetEffet()->GetId() : 0);
}

void MainWindow::on_capacite_spinBox_valueChanged(int arg1) {
    int i = ui->capacite_listWidget->count();
    while (arg1 > i) {
        capacites[i+1] = new Capacite(i+1, "Sans nom");
        ui->capacite_listWidget->addItem(latintoQString(capacites[i+1]->GetNom()));
        ++i;
    }
    while (arg1 < i) {
        QMessageBox::StandardButton reponse(QMessageBox::question(this,\
            "Confirmer", MESSAGE_CONFIRMATION,\
            QMessageBox::Yes | QMessageBox::No));
        if (reponse == QMessageBox::No) {
            ui->capacite_spinBox->setValue(i);
            return;
        }
        delete capacites[i];
        capacites[i] = NULL;
        delete ui->capacite_listWidget->takeItem(i-1);
        --i;
    }
}

void MainWindow::on_capacite_nom_lineEdit_textEdited(const QString &arg1) {
    Capacite* capacite = getCapacite();
    if (capacite == NULL)
        return;
    capacite->SetNom(arg1.toStdString().c_str());
    ui->capacite_listWidget->currentItem()->setText(arg1);
    setCapaciteLabel(capacite);
}

void MainWindow::on_capacite_description_lineEdit_textEdited(const QString &arg1) {
    Capacite* capacite = getCapacite();
    if (capacite == NULL)
        return;
    capacite->SetDescription(arg1.toStdString().c_str());
    setCapaciteLabel(capacite);
}

void MainWindow::on_capacite_coutmagie_spinBox_valueChanged(int arg1) {
    Capacite* capacite = getCapacite();
    if (capacite == NULL)
        return;
    capacite->SetCoutMagie(arg1);
    setCapaciteLabel(capacite);
}

void MainWindow::on_capacite_coutmagiep_spinBox_valueChanged(int arg1) {
    Capacite* capacite = getCapacite();
    if (capacite == NULL)
        return;
    capacite->SetCoutMagieP(arg1);
    setCapaciteLabel(capacite);
}

void MainWindow::on_capacite_coutvie_spinBox_valueChanged(int arg1) {
    Capacite* capacite = getCapacite();
    if (capacite == NULL)
        return;
    capacite->SetCoutVie(arg1);
    setCapaciteLabel(capacite);
}

void MainWindow::on_capacite_coutviep_spinBox_valueChanged(int arg1) {
    Capacite* capacite = getCapacite();
    if (capacite == NULL)
        return;
    capacite->SetCoutVieP(arg1);
    setCapaciteLabel(capacite);
}

void MainWindow::on_capacite_id_spinBox_valueChanged(int arg1) {
    Capacite* capacite = getCapacite();
    if (capacite == NULL)
        return;
    capacite->SetEffet(effets[arg1]);
    setCapaciteLabel(capacite);
}
