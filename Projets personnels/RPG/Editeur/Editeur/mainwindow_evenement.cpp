#include "mainwindow.h"
#include "ui_mainwindow.h"

extern Evenement*      evenements[NOMBRE_EVENEMENTS+1];

Evenement* MainWindow::getEvenement(int row) const {
    int currentRow = (row == -1) ? ui->evenement_listWidget->currentRow() : row;
    if (currentRow < 0 || currentRow >= NOMBRE_EVENEMENTS || evenements[currentRow+1] == NULL)
        return NULL;
    return evenements[currentRow+1];
}

void MainWindow::setEvenementLabel(Evenement* evenement) {
    char data[16];
    evenement->Ecrire(data);
    ui->evenement_label->setText(latintoQString(data));
}

bool MainWindow::getEvenementNombreBounds(int row) const {
    Evenement* evenement = getEvenement();
    if (evenement == NULL)
        return true;
    return row < 0 || row >= ui->evenement_nombre_spinBox->value() || row >= evenement->GetNombre();
}

void MainWindow::on_evenement_listWidget_currentRowChanged(int currentRow) {
    Evenement* evenement = getEvenement(currentRow);
    if (evenement == NULL)
        return;
    ui->evenement_image_lineEdit->setText(latintoQString(evenement->GetImage()));
    ui->evenement_script_listWidget->clear();
    for (unsigned char i = 0; i < evenement->GetNombre(); ++i)
        ui->evenement_script_listWidget->addItem(QString::number(evenement->GetScripts(i) ? evenement->GetScripts(i)->GetId() : 0));
    ui->evenement_nombre_spinBox->setValue(evenement->GetNombre());
    ui->evenement_script_listWidget->setCurrentRow(0);    //ui->evenement_script_spinBox->setValue(evenement->GetScripts(0)->GetId());
    setEvenementLabel(evenement);
}

void MainWindow::on_evenement_spinBox_valueChanged(int arg1) {
    int i = ui->evenement_listWidget->count();
    while (arg1 > i) {
        evenements[i+1] = new Evenement(i+1);
        ui->evenement_listWidget->addItem(QString::number(evenements[i+1]->GetId()));
        ++i;
    }
    while (arg1 < i) {
        QMessageBox::StandardButton reponse(QMessageBox::question(this,\
            "Confirmer", MESSAGE_CONFIRMATION,\
            QMessageBox::Yes | QMessageBox::No));
        if (reponse == QMessageBox::No) {
            ui->evenement_spinBox->setValue(i);
            return;
        }
        delete evenements[i];
        evenements[i] = NULL;
        delete ui->evenement_listWidget->takeItem(i-1);
        --i;
    }
}

void MainWindow::on_evenement_script_listWidget_currentRowChanged(int currentRow) {
    Evenement* evenement = getEvenement();
    if (evenement == NULL)
        return;
    if (getEvenementNombreBounds(currentRow))
        return;
    ui->evenement_script_spinBox->setValue(evenement->GetScripts(currentRow) ? evenement->GetScripts(currentRow)->GetId() : 0);
}

void MainWindow::on_evenement_script_spinBox_valueChanged(int arg1) {
    Evenement* evenement = getEvenement();
    if (evenement == NULL)
        return;
    int currentRow2 = ui->evenement_script_listWidget->currentRow();
    if (getEvenementNombreBounds(currentRow2))
        return;
    evenement->SetScripts(scripts[arg1],currentRow2);
    ui->evenement_script_listWidget->currentItem()->setText(QString::number(arg1));
    setEvenementLabel(evenement);
}

void MainWindow::on_evenement_nombre_spinBox_valueChanged(int arg1) {
    Evenement* evenement = getEvenement();
    if (evenement == NULL)
        return;
    int i = ui->evenement_script_listWidget->count();
    while (arg1 > i) {
        //evenements[i+1] = new Evenement(i+1);
        //ui->evenement_listWidget->addItem(QString::number(evenements[i+1]->GetId()));
        evenement->SetNombre(i+1); //evenement->SetScripts(NULL,i);
        ui->evenement_script_listWidget->addItem(QString::number(evenement->GetScripts(i)->GetId()));
        ++i;
        setEvenementLabel(evenement);
    }
    while (arg1 < i) {
        QMessageBox::StandardButton reponse(QMessageBox::question(this,\
            "Confirmer", MESSAGE_CONFIRMATION,\
            QMessageBox::Yes | QMessageBox::No));
        if (reponse == QMessageBox::No) {
            ui->evenement_nombre_spinBox->setValue(i);
            return;
        }
        //delete evenements[i];
        //evenements[i] = NULL;
        evenement->SetNombre(i-1);
        delete ui->evenement_script_listWidget->takeItem(i-1);
        --i;
        setEvenementLabel(evenement);
    }
}

void MainWindow::on_evenement_image_lineEdit_textEdited(const QString &arg1) {
    Evenement* evenement = getEvenement();
    if (evenement == NULL)
        return;
    evenement->SetImage(arg1.toStdString().c_str());
    setEvenementLabel(evenement);
}
