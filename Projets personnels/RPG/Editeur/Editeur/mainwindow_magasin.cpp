#include "mainwindow.h"
#include "ui_mainwindow.h"

extern Objet*          objets[NOMBRE_OBJETS+1];
extern Magasin*        magasins[NOMBRE_MAGASINS+1];

Magasin* MainWindow::getMagasin(int row) const {
    int currentRow = (row == -1) ? ui->magasin_listWidget->currentRow() : row;
    if (currentRow < 0 || currentRow >= NOMBRE_MAGASINS || magasins[currentRow+1] == NULL)
        return NULL;
    return magasins[currentRow+1];
}

void MainWindow::setMagasinLabel(Magasin* magasin) {
    char data[32];
    magasin->Ecrire(data);
    ui->magasin_label->setText(latintoQString(data));
}

bool MainWindow::getMagasinNombreBounds(int row) const {
    Magasin* magasin = getMagasin();
    if (magasin == NULL)
        return true;
    return row < 0 || row >= ui->magasin_nombre_spinBox->value() || row >= magasin->GetNombre();
}

void MainWindow::on_magasin_listWidget_currentRowChanged(int currentRow) {
    Magasin* magasin = getMagasin(currentRow);
    if (magasin == NULL)
        return;
    ui->magasin_objet_listWidget->clear();
    for (unsigned char i = 0; i < magasin->GetNombre(); ++i)
        ui->magasin_objet_listWidget->addItem(latintoQString(magasin->GetNom(i))+QString("\t\t")+QString::number(magasin->GetPrix(i)));
    ui->magasin_nombre_spinBox->setValue(magasin->GetNombre());
    ui->magasin_objet_listWidget->setCurrentRow(0);
    setMagasinLabel(magasin);
}

void MainWindow::on_magasin_spinBox_valueChanged(int arg1) {
    int i = ui->magasin_listWidget->count();
    while (arg1 > i) {
        magasins[i+1] = new Magasin(i+1);
        ui->magasin_listWidget->addItem(QString::number(magasins[i+1]->GetId()));
        ++i;
    }
    while (arg1 < i) {
        QMessageBox::StandardButton reponse(QMessageBox::question(this,\
            "Confirmer", MESSAGE_CONFIRMATION,\
            QMessageBox::Yes | QMessageBox::No));
        if (reponse == QMessageBox::No) {
            ui->magasin_spinBox->setValue(i);
            return;
        }
        delete magasins[i];
        magasins[i] = NULL;
        delete ui->magasin_listWidget->takeItem(i-1);
        --i;
    }
}

void MainWindow::on_magasin_nombre_spinBox_valueChanged(int arg1) {
    Magasin* magasin = getMagasin();
    if (magasin == NULL)
        return;
    int i = ui->magasin_objet_listWidget->count();
    while (arg1 > i) {
        magasin->SetNombre(i+1);
        ui->magasin_objet_listWidget->addItem(latintoQString(magasin->GetNom(i)));
        ui->magasin_listWidget->currentItem()->setText(QString::number(magasin->GetId()));
        ++i;
        setMagasinLabel(magasin);
    }
    while (arg1 < i) {
        QMessageBox::StandardButton reponse(QMessageBox::question(this,\
            "Confirmer", MESSAGE_CONFIRMATION,\
            QMessageBox::Yes | QMessageBox::No));
        if (reponse == QMessageBox::No) {
            ui->magasin_nombre_spinBox->setValue(i);
            return;
        }
        magasin->SetNombre(i-1);
        delete ui->magasin_objet_listWidget->takeItem(i-1);
        ui->magasin_listWidget->currentItem()->setText(QString::number(magasin->GetId()));
        --i;
        setMagasinLabel(magasin);
    }
}

void MainWindow::update_magasin_objet_comboBox(unsigned int nombre) {
    ui->magasin_objet_comboBox->clear();
    for (unsigned int i = 1; i < nombre+1; ++i) {
        if (objets[i] == 0)
            break; // pas de discontinuité entre comboxBox.index et objet.id
        ui->magasin_objet_comboBox->addItem(latintoQString(objets[i]->GetNom()));
    }
}

void MainWindow::on_magasin_objet_comboBox_currentIndexChanged(int index) {
    Magasin* magasin = getMagasin();
    if (magasin == NULL)
        return;
    int currentRow2 = ui->magasin_objet_listWidget->currentRow();
    if (getMagasinNombreBounds(currentRow2))
        return;
    magasin->SetObjets(objets[index+1],currentRow2);
    ui->magasin_objet_listWidget->currentItem()->setText(latintoQString(magasin->GetNom(currentRow2))+QString("\t\t")+QString::number(magasin->GetPrix(currentRow2)));
    ui->magasin_listWidget->currentItem()->setText(QString::number(magasin->GetId()));
    setMagasinLabel(magasin);
}

void MainWindow::update_magasin_objet_listWidget(const Objet* objet) {
    Magasin* magasin = getMagasin();
    if (magasin == NULL)
        return;
    const int id = objet->GetId();
    for (unsigned char i = 0; i < magasin->GetNombre(); ++i)
        if (magasin->GetObjets(i)->GetId() == id)
            ui->magasin_objet_listWidget->item(i)->setText(latintoQString(magasin->GetNom(i))+QString("\t\t")+QString::number(magasin->GetPrix(i)));
}

void MainWindow::on_magasin_objet_listWidget_currentRowChanged(int currentRow) {
    Magasin* magasin = getMagasin();
    if (magasin == NULL)
        return;
    if (getMagasinNombreBounds(currentRow))
        return;
    ui->magasin_objet_comboBox->setCurrentIndex(magasin->GetObjets(currentRow)->GetId()-1);
}

void MainWindow::on_magasin_objet_listWidget_itemDoubleClicked(QListWidgetItem *item) {
    Magasin* magasin = getMagasin();
    if (magasin == NULL)
        return;
    if (item->isSelected() == false)
        return;
    int currentRow = ui->magasin_objet_listWidget->currentRow();
    if (getMagasinNombreBounds(currentRow))
        return;
    ui->tabWidget->setCurrentIndex(9);
    ui->objet_listWidget->setCurrentRow(magasin->GetObjets(currentRow)->GetId()-1);
}
