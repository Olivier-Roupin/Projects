#include "mainwindow.h"
#include "ui_mainwindow.h"

extern Objet*          objets[NOMBRE_OBJETS+1];
extern Heros*          heross[NOMBRE_HEROS+1];

Heros* MainWindow::getHeros(int row) const {
    int currentRow = (row == -1) ? ui->heros_listWidget->currentRow() : row;
    if (currentRow < 0 || currentRow >= NOMBRE_HEROS || heross[currentRow+1] == NULL)
        return NULL;
    return heross[currentRow+1];
}

void MainWindow::setHerosLabel(Heros* heros) {
    char data[128];
    heros->Ecrire(data);
    ui->heros_label->setText(latintoQString(data));
}

void MainWindow::on_heros_listWidget_currentRowChanged(int currentRow) {
    if (currentRow >= NOMBRE_HEROS || heross[currentRow+1] == NULL)
        return;
    Heros* heros = heross[currentRow+1];
    setHerosLabel(heros);
    ui->heros_nom_lineEdit->setText(latintoQString(heros->GetNom()));
    ui->heros_vie_spinBox->setValue(heros->GetVie());
    ui->heros_magie_spinBox->setValue(heros->GetMagie());
    ui->heros_viem_spinBox->setValue(heros->GetAttribut(ATTRIBUT_VIE));
    ui->heros_atp_spinBox->setValue(heros->GetAttribut(ATTRIBUT_ATKP));
    ui->heros_dep_spinBox->setValue(heros->GetAttribut(ATTRIBUT_DEFP));
    ui->heros_magiem_spinBox->setValue(heros->GetAttribut(ATTRIBUT_MAG));
    ui->heros_atm_spinBox->setValue(heros->GetAttribut(ATTRIBUT_ATKM));
    ui->heros_dem_spinBox->setValue(heros->GetAttribut(ATTRIBUT_DEFM));
    ui->heros_vit_spinBox->setValue(heros->GetAttribut(ATTRIBUT_VIT));
    ui->heros_pre_spinBox->setValue(heros->GetAttribut(ATTRIBUT_PRE));
    ui->heros_esq_spinBox->setValue(heros->GetAttribut(ATTRIBUT_ESQ));
    ui->heros_maindroite_comboBox->setCurrentIndex(heros->GetEquipement(EQUIPEMENT_MAINDROITE) ? heros->GetEquipement(EQUIPEMENT_MAINDROITE)->GetId() : 0);
    ui->heros_maingauche_comboBox->setCurrentIndex(heros->GetEquipement(EQUIPEMENT_MAINGAUCHE) ? heros->GetEquipement(EQUIPEMENT_MAINGAUCHE)->GetId() : 0);
    ui->heros_casque_comboBox->setCurrentIndex(heros->GetEquipement(EQUIPEMENT_TETE) ? heros->GetEquipement(EQUIPEMENT_TETE)->GetId() : 0);
    ui->heros_armure_comboBox->setCurrentIndex(heros->GetEquipement(EQUIPEMENT_CORPS) ? heros->GetEquipement(EQUIPEMENT_CORPS)->GetId() : 0);
    ui->heros_accessoire1_comboBox->setCurrentIndex(heros->GetEquipement(EQUIPEMENT_ACCESSOIRE1) ? heros->GetEquipement(EQUIPEMENT_ACCESSOIRE1)->GetId() : 0);
    ui->heros_accessoire2_comboBox->setCurrentIndex(heros->GetEquipement(EQUIPEMENT_ACCESSOIRE2) ? heros->GetEquipement(EQUIPEMENT_ACCESSOIRE2)->GetId() : 0);
}

void MainWindow::on_heros_spinBox_valueChanged(int arg1) {
    int i = ui->heros_listWidget->count();
    while (arg1 > i) {
        heross[i+1] = new Heros(i+1);
        heross[i+1]->SetNom("Sans nom");
        ui->heros_listWidget->addItem(latintoQString(heross[i+1]->GetNom()));
        ++i;
    }
    while (arg1 < i) {
        QMessageBox::StandardButton reponse(QMessageBox::question(this,\
            "Confirmer", MESSAGE_CONFIRMATION,\
            QMessageBox::Yes | QMessageBox::No));
        if (reponse == QMessageBox::No) {
            ui->heros_spinBox->setValue(i);
            return;
        }
        delete heross[i];
        heross[i] = NULL;
        delete ui->heros_listWidget->takeItem(i-1);
        --i;
    }
}

void MainWindow::on_heros_nom_lineEdit_textEdited(const QString &arg1) {
    int currentRow = ui->heros_listWidget->currentRow();
    if (currentRow >= NOMBRE_HEROS || heross[currentRow+1] == NULL)
        return;
    heross[currentRow+1]->SetNom(arg1.toStdString().c_str());
    ui->heros_listWidget->currentItem()->setText(arg1);
}

void MainWindow::on_heros_vie_spinBox_valueChanged(int arg1) {
    Heros* heros = getHeros();
    if (heros == NULL)
        return;
    heros->SetVie(arg1);
    setHerosLabel(heros);
}

void MainWindow::on_heros_magie_spinBox_valueChanged(int arg1) {
    Heros* heros = getHeros();
    if (heros == NULL)
        return;
    heros->SetMagie(arg1);
    setHerosLabel(heros);
}

void MainWindow::on_heros_viem_spinBox_valueChanged(int arg1) {
    Heros* heros = getHeros();
    if (heros == NULL)
        return;
    heros->SetVieMax(arg1);
    setHerosLabel(heros);
}

void MainWindow::setHerosAttribut(int val, unsigned char id) {
    Heros* heros = getHeros();
    if (heros == NULL)
        return;
    heros->SetAttribut(val, id);
    setHerosLabel(heros);
}

void MainWindow::on_heros_atp_spinBox_valueChanged(int arg1) {
    setHerosAttribut(arg1, ATTRIBUT_ATKP);
}

void MainWindow::on_heros_dep_spinBox_valueChanged(int arg1) {
    setHerosAttribut(arg1, ATTRIBUT_DEFP);
}

void MainWindow::on_heros_magiem_spinBox_valueChanged(int arg1) {
    Heros* heros = getHeros();
    if (heros == NULL)
        return;
    heros->SetMagieMax(arg1);
    setHerosLabel(heros);
}

void MainWindow::on_heros_atm_spinBox_valueChanged(int arg1) {
    setHerosAttribut(arg1, ATTRIBUT_ATKM);
}

void MainWindow::on_heros_dem_spinBox_valueChanged(int arg1) {
    setHerosAttribut(arg1, ATTRIBUT_DEFM);
}

void MainWindow::on_heros_vit_spinBox_valueChanged(int arg1) {
    setHerosAttribut(arg1, ATTRIBUT_VIT);
}

void MainWindow::on_heros_pre_spinBox_valueChanged(int arg1) {
    setHerosAttribut(arg1, ATTRIBUT_PRE);
}

void MainWindow::on_heros_esq_spinBox_valueChanged(int arg1) {
    setHerosAttribut(arg1, ATTRIBUT_ESQ);
}

void MainWindow::on_heros_status_comboBox_currentIndexChanged(int index) {
    Heros* heros = getHeros();
    if (heros == NULL)
        return;
    heros->SetStatut(index);
    setHerosLabel(heros);
}

void MainWindow::on_heros_exp_spinBox_valueChanged(int arg1) {
    Heros* heros = getHeros();
    if (heros == NULL)
        return;
    heros->SetExperience(arg1);
    setHerosLabel(heros);
}

void MainWindow::on_heros_niv_spinBox_valueChanged(int arg1) {
    Heros* heros = getHeros();
    if (heros == NULL)
        return;
    heros->SetNiveau(arg1);
    setHerosLabel(heros);
}

void MainWindow::setHerosEquipement(int val, unsigned char id) {
    Heros* heros = getHeros();
    if (heros == NULL)
        return;
    if (val) {
        unsigned char i, j = 0;
        for (i = 1; i < NOMBRE_OBJETS+1; ++i) {
            switch (id) {
                case EQUIPEMENT_MAINGAUCHE:
                case EQUIPEMENT_MAINDROITE:
                    if (objets[i]->GetType() == EQUIPABLE_ARME
                    || objets[i]->GetType() == EQUIPABLE_BOUCLIER)
                        ++j;
                    break;
                case EQUIPEMENT_TETE:
                    if (objets[i]->GetType() == EQUIPABLE_CASQUE)
                        ++j;
                    break;
                case EQUIPEMENT_CORPS:
                    if (objets[i]->GetType() == EQUIPABLE_ARMURE)
                        ++j;
                    break;
                case EQUIPEMENT_ACCESSOIRE1:
                case EQUIPEMENT_ACCESSOIRE2:
                    if (objets[i]->GetType() == EQUIPABLE_ACCESSOIRE)
                        ++j;
                    break;
            }
            if (j == val)
                break;
        }
        heros->SetEquipement((Equipable*)objets[i],id);
    } else
        heros->SetEquipement((Equipable*)0,id);
    setHerosLabel(heros);
}

void MainWindow::on_heros_maindroite_comboBox_currentIndexChanged(int index) {
    setHerosEquipement(index, EQUIPEMENT_MAINDROITE);
}

void MainWindow::on_heros_maingauche_comboBox_currentIndexChanged(int index) {
    setHerosEquipement(index, EQUIPEMENT_MAINGAUCHE);
}

void MainWindow::on_heros_casque_comboBox_currentIndexChanged(int index) {
    setHerosEquipement(index, EQUIPEMENT_TETE);
}

void MainWindow::on_heros_armure_comboBox_currentIndexChanged(int index) {
    setHerosEquipement(index, EQUIPEMENT_CORPS);
}

void MainWindow::on_heros_accessoire1_comboBox_currentIndexChanged(int index) {
    setHerosEquipement(index, EQUIPEMENT_ACCESSOIRE1);
}

void MainWindow::on_heros_accessoire2_comboBox_currentIndexChanged(int index) {
    setHerosEquipement(index, EQUIPEMENT_ACCESSOIRE2);
}
