# InterDigital - Thèse de doctorat

Sujet : *Détection de changements géométriques et mise à jour de modèle pour les applications de réalité mixte*

## ObjectRemovalDetection

Première approche au sujet de la thèse : détecter les changements dans une scène à partir des informations visuelles dans des images actuelles de la scène, comparées à un maillage 3D antérieur.

Cette méthode redessine les images en simulant des modifications du point de vue de la caméra, à l'aide de la géométrie du maillage. S'il y a eu des changements, le maillage et les images diffèrent en contenu, et des erreurs visuelles apparaissent dans ces images redessinées, rendant détectables les-dits changements.

## GraphBasedSceneRegistration

Incorporation de l'analyse sémantique à l'étude de la scène (au-delà de la géométrie et des textures) : construire une représentation sémantique de la scène sous forme d'un graphe organisant les différents objets qui s'y trouvent.

Cette méthode aligne deux graphes, générés à partir de deux vidéos d'une même scène, sur la base de leur topologie. Une fois que des objets dans une vidéo (ou nœuds du graphe correspondant) sont appairés à des objets identiques dans l'autre vidéo, leurs coordonnées spatiales permettent d'estimer les positions relatives de la caméra entre les deux vidéos.
