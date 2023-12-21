#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <lib/Alteration.h>
#include <lib/Capacite.h>
#include <lib/Carte.h>
#include <lib/Effet.h>
#include <lib/Evenement.h>
#include <lib/GroupeMonstres.h>
#include <lib/Heros.h>
#include <lib/Magasin.h>
#include <lib/Monstre.h>
#include <lib/Objet.h>
    #include <lib/Equipable.h>
    #include <lib/Utilisable.h>
#include <lib/Tileset.h>
#undef main

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QListWidgetItem>

#include <QGraphicsSimpleTextItem>

#include <QComboBox>
#include <QSpinBox>

#define NOMBRE_EFFETS           200
#define NOMBRE_CAPACITES        100
#define NOMBRE_OBJETS           100
#define NOMBRE_EVENEMENTS       1000
#define NOMBRE_CARTES           100
#define NOMBRE_MONSTRES         100
#define NOMBRE_GROUPES_MONSTRES 100
#define NOMBRE_HEROS            8
#define NOMBRE_TILESETS         100
#define NOMBRE_SCRIPTS          1000
#define NOMBRE_MAGASINS         50
#define NOMBRE_ALTERATIONS      20

#define COUCHE_BAS Z_BAS
#define COUCHE_MOYEN Z_MILIEU
#define COUCHE_HAUT Z_HAUT
#define COUCHE_EVENEMENTS (Z_HAUT+1)
#define COUCHE_RENCONTRES (Z_HAUT+2)

#define MESSAGE_CONFIRMATION "Vous allez supprimer des éléments, êtes vous sûr de vouloir continuer ?"

QString latintoQString(std::string latin);

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void load_ini(QString fileName);
    void save_ini(QString fileName);

private slots:
    void on_actionOuvrir_triggered();
    void on_actionEnregistrer_triggered();

    //Alteration
    Alteration* getAlteration(int row = -1) const;
    void setAlterationLabel(Alteration* alteration);
    void on_alteration_listWidget_currentRowChanged(int currentRow);
    void on_alteration_spinBox_valueChanged(int arg1);
    void on_alteration_nom_lineEdit_textEdited(const QString &arg1);
    void on_alteration_id_spinBox_valueChanged(int arg1);
    void on_alteration_postcombat_checkBox_clicked(bool checked);
    void on_alteration_postdeces_checkBox_clicked(bool checked);
    void on_alteration_priorite_spinBox_valueChanged(int arg1);
    void on_alteration_id_terrain_spinBox_valueChanged(int arg1);

    //Capacité
    Capacite* getCapacite(int row = -1) const;
    void setCapaciteLabel(Capacite* capacite);
    void on_capacite_listWidget_currentRowChanged(int currentRow);
    void on_capacite_spinBox_valueChanged(int arg1);
    void on_capacite_nom_lineEdit_textEdited(const QString &arg1);
    void on_capacite_description_lineEdit_textEdited(const QString &arg1);
    void on_capacite_coutmagie_spinBox_valueChanged(int arg1);
    void on_capacite_coutmagiep_spinBox_valueChanged(int arg1);
    void on_capacite_coutvie_spinBox_valueChanged(int arg1);
    void on_capacite_coutviep_spinBox_valueChanged(int arg1);
    void on_capacite_id_spinBox_valueChanged(int arg1);

    //Carte
    Carte* getCarte(int row = -1) const;
    void setCarteLabel(Carte* carte);
    bool getCarteNombreBounds(int row) const;
    bool getCarteNombreRencontresBounds(int row) const;
    bool getCarteNombreGroupesBounds(int row) const;
    int getCouche() const;
    void populateScene(int couche = COUCHE_EVENEMENTS);
    void changeTile();
    void on_carte_listWidget_currentRowChanged(int currentRow);
    void on_carte_spinBox_valueChanged(int arg1);
    void on_carte_nom_lineEdit_textEdited(const QString &arg1);
    void on_carte_fond_lineEdit_textEdited(const QString &arg1);
    void on_carte_largeur_spinBox_valueChanged(int arg1);
    void on_carte_hauteur_spinBox_valueChanged(int arg1);
    void on_carte_repetition_checkBox_clicked(bool checked);
    void on_carte_tileset_spinBox_valueChanged(int arg1);
    void on_carte_tileset_listWidget_itemDoubleClicked(QListWidgetItem *item);
    void setCarteCouche(int couche);
    void on_carte_bas_pushButton_clicked();
    void on_carte_moyen_pushButton_clicked();
    void on_carte_haut_pushButton_clicked();
    void on_carte_evenements_pushButton_clicked();
    void on_carte_rencontres_pushButton_clicked();
    void on_carte_nombre_spinBox_valueChanged(int arg1);
    Rencontreset* getRencontreset(int row = -1) const;
    void on_carte_nombrerencontres_spinBox_valueChanged(int arg1);
    void on_carte_evenement_comboBox_currentIndexChanged(int index);
    void on_carte_x_spinBox_valueChanged(int arg1);
    void on_carte_y_spinBox_valueChanged(int arg1);
    void on_carte_z_spinBox_valueChanged(int arg1);
    void on_carte_traversable_checkBox_clicked(bool checked);
    void on_carte_evenement_listWidget_currentRowChanged(int currentRow);
    void on_carte_evenement_listWidget_itemDoubleClicked(QListWidgetItem *item);
    void on_carte_nombregroupes_spinBox_valueChanged(int arg1);
    void on_carte_groupe_comboBox_currentIndexChanged(int index);
    void on_carte_rencontre_listWidget_currentRowChanged(int currentRow);
    void on_carte_groupe_listWidget_currentRowChanged(int currentRow);
    void on_carte_groupe_listWidget_itemDoubleClicked(QListWidgetItem *item);

    //Effet
    Effet* getEffet(int row = -1) const;
    void setEffetLabel(Effet* effet);
    void on_effet_listWidget_currentRowChanged(int currentRow);
    void on_effet_spinBox_valueChanged(int arg1);
    void on_effet_script_spinBox_valueChanged(int arg1);
    void on_effet_element_spinBox_valueChanged(int arg1);
    void on_effet_disponibilite_comboBox_currentIndexChanged(int index);
    void on_effet_choixcible_checkBox_clicked(bool checked);
    void on_effet_choixfaction_checkBox_clicked(bool checked);
    void on_effet_choixquantite_checkBox_clicked(bool checked);
    void on_effet_defautcible_comboBox_currentIndexChanged(int index);
    void on_effet_defautfaction_comboBox_currentIndexChanged(int index);
    void on_effet_defautquantite_comboBox_currentIndexChanged(int index);

    //Evénement
    Evenement* getEvenement(int row = -1) const;
    void setEvenementLabel(Evenement* evenement);
    bool getEvenementNombreBounds(int row) const;
    void on_evenement_listWidget_currentRowChanged(int currentRow);
    void on_evenement_spinBox_valueChanged(int arg1);
    void on_evenement_script_listWidget_currentRowChanged(int currentRow);
    void on_evenement_script_spinBox_valueChanged(int arg1);
    void on_evenement_nombre_spinBox_valueChanged(int arg1);
    void on_evenement_image_lineEdit_textEdited(const QString &arg1);

    //Groupes monstres
    GroupeMonstres* getGroupeMonstres(int row = -1) const;
    void setGroupeMonstresLabel(GroupeMonstres* groupe_monstres);
    bool getGroupeMonstresNombreBounds(int row) const;
    void on_groupesmonstre_listWidget_currentRowChanged(int currentRow);
    void on_groupesmonstre_spinBox_valueChanged(int arg1);
    void on_groupesmonstre_nombre_spinBox_valueChanged(int arg1);
    void on_groupesmonstre_monstre_comboBox_currentIndexChanged(int index);
    void on_groupesmonstre_x_spinBox_valueChanged(int arg1);
    void on_groupesmonstre_y_spinBox_valueChanged(int arg1);
    void on_groupesmonstre_monstre_listWidget_currentRowChanged(int currentRow);
    void on_groupesmonstre_monstre_listWidget_itemDoubleClicked(QListWidgetItem *item);

    //Héros
    Heros* getHeros(int row = -1) const;
    void setHerosLabel(Heros* heros);
    void on_heros_listWidget_currentRowChanged(int currentRow);
    void on_heros_spinBox_valueChanged(int arg1);
    void on_heros_nom_lineEdit_textEdited(const QString &arg1);
    void on_heros_vie_spinBox_valueChanged(int arg1);
    void on_heros_magie_spinBox_valueChanged(int arg1);
    void setHerosAttribut(int val, unsigned char id);
    void on_heros_viem_spinBox_valueChanged(int arg1);
    void on_heros_atp_spinBox_valueChanged(int arg1);
    void on_heros_dep_spinBox_valueChanged(int arg1);
    void on_heros_magiem_spinBox_valueChanged(int arg1);
    void on_heros_atm_spinBox_valueChanged(int arg1);
    void on_heros_dem_spinBox_valueChanged(int arg1);
    void on_heros_vit_spinBox_valueChanged(int arg1);
    void on_heros_pre_spinBox_valueChanged(int arg1);
    void on_heros_esq_spinBox_valueChanged(int arg1);
    void on_heros_status_comboBox_currentIndexChanged(int index);
    void on_heros_exp_spinBox_valueChanged(int arg1);
    void on_heros_niv_spinBox_valueChanged(int arg1);
    void setHerosEquipement(int val, unsigned char id);
//    void update_heros_comboBox(QComboBox* comboBox, const Objet* objet);
//    void update_heros_maindroite_comboBox(const Objet* objet);
    void on_heros_maindroite_comboBox_currentIndexChanged(int index);
//    void update_heros_maingauche_comboBox(const Objet* objet);
    void on_heros_maingauche_comboBox_currentIndexChanged(int index);
//    void update_heros_maincasque_comboBox(const Objet* objet);
    void on_heros_casque_comboBox_currentIndexChanged(int index);
//    void update_heros_mainarmure_comboBox(const Objet* objet);
    void on_heros_armure_comboBox_currentIndexChanged(int index);
//    void update_heros_accessoire1_comboBox(const Objet* objet);
    void on_heros_accessoire1_comboBox_currentIndexChanged(int index);
//    void update_heros_accessoire2_comboBox(const Objet* objet);
    void on_heros_accessoire2_comboBox_currentIndexChanged(int index);

    //Magasin
    Magasin* getMagasin(int row = -1) const;
    void setMagasinLabel(Magasin* magasin);
    bool getMagasinNombreBounds(int row) const;
    void on_magasin_listWidget_currentRowChanged(int currentRow);
    void on_magasin_spinBox_valueChanged(int arg1);
    void on_magasin_nombre_spinBox_valueChanged(int arg1);
    void update_magasin_objet_comboBox(unsigned int nombre);
    void on_magasin_objet_comboBox_currentIndexChanged(int index);
    void update_magasin_objet_listWidget(const Objet* objet);
    void on_magasin_objet_listWidget_currentRowChanged(int currentRow);
    void on_magasin_objet_listWidget_itemDoubleClicked(QListWidgetItem *item);

    //Monstre
    Monstre* getMonstre(int row = -1) const;
    void setMonstreLabel(Monstre* monstre);
    void on_monstre_listWidget_currentRowChanged(int currentRow);
    void on_monstre_spinBox_valueChanged(int arg1);
    void on_monstre_nom_lineEdit_textEdited(const QString &arg1);
    void on_monstre_vie_spinBox_valueChanged(int arg1);
    void on_monstre_magie_spinBox_valueChanged(int arg1);
    void on_monstre_script_spinBox_valueChanged(int arg1);
    void setMonstreAttribut(int val, unsigned char id);
    void on_monstre_viem_spinBox_valueChanged(int arg1);
    void on_monstre_atp_spinBox_valueChanged(int arg1);
    void on_monstre_dep_spinBox_valueChanged(int arg1);
    void on_monstre_magiem_spinBox_valueChanged(int arg1);
    void on_monstre_atm_spinBox_valueChanged(int arg1);
    void on_monstre_dem_spinBox_valueChanged(int arg1);
    void on_monstre_vit_spinBox_valueChanged(int arg1);
    void on_monstre_pre_spinBox_valueChanged(int arg1);
    void on_monstre_esq_spinBox_valueChanged(int arg1);
    void on_monstre_status_comboBox_currentIndexChanged(int index);
    void on_monstre_exp_spinBox_valueChanged(int arg1);
    void on_monstre_niv_spinBox_valueChanged(int arg1);
    void on_monstre_butin_comboBox_currentIndexChanged(int index);
    void on_monstre_objet_comboBox_currentIndexChanged(int index);
    void on_monstre_or_spinBox_valueChanged(int arg1);
    void on_monstre_element_atk_spinBox_valueChanged(int arg1);
    void on_monstre_element_def_spinBox_valueChanged(int arg1);

    //Objet
    Objet* getObjet(int row = -1) const;
    void setObjetLabel(Objet* objet);
    Utilisable* getUtilisable(int row = -1) const;
    Equipable* getEquipable(int row = -1) const;
    void on_objet_listWidget_currentRowChanged(int currentRow);
    void on_objet_spinBox_valueChanged(int arg1);
    void on_objet_nom_lineEdit_textEdited(const QString &arg1);
    void on_objet_description_lineEdit_textEdited(const QString &arg1);
    void on_objet_type_comboBox_currentIndexChanged(int index);
        //Utilisable
    void on_objet_illimite_checkBox_clicked(bool checked);
    void on_objet_effet_spinBox_valueChanged(int arg1);
        //Equipable
    void setEquipableAttribut(int val, unsigned char id);
    void on_objet_vie_spinBox_valueChanged(int arg1);
    void on_objet_atp_spinBox_valueChanged(int arg1);
    void on_objet_dep_spinBox_valueChanged(int arg1);
    void on_objet_mag_spinBox_valueChanged(int arg1);
    void on_objet_atm_spinBox_valueChanged(int arg1);
    void on_objet_dem_spinBox_valueChanged(int arg1);
    void on_objet_vit_spinBox_valueChanged(int arg1);
    void on_objet_pre_spinBox_valueChanged(int arg1);
    void on_objet_esq_spinBox_valueChanged(int arg1);
    void on_objet_pds_spinBox_valueChanged(int arg1);
    void on_objet_off_spinBox_valueChanged(int arg1);
    void on_objet_element_spinBox_valueChanged(int arg1);
    void on_objet_prix_spinBox_valueChanged(int arg1);

    //Tileset
    Tileset* getTileset(int row = -1) const;
    void setTilesetLabel(Tileset* tileset);
    bool getTilesetNombreBounds(int row) const;
    void on_tileset_listWidget_currentRowChanged(int currentRow);
    void on_tileset_spinBox_valueChanged(int arg1);
    void on_tileset_tile_lineEdit_textEdited(const QString &arg1);
    void on_tileset_traversable_checkBox_clicked(bool checked);
    void on_tileset_tile_listWidget_currentRowChanged(int currentRow);
    void on_tileset_nombre_spinBox_valueChanged(int arg1);
    //SUITE

private:
    Ui::MainWindow *ui;
    QString workFolder;
    QGraphicsScene *scene;
};

#endif // MAINWINDOW_H
