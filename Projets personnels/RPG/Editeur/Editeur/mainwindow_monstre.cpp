#include "mainwindow.h"
#include "ui_mainwindow.h"

extern Script*         scripts[NOMBRE_SCRIPTS+1];
extern Objet*          objets[NOMBRE_OBJETS+1];
extern Monstre*        monstres[NOMBRE_MONSTRES+1];
extern GroupeMonstres* groupes_monstres[NOMBRE_GROUPES_MONSTRES+1];

Monstre* MainWindow::getMonstre(int row) const {
    int currentRow = (row == -1) ? ui->monstre_listWidget->currentRow() : row;
    if (currentRow < 0 || currentRow >= NOMBRE_MONSTRES || monstres[currentRow+1] == NULL)
        return NULL;
    return monstres[currentRow+1];
}

void MainWindow::setMonstreLabel(Monstre* monstre) {
    char data[64];
    monstre->Ecrire(data);
    ui->monstre_label->setText(latintoQString(data));
}

void MainWindow::on_monstre_listWidget_currentRowChanged(int currentRow) {
    Monstre* monstre = getMonstre(currentRow);
    if (monstre == NULL)
        return;
    setMonstreLabel(monstre);
    ui->monstre_nom_lineEdit->setText(latintoQString(monstre->GetNom()));
    ui->monstre_vie_spinBox->setValue(monstre->GetVie());
    ui->monstre_magie_spinBox->setValue(monstre->GetMagie());
    ui->monstre_script_spinBox->setValue(monstre->GetScript() ? monstre->GetScript()->GetId() : 0);

    ui->monstre_viem_spinBox->setValue(monstre->GetAttribut(ATTRIBUT_VIE));
    ui->monstre_atp_spinBox->setValue(monstre->GetAttribut(ATTRIBUT_ATKP));
    ui->monstre_dep_spinBox->setValue(monstre->GetAttribut(ATTRIBUT_DEFP));
    ui->monstre_magiem_spinBox->setValue(monstre->GetAttribut(ATTRIBUT_MAG));
    ui->monstre_atm_spinBox->setValue(monstre->GetAttribut(ATTRIBUT_ATKM));
    ui->monstre_dem_spinBox->setValue(monstre->GetAttribut(ATTRIBUT_DEFM));
    ui->monstre_vit_spinBox->setValue(monstre->GetAttribut(ATTRIBUT_VIT));
    ui->monstre_pre_spinBox->setValue(monstre->GetAttribut(ATTRIBUT_PRE));
    ui->monstre_esq_spinBox->setValue(monstre->GetAttribut(ATTRIBUT_ESQ));

    ui->monstre_status_comboBox->setCurrentIndex(monstre->GetStatut());
    ui->monstre_exp_spinBox->setValue(monstre->GetExperience());
    ui->monstre_niv_spinBox->setValue(monstre->GetNiveau());

    ui->monstre_butin_comboBox->setCurrentIndex(monstre->GetButin() ? monstre->GetButin()->GetId() : 0);
    ui->monstre_objet_comboBox->setCurrentIndex(monstre->GetObjetPorte() ? monstre->GetObjetPorte()->GetId() : 0);
    ui->monstre_or_spinBox->setValue(monstre->GetOr());
    ui->monstre_element_atk_spinBox->setValue(monstre->GetElementAttaque());
    ui->monstre_element_def_spinBox->setValue(monstre->GetElementDefense());
}

void MainWindow::on_monstre_spinBox_valueChanged(int arg1) {
    int i = ui->monstre_listWidget->count();
    while (arg1 > i) {
        monstres[i+1] = new Monstre(i+1, "Sans nom");
        ui->monstre_listWidget->addItem(latintoQString(monstres[i+1]->GetNom()));
        ui->groupesmonstre_monstre_comboBox->addItem(latintoQString(monstres[i+1]->GetNom()));
        ++i;
    }
    while (arg1 < i) {
        QMessageBox::StandardButton reponse(QMessageBox::question(this,\
            "Confirmer", MESSAGE_CONFIRMATION,\
            QMessageBox::Yes | QMessageBox::No));
        if (reponse == QMessageBox::No) {
            ui->monstre_spinBox->setValue(i);
            return;
        }
        for (int j = 1; j < ui->groupesmonstre_listWidget->count()+1; ++j)
            for (unsigned char k = 0; k < groupes_monstres[j]->GetNombre(); ++k)
            //  if (groupes_monstres[j]->GetId(k) == i)
                if (groupes_monstres[j]->GetMonstres(k)->GetId() == i)
                    groupes_monstres[j]->SetMonstres(NULL, k);
        delete monstres[i];
        monstres[i] = NULL;
        delete ui->monstre_listWidget->takeItem(i-1);
        ui->groupesmonstre_monstre_comboBox->removeItem(i-1);
        --i;
    }
}

void MainWindow::on_monstre_nom_lineEdit_textEdited(const QString &arg1) {
    Monstre* monstre = getMonstre();
    if (monstre == NULL)
        return;
    monstre->SetNom(arg1.toStdString().c_str());
    ui->monstre_listWidget->currentItem()->setText(arg1);
    setMonstreLabel(monstre);
}

void MainWindow::on_monstre_vie_spinBox_valueChanged(int arg1) {
    Monstre* monstre = getMonstre();
    if (monstre == NULL)
        return;
    monstre->SetVie(arg1);
    setMonstreLabel(monstre);
}

void MainWindow::on_monstre_magie_spinBox_valueChanged(int arg1) {
    Monstre* monstre = getMonstre();
    if (monstre == NULL)
        return;
    monstre->SetMagie(arg1);
    setMonstreLabel(monstre);
}

void MainWindow::on_monstre_script_spinBox_valueChanged(int arg1) {
    Monstre* monstre = getMonstre();
    if (monstre == NULL)
        return;
    monstre->SetScript(scripts[arg1]);
    setMonstreLabel(monstre);
}

void MainWindow::setMonstreAttribut(int val, unsigned char id) {
    Monstre* monstre = getMonstre();
    if (monstre == NULL)
        return;
    monstre->SetAttribut(val, id);
    setMonstreLabel(monstre);
}

void MainWindow::on_monstre_viem_spinBox_valueChanged(int arg1) {
    setMonstreAttribut(arg1, ATTRIBUT_VIE);
}

void MainWindow::on_monstre_atp_spinBox_valueChanged(int arg1) {
    setMonstreAttribut(arg1, ATTRIBUT_ATKP);
}

void MainWindow::on_monstre_dep_spinBox_valueChanged(int arg1) {
    setMonstreAttribut(arg1, ATTRIBUT_DEFP);
}

void MainWindow::on_monstre_magiem_spinBox_valueChanged(int arg1) {
    setMonstreAttribut(arg1, ATTRIBUT_MAG);
}

void MainWindow::on_monstre_atm_spinBox_valueChanged(int arg1) {
    setMonstreAttribut(arg1, ATTRIBUT_ATKM);
}

void MainWindow::on_monstre_dem_spinBox_valueChanged(int arg1) {
    setMonstreAttribut(arg1, ATTRIBUT_DEFM);
}

void MainWindow::on_monstre_vit_spinBox_valueChanged(int arg1) {
    setMonstreAttribut(arg1, ATTRIBUT_VIT);
}

void MainWindow::on_monstre_pre_spinBox_valueChanged(int arg1) {
    setMonstreAttribut(arg1, ATTRIBUT_PRE);
}

void MainWindow::on_monstre_esq_spinBox_valueChanged(int arg1) {
    setMonstreAttribut(arg1, ATTRIBUT_ESQ);
}

void MainWindow::on_monstre_status_comboBox_currentIndexChanged(int index) {
    Monstre* monstre = getMonstre();
    if (monstre == NULL)
        return;
    monstre->SetStatut(index);
    setMonstreLabel(monstre);
}

void MainWindow::on_monstre_exp_spinBox_valueChanged(int arg1) {
    Monstre* monstre = getMonstre();
    if (monstre == NULL)
        return;
    monstre->SetExperience(arg1);
    setMonstreLabel(monstre);
}

void MainWindow::on_monstre_niv_spinBox_valueChanged(int arg1) {
    Monstre* monstre = getMonstre();
    if (monstre == NULL)
        return;
    monstre->SetNiveau(arg1);
    setMonstreLabel(monstre);
}

void MainWindow::on_monstre_butin_comboBox_currentIndexChanged(int index) {
    Monstre* monstre = getMonstre();
    if (monstre == NULL)
        return;
    monstre->SetButin(objets[index]);
    setMonstreLabel(monstre);
}

void MainWindow::on_monstre_objet_comboBox_currentIndexChanged(int index) {
    Monstre* monstre = getMonstre();
    if (monstre == NULL)
        return;
    GroupeObjets* objet = new GroupeObjets(objets[index]);
    delete monstre->GetObjetPorte();
    monstre->SetObjetPorte(objet);
    setMonstreLabel(monstre);
}

void MainWindow::on_monstre_or_spinBox_valueChanged(int arg1) {
    Monstre* monstre = getMonstre();
    if (monstre == NULL)
        return;
    monstre->SetOr(arg1);
    setMonstreLabel(monstre);
}

void MainWindow::on_monstre_element_atk_spinBox_valueChanged(int arg1) {
    Monstre* monstre = getMonstre();
    if (monstre == NULL)
        return;
    monstre->SetElementAttaque(arg1);
    setMonstreLabel(monstre);
}

void MainWindow::on_monstre_element_def_spinBox_valueChanged(int arg1) {
    Monstre* monstre = getMonstre();
    if (monstre == NULL)
        return;
    monstre->SetElementDefense(arg1);
    setMonstreLabel(monstre);
}
