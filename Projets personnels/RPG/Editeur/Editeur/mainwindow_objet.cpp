#include "mainwindow.h"
#include "ui_mainwindow.h"

extern Effet*          effets[NOMBRE_EFFETS+1];
extern Objet*          objets[NOMBRE_OBJETS+1];
extern Monstre*        monstres[NOMBRE_MONSTRES+1];
extern Heros*          heross[NOMBRE_HEROS+1];
extern Magasin*        magasins[NOMBRE_MAGASINS+1];

Objet* MainWindow::getObjet(int row) const {
    int currentRow = (row == -1) ? ui->objet_listWidget->currentRow() : row;
    if (currentRow < 0 || currentRow >= NOMBRE_OBJETS || objets[currentRow+1] == NULL)
        return NULL;
    return objets[currentRow+1];
}

Utilisable* MainWindow::getUtilisable(int row) const {
    Objet* objet = getObjet(row);
    if (objet == NULL || objet->GetType() != UTILISABLE)
        return NULL;
    return (Utilisable*)objet;
}

Equipable* MainWindow::getEquipable(int row) const {
    Objet* objet = getObjet(row);
    if (objet == NULL || objet->GetType() == UTILISABLE || objet->GetType() == OBJET)
        return NULL;
    return (Equipable*)objet;
}

void MainWindow::setObjetLabel(Objet* objet) {
    char data[128];
    objet->Ecrire(data);
    ui->objet_label->setText(latintoQString(data));
}

void MainWindow::on_objet_listWidget_currentRowChanged(int currentRow) {
    if (currentRow >= NOMBRE_OBJETS || objets[currentRow+1] == NULL)
        return;
    Objet* objet = objets[currentRow+1];
    setObjetLabel(objet);
    ui->objet_nom_lineEdit->setText(latintoQString(objet->GetNom()));
    int type;
    switch (objet->GetType()) {
    case UTILISABLE :
        type = 0;
        break;
    case EQUIPABLE :
    case EQUIPABLE_ARME :
        type = 1;
        break;
    case EQUIPABLE_BOUCLIER :
        type = 2;
        break;
    case EQUIPABLE_CASQUE :
        type = 3;
        break;
    case EQUIPABLE_ARMURE :
        type = 4;
        break;
    case EQUIPABLE_ACCESSOIRE :
        type = 5;
        break;
    default :
        type = 0;
        break;
    }
    ui->objet_type_comboBox->setCurrentIndex(type); //ui->objet_stackedWidget->setCurrentIndex(type != UTILISABLE);
    ui->objet_prix_spinBox->setValue(objet->GetPrix());
    ui->objet_description_lineEdit->setText(latintoQString(objet->GetDescription()));

    if (objet->GetType() == UTILISABLE) {
        Utilisable* utilisable = (Utilisable*)objet;
        ui->objet_stackedWidget->setCurrentIndex(0);
        ui->objet_illimite_checkBox->setChecked(utilisable->GetIllimite());
        ui->objet_effet_spinBox->setValue(utilisable->GetEffet() ? utilisable->GetEffet()->GetId() : 0);
    } else {
        Equipable* equipable = (Equipable*)objet;
        ui->objet_stackedWidget->setCurrentIndex(1);
        ui->objet_vie_spinBox->setValue(equipable->GetAttribut(ATTRIBUT_VIE));
        ui->objet_atp_spinBox->setValue(equipable->GetAttribut(ATTRIBUT_ATKP));
        ui->objet_dep_spinBox->setValue(equipable->GetAttribut(ATTRIBUT_DEFP));
        ui->objet_mag_spinBox->setValue(equipable->GetAttribut(ATTRIBUT_MAG));
        ui->objet_atm_spinBox->setValue(equipable->GetAttribut(ATTRIBUT_ATKM));
        ui->objet_dem_spinBox->setValue(equipable->GetAttribut(ATTRIBUT_DEFM));
        ui->objet_vit_spinBox->setValue(equipable->GetAttribut(ATTRIBUT_VIT));
        ui->objet_pre_spinBox->setValue(equipable->GetAttribut(ATTRIBUT_PRE));
        ui->objet_esq_spinBox->setValue(equipable->GetAttribut(ATTRIBUT_ESQ));
        ui->objet_pds_spinBox->setValue(equipable->GetPoids());
        ui->objet_off_spinBox->setValue(equipable->GetRatio());
        ui->objet_element_spinBox->setValue(equipable->GetElement());
    }
}

void MainWindow::on_objet_spinBox_valueChanged(int arg1) {
    int i = ui->objet_listWidget->count();
    while (arg1 > i) {
//        objets[i+1] = new Objet(i+1, "Sans nom");
        objets[i+1] = new Utilisable(i+1, "Sans nom");
        ui->objet_listWidget->addItem(latintoQString(objets[i+1]->GetNom()));
        ui->magasin_objet_comboBox->addItem(latintoQString(objets[i+1]->GetNom()));
        ui->monstre_objet_comboBox->addItem(latintoQString(objets[i+1]->GetNom()));
        ui->monstre_butin_comboBox->addItem(latintoQString(objets[i+1]->GetNom()));
        ++i;
    }
    while (arg1 < i) {
        QMessageBox::StandardButton reponse(QMessageBox::question(this,\
            "Confirmer", MESSAGE_CONFIRMATION,\
            QMessageBox::Yes | QMessageBox::No));
        if (reponse == QMessageBox::No) {
            ui->objet_spinBox->setValue(i);
            return;
        }
        for (int j(1); j < ui->magasin_listWidget->count()+1; j++)
            for (unsigned int k(0); k < magasins[j]->GetNombre(); k++)
                if (magasins[j]->GetObjets(k)->GetId() == i)
//                if (magasins[j]->GetId(k) == i)
                    magasins[j]->SetObjets(NULL, k);
        for (int j(1); j < ui->monstre_listWidget->count()+1; j++) {
            if (monstres[j]->GetObjetPorte()->GetId() == i)
               monstres[j]->SetObjetPorte(NULL);
            if (monstres[j]->GetButin()->GetId() == i)
               monstres[j]->SetButin(NULL);
        }
        delete objets[i];
        objets[i] = NULL;
        delete ui->objet_listWidget->takeItem(i-1);
        ui->magasin_objet_comboBox->removeItem(i-1);
        ui->monstre_objet_comboBox->removeItem(i);
        ui->monstre_butin_comboBox->removeItem(i);
        --i;
    }
}

void MainWindow::on_objet_nom_lineEdit_textEdited(const QString &arg1) {
    Objet* objet = getObjet();
    if (objet == NULL)
        return;
    objet->SetNom(arg1.toStdString().c_str());
    ui->objet_listWidget->currentItem()->setText(arg1);

    int id = objet->GetId();
    ui->magasin_objet_comboBox->setItemText(id-1, arg1);
    update_magasin_objet_listWidget(objet);
    ui->monstre_objet_comboBox->setItemText(id,   arg1);
    ui->monstre_butin_comboBox->setItemText(id,   arg1);
    setObjetLabel(objet);
}

void MainWindow::on_objet_description_lineEdit_textEdited(const QString &arg1) {
    Objet* objet = getObjet();
    if (objet == NULL)
        return;
    objet->SetDescription(arg1.toStdString().c_str());
    setObjetLabel(objet);
}

void MainWindow::on_objet_type_comboBox_currentIndexChanged(int index) {
    Objet* objet = getObjet();
    if (objet == NULL)
        return;
    int type;
    switch (index) {
    case 0 :
        type = UTILISABLE;
        break;
    case 1 :
        type = EQUIPABLE_ARME;
        break;
    case 2 :
        type = EQUIPABLE_BOUCLIER;
        break;
    case 3 :
        type = EQUIPABLE_CASQUE;
        break;
    case 4 :
        type = EQUIPABLE_ARMURE;
        break;
    case 5 :
        type = EQUIPABLE_ACCESSOIRE;
        break;
    default :
        type = OBJET;
        break;
    }

    ui->objet_stackedWidget->setCurrentIndex(type != UTILISABLE);

    if (type == objet->GetType()) //Ne pas créer un nouvel objet
        return;
    if (type != UTILISABLE && objet->GetType() != UTILISABLE) {
        objet->SetType(type);
        setObjetLabel(objet);
        return;
    }

    int id = objet->GetId();
    switch(type) {
    case OBJET:
        objets[id] = new      Objet(id, objet->GetNom(), type,
                                    objet->GetPrix(), objet->GetDescription());
        break;
    case UTILISABLE:
        objets[id] = new Utilisable(id, objet->GetNom(), type,
                                    objet->GetPrix(), objet->GetDescription());
        break;
    case EQUIPABLE:
    case EQUIPABLE_ACCESSOIRE:
    case EQUIPABLE_ARME:
    case EQUIPABLE_ARMURE:
    case EQUIPABLE_BOUCLIER:
    case EQUIPABLE_CASQUE:
        objets[id] = new  Equipable(id, objet->GetNom(), type,
                                    objet->GetPrix(), objet->GetDescription());
        break;
    }
    delete objet;
    objet = objets[id];
    setObjetLabel(objet);
}

//Utilisable
void MainWindow::on_objet_illimite_checkBox_clicked(bool checked) {
    Utilisable* objet = getUtilisable();
    if (objet == NULL)
        return;
    objet->SetIllimite(checked);
    setObjetLabel(objet);
}

void MainWindow::on_objet_effet_spinBox_valueChanged(int arg1) {
    Utilisable* objet = getUtilisable();
    if (objet == NULL)
        return;
    objet->SetEffet(effets[arg1]);
    setObjetLabel(objet);
}

//Equipable
void MainWindow::setEquipableAttribut(int val, unsigned char id) {
    Equipable* objet = getEquipable();
    if (objet == NULL)
        return;
    objet->SetAttribut(val, id);
    setObjetLabel(objet);
}

void MainWindow::on_objet_vie_spinBox_valueChanged(int arg1) {
    setEquipableAttribut(arg1, ATTRIBUT_VIE);
}

void MainWindow::on_objet_atp_spinBox_valueChanged(int arg1) {
    setEquipableAttribut(arg1, ATTRIBUT_ATKP);
}

void MainWindow::on_objet_dep_spinBox_valueChanged(int arg1) {
    setEquipableAttribut(arg1, ATTRIBUT_DEFP);
}

void MainWindow::on_objet_mag_spinBox_valueChanged(int arg1) {
    setEquipableAttribut(arg1, ATTRIBUT_MAG);
}

void MainWindow::on_objet_atm_spinBox_valueChanged(int arg1) {
    setEquipableAttribut(arg1, ATTRIBUT_ATKM);
}

void MainWindow::on_objet_dem_spinBox_valueChanged(int arg1) {
    setEquipableAttribut(arg1, ATTRIBUT_DEFM);
}

void MainWindow::on_objet_vit_spinBox_valueChanged(int arg1) {
    setEquipableAttribut(arg1, ATTRIBUT_VIT);
}

void MainWindow::on_objet_pre_spinBox_valueChanged(int arg1) {
    setEquipableAttribut(arg1, ATTRIBUT_PRE);
}

void MainWindow::on_objet_esq_spinBox_valueChanged(int arg1) {
    setEquipableAttribut(arg1, ATTRIBUT_ESQ);
}

void MainWindow::on_objet_pds_spinBox_valueChanged(int arg1) {
    Equipable* objet = getEquipable();
    if (objet == NULL)
        return;
    objet->SetPoids(arg1);
    setObjetLabel(objet);
}

void MainWindow::on_objet_off_spinBox_valueChanged(int arg1) {
    Equipable* objet = getEquipable();
    if (objet == NULL)
        return;
    objet->SetRatio(arg1);
    setObjetLabel(objet);
}

void MainWindow::on_objet_element_spinBox_valueChanged(int arg1) {
    Equipable* objet = getEquipable();
    if (objet == NULL)
        return;
    objet->SetElement(arg1);
    setObjetLabel(objet);
}

void MainWindow::on_objet_prix_spinBox_valueChanged(int arg1) {
    Equipable* objet = getEquipable();
    if (objet == NULL)
        return;
    objet->SetPrix(arg1);
    setObjetLabel(objet);
}
