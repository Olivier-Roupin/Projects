#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>
#include <fstream>
#include <QTextCodec>
#define EXPORTOUT
#include <fichierES.h>

Effet*          effets[NOMBRE_EFFETS+1];
Capacite*       capacites[NOMBRE_CAPACITES+1];
Objet*          objets[NOMBRE_OBJETS+1];
Evenement*      evenements[NOMBRE_EVENEMENTS+1];
Carte*          cartes[NOMBRE_CARTES+1];
Monstre*        monstres[NOMBRE_MONSTRES+1];
GroupeMonstres* groupes_monstres[NOMBRE_GROUPES_MONSTRES+1];
Heros*          heross[NOMBRE_HEROS+1];
Tileset*        tilesets[NOMBRE_TILESETS+1];
Script*         scripts[NOMBRE_SCRIPTS+1];
Magasin*        magasins[NOMBRE_MAGASINS+1];
Alteration*     alterations[NOMBRE_ALTERATIONS+1];

QString latintoQString(std::string latin) {
    return QString::fromLatin1(latin.c_str());
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    scene(new QGraphicsScene(this)) {
    ui->setupUi(this);
    load_ini(QString("config.ini"));
    /*QLocale curLocale(QLocale("fr_FR"));
    QLocale::setDefault(curLocale);
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("latin-1"));
    //QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    std::cout << QTextCodec::codecForName("Latin-1") << std::endl;
    QTextCodec::setCodecForLocale( QTextCodec::codecForName("Latin-1") );
    QLocale::setDefault(QLocale::)
    //setlocale(LC_ALL, "fr_FR");*/

    unsigned int i, nombre = 0;
    char* fbuf = 0;
    unsigned int taille = 0;
    using namespace std;
#include <bdd-ascii/SCRIPTS.h>
#include <bdd-ascii/EFFETS.h>
    for (i = 1; i < nombre+1; ++i)
        ui->effet_listWidget->addItem(QString::number(effets[i]->GetId()));
    ui->effet_spinBox->setValue(nombre);
#include <bdd-ascii/OBJETS.h>
    ui->monstre_butin_comboBox->addItem(QString("AUCUN"));
    ui->monstre_objet_comboBox->addItem(QString("AUCUN"));
    ui->heros_maindroite_comboBox->addItem(QString("AUCUN"));
    ui->heros_maingauche_comboBox->addItem(QString("AUCUN"));
    ui->heros_casque_comboBox->addItem(QString("AUCUN"));
    ui->heros_armure_comboBox->addItem(QString("AUCUN"));
    ui->heros_accessoire1_comboBox->addItem(QString("AUCUN"));
    ui->heros_accessoire2_comboBox->addItem(QString("AUCUN"));
    for (i = 1; i < nombre+1; ++i) {
        ui->objet_listWidget->addItem(latintoQString(objets[i]->GetNom()));
        ui->magasin_objet_comboBox->addItem(latintoQString(objets[i]->GetNom()));
        ui->monstre_butin_comboBox->addItem(latintoQString(objets[i]->GetNom()));
        ui->monstre_objet_comboBox->addItem(latintoQString(objets[i]->GetNom()));
        if (objets[i]->GetType() == EQUIPABLE_ARME || objets[i]->GetType() == EQUIPABLE_BOUCLIER) {
            ui->heros_maindroite_comboBox->addItem(latintoQString(objets[i]->GetNom()));
            ui->heros_maingauche_comboBox->addItem(latintoQString(objets[i]->GetNom()));
        } else if (objets[i]->GetType() == EQUIPABLE_CASQUE)
            ui->heros_casque_comboBox->addItem(latintoQString(objets[i]->GetNom()));
        else if (objets[i]->GetType() == EQUIPABLE_ARMURE)
            ui->heros_armure_comboBox->addItem(latintoQString(objets[i]->GetNom()));
        else if (objets[i]->GetType() == EQUIPABLE_ACCESSOIRE) {
            ui->heros_accessoire1_comboBox->addItem(latintoQString(objets[i]->GetNom()));
            ui->heros_accessoire2_comboBox->addItem(latintoQString(objets[i]->GetNom()));
        }
    }
    ui->objet_spinBox->setValue(nombre);
#include <bdd-ascii/MAGASINS.h>
    for (i = 1; i < nombre+1; ++i)
//        ui->magasin_listWidget->addItem(latintoQString(magasins[i]->GetNom()));
        ui->magasin_listWidget->addItem(QString::number(magasins[i]->GetId()));
    ui->magasin_spinBox->setValue(nombre);
#include <bdd-ascii/HEROSS.h>
    for (i = 1; i < nombre+1; ++i)
        ui->heros_listWidget->addItem(latintoQString(heross[i]->GetNom()));
    ui->heros_spinBox->setValue(nombre);
#include <bdd-ascii/MONSTRES.h>
    for (i = 1; i < nombre+1; ++i) {
        ui->monstre_listWidget->addItem(latintoQString(monstres[i]->GetNom()));
        ui->groupesmonstre_monstre_comboBox->addItem(latintoQString(monstres[i]->GetNom()));
    }
    ui->monstre_spinBox->setValue(nombre);
#include <bdd-ascii/GROUPESMONSTRES.h>
    for (i = 1; i < nombre+1; ++i) {
        ui->groupesmonstre_listWidget->addItem(QString::number(groupes_monstres[i]->GetId()));
//        ui->groupesmonstre_listWidget->addItem(latintoQString(groupes_monstres[i]->GetNom()));
        ui->carte_groupe_comboBox->addItem(QString::number(groupes_monstres[i]->GetId()));
//        ui->carte_groupe_comboBox->addItem(latintoQString(groupes_monstres[i]->GetNom()));
    }
    ui->groupesmonstre_spinBox->setValue(nombre);
#include <bdd-ascii/TILESETS.h>
    for (i = 1; i < nombre+1; ++i)
        ui->tileset_listWidget->addItem(QString::number(tilesets[i]->GetId()));
    ui->tileset_spinBox->setValue(nombre);
#include <bdd-ascii/EVENEMENTS.h>
    for (i = 1; i < nombre+1; ++i) {
        ui->evenement_listWidget->addItem(QString::number(evenements[i]->GetId()));
        ui->carte_evenement_comboBox->addItem(QString::number(evenements[i]->GetId()));
    }
    ui->evenement_spinBox->setValue(nombre);
#include <bdd-ascii/CARTES.h>
    for (i = 1; i < nombre+1; ++i)
        ui->carte_listWidget->addItem(latintoQString(cartes[i]->GetNom()));
    ui->carte_spinBox->setValue(nombre);
#include <bdd-ascii/CAPACITES.h>
    for (i = 1; i < nombre+1; ++i)
        ui->capacite_listWidget->addItem(latintoQString(capacites[i]->GetNom()));
    ui->capacite_spinBox->setValue(nombre);
#include <bdd-ascii/ALTERATIONS.h>
    for (i = 1; i < nombre+1; ++i)
        ui->alteration_listWidget->addItem(latintoQString(alterations[i]->GetNom()));
    ui->alteration_spinBox->setValue(nombre); //après car signal "valeur changée"
    //init((char*)"JeuOne");
//#include <GRAPHISMES.h>

    ui->alteration_listWidget->setCurrentRow(0);
    ui->capacite_listWidget->setCurrentRow(0);
    ui->carte_listWidget->setCurrentRow(0);
    ui->effet_listWidget->setCurrentRow(0);
    ui->evenement_listWidget->setCurrentRow(0);
    ui->groupesmonstre_listWidget->setCurrentRow(0);
    ui->heros_listWidget->setCurrentRow(0);
    ui->magasin_listWidget->setCurrentRow(0);
    ui->monstre_listWidget->setCurrentRow(0);
    ui->objet_listWidget->setCurrentRow(0);
    ui->tileset_listWidget->setCurrentRow(0);

    ui->alteration_nom_lineEdit->setMaxLength(TAILLE_NOM_ALTERATION);
    ui->capacite_nom_lineEdit->setMaxLength(TAILLE_NOM_CAPACITE);
    ui->carte_nom_lineEdit->setMaxLength(TAILLE_NOM_CARTE);
    ui->heros_nom_lineEdit->setMaxLength(TAILLE_NOM_PERSONNAGE);
    ui->monstre_nom_lineEdit->setMaxLength(TAILLE_NOM_PERSONNAGE);
    ui->objet_nom_lineEdit->setMaxLength(TAILLE_NOM_OBJET);

    ui->alteration_label->setVisible(false);
    ui->capacite_label->setVisible(false);
    ui->carte_label->setVisible(false);
    ui->effet_label->setVisible(false);
    ui->evenement_label->setVisible(false);
    ui->groupesmonstre_label->setVisible(false);
    ui->heros_label->setVisible(false);
    ui->magasin_label->setVisible(false);
    ui->monstre_label->setVisible(false);
    ui->objet_label->setVisible(false);
    ui->tileset_label->setVisible(false);

    /*ui->carte_bas_pushButton->setCheckable(true);
    ui->carte_moyen_pushButton->setCheckable(true);
    ui->carte_haut_pushButton->setCheckable(true);
    ui->carte_evenements_pushButton->setCheckable(true);
    ui->carte_bas_pushButton->setChecked(true);*/
    //ui->carte_bas_pushButton->setEnabled(false);
    on_carte_evenements_pushButton_clicked();
    ui->carte_graphicsView->setScene(scene);
    connect(scene, &QGraphicsScene::selectionChanged, this, &MainWindow::changeTile);
}

#define MAX_TAILLE_DATA 8192

MainWindow::~MainWindow() {
    unsigned int i, nombre;
    char str2[MAX_TAILLE_DATA*2];
    char secteur[2048];
    char* p_secteur;
#include <bdd/ALTERATIONS_D.h>
#include <bdd/MAGASINS_D.h>
#include <bdd/HEROSS_D.h>
#include <bdd/GROUPESMONSTRES_D.h>
#include <bdd/CARTES_D.h>
#include <bdd/OBJETS_D.h>
#include <bdd/CAPACITES_D.h>
#include <bdd/EFFETS_D.h>
    save_ini(QString("config.ini"));
    delete ui;
}

void MainWindow::load_ini(QString fileName) {
    if (fileName.isEmpty())
        return;
    else {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::information(this, tr("Unable to open file"),
                                     file.errorString());
            return;
        }
        QTextStream in(&file);
        in >> workFolder;
    }
}

void MainWindow::save_ini(QString fileName) {
    if (fileName.isEmpty())
        return;
    else {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly)) {
            QMessageBox::information(this, tr("Unable to open file"),
                                     file.errorString());
            return;
        }
        QTextStream out(&file);
        out << workFolder;
    }
}

void MainWindow::on_actionOuvrir_triggered() {
    QString path = workFolder.isEmpty() ? "." : workFolder;
    QString newPath = QFileDialog::getExistingDirectory(this, tr("Open Directory"), path, QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    if (newPath.isEmpty())
        return;
    workFolder = newPath;
}

void MainWindow::on_actionEnregistrer_triggered() {

}
