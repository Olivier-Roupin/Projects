#include "mainwindow.h"
#include "ui_mainwindow.h"

extern Evenement*      evenements[NOMBRE_EVENEMENTS+1];
extern Carte*          cartes[NOMBRE_CARTES+1];
extern GroupeMonstres* groupes_monstres[NOMBRE_GROUPES_MONSTRES+1];
extern Tileset*        tilesets[NOMBRE_TILESETS+1];

Carte* MainWindow::getCarte(int row) const {
    int currentRow = (row == -1) ? ui->carte_listWidget->currentRow() : row;
    if (currentRow < 0 || currentRow >= NOMBRE_CARTES || cartes[currentRow+1] == NULL)
        return NULL;
    return cartes[currentRow+1];
}

void MainWindow::setCarteLabel(Carte* carte) {
    char data[4096];
    carte->Ecrire(data);
    ui->carte_label->setText(latintoQString(data));
}

bool MainWindow::getCarteNombreBounds(int row) const { // événements
    Carte* carte = getCarte();
    if (carte == NULL)
        return true;
    return row < 0 || row >= ui->carte_nombre_spinBox->value() || row >= carte->GetNombre();
}

bool MainWindow::getCarteNombreRencontresBounds(int row) const {
    Rencontreset* rencontreset = getRencontreset();
    if (rencontreset == NULL)
        return true;
    return row < 0 || row >= ui->carte_nombrerencontres_spinBox->value()+1 || row >= rencontreset->GetNombre()+1;
}

bool MainWindow::getCarteNombreGroupesBounds(int row) const {
    Rencontreset* rencontreset = getRencontreset();
    if (rencontreset == NULL)
        return true;
    int currentRow2 = ui->carte_rencontre_listWidget->currentRow();
    return row < 0 || row >= ui->carte_nombregroupes_spinBox->value() || row >= rencontreset->GetNombreGroupes(currentRow2-1);
}

int MainWindow::getCouche() const {
    if (!ui->carte_bas_pushButton->isEnabled())
        return COUCHE_BAS;
    if (!ui->carte_moyen_pushButton->isEnabled())
        return COUCHE_MOYEN;
    if (!ui->carte_haut_pushButton->isEnabled())
        return COUCHE_HAUT;
    if (!ui->carte_evenements_pushButton->isEnabled())
        return COUCHE_EVENEMENTS;
    return COUCHE_RENCONTRES;
}

void MainWindow::populateScene(int couche) {
    scene->clear();
    Carte* carte = getCarte();
    if (carte == NULL)
        return;
    Tileset* tileset = carte->GetTileset();
    for (unsigned int i = 0; i < carte->GetHauteur(); ++i) {
        for (unsigned int j = 0; j < carte->GetLargeur(); ++j) {
            std::string tile = "_";
            switch (couche) {
            case COUCHE_BAS:
            case COUCHE_MOYEN:
            case COUCHE_HAUT:
                if (tileset)
                    tile = tileset->GetImage(carte->GetTuile(j,i,couche));
                break;
            case COUCHE_RENCONTRES:
                tile = std::to_string(carte->GetRencontres(j,i));
                break;
            case COUCHE_EVENEMENTS:
            default:
                if (tileset) {
                    if (carte->GetTuile(j,i,Z_HAUT))
                        tile = tileset->GetImage(carte->GetTuile(j,i,Z_HAUT));
                    else if (carte->GetTuile(j,i,Z_MILIEU))
                        tile = tileset->GetImage(carte->GetTuile(j,i,Z_MILIEU));
                    else
                        tile = tileset->GetImage(carte->GetTuile(j,i,Z_BAS));
                }
                break;
            }

            QGraphicsItem *item = new QGraphicsSimpleTextItem(latintoQString(tile));//Tile(tile);
            if (couche != COUCHE_EVENEMENTS)
                item->setFlag(QGraphicsItem::ItemIsSelectable, true);
            item->setPos(QPointF(j*8*2, i*12*2));
            item->setScale(2);
            scene->addItem(item);
        }
    }
    if (couche == COUCHE_EVENEMENTS) {
        for (unsigned char i = 0; i < carte->GetNombre(); ++i) {
            Evenement* evenement = carte->GetEvenements(i);
            if (evenement) {
                QGraphicsItem *item = new QGraphicsSimpleTextItem(latintoQString(evenement->GetImage()));
                item->setFlag(QGraphicsItem::ItemIsSelectable, true);
                //item->setFlag(QGraphicsItem::ItemIsMovable, true);
                item->setPos(QPointF(evenement->GetX()*8*2, evenement->GetY()*12*2));
                item->setScale(2);
                scene->addItem(item);
            }
        }
    }
}

void MainWindow::changeTile() {
    Carte* carte = getCarte();
    if (carte == NULL)
        return;
    int couche = getCouche();
    if (couche == COUCHE_EVENEMENTS) {
        if (scene->selectedItems().isEmpty()) {
            return;
            /*for (int i = 0; i < carte->GetNombre(); i++) {
                scene->itemAt();
                Evenement* evenement = carte->GetEvenements(i);
                QGraphicsItem *item = new QGraphicsSimpleTextItem(latintoQString(evenement->GetImage()));
                item->setPos(QPointF(evenement->GetX()*8*2, evenement->GetY()*12*2));
                item->setScale(2);
                scene->addItem(item);
            }*/
        }
        QGraphicsItem *item = scene->selectedItems().first();
        /*item->setVisible(false);
        QGraphicsItem *item2 = scene->itemAt(item->pos(), ui->carte_graphicsView->transform());
        item->setVisible(true);
        item->setPos(item2->pos());*/
        int x = item->x(), y = item->y();
        x -= x % (8*2);
        y -= y % (12*2);
        item->setX(x);
        item->setY(y);
        return;
    }

    if (scene->selectedItems().isEmpty())
        return;
    QGraphicsItem *item = scene->selectedItems().first();
    int i = item->y()/12/2, j = item->x()/8/2;

    if (couche == COUCHE_RENCONTRES) {
        // TODO FOR INDEX 0
        int currentRow = ui->carte_rencontre_listWidget->currentRow();
        if (getCarteNombreRencontresBounds(currentRow))
            return;
        carte->SetRencontres(currentRow, j,i);
        ((QGraphicsSimpleTextItem*)item)->setText(QString::number(currentRow));
    } else {
        Tileset* tileset = carte->GetTileset();
        if (tileset) {
            int currentRow = ui->carte_tileset_listWidget->currentRow();
            if (currentRow < 0 || currentRow >= ui->carte_tileset_listWidget->count() || (unsigned int)currentRow >= tileset->GetNombre())
                return;
            carte->SetTuile(currentRow,j,i,couche);
            ((QGraphicsSimpleTextItem*)item)->setText(latintoQString(tileset->GetImage(currentRow)));
        }
    }
    item->setSelected(false);
    setCarteLabel(carte);
}

void MainWindow::on_carte_listWidget_currentRowChanged(int currentRow) {
    Carte* carte = getCarte(currentRow);
    if (carte == NULL)
        return;
    ui->carte_nom_lineEdit->setText(latintoQString(carte->GetNom()));
    ui->carte_fond_lineEdit->setText(latintoQString(carte->GetFond()));
    ui->carte_largeur_spinBox->setValue(carte->GetLargeur());
    ui->carte_hauteur_spinBox->setValue(carte->GetHauteur());
    ui->carte_repetition_checkBox->setChecked(carte->GetRepetition());
    ui->carte_tileset_spinBox->setValue(carte->GetTileset() ? carte->GetTileset()->GetId() : 0);
    bool rencontres = carte->GetRencontreset() != 0 && carte->GetRencontreset()->GetNombre() != 0;
    if (getCouche() == COUCHE_RENCONTRES && !rencontres)
        on_carte_evenements_pushButton_clicked();
    else
        populateScene(getCouche());

    //Evenements
    ui->carte_evenement_listWidget->clear();
    for (unsigned char i = 0; i < carte->GetNombre(); ++i)
        if (carte->GetEvenements(i))
            ui->carte_evenement_listWidget->addItem(QString::number(carte->GetEvenements(i)->GetId())+"\t("+QString::number(carte->GetEvenements(i)->GetX())+","+QString::number(carte->GetEvenements(i)->GetY())+","+QString::number(carte->GetEvenements(i)->GetZ())+")");

    ui->carte_nombre_spinBox->setValue(carte->GetNombre()); //nombre événements
    ui->carte_evenement_listWidget->setCurrentRow(0);

    //Rencontres
    ui->carte_groupe_listWidget->clear();
    ui->carte_rencontre_listWidget->clear();
    //for (int i(0); i < carte->GetRencontreset()->GetNombre(); i++)
    //    ui->carte_rencontre_listWidget->addItem(QString::number(i+1));
    if (rencontres) {
        for (unsigned char i = 0; i < carte->GetRencontreset()->GetNombre()+1; ++i)
            ui->carte_rencontre_listWidget->addItem(QString::number(i));
        ui->carte_nombrerencontres_spinBox->setValue(carte->GetRencontreset()->GetNombre());
    } else
        ui->carte_nombrerencontres_spinBox->setValue(0);
    if (!rencontres) {
        ui->carte_nombregroupes_spinBox->setValue(0);
        ui->carte_nombregroupes_spinBox->setEnabled(false);
        ui->carte_groupe_comboBox->setCurrentIndex(-1);
        ui->carte_groupe_comboBox->setEnabled(false);
        ui->carte_rencontres_pushButton->setEnabled(false);
    } else {
        ui->carte_nombregroupes_spinBox->setEnabled(true);
        ui->carte_groupe_comboBox->setEnabled(true);
        ui->carte_rencontres_pushButton->setEnabled(true);
    }
    ui->carte_rencontre_listWidget->setCurrentRow(0);
    setCarteLabel(carte);
}

void MainWindow::on_carte_spinBox_valueChanged(int arg1) {
    int i = ui->carte_listWidget->count();
    while (arg1 > i) {
        cartes[i+1] = new Carte(i+1, "Sans nom");
        ui->carte_listWidget->addItem(latintoQString(cartes[i+1]->GetNom()));
        ++i;
    }
    while (arg1 < i) {
        QMessageBox::StandardButton reponse(QMessageBox::question(this,\
            "Confirmer", MESSAGE_CONFIRMATION,\
            QMessageBox::Yes | QMessageBox::No));
        if (reponse == QMessageBox::No) {
            ui->carte_spinBox->setValue(i);
            return;
        }
        delete cartes[i];
        cartes[i] = NULL;
        delete ui->carte_listWidget->takeItem(i-1);
        --i;
    }
}

void MainWindow::on_carte_nom_lineEdit_textEdited(const QString &arg1) {
    Carte* carte = getCarte();
    if (carte == NULL)
        return;
    carte->SetNom(arg1.toStdString().c_str());
    ui->carte_listWidget->currentItem()->setText(arg1);
    setCarteLabel(carte);
}

void MainWindow::on_carte_fond_lineEdit_textEdited(const QString &arg1) {
    Carte* carte = getCarte();
    if (carte == NULL)
        return;
    carte->SetFond(arg1.toStdString().c_str());
    setCarteLabel(carte);
}

void MainWindow::on_carte_largeur_spinBox_valueChanged(int arg1) {
    Carte* carte = getCarte();
    if (carte == NULL)
        return;
    carte->SetLargeur(arg1);
    populateScene(getCouche());
    setCarteLabel(carte);
}

void MainWindow::on_carte_hauteur_spinBox_valueChanged(int arg1) {
    Carte* carte = getCarte();
    if (carte == NULL)
        return;
    carte->SetHauteur(arg1);
    populateScene(getCouche());
    setCarteLabel(carte);
}

void MainWindow::on_carte_repetition_checkBox_clicked(bool checked) {
    Carte* carte = getCarte();
    if (carte == NULL)
        return;
    carte->SetRepetition(checked);
    setCarteLabel(carte);
}

void MainWindow::on_carte_tileset_spinBox_valueChanged(int arg1) {
    Carte* carte = getCarte();
    if (carte == NULL)
        return;
    Tileset* tileset = getTileset(arg1-1);
    if (tileset == NULL || arg1 == 0) {
        ui->carte_tileset_spinBox->setValue(carte->GetTileset()->GetId());
        return;
    }

    ui->carte_tileset_listWidget->clear();
    for (unsigned int i = 0; i < tileset->GetNombre(); ++i)
        ui->carte_tileset_listWidget->addItem(latintoQString(tileset->GetImage(i)));
    ui->carte_tileset_listWidget->setCurrentRow(0);

    if (tileset == carte->GetTileset())
        return;
    carte->SetTileset(tileset);
    populateScene(getCouche());
    setCarteLabel(carte);
}

void MainWindow::on_carte_tileset_listWidget_itemDoubleClicked(QListWidgetItem *item) {
    Carte* carte = getCarte();
    if (carte == NULL)
        return;
    if (item->isSelected() == false)
        return;

    int currentRow = ui->carte_tileset_spinBox->value();
    int currentRow2 = ui->carte_tileset_listWidget->currentRow();
    if (currentRow < 0 || currentRow > ui->tileset_spinBox->value() || carte->GetTileset() == 0 || currentRow != carte->GetTileset()->GetId())
        return;
    ui->tabWidget->setCurrentIndex(10);
    ui->tileset_listWidget->setCurrentRow(currentRow-1);

    if (getTilesetNombreBounds(currentRow2))
        return;
    ui->tileset_tile_listWidget->setCurrentRow(currentRow2);
}

void MainWindow::setCarteCouche(int couche) {
    Carte* carte = getCarte();
    if (carte == NULL)
        return;
    ui->carte_bas_pushButton->setEnabled(couche != COUCHE_BAS);
    ui->carte_moyen_pushButton->setEnabled(couche != COUCHE_MOYEN);
    ui->carte_haut_pushButton->setEnabled(couche != COUCHE_HAUT);
    ui->carte_evenements_pushButton->setEnabled(couche != COUCHE_EVENEMENTS);
    if (carte->GetRencontreset() == 0 || carte->GetRencontreset()->GetNombre() == 0)
        ui->carte_rencontres_pushButton->setEnabled(false);
    else
        ui->carte_rencontres_pushButton->setEnabled(couche != COUCHE_RENCONTRES);
    populateScene(couche);
}

void MainWindow::on_carte_bas_pushButton_clicked() {
    setCarteCouche(COUCHE_BAS);
}

void MainWindow::on_carte_moyen_pushButton_clicked() {
    setCarteCouche(COUCHE_MOYEN);
}

void MainWindow::on_carte_haut_pushButton_clicked() {
    setCarteCouche(COUCHE_HAUT);
}

void MainWindow::on_carte_evenements_pushButton_clicked() {
    setCarteCouche(COUCHE_EVENEMENTS);
}

void MainWindow::on_carte_rencontres_pushButton_clicked() {
    setCarteCouche(COUCHE_RENCONTRES);
}

void MainWindow::on_carte_nombre_spinBox_valueChanged(int arg1) {
    Carte* carte = getCarte();
    if (carte == NULL)
        return;
    int i = ui->carte_evenement_listWidget->count();
    while (arg1 > i) {
        carte->SetNombre(i+1);
        ui->carte_evenement_listWidget->addItem(QString::number(carte->GetEvenements(i)->GetId()));
        ++i;
        setCarteLabel(carte);
    }
    while (arg1 < i) {
        QMessageBox::StandardButton reponse(QMessageBox::question(this,\
            "Confirmer", MESSAGE_CONFIRMATION,\
            QMessageBox::Yes | QMessageBox::No));
        if (reponse == QMessageBox::No) {
            ui->carte_nombre_spinBox->setValue(i);
            return;
        }
        carte->SetNombre(i-1);
        delete ui->carte_evenement_listWidget->takeItem(i-1);
        --i;
        setCarteLabel(carte);
    }
}

Rencontreset* MainWindow::getRencontreset(int row) const {
    Carte* carte = getCarte(row);
    if (carte == NULL)
        return NULL;
    return carte->GetRencontreset();
}

void MainWindow::on_carte_nombrerencontres_spinBox_valueChanged(int arg1) {
    Carte* carte = getCarte();
    Rencontreset* rencontreset = getRencontreset(); //teste carte == NULL
    if (rencontreset == NULL)
        return;
    //int i(ui->carte_rencontre_listWidget->count());
    int i = ui->carte_rencontre_listWidget->count()-1;
    while (arg1 > i) {
        rencontreset->SetNombre(i+1);
        ui->carte_rencontre_listWidget->addItem(QString::number(i+1));
        ++i;
        setCarteLabel(carte);
    }
    while (arg1 < i) {
        QMessageBox::StandardButton reponse(QMessageBox::question(this,\
            "Confirmer", MESSAGE_CONFIRMATION,\
            QMessageBox::Yes | QMessageBox::No));
        if (reponse == QMessageBox::No) {
            ui->carte_nombrerencontres_spinBox->setValue(i);
            return;
        }
        rencontreset->SetNombre(i-1);
        delete ui->carte_rencontre_listWidget->takeItem(i);
        --i;
        setCarteLabel(carte);
    }
}

void MainWindow::on_carte_evenement_comboBox_currentIndexChanged(int index) {
    Carte* carte = getCarte();
    if (carte == NULL)
        return;
    int currentRow2 = ui->carte_evenement_listWidget->currentRow();
    if (getCarteNombreBounds(currentRow2))
        return;
    carte->SetEvenements(evenements[index+1], currentRow2);
    Evenement* evenement = carte->GetEvenements(currentRow2);
    if (evenement == NULL)
        return;
    ui->carte_evenement_listWidget->currentItem()->setText(QString::number(evenement->GetId())+"\t("+QString::number(evenement->GetX())+","+QString::number(evenement->GetY())+","+QString::number(evenement->GetZ())+")");
    populateScene(getCouche());
    setCarteLabel(carte);
}

void MainWindow::on_carte_x_spinBox_valueChanged(int arg1) {
    Carte* carte = getCarte();
    if (carte == NULL)
        return;
    int currentRow2 = ui->carte_evenement_listWidget->currentRow();
    if (getCarteNombreBounds(currentRow2))
        return;
    Evenement* evenement = carte->GetEvenements(currentRow2);
    if (evenement == NULL)
        return;
    evenement->SetX(arg1);
    ui->carte_evenement_listWidget->currentItem()->setText(QString::number(evenement->GetId())+"\t("+QString::number(evenement->GetX())+","+QString::number(evenement->GetY())+","+QString::number(evenement->GetZ())+")");
    populateScene(getCouche());
    setCarteLabel(carte);
}

void MainWindow::on_carte_y_spinBox_valueChanged(int arg1) {
    Carte* carte = getCarte();
    if (carte == NULL)
        return;
    int currentRow2 = ui->carte_evenement_listWidget->currentRow();
    if (getCarteNombreBounds(currentRow2))
        return;
    Evenement* evenement = carte->GetEvenements(currentRow2);
    if (evenement == NULL)
        return;
    evenement->SetY(arg1);
    ui->carte_evenement_listWidget->currentItem()->setText(QString::number(evenement->GetId())+"\t("+QString::number(evenement->GetX())+","+QString::number(evenement->GetY())+","+QString::number(evenement->GetZ())+")");
    populateScene(getCouche());
    setCarteLabel(carte);
}

void MainWindow::on_carte_z_spinBox_valueChanged(int arg1) {
    Carte* carte = getCarte();
    if (carte == NULL)
        return;
    int currentRow2 = ui->carte_evenement_listWidget->currentRow();
    if (getCarteNombreBounds(currentRow2))
        return;
    Evenement* evenement = carte->GetEvenements(currentRow2);
    if (evenement == NULL)
        return;
    evenement->SetZ(arg1);
    ui->carte_evenement_listWidget->currentItem()->setText(QString::number(evenement->GetId())+"\t("+QString::number(evenement->GetX())+","+QString::number(evenement->GetY())+","+QString::number(evenement->GetZ())+")");
    populateScene(getCouche());
    setCarteLabel(carte);
}

void MainWindow::on_carte_traversable_checkBox_clicked(bool checked) {
    Carte* carte = getCarte();
    if (carte == NULL)
        return;
    int currentRow2 = ui->carte_evenement_listWidget->currentRow();
    if (getCarteNombreBounds(currentRow2))
        return;
    Evenement* evenement = carte->GetEvenements(currentRow2);
    if (evenement == NULL)
        return;
    evenement->SetTraversable(checked);
    //ui->carte_evenement_listWidget->currentItem()->setText(QString::number(evenement->GetId())+"\t("+QString::number(evenement->GetX())+","+QString::number(evenement->GetY())+","+QString::number(evenement->GetZ())+")");
    //populateScene(getCouche());
    setCarteLabel(carte);
}

void MainWindow::on_carte_evenement_listWidget_currentRowChanged(int currentRow) {
    Carte* carte = getCarte();
    if (carte == NULL)
        return;
    if (getCarteNombreBounds(currentRow))
        return;
    Evenement* evenement = evenements[carte->GetEvenements(currentRow)->GetId()];
    if (evenement == NULL)
        return;
    ui->carte_evenement_comboBox->setCurrentIndex(evenement->GetId()-1);
    ui->carte_x_spinBox->setValue(evenement->GetX());
    ui->carte_y_spinBox->setValue(evenement->GetY());
    ui->carte_z_spinBox->setValue(evenement->GetZ());
    ui->carte_traversable_checkBox->setChecked(evenement->GetTraversable());
}

void MainWindow::on_carte_evenement_listWidget_itemDoubleClicked(QListWidgetItem *item) {
    Carte* carte = getCarte();
    if (carte == NULL)
        return;
    if (item->isSelected() == false)
        return;
    int currentRow = ui->carte_evenement_comboBox->currentIndex()+1;
    if (currentRow < 0 || currentRow > ui->evenement_spinBox->value() || carte->GetEvenements(ui->carte_evenement_listWidget->currentRow()) == 0 || currentRow != carte->GetEvenements(ui->carte_evenement_listWidget->currentRow())->GetId())
        return;
    ui->tabWidget->setCurrentIndex(4);
    ui->evenement_listWidget->setCurrentRow(currentRow-1);
}

void MainWindow::on_carte_nombregroupes_spinBox_valueChanged(int arg1) {
    Carte* carte = getCarte();
    if (carte == NULL)
        return;
    Rencontreset* rencontreset = getRencontreset();
    if (rencontreset == NULL)
        return;
    int currentRow = ui->carte_rencontre_listWidget->currentRow();
    if (getCarteNombreRencontresBounds(currentRow))
        return;
    if (currentRow == 0)
        return;
    int i = ui->carte_groupe_listWidget->count();
    while (arg1 > i) {
        rencontreset->SetNombreGroupes(i+1,currentRow-1);
        ui->carte_groupe_listWidget->addItem((QString::number(carte->GetRencontreset()->GetGroupes(currentRow-1,i)->GetId())));
        ++i;
        setCarteLabel(carte);
    }
    while (arg1 < i) {
        QMessageBox::StandardButton reponse(QMessageBox::question(this,\
            "Confirmer", MESSAGE_CONFIRMATION,\
            QMessageBox::Yes | QMessageBox::No));
        if (reponse == QMessageBox::No) {
            ui->carte_nombrerencontres_spinBox->setValue(i);
            return;
        }
        rencontreset->SetNombreGroupes(i-1,currentRow-1);
        delete ui->carte_groupe_listWidget->takeItem(i-1);
        --i;
        setCarteLabel(carte);
    }
}

void MainWindow::on_carte_groupe_comboBox_currentIndexChanged(int index) {
    Carte* carte = getCarte();
    if (carte == NULL)
        return;
    Rencontreset* rencontreset = getRencontreset();
    if (rencontreset == NULL)
        return;
    int currentRow2 = ui->carte_rencontre_listWidget->currentRow();
    if (getCarteNombreRencontresBounds(currentRow2))
        return;
    if (currentRow2 == 0)
        return;
    int currentRow = ui->carte_groupe_listWidget->currentRow();
    if (getCarteNombreGroupesBounds(currentRow))
        return;
    carte->GetRencontreset()->SetGroupes(groupes_monstres[index+1], currentRow2-1, currentRow);
    ui->carte_groupe_listWidget->currentItem()->setText(QString::number(carte->GetRencontreset()->GetGroupes(currentRow2-1,currentRow)->GetId()));
    setCarteLabel(carte);
}

void MainWindow::on_carte_rencontre_listWidget_currentRowChanged(int currentRow) {
    Carte* carte = getCarte();
    if (carte == NULL)
        return;
    Rencontreset* rencontreset = getRencontreset();
    if (rencontreset == NULL)
        return;
    if (getCarteNombreRencontresBounds(currentRow))
        return;
    ui->carte_groupe_listWidget->clear();
    if (currentRow == 0) {
        ui->carte_groupe_listWidget->setEnabled(false);
        ui->carte_nombregroupes_spinBox->setValue(0);
        return;
    }
    ui->carte_groupe_listWidget->setEnabled(true);
    for (unsigned char i = 0; i < carte->GetRencontreset()->GetNombreGroupes(currentRow-1); ++i)
        ui->carte_groupe_listWidget->addItem(QString::number(carte->GetRencontreset()->GetGroupes(currentRow-1,i)->GetId()));

    ui->carte_nombregroupes_spinBox->setValue(carte->GetRencontreset()->GetNombreGroupes(currentRow-1));
    ui->carte_groupe_listWidget->setCurrentRow(0);
}

void MainWindow::on_carte_groupe_listWidget_currentRowChanged(int currentRow) {
    Carte* carte = getCarte();
    if (carte == NULL)
        return;
    Rencontreset* rencontreset = getRencontreset();
    if (rencontreset == NULL)
        return;
    int currentRow2 = ui->carte_rencontre_listWidget->currentRow();
    if (getCarteNombreRencontresBounds(currentRow2))
        return;
    if (currentRow2 == 0)
        return;
    if (getCarteNombreGroupesBounds(currentRow))
        return;
    if (rencontreset->GetGroupes(currentRow2-1,currentRow))
        ui->carte_groupe_comboBox->setCurrentIndex(rencontreset->GetGroupes(currentRow2-1,currentRow)->GetId()-1);
}

void MainWindow::on_carte_groupe_listWidget_itemDoubleClicked(QListWidgetItem *item) {
    Carte* carte = getCarte();
    if (carte == NULL)
        return;
    if (item->isSelected() == false)
        return;
    int currentRow = ui->carte_groupe_comboBox->currentIndex()+1;
    if (currentRow < 0 || currentRow > ui->groupesmonstre_spinBox->value() || currentRow != carte->GetRencontreset()->GetGroupes(ui->carte_rencontre_listWidget->currentRow(),ui->carte_groupe_listWidget->currentRow())->GetId())
        return;
    ui->tabWidget->setCurrentIndex(5);
    ui->groupesmonstre_listWidget->setCurrentRow(currentRow-1);
}
