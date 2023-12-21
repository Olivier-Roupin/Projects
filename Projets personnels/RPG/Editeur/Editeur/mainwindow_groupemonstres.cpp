#include "mainwindow.h"
#include "ui_mainwindow.h"

extern Monstre*        monstres[NOMBRE_MONSTRES+1];
extern GroupeMonstres* groupes_monstres[NOMBRE_GROUPES_MONSTRES+1];

GroupeMonstres* MainWindow::getGroupeMonstres(int row) const {
    int currentRow = (row == -1) ? ui->groupesmonstre_listWidget->currentRow() : row;
    if (currentRow < 0 || currentRow >= NOMBRE_GROUPES_MONSTRES || groupes_monstres[currentRow+1] == NULL)
        return NULL;
    return groupes_monstres[currentRow+1];
}

void MainWindow::setGroupeMonstresLabel(GroupeMonstres* groupe_monstres) {
    char data[64];
    groupe_monstres->Ecrire(data);
    ui->groupesmonstre_label->setText(latintoQString(data));
}

bool MainWindow::getGroupeMonstresNombreBounds(int row) const {
    GroupeMonstres* groupe_monstres = getGroupeMonstres();
    if (groupe_monstres == NULL)
        return true;
    return row < 0 || row >= ui->groupesmonstre_nombre_spinBox->value() || row >= groupe_monstres->GetNombre();
}

void MainWindow::on_groupesmonstre_listWidget_currentRowChanged(int currentRow) {
    GroupeMonstres* groupe_monstres = getGroupeMonstres(currentRow);
    if (groupe_monstres == NULL)
        return;
    ui->groupesmonstre_monstre_listWidget->clear();
    for (unsigned char i = 0; i < groupe_monstres->GetNombre(); ++i)
        if (groupe_monstres->GetMonstres(i))
            ui->groupesmonstre_monstre_listWidget->addItem(latintoQString(groupe_monstres->GetMonstres(i)->GetNom()));
    ui->groupesmonstre_nombre_spinBox->setValue(groupe_monstres->GetNombre());
    ui->groupesmonstre_monstre_listWidget->setCurrentRow(0);
    setGroupeMonstresLabel(groupe_monstres);
}

void MainWindow::on_groupesmonstre_spinBox_valueChanged(int arg1) {
    int i = ui->groupesmonstre_listWidget->count();
    while (arg1 > i) {
        groupes_monstres[i+1] = new GroupeMonstres(i+1);
        ui->groupesmonstre_listWidget->addItem(QString::number(groupes_monstres[i+1]->GetId()));
        ++i;
    }
    while (arg1 < i) {
        QMessageBox::StandardButton reponse(QMessageBox::question(this,\
            "Confirmer", MESSAGE_CONFIRMATION,\
            QMessageBox::Yes | QMessageBox::No));
        if (reponse == QMessageBox::No) {
            ui->groupesmonstre_spinBox->setValue(i);
            return;
        }
        delete groupes_monstres[i];
        groupes_monstres[i] = NULL;
        delete ui->groupesmonstre_listWidget->takeItem(i-1);
        --i;
    }
}

void MainWindow::on_groupesmonstre_nombre_spinBox_valueChanged(int arg1) {
    GroupeMonstres* groupe_monstres = getGroupeMonstres();
    if (groupe_monstres == NULL)
        return;
    int i = ui->groupesmonstre_monstre_listWidget->count();
    while (arg1 > i) {
        groupe_monstres->SetNombre(i+1);
        ui->groupesmonstre_monstre_listWidget->addItem(latintoQString(groupe_monstres->GetMonstres(i)->GetNom()));
        ui->groupesmonstre_listWidget->currentItem()->setText(QString::number(groupe_monstres->GetId()));
        ++i;
        setGroupeMonstresLabel(groupe_monstres);
    }
    while (arg1 < i) {
        QMessageBox::StandardButton reponse(QMessageBox::question(this,\
            "Confirmer", MESSAGE_CONFIRMATION,\
            QMessageBox::Yes | QMessageBox::No));
        if (reponse == QMessageBox::No) {
            ui->groupesmonstre_nombre_spinBox->setValue(i);
            return;
        }
        groupe_monstres->SetNombre(i-1);
        delete ui->groupesmonstre_monstre_listWidget->takeItem(i-1);
        ui->groupesmonstre_listWidget->currentItem()->setText(QString::number(groupe_monstres->GetId()));
        --i;
        setGroupeMonstresLabel(groupe_monstres);
    }
}

void MainWindow::on_groupesmonstre_monstre_comboBox_currentIndexChanged(int index) {
    GroupeMonstres* groupe_monstres = getGroupeMonstres();
    if (groupe_monstres == NULL)
        return;
    int currentRow2 = ui->groupesmonstre_monstre_listWidget->currentRow();
    if (getGroupeMonstresNombreBounds(currentRow2))
        return;
    groupe_monstres->SetMonstres(monstres[index+1],currentRow2);
    ui->groupesmonstre_monstre_listWidget->currentItem()->setText(latintoQString(groupe_monstres->GetMonstres(currentRow2)->GetNom()));
    ui->groupesmonstre_listWidget->currentItem()->setText(QString::number(groupe_monstres->GetId()));
    setGroupeMonstresLabel(groupe_monstres);
}

void MainWindow::on_groupesmonstre_x_spinBox_valueChanged(int arg1) {
    GroupeMonstres* groupe_monstres = getGroupeMonstres();
    if (groupe_monstres == NULL)
        return;
    int currentRow2 = ui->groupesmonstre_monstre_listWidget->currentRow();
    if (getGroupeMonstresNombreBounds(currentRow2))
        return;
    groupe_monstres->SetX(arg1,currentRow2);
    setGroupeMonstresLabel(groupe_monstres);
}

void MainWindow::on_groupesmonstre_y_spinBox_valueChanged(int arg1) {
    GroupeMonstres* groupe_monstres = getGroupeMonstres();
    if (groupe_monstres == NULL)
        return;
    int currentRow2 = ui->groupesmonstre_monstre_listWidget->currentRow();
    if (getGroupeMonstresNombreBounds(currentRow2))
        return;
    groupe_monstres->SetY(arg1,currentRow2);
    setGroupeMonstresLabel(groupe_monstres);
}

void MainWindow::on_groupesmonstre_monstre_listWidget_currentRowChanged(int currentRow) {
    GroupeMonstres* groupe_monstres = getGroupeMonstres();
    if (groupe_monstres == NULL)
        return;
    if (getGroupeMonstresNombreBounds(currentRow))
        return;
    ui->groupesmonstre_monstre_comboBox->setCurrentIndex(groupe_monstres->GetMonstres(currentRow)->GetId()-1);
    ui->groupesmonstre_x_spinBox->setValue(groupe_monstres->GetX(currentRow));
    ui->groupesmonstre_y_spinBox->setValue(groupe_monstres->GetY(currentRow));
}

void MainWindow::on_groupesmonstre_monstre_listWidget_itemDoubleClicked(QListWidgetItem *item) {
    GroupeMonstres* groupe_monstres = getGroupeMonstres();
    if (groupe_monstres == NULL)
        return;
    if (item->isSelected() == false)
        return;
    int currentRow = ui->groupesmonstre_monstre_listWidget->currentRow();
    if (getGroupeMonstresNombreBounds(currentRow))
        return;
    ui->tabWidget->setCurrentIndex(8);
    ui->monstre_listWidget->setCurrentRow(groupe_monstres->GetMonstres(currentRow)->GetId()-1);
}
