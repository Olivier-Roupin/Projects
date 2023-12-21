#include "mainwindow.h"
#include "ui_mainwindow.h"

extern Tileset*        tilesets[NOMBRE_TILESETS+1];

Tileset* MainWindow::getTileset(int row) const {
    int currentRow = (row == -1) ? ui->tileset_listWidget->currentRow() : row;
    if (currentRow < 0 || currentRow >= NOMBRE_TILESETS || tilesets[currentRow+1] == NULL)
        return NULL;
    return tilesets[currentRow+1];
}

void MainWindow::setTilesetLabel(Tileset* tileset) {
    char data[128];
    tileset->Ecrire(data);
    ui->tileset_label->setText(latintoQString(data));
}

bool MainWindow::getTilesetNombreBounds(int row) const {
    Tileset* tileset = getTileset();
    if (tileset == NULL)
        return true;
    return row < 0 || row >= ui->tileset_nombre_spinBox->value() || (unsigned int)row >= tileset->GetNombre();
}

void MainWindow::on_tileset_listWidget_currentRowChanged(int currentRow) {
    Tileset* tileset = getTileset(currentRow);
    if (tileset == NULL)
        return;
    ui->tileset_tile_listWidget->clear();
    for (unsigned int i = 0; i < tileset->GetNombre(); ++i)
        ui->tileset_tile_listWidget->addItem(latintoQString(tileset->GetImage(i)));
    ui->tileset_nombre_spinBox->setValue(tileset->GetNombre());
    ui->tileset_tile_listWidget->setCurrentRow(0);
    setTilesetLabel(tileset);
}

void MainWindow::on_tileset_spinBox_valueChanged(int arg1) {
    int i = ui->tileset_listWidget->count();
    while (arg1 > i) {
        tilesets[i+1] = new Tileset(i+1);
        ui->tileset_listWidget->addItem(QString::number(tilesets[i+1]->GetId()));
        ++i;
    }
    while (arg1 < i) {
        QMessageBox::StandardButton reponse(QMessageBox::question(this,\
            "Confirmer", MESSAGE_CONFIRMATION,\
            QMessageBox::Yes | QMessageBox::No));
        if (reponse == QMessageBox::No) {
            ui->tileset_spinBox->setValue(i);
            return;
        }
        delete tilesets[i];
        tilesets[i] = NULL;
        delete ui->tileset_listWidget->takeItem(i-1);
        --i;
    }
}

void MainWindow::on_tileset_tile_lineEdit_textEdited(const QString &arg1) {
    Tileset* tileset = getTileset();
    if (tileset == NULL)
        return;
    int currentRow2 = ui->tileset_tile_listWidget->currentRow();
    if (getTilesetNombreBounds(currentRow2))
        return;
    tileset->SetImage(arg1.toStdString().c_str(),currentRow2);
    ui->tileset_tile_listWidget->currentItem()->setText(latintoQString(tileset->GetImage(currentRow2)));
    setTilesetLabel(tileset);
}

void MainWindow::on_tileset_traversable_checkBox_clicked(bool checked) {
    Tileset* tileset = getTileset();
    if (tileset == NULL)
        return;
    int currentRow2 = ui->tileset_tile_listWidget->currentRow();
    if (getTilesetNombreBounds(currentRow2))
        return;
    tileset->SetTraversable(checked,currentRow2);
    //ui->magasin_listWidget->currentItem()->setText(latintoQString(magasin->GetNom()));
    setTilesetLabel(tileset);
}

void MainWindow::on_tileset_tile_listWidget_currentRowChanged(int currentRow) {
    Tileset* tileset = getTileset();
    if (tileset == NULL)
        return;
    if (getTilesetNombreBounds(currentRow))
        return;
    ui->tileset_tile_lineEdit->setText(latintoQString(tileset->GetImage(currentRow)));
    ui->tileset_traversable_checkBox->setChecked(tileset->GetTraversable(currentRow));
}

void MainWindow::on_tileset_nombre_spinBox_valueChanged(int arg1) {
    Tileset* tileset = getTileset();
    if (tileset == NULL)
        return;
    int i = ui->tileset_tile_listWidget->count();
    while (arg1 > i) {
        tileset->SetNombre(i+1);
        ui->tileset_tile_listWidget->addItem(latintoQString(tileset->GetImage(i)));
        //ui->magasin_listWidget->currentItem()->setText(latintoQString(magasin->GetNom()));
        ++i;
        setTilesetLabel(tileset);
    }
    while (arg1 < i) {
        QMessageBox::StandardButton reponse(QMessageBox::question(this,\
            "Confirmer", MESSAGE_CONFIRMATION,\
            QMessageBox::Yes | QMessageBox::No));
        if (reponse == QMessageBox::No) {
            ui->tileset_nombre_spinBox->setValue(i);
            return;
        }
        tileset->SetNombre(i-1);
        delete ui->tileset_tile_listWidget->takeItem(i-1);
        //ui->groupesmonstre_listWidget->currentItem()->setText(latintoQString(tileset->GetNom()));
        --i;
        setTilesetLabel(tileset);
    }
}
