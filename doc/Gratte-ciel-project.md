## Gratte-ciel project

### Data used :
We used the data available on the OpenDataGrandLyon website to produce the Lego model of the Gratte-ciel district (Lyon)
[Villeurbanne 2018 CityGML](https://data.grandlyon.com/jeux-de-donnees/maquettes-3d-texturees-2018-communes-metropole-lyon/donnees)

### Step to construct Lego model
#### Parsing data
* First, get the CityGML data of your city which will allow you to transform it into Lego later. In this use-case we have used the Villeurbanne cityGML data available in opensource on [DataGrandLyon](https://data.grandlyon.com/jeux-de-donnees/maquettes-3d-texturees-2018-communes-metropole-lyon/donnees). 
* Launch the github project [Unity CityGML Parser](https://github.com/VCityTeam/UD-CityGMLParser):
  * The project includes a C# script that will allow you to take CityGML data as input and visualize it in 3D in a Unity scene. Thanks to this visualization you will be able to check that the modeling corresponds to your expectations for the construction of the model and it will be useful for the transformation in Lego. 
  * Create an [Unity GameObject](https://docs.unity3d.com/ScriptReference/GameObject.html) in a new 3D scene. On this Gameobject add the component script _CreateCity.cs_ which is the script to build the 3D model of your City.
  ![image](https://user-images.githubusercontent.com/32339907/173315079-34de94ba-85e3-47d7-93d8-fb77460096d0.png)
  * In the script, indicate the path of your CityGML to be parsed and you just have to press the _Build City GML_ button to build your digital city which will give you a preview in the Unity scene of the 3D modeling of your CityGML data.
  
![image](https://user-images.githubusercontent.com/32339907/173318229-263a0b37-c5a7-4e34-bd13-994c97094800.png)


#### Legonize 3D model
Once the 3D model is integrated into the Unity scene:
  * Get the algorithm [Legonizer](https://github.com/VCityTeam/UD-Legonizer/tree/master/Unity) for integrate it in the scene. The github project is composed of 2 algorithms: The Lego analyzer which will transform your 3D Unity modelisation into a Lego CSV grid and the voxel generator which will allow you to pre-visualise if the CSV files are well conformed by giving you a numerical model of what the Lego city will be.
  * Configure the legonizer to match the lego model you want to generate:
    * Tiles number (x and y parameters)
    * TSize of the lego tile
    * Positioning on the 3D model of the city
    * Reducing height as lego is not a perfect cube and can accentuate building heights
    
![image](https://user-images.githubusercontent.com/32339907/173321453-045492aa-9acc-4f1e-84ca-8ed2f8806662.png)

  * The legonizer will produce CSV files for each Lego tile and cut your model into the matrix you have configured. The name of the CSV file corresponds to the position of your tile in your Lego model.  


![image](https://user-images.githubusercontent.com/32339907/173313306-bf00ff12-fe7d-4f93-a23c-bb4d513bf4ea.png)
The CSV files of the Gratte-ciel district (Lyon) are available [here](https://github.com/VCityTeam/UD-Legonizer/tree/master/doc/csv-files/Gratte-Ciel) and were generated for a Lego model of 6x4 lego tiles which is equivalent to a table of 150x100 cm.  
