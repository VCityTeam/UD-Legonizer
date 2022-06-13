## Gratte-ciel project

### Data used :
Nous avons utilisé les données disponibles sur le site OpenDataGrandLyon pour produire la maquette Lego du quartier Gratte-ciel (Lyon)
[Villeurbanne 2018 CityGML](https://data.grandlyon.com/jeux-de-donnees/maquettes-3d-texturees-2018-communes-metropole-lyon/donnees)

### Step to construct Lego model
#### Parsing data
* Dans un premier temps récupérer les données CityGML de votre ville qui vont vous permettre de la transformer en Lego par la suite. Dans ce use-case nous avons utilisé les données cityGML de Vulleurbanne disponible en opensource sur [DataGrandLyon](https://data.grandlyon.com/jeux-de-donnees/maquettes-3d-texturees-2018-communes-metropole-lyon/donnees). 
* Lancez le projet github [Unity CityGML Parser](https://github.com/VCityTeam/UD-CityGMLParser):
  * Le projet comprend un script C# qui va vous permettre de prendre en entrée des données CityGML et de les visualiser en 3D dans une scène 3D Unity. Grâce à cette visualisation vous allez pouvoir vérifier que la modélisation correspond bien à vos attentes pour la construction de la maquette et elle va vous servir pour la transformation en Lego. 
  * Créez un [GameObject Unity](https://docs.unity3d.com/ScriptReference/GameObject.html) dans une nouvelle scène 3D. Sur ce Gameobject ajoutez le composent script _CreateCity.cs_ qui est le script pour construise le modèle 3D de votre Ville.
  ![image](https://user-images.githubusercontent.com/32339907/173315079-34de94ba-85e3-47d7-93d8-fb77460096d0.png)
  * Dans le script, indiquez le chemin de votre CityGML à parser et vous n'avez plus qu'à appuyer sur le bouton _Build City GML_ pour construire votre ville numérique qui vous donnera un apercu dans la scène Unity la modélisation 3D de votre donnée CityGML.

![image](https://user-images.githubusercontent.com/32339907/173318229-263a0b37-c5a7-4e34-bd13-994c97094800.png)


#### Legonize 3D model
* Une fois le model 3D intégré dans la scène Unity:
  * récupérer l'algorithme de [Legonizer](https://github.com/VCityTeam/UD-Legonizer/tree/master/Unity) pour l'intégrer dans la scène. Le projet github est composé de 2 algorithme :  Le Lego analyzer qui va transformer votre modelisation 3D Unity en grille CSV Lego et Le voxel generator qui va vous permettre de pré-visualizer si les fichiers CSV sont bien conforme en vous donnant une modélisation numérique de ce que va être la ville en Lego.
  * Configurez le legonizer pour qu'il corresponde à la maquette lego que vous voulez générer :
    * Nombre de tuiles
    * Taille de la tuille
    * Positionnement sur le model 3D de la ville
    * Hauteur reducteur car le lego n'est pas un cube parfait et peux accentuer les hauteurs de bâtiments
  * Le legonizer va vous produire les fichiers CSV par tuile de Lego et découper votre maquette en matrice que vous avez configuré. Le noms des CSV correspond à la position ou va se trouver votre tuile dans votre maquette Lego. 


![image](https://user-images.githubusercontent.com/32339907/173313306-bf00ff12-fe7d-4f93-a23c-bb4d513bf4ea.png)
